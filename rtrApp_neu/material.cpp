#include "material.h"

void PhongMaterial::apply()
{
    prog_->bind();
    prog_->setUniformValue("material.k_ambient", k_ambient);
    prog_->setUniformValue("material.k_diffuse", k_diffuse);
    prog_->setUniformValue("material.k_specular", k_specular);
    prog_->setUniformValue("material.shininess", shininess);
    prog_->setUniformValue("ambientLightIntensity", ambientLightIntensity);
    prog_->setUniformValue("light.position_EC", lightPos_EC);
    prog_->setUniformValue("light.intensity", lightIntensity);
}

void ToonMaterial::apply()
{
    prog_->bind();
    prog_->setUniformValue("material.k_ambient", k_ambient);
    prog_->setUniformValue("material.k_diffuse", k_diffuse);
    prog_->setUniformValue("material.k_specular", k_specular);
    prog_->setUniformValue("material.shininess", shininess);
    prog_->setUniformValue("ambientLightIntensity", ambientLightIntensity);
    prog_->setUniformValue("light.position_EC", lightPos_EC);
    prog_->setUniformValue("light.intensity", lightIntensity);
    prog_->setUniformValue("bands", bands);
    prog_->setUniformValue("specularBias", specularBias);
}


void ProcMaterial::apply()
{
    prog_->bind();
    prog_->setUniformValue("material.k_ambient", k_ambient);
    prog_->setUniformValue("material.k_diffuse", k_diffuse);
    prog_->setUniformValue("material.k_specular", k_specular);
    prog_->setUniformValue("material.shininess", shininess);
    prog_->setUniformValue("ambientLightIntensity", ambientLightIntensity);
    prog_->setUniformValue("light.position_EC", lightPos_EC);
    prog_->setUniformValue("light.intensity", lightIntensity);
    prog_->setUniformValue("myUniformColor", myUniformColor);
    prog_->setUniformValue("time", time);
}

void DotsMaterial::apply()
{
    prog_->bind();
    prog_->setUniformValue("material.k_ambient", k_ambient);
    prog_->setUniformValue("material.k_diffuse", k_diffuse);
    prog_->setUniformValue("material.k_specular", k_specular);
    prog_->setUniformValue("material.shininess", shininess);
    prog_->setUniformValue("ambientLightIntensity", ambientLightIntensity);
    prog_->setUniformValue("light.position_EC", lightPos_EC);
    prog_->setUniformValue("light.intensity", lightIntensity);
    prog_->setUniformValue("bands", bands);
    prog_->setUniformValue("specularBias", specularBias);

    prog_->setUniformValue("dotColor", dotColor);
    prog_->setUniformValue("density", density);
    prog_->setUniformValue("radius", radius);

    // Canvas size! Set in updateViewport in scene.cpp
    prog_->setUniformValue("u_resolution", uResolution);
}
