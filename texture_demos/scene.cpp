#include "scene.h"

#include <iostream> // std::cout etc.
#include <assert.h> // assert()
#include <random>   // random number generation

#include "geometries/cube.h" // geom::Cube
#include "geometries/parametric.h" // geom::Sphere etc.

using namespace std;

Scene::Scene(QWidget* parent, QOpenGLContext *context) :
    QOpenGLFunctions(context),
    parent_(parent),
    timer_(),
    firstDrawTime_(clock_.now()),
    lastDrawTime_(clock_.now()),
    currentNode_(nullptr)
{

    // check some OpenGL parameters
    {
        int minor, major;
        glGetIntegerv(GL_MINOR_VERSION, &minor);
        glGetIntegerv(GL_MAJOR_VERSION, &major);
        cout << "OpenGL context version " << major << "." << minor << endl;

        int texunits_frag, texunits_vert;
        glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &texunits_frag);
        glGetIntegerv(GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS, &texunits_vert);
        cout << "texture units: " << texunits_frag << " (frag), "
             << texunits_vert << " (vert)" << endl;

        int texsize;
        glGetIntegerv(GL_MAX_TEXTURE_SIZE, &texsize);
        cout << "max texture size: " << texsize << "x" << texsize << endl;
    }

    // load shader source files and compile them into OpenGL program objects
    auto planet_prog = createProgram(":/assets/shaders/planet_with_bumps.vert", ":/assets/shaders/planet_with_bumps.frag");
    planetMaterial_ = std::make_shared<PlanetMaterial>(planet_prog);
    planetMaterial_->light.position_EC = QVector3D(4,0,2);
    planetMaterial_->phong.shininess = 10;

    // program (with additional geometry shader) to visualize wireframe
    auto wire_prog = createProgram(":/assets/shaders/wireframe.vert",
                                   ":/assets/shaders/wireframe.frag",
                                   ":/assets/shaders/wireframe.geom");
    wireframeMaterial_ = std::make_shared<WireframeMaterial>(wire_prog);

    // program (with additional geometry shader) to visualize normal/tangent vectors
    auto vectors_prog = createProgram(":/assets/shaders/vectors.vert",
                                      ":/assets/shaders/vectors.frag",
                                      ":/assets/shaders/vectors.geom");
    vectorsMaterial_ = std::make_shared<VectorsMaterial>(vectors_prog);
    vectorsMaterial_->vectorToShow  = 0;

    // load textures
    auto day    = std::make_shared<QOpenGLTexture>(QImage(":/assets/textures/earth_day.jpg").mirrored());
    auto night  = std::make_shared<QOpenGLTexture>(QImage(":/assets/textures/earth_at_night_2048.jpg").mirrored());
    auto gloss  = std::make_shared<QOpenGLTexture>(QImage(":/assets/textures/earth_bathymetry_2048.jpg").mirrored());
    auto clouds = std::make_shared<QOpenGLTexture>(QImage(":/assets/textures/earth_clouds_2048.jpg").mirrored());
    auto disp   = std::make_shared<QOpenGLTexture>(QImage(":/assets/textures/earth_topography_2048.jpg").mirrored());
    auto bumps  = std::make_shared<QOpenGLTexture>(QImage(":/assets/textures/earth_topography_2048_NRM.png").mirrored());

    // tex parameters
    clouds->setWrapMode(QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat);
    clouds->setWrapMode(QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat);

    // assign textures to material
    planetMaterial_->planet.dayTexture = day;
    planetMaterial_->planet.nightTexture = night;
    planetMaterial_->planet.glossTexture = gloss;
    planetMaterial_->planet.cloudsTexture = clouds;
    planetMaterial_->bump.tex = bumps;
    planetMaterial_->displacement.tex = disp;

    // load meshes from .obj files and assign shader programs to them
    auto std = planetMaterial_;
    meshes_["Duck"]    = std::make_shared<Mesh>(":/assets/models/duck/duck.obj", std);

    // add meshes of some procedural geometry objects (not loaded from OBJ files)
    meshes_["Cube"]   = std::make_shared<Mesh>(make_shared<geom::Cube>(), std);
    meshes_["Sphere"] = std::make_shared<Mesh>(make_shared<geom::Planet>(80,80), std);
    meshes_["Torus"]  = std::make_shared<Mesh>(make_shared<geom::Torus>(4, 2, 80,20), std);
    meshes_["Rect"]   = std::make_shared<Mesh>(make_shared<geom::Rect>(20,20), std);

    // pack each mesh into a scene node, along with a transform that scales
    // it to standard size [1,1,1]
    nodes_["Sphere"]  = createNode(meshes_["Sphere"], true);
    nodes_["Torus"]   = createNode(meshes_["Torus"], true);
    nodes_["Rect"]    = createNode(meshes_["Rect"], true);
    nodes_["Cube"]    = createNode(meshes_["Cube"], true);
    nodes_["Duck"]    = createNode(meshes_["Duck"], true);

    // rotate some models
    nodes_["Sphere"]->transformation.rotate(-90, QVector3D(1,0,0));
    nodes_["Torus"]->transformation.rotate(-60, QVector3D(1,0,0));
    nodes_["Rect"]->transformation.rotate(30, QVector3D(1,0,0));

    // current model and shader
    changeModel("Sphere");
    changeShader("Phong");

    // create default camera (0,0,4) -> (0,0,0), 45°
    float aspect = float(parent->width())/float(parent->height());
    camera_ = std::make_shared<Camera>(
                QVector3D(0,0.3f,3), // look from
                QVector3D(0,0,0), // look to
                QVector3D(0,1,0), // this way is up
                30.0,   // field of view in up direction
                aspect, // aspect ratio
                0.01,   // near plane
                10.0    // far plane
                );

    // make sure we redraw when the timer hits
    connect(&timer_, SIGNAL(timeout()), this, SLOT(update()) );

}

