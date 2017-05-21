#include "scene.h"
#include <QTime>
#include <QDateTime>
#include <iostream> // std::cout etc.
#include <assert.h> // assert()
#include "geometries/cube.h" // geom::Cube
#include "appwindow.h"
#include "ui_appwindow.h"
#include "scene.h"

using namespace std;

Scene::Scene(QWidget* parent, QOpenGLContext *context) :
    QOpenGLFunctions(context),
    parent_(parent),
    currentNode_(nullptr)
{
    auto phong_prog = createProgram(":/assets/shaders/myphong.vert", ":/assets/shaders/myphong.frag");
    shared_ptr<PhongMaterial> phongMaterial = std::make_shared<PhongMaterial>(phong_prog);

    auto toon_prog = createProgram(":/assets/shaders/toon.vert", ":/assets/shaders/toon.frag");
    shared_ptr<ToonMaterial> toonMaterial = std::make_shared<ToonMaterial>(toon_prog);

    auto uniform_prog = createProgram(":/assets/shaders/uniform.vert", ":/assets/shaders/uniform.frag");
    shared_ptr<UniformMaterial> uniformMaterial = std::make_shared<UniformMaterial>(uniform_prog);

    auto dots_prog = createProgram(":/assets/shaders/dots.vert", ":/assets/shaders/dots.frag");
    shared_ptr<DotsMaterial> dotsMaterial = std::make_shared<DotsMaterial>(dots_prog);

    auto proc_prog = createProgram(":/assets/shaders/proc.vert", ":/assets/shaders/proc.frag");
    shared_ptr<ProcMaterial> procMaterial = std::make_shared<ProcMaterial>(proc_prog);

    //Store uniform material to enable modification through setNewRandomColor

    uniformMaterialL = uniformMaterial;

    // Workaround while ComboBox not implemented: --> Change Material here.
    shared_ptr<Material> currentMaterial = toonMaterial;

    // store materials in map container
    materials_["Phong"] = phongMaterial;
    materials_["Toon"] = toonMaterial;
    materials_["Uniform"] = uniformMaterial;

    // load meshes from .obj files and assign shader programs to them
    meshes_["Duck"] = std::make_shared<Mesh>(":/assets/models/duck/duck.obj", currentMaterial);
    meshes_["Trefoil"] = std::make_shared<Mesh>(":/assets/models/trefoil.obj", currentMaterial);

    // add meshes of some procedural geometry objects (not loaded from OBJ files)
    meshes_["Cube"] = std::make_shared<Mesh>(make_shared<geom::Cube>(), currentMaterial);

    // pack each mesh into a scene node, along with a transform that scales
    // it to standard size [1,1,1]
    nodes_["Duck"]    = createNode(meshes_["Duck"], true);
    nodes_["Trefoil"] = createNode(meshes_["Trefoil"], true);
    nodes_["Cube"]    = createNode(meshes_["Cube"], true);


    // make the duck the current model
    changeModel("Duck");

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

}

// helper to load shaders and create programs
shared_ptr<QOpenGLShaderProgram>
Scene::createProgram(const string& vertex, const string& fragment)
{
    auto p = make_shared<QOpenGLShaderProgram>();
    if(!p->addShaderFromSourceFile(QOpenGLShader::Vertex, vertex.c_str()))
        qFatal("could not add vertex shader");
    if(!p->addShaderFromSourceFile(QOpenGLShader::Fragment, fragment.c_str()))
        qFatal("could not add fragment shader");
    if(!p->link())
        qFatal("could not link shader program");
    return p;
}

// helper to make a node from a mesh, and
// scale the mesh to standard size 1 of desired
shared_ptr<Node> Scene::createNode(shared_ptr<Mesh> mesh,
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


void Scene::changeMaterial(const QString &txt)
{
    qDebug() << "Change material function called." << txt;
    update();

}


void Scene::setNewRandomColor()
{
    QTime now;
    float wtime = ((float) rand() / (RAND_MAX));
    //qDebug() << "wtime :____", wtime;
    uniformMaterialL->time = wtime;
    update();


    double r = ((double) rand() / (RAND_MAX));
    double g = ((double) rand() / (RAND_MAX));
    double b = ((double) rand() / (RAND_MAX));

    QVector3D color(r, g, b);
    uniformMaterialL->myUniformColor = color;
    update();

}


void Scene::draw()
{

    assert(currentNode_);
    assert(camera_);

    // clear background
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // draw selected node, apply current world transformation
    currentNode_->draw(*camera_, worldTransform_);

    qDebug() << "Draw Call!";

}

void Scene::updateViewport(size_t width, size_t height)
{

    camera_->setAspectRatio(float(width)/float(height));
    //camera_->setAspectRatio(());
    glViewport(0,0,GLint(width),GLint(height));
}

