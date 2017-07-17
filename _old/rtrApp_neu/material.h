#ifndef MATERIAL_H
#define MATERIAL_H

#include <memory> // std::shared_ptr

#include <QOpenGLShaderProgram>
#include <QTime>
#include <QDateTime>
#include <QDebug>
#include <limits>
/*
 *   Interface for surface materials.
 *
 */
class Material
{
public:

    // constructor requires an existing shader program
    Material(std::shared_ptr<QOpenGLShaderProgram> prog)
        :prog_(prog)
    {}

    // bind underlying shader program and set required uniforms
    virtual void apply() = 0;

    // getter for the program object
    QOpenGLShaderProgram& program() const { return *prog_; }

protected:

    // reference to underlying shader program
    std::shared_ptr<QOpenGLShaderProgram> prog_;
};

/*
 * Phong illumination model with a single point light and
 * a light in camera coordinates (headlight)
 *
 */
class PhongMaterial : public Material {
public:

    // constructor requires existing shader program
    PhongMaterial(std::shared_ptr<QOpenGLShaderProgram> prog) : Material(prog) {}

    // actual properties of the object's materia
    QVector3D k_ambient  = QVector3D(0.50f,0.10f,0.10f); // red-ish
    QVector3D k_diffuse  = QVector3D(0.50f,0.10f,0.10f); // red-ish
    QVector3D k_specular = QVector3D(0.80f,0.80f,0.80f); // white-ish
    float     shininess  = 80; // middle-ish

    // light position: up right from the camera, in eye coordinates
    QVector4D lightPos_EC    = QVector4D(2,2,0,1);
    QVector3D lightIntensity = QVector3D(1,1,1);

    // ambient light
    QVector3D ambientLightIntensity = QVector3D(0.3f,0.3f,0.3f);

    // bind underlying shader program and set required uniforms
    void apply() override;
};


class ToonMaterial : public Material {
public:

   ToonMaterial(std::shared_ptr<QOpenGLShaderProgram> prog) : Material(prog) {}

   // actual properties of the object's materia
   QVector3D k_ambient  = QVector3D(0.30, 0.30, 0.01); // red-ish
   QVector3D k_diffuse  = QVector3D(0.30, 0.30, 0.01); // red-ish
   QVector3D k_specular = QVector3D(1.0, 1.0, 1.0); // white-ish
   float     shininess  = 100; // middle-ish


   // light position: up right from the camera, in eye coordinates
   QVector4D lightPos_EC    = QVector4D(0,100,100,0);
   QVector3D lightIntensity = QVector3D(4,4,4);

   // ambient light
   QVector3D ambientLightIntensity = QVector3D(0.5/3, 0.8/3, 1.0/3);

   int bands = 5;
   float specularBias = 90.0f;

   // bind underlying shader program and set required uniforms
   void apply() override;


};

class ProcMaterial : public Material {
public:

    // constructor requires existing shader program
    ProcMaterial(std::shared_ptr<QOpenGLShaderProgram> prog) : Material(prog) {}

    // actual properties of the object's materia
    QVector3D k_ambient  = QVector3D(0.50f,0.10f,0.10f); // red-ish
    QVector3D k_diffuse  = QVector3D(0.50f,0.10f,0.10f); // red-ish
    QVector3D k_specular = QVector3D(0.80f,0.80f,0.80f); // white-ish
    float     shininess  = 80; // middle-ish

    // light position: up right from the camera, in eye coordinates
    QVector4D lightPos_EC    = QVector4D(2,2,0,1);
    QVector3D lightIntensity = QVector3D(1,1,1);

    // ambient light
    QVector3D ambientLightIntensity = QVector3D(0.3f,0.3f,0.3f);

    QVector3D myUniformColor = QVector3D(0.0f, 0.0f, 0.0f);


    float time = std::numeric_limits<float>::max();

    void apply() override;
};

class DotsMaterial : public Material {
public:
    DotsMaterial(std::shared_ptr<QOpenGLShaderProgram> prog) : Material(prog) {}

    // actual properties of the object's materia
    QVector3D k_ambient  = QVector3D(0.30, 0.30, 0.01); // red-ish
    QVector3D k_diffuse  = QVector3D(0.30, 0.30, 0.01); // red-ish
    QVector3D k_specular = QVector3D(1.0, 1.0, 1.0); // white-ish
    float     shininess  = 100; // middle-ish


    // light position: up right from the camera, in eye coordinates
    QVector4D lightPos_EC    = QVector4D(0,100,100,0);
    QVector3D lightIntensity = QVector3D(4,4,4);

    // ambient light
    QVector3D ambientLightIntensity = QVector3D(0.5/3, 0.8/3, 1.0/3);

    QVector3D dotColor = QVector3D(0.0, 0.5, 0.0);

    float density = 10;
    float radius = 0.5;
    int bands = 3;

    float specularBias = 9.0f;

    QVector2D uResolution = QVector2D(300, 300);

    // bind underlying shader program and set required uniforms
    void apply() override;
};

#endif // MATERIAL_H