// helper to load shaders and create programs
shared_ptr<QOpenGLShaderProgram>
Scene::createProgram(const string& vertex, const string& fragment, const string& geom)
{
    auto p = make_shared<QOpenGLShaderProgram>();
    if(!p->addShaderFromSourceFile(QOpenGLShader::Vertex, vertex.c_str()))
        qFatal("could not add vertex shader");
    if(!p->addShaderFromSourceFile(QOpenGLShader::Fragment, fragment.c_str()))
        qFatal("could not add fragment shader");
    if(!geom.empty()) {
        if(!p->addShaderFromSourceFile(QOpenGLShader::Geometry, geom.c_str()))
            qFatal("could not add geometryshader");
    }
    if(!p->link())
        qFatal("could not link shader program");

    return p;
}

// helper to make a node from a mesh, and
// scale the mesh to standard size 1 of desired
shared_ptr<Node>
Scene::createNode(shared_ptr<Mesh> mesh,
                  bool scale_to_1)
{
    float r = mesh->geometry()->bbox().maxExtent();
    QMatrix4x4 transform;
    if(scale_to_1)
        transform.scale(QVector3D(1.0/r,1.0/r,1.0/r));

    return make_shared<Node>(mesh,transform);
}


void Scene::changeModel(const QString &txt)
{
    currentNode_ = nodes_[txt];
    if(!currentNode_)
        qFatal("scene: desired mesh/node not found");

    update();

}

