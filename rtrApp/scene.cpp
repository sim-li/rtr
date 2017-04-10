
#include "scene.h"

#include <iostream> // std::cout etc.
using namespace std;

Scene::Scene(QWidget* parent, QOpenGLContext *context) :
    QOpenGLFunctions(context),
    parent_(parent),
    currentMesh_(nullptr)
{

    // create shader program to be used for rendering
    program_ = new QOpenGLShaderProgram();
    if(!program_->addShaderFromSourceFile(QOpenGLShader::Vertex,
                                    ":/assets/shaders/toon.vert"))
        qFatal("could not add vertex shader");
    if(!program_->addShaderFromSourceFile(QOpenGLShader::Fragment,
                                    ":/assets/shaders/toon.frag"))
        qFatal("coudl not add fragment shader");

    if(!program_->link())
        qFatal("could not link shader program");

    // Material: use default Phong material
    //material_ = std::make_shared<ToonMaterial>();
    material_ = std::make_shared<PhongMaterial>();
    material_->setUniforms(*program_);

    // load meshes from .obj files and assign shader programs to them
    meshes_["Duck"] = std::make_shared<Mesh>(":/assets/models/duck/duck.obj", program_);
    meshes_["Trefoil"] = std::make_shared<Mesh>(":/assets/models/trefoil.obj", program_);

    // make the duck the current model
    changeModel("Duck");

    // create default camera (0,0,4) -> (0,0,0), 45°
    float aspect = float(parent->width())/float(parent->height());
    camera_ = std::make_shared<Camera>(
                QVector3D(0,0.3,3), // look from
                QVector3D(0,0,0), // look to
                QVector3D(0,1,0), // this way is up
                30.0,   // field of view in up direction
                aspect, // aspect ratio
                0.01,   // near plane
                10.0    // far plane
                );

}

Scene::~Scene()
{
    delete program_;
}

void Scene::changeModel(const QString &txt)
{
    currentMesh_ = meshes_[txt];

    // reset transform, create scaling so scene is within (-0.5 : 0.5)
    float r = currentMesh_->bbox().maxExtent();
    worldTransform_ = QMatrix4x4();
    worldTransform_.scale(QVector3D(1.0/r,1.0/r,1.0/r));
    update();

}

void Scene::draw()
{

    // clear background
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // set up transformation matrices
    camera_->setMatrices(*program_, worldTransform_);

    // draw our only object
    if(currentMesh_)
        currentMesh_->draw();

}

void Scene::updateViewport(size_t width, size_t height)
{
    camera_->setAspectRatio(float(width)/float(height));
    glViewport(0,0,width,height);
}
