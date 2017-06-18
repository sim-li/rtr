#include "flymover.h"

using namespace glm;

FlySimpleWasd::FlySimpleWasd(const std::string& name, Node::Ptr node, vec3 position, mat4 orientation) :
    Mover(name, node), position(position), orientation(orientation), aSpeed(90.0f), vSpeed(0.0f) {
}

void FlySimpleWasd::simulate(AppRunner& runner) {
    if (runner.input.isPressed(GLFW_KEY_UP)) {
        orientation *= rotate(glm::radians(aSpeed) * runner.elapsed, vec3(1, 0, 0));
    }
    if (runner.input.isPressed(GLFW_KEY_DOWN)) {
        orientation *= rotate(glm::radians(-aSpeed) * runner.elapsed, vec3(1, 0, 0));
    }
    if (runner.input.isPressed(GLFW_KEY_LEFT)) {
        orientation = rotate(glm::radians(aSpeed) * runner.elapsed, vec3(0, 1, 0)) * orientation;
    }
    if (runner.input.isPressed(GLFW_KEY_RIGHT)) {
        orientation = rotate(glm::radians(-aSpeed) * runner.elapsed, vec3(0, 1, 0)) * orientation;
    }

    vec3 moveDir(orientation * vec4(0, 0, 1, 0));
    vec3 strafeDir(orientation * vec4(1, 0, 0, 0));

    if (runner.input.isPressed(GLFW_KEY_D)) {
        position += strafeDir * vSpeed * runner.elapsed;
    }
    if (runner.input.isPressed(GLFW_KEY_A)) {
        position -= strafeDir * vSpeed * runner.elapsed;
    }
    if (runner.input.isPressed(GLFW_KEY_W)) {
        vSpeed += 0.01f;
//        position -= moveDir * vSpeed * runner.elapsed;
    }
    if (runner.input.isPressed(GLFW_KEY_S)) {
        vSpeed -= 0.01f;
//        position += moveDir * vSpeed * runner.elapsed;
    }
    if (runner.input.isPressed(GLFW_KEY_Q)) {
        position -= vec3(0, 1, 0) * vSpeed * runner.elapsed;
    }
    if (runner.input.isPressed(GLFW_KEY_E)) {
        position += vec3(0, 1, 0) * vSpeed * runner.elapsed;
    }

    if (vSpeed != 0.0) {
        position -= moveDir * vSpeed * runner.elapsed;
    }

    node->transform = translate(position) * orientation;
}

FlySimpleWasd::Ptr FlySimpleWasd::make(const std::string& name, Node::Ptr node, glm::vec3 position, glm::mat4 orientation) {
    return std::make_shared<FlySimpleWasd>(name, node, position, orientation);
}



FlyRandom::FlyRandom(const std::string& name, Node::Ptr node, vec3 position, mat4 orientation) :
    tr(0),
    ro(0),
    interval(rand() % 15 + 12),
    intervalTwo(rand() % 15 + 12),
    Mover(name, node), position(position), orientation(orientation), aSpeed(90.0f), vSpeed(1.0f) {
}

void FlyRandom::simulate(AppRunner& runner) {
    if (ro == 1) {
        orientation *= rotate(glm::radians(aSpeed) * runner.elapsed, vec3(1, 0, 0));
    }
    if (ro == 2) {
        orientation *= rotate(glm::radians(-aSpeed) * runner.elapsed, vec3(1, 0, 0));
    }
    if (ro == 3) {
        orientation = rotate(glm::radians(aSpeed) * runner.elapsed, vec3(0, 1, 0)) * orientation;
    }
    if (ro == 4) {
        orientation = rotate(glm::radians(-aSpeed) * runner.elapsed, vec3(0, 1, 0)) * orientation;
    }

    vec3 moveDir(orientation * vec4(0, 0, 1, 0));
    vec3 strafeDir(orientation * vec4(1, 0, 0, 0));

    if (tr == 1) {
        position += strafeDir * vSpeed * runner.elapsed;
    }
    if (tr == 2) {
        position -= strafeDir * vSpeed * runner.elapsed;
    }
    if (tr == 3) {
        vSpeed += 0.1f;
//        position -= moveDir * vSpeed * runner.elapsed;
    }
    if (tr == 4) {
        vSpeed -= 0.1f;
//        position += moveDir * vSpeed * runner.elapsed;
    }
    if (tr == 5) {
        position += vec3(0, 1, 0) * vSpeed * runner.elapsed;
    }
    if (tr == 6) {
        position -= vec3(0, 1, 0) * vSpeed * runner.elapsed;
    }

    if (vSpeed != 0.0) {
        position -= moveDir * vSpeed * runner.elapsed;
    }

    node->transform = translate(position) * orientation;
}

FlyRandom::Ptr FlyRandom::make(const std::string& name, Node::Ptr node, glm::vec3 position, glm::mat4 orientation) {
    return std::make_shared<FlyRandom>(name, node, position, orientation);
}