void Scene::changeShader(const QString &txt)
{
    if(txt == "None") {
        material_ = nullptr;
    }
    else if(txt == "Phong") {
        material_ = planetMaterial_;
        planetMaterial_->phong.debug_texcoords = false;
        planetMaterial_->planet.debugWaterLand = false;
        planetMaterial_->planet.useDayTexture = false;
        planetMaterial_->planet.useNightTexture = false;
        planetMaterial_->planet.useGlossTexture = false;
        planetMaterial_->planet.useCloudsTexture = false;
    }
    else if(txt == "Debug Tex Coords") {
        material_ = planetMaterial_;
        planetMaterial_->phong.debug_texcoords = true;
        planetMaterial_->planet.debugWaterLand = false;
        planetMaterial_->planet.useDayTexture = false;
        planetMaterial_->planet.useNightTexture = false;
        planetMaterial_->planet.useGlossTexture = false;
        planetMaterial_->planet.useCloudsTexture = false;
    }
    else if(txt == "Debug Day/Night") {
        material_ = planetMaterial_;
        planetMaterial_->phong.debug_texcoords = false;
        planetMaterial_->planet.debug = true;
        planetMaterial_->planet.debugWaterLand = false;
        planetMaterial_->planet.useDayTexture = false;
        planetMaterial_->planet.useNightTexture = false;
        planetMaterial_->planet.useGlossTexture = false;
        planetMaterial_->planet.useCloudsTexture = false;
    }
    else if(txt == "Day Texture") {
        material_ = planetMaterial_;
        planetMaterial_->phong.debug_texcoords = false;
        planetMaterial_->planet.debug = false;
        planetMaterial_->planet.debugWaterLand = false;
        planetMaterial_->planet.useDayTexture = true;
        planetMaterial_->planet.useNightTexture = false;
        planetMaterial_->planet.useGlossTexture = false;
        planetMaterial_->planet.useCloudsTexture = false;
    }
    else if(txt == "Night Texture") {
        material_ = planetMaterial_;
        planetMaterial_->phong.debug_texcoords = false;
        planetMaterial_->planet.debug = false;
        planetMaterial_->planet.debugWaterLand = false;
        planetMaterial_->planet.useDayTexture = false;
        planetMaterial_->planet.useNightTexture = true;
        planetMaterial_->planet.useGlossTexture = false;
        planetMaterial_->planet.useCloudsTexture = false;
    }
    else if(txt == "Day+Night Texture") {
        material_ = planetMaterial_;
        planetMaterial_->phong.debug_texcoords = false;
        planetMaterial_->planet.debug = false;
        planetMaterial_->planet.debugWaterLand = false;
        planetMaterial_->planet.useDayTexture = true;
        planetMaterial_->planet.useNightTexture = true;
        planetMaterial_->planet.useGlossTexture = false;
        planetMaterial_->planet.useCloudsTexture = false;
    }
    else if(txt == "Debug Gloss") {
        material_ = planetMaterial_;
        planetMaterial_->phong.debug_texcoords = false;
        planetMaterial_->planet.debug = false;
        planetMaterial_->planet.debugWaterLand = true;
        planetMaterial_->planet.useDayTexture = false;
        planetMaterial_->planet.useNightTexture = false;
        planetMaterial_->planet.useGlossTexture = true;
        planetMaterial_->planet.useCloudsTexture = false;
    }
    else if(txt == "Phong+Gloss") {
        material_ = planetMaterial_;
        planetMaterial_->phong.debug_texcoords = false;
        planetMaterial_->planet.debug = false;
        planetMaterial_->planet.debugWaterLand = false;
        planetMaterial_->planet.useDayTexture = false;
        planetMaterial_->planet.useNightTexture = false;
        planetMaterial_->planet.useGlossTexture = true;
        planetMaterial_->planet.useCloudsTexture = false;
    }
    else if(txt == "Day+Night+Gloss") {
        material_ = planetMaterial_;
        planetMaterial_->phong.debug_texcoords = false;
        planetMaterial_->planet.debug = false;
        planetMaterial_->planet.debugWaterLand = false;
        planetMaterial_->planet.useDayTexture = true;
        planetMaterial_->planet.useNightTexture = true;
        planetMaterial_->planet.useGlossTexture = true;
        planetMaterial_->planet.useCloudsTexture = false;
    }
    else if(txt == "+Clouds") {
        material_ = planetMaterial_;
        planetMaterial_->phong.debug_texcoords = false;
        planetMaterial_->planet.debug = false;
        planetMaterial_->planet.debugWaterLand = false;
        planetMaterial_->planet.useDayTexture = true;
        planetMaterial_->planet.useNightTexture = true;
        planetMaterial_->planet.useGlossTexture = true;
        planetMaterial_->planet.useCloudsTexture = true;
    }

    update();
}


void Scene::toggleAnimation(bool flag)
{
    if(flag) {
        timer_.start(1000.0 / 60.0); // update *roughly* every 60 ms
    } else {
        timer_.stop();
    }
    planetMaterial_->planet.animateClouds = flag;
}

void Scene::draw()
{
    assert(currentNode_);
    assert(camera_);

    // calculate animation time
    chrono::milliseconds millisec_since_first_draw;

    if(timer_.isActive()) {
        // calculate total elapsed time and time since last draw call
        auto current = clock_.now();
        millisec_since_first_draw = chrono::duration_cast<chrono::milliseconds>(current - firstDrawTime_);
        lastDrawTime_ = current;
    } else {
        millisec_since_first_draw = chrono::duration_cast<chrono::milliseconds>(lastDrawTime_ - firstDrawTime_);
    }

    // set time uniform in animated shader(s)
    float t = millisec_since_first_draw.count() / 1000.0f;
    planetMaterial_->time = t;

    // clear background, set OpenGL state
    glClearColor(bgcolor_[0], bgcolor_[1], bgcolor_[2], 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // draw using currently selected material, if one is selected at all
    if(material_)
        replaceMaterialAndDrawScene(material_);

    // show wireframe in addition?
    if(showWireframe)
        replaceMaterialAndDrawScene(wireframeMaterial_);

    // show vectors in addition?
    if(vectorsMaterial_->vectorToShow != 0)
        replaceMaterialAndDrawScene(vectorsMaterial_);

}

void Scene::replaceMaterialAndDrawScene(shared_ptr<Material> material)
{
    // replace material in all meshes, if necessary
    if(material != meshes_.begin()->second->material())
        for (auto& element : meshes_) {
            auto mesh = element.second;
            mesh->replaceMaterial(material);
        }

    // draw the actual node
    currentNode_->draw(*camera_, worldTransform_);
}

void Scene::updateViewport(size_t width, size_t height)
{
    qDebug() << "viewport:" << width << "x" << height;
    camera_->setAspectRatio(float(width)/float(height));
    glViewport(0,0,GLint(width),GLint(height));
}

