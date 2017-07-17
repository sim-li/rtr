#ifndef MATERIAL_H
#define MATERIAL_H

#include <QOpenGLShaderProgram>

/*
 *   Interface for material descriptions.
 *
 */
class MaterialDescription
{
public:

    // set all uniforms that are required for a certain type shader / material
    virtual void setUniforms(QOpenGLShaderProgram& prog) = 0;
};

/*
 * Phong illumination model with a single point light and
 * a light in camera coordinates (headlight)
 *
 */
class PhongMaterial : public MaterialDescription {
public:

    // actual properties of the object's materia
    QVector3D k_ambient  = QVector3D(0.50,0.10,0.10); // red-ish
    QVector3D k_diffuse  = QVector3D(0.50,0.10,0.10); // red-ish
    QVector3D k_specular = QVector3D(0.80,0.80,0.80); // white-ish
    float     shininess  = 80; // middle-ish

    // light position: up right from the camera, in eye coordinates
    QVector4D lightPos_EC    = QVector4D(2,2,0,1);
    QVector3D lightIntensity = QVector3D(1,1,1);

    // ambient light
    QVector3D ambientLightIntensity = QVector3D(0.3,0.3,0.3);

    void setUniforms(QOpenGLShaderProgram& prog);
};


class ToonMaterial : public MaterialDescription {
public:

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

   int bands = 3;
   float specularBias = 9.0f;

   void setUniforms(QOpenGLShaderProgram& prog);
};




#endif // MATERIAL_H
