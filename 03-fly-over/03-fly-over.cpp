/* Copyright 2013 Henrik Tramberend. All Rights Reserved. Absolutely No Warranty. */

#include <jet/jet.h>
#include "flymover.h"
using namespace jet;
using namespace glm;

class CubeApp : public App {
public:

    CubeApp() :
        textureRepeat(2),
//        rotate(false),
        drawLines(false),
//        coutAfter(10.0f),

        planeSize(40.0f),
        cameraFar(100.0f),
        numSpheres(50)
    {
    }

//    std::vector<Node::Vec> planes;
//    std::vector< Node::Vec > planes(3, Node::Vec(3));
//    std::vector< vector<Node::Ptr> > planes(3, std::vector<Node::Ptr>(3));
    Node::Vec planes;
    std::vector<FlyRandom::Ptr> kiMovers;
    int numSpheres;

    Renderer::Ptr renderer, skyRenderer;

//    bool rotate;
    bool drawLines;
    int textureRepeat;
    float nextBorderXp, nextBorderXn, nextBorderZp, nextBorderZn;
    float planeSize, cameraFar;
    PerspectiveCamera::Ptr cameraNode;
//    float negativeZdist;

    FlySimpleWasd::Ptr wasdMover;
//    FlyRandom::Ptr wasdKiMover_R, wasdKiMover_G, wasdKiMover_B;

    virtual Info info() {
        // Provide app info

        return Info("Fly Over", 800, 600);
    }

    //source: http://stackoverflow.com/questions/5289613/generate-random-float-between-two-floats
    float randomFloat(float a, float b) {
        float random = ((float) rand()) / (float) RAND_MAX;
        float diff = b - a;
        float r = random * diff;
        return a + r;
    }

    virtual void init(AppRunner& runner) {

        nextBorderXp = (planeSize/2.0f);
        nextBorderXn = (planeSize/-2.0f);
        nextBorderZp = (planeSize/2.0f);
        nextBorderZn = (planeSize/-2.0f);

        auto mapFolder = sourceDir() / "maps";

        //textures
        auto terrainNZ = ImageTexture::make(mapFolder / "rocks_NZ.png");
        auto terrainRocks = ImageTexture::make(mapFolder / "rocks_texture.png");
        auto terrainWater = ImageTexture::make(mapFolder / "water_texture.png");
        auto terrainGrass = ImageTexture::make(mapFolder / "grass_texture.png");
        auto terrainSand = ImageTexture::make(mapFolder / "sand_texture.png");

        auto skyTexture = CubeTexture::make({
             mapFolder / "posx.png", mapFolder / "negx.png",
             mapFolder / "posy.png", mapFolder / "negy.png",
             mapFolder / "posz.png", mapFolder / "negz.png" });

        // materials
        auto terrainMaterial = GenericMaterial::make(
            sourceDir() / "terrain.vsh",
            sourceDir() / "terrain.fsh"
        );
        terrainMaterial->uniform("terrainNZ", terrainNZ);
        terrainMaterial->uniform("terrainRocks", terrainRocks);
        terrainMaterial->uniform("terrainWater", terrainWater);
        terrainMaterial->uniform("terrainGrass", terrainGrass);
        terrainMaterial->uniform("terrainSand", terrainSand);

//        auto phongMaterial = GenericMaterial::make(
//            sourceDir() / "phong.vsh",
//            sourceDir() / "phong.fsh"
//        );

        auto skyMaterial = GenericMaterial::make(
            sourceDir() / "skybox.vsh",
            sourceDir() / "skybox.fsh"
        );
        skyMaterial->uniform("specularEnvMap", skyTexture);

        // Build the scene graph

        //KI



        auto planeNode = Node::make("plane", translate(vec3(0.0f, -15.0f, 0.0f)));
        auto onePlaneNode = Node::make("onePlane");
        onePlaneNode->add(Shape::make(Mesh::makePlane(planeSize, 400), terrainMaterial));

        for (int x = -1; x < 2; x++) {
            for (int z = -1; z < 2; z++) {
                vec3 pos(0 + planeSize * x, 0, 0 + planeSize * z);
                auto aPlaneNode = Node::make("aPlane", translate(pos));
                aPlaneNode->add(onePlaneNode);
                planeNode->add(aPlaneNode);
                planes.push_back(aPlaneNode);
//                planes[x+1][z+1] = aPlaneNode;
            }
        }
//        for (int t = 0; t != 3; t++) {
//           vec3 pos(0, 0, 0 - planeSize * t);
//           auto aPlaneNode = Node::make("aPlane", translate(pos));
//           aPlaneNode->add(onePlaneNode);
//           planeNode->add(aPlaneNode);
//           planes.push_back(aPlaneNode);
//        }

        auto cameraPosition = vec3(0.0f, -7.5f, 0.0f);
        auto cameraNode = PerspectiveCamera::make("camera", translate(cameraPosition), radians(90.0f), 0.1f, cameraFar);
        wasdMover = FlySimpleWasd::make("wasd", cameraNode, cameraPosition);
        wasdMover->vSpeed *= 3;

        auto lightNode = PointLight::make("light", translate(vec3(-10, 10, 10)));

        auto skyNode = Node::make("sky");
        skyNode->add(Shape::make(Mesh::makeCube(), skyMaterial));
        auto skyNodeRoot = Node::make("skyRoot");
        skyNodeRoot->children = {cameraNode, lightNode, skyNode};

        auto rootNode = Node::make("root");
        rootNode->children = {cameraNode, lightNode, planeNode};

        // create spheres
        for (int i = 0; i < numSpheres; ++i) {
            auto spherePosition = vec3(randomFloat(cameraFar * -1, cameraFar), randomFloat(-13.0f, cameraFar), randomFloat(cameraFar * -1, cameraFar));
            auto sphereNode = Node::make("sphere" + std::string(std::to_string(i)), translate(spherePosition));
            auto phongMaterial = GenericMaterial::make(
                sourceDir() / "phong.vsh",
                sourceDir() / "phong.fsh"
            );

            auto sphereColor = vec3(randomFloat(0, 1), randomFloat(0, 1), randomFloat(0, 1));
            std::cout << "sphereColor : " << sphereColor << std::endl;
            phongMaterial->uniform("kd", sphereColor);
            sphereNode->add(Shape::make(Mesh::makeSphere(50), phongMaterial));
            rootNode->add(sphereNode);

            FlyRandom::Ptr kiMover = FlyRandom::make("kiMover" + std::string(std::to_string(i)), sphereNode, spherePosition);
            kiMover->vSpeed = rand() % 5;
            kiMovers.push_back(kiMover);
        }

        renderer = Renderer::make(runner.backBuffer, rootNode);
        skyRenderer = Renderer::make(runner.backBuffer, skyNodeRoot);

        runner.input.onPress(GLFW_KEY_L, [this](int mods) {
            drawLines = !drawLines;
        });

        runner.input.onPress(GLFW_KEY_T, [this](int mods){
            textureRepeat = (textureRepeat + 1) % 10;
        });
    }

    virtual void frame(AppRunner& runner) {
        // Simulate
//        if (rotate) {
//            cubeNode->transform =
//                    rotate(cubeNode->transform, radians(90.0f) * runner.elapsed, vec3(1.0f, 1.0f, 1.0f));
//        }

        wasdMover->simulate(runner);
        // KI Mover

//

        float totalTime = runner.clock;

        for (int i = 0; i < numSpheres; ++i) {
            FlyRandom::Ptr kiMover = kiMovers[i];
            kiMover->simulate(runner);

            if (abs(wasdMover->position.x - kiMover->position.x) > cameraFar) {
                kiMover->position.x = wasdMover->position.x;
            }
            if (abs(wasdMover->position.y - kiMover->position.y) > cameraFar) {
                kiMover->position.y = wasdMover->position.y;
            }
            if (abs(wasdMover->position.z - kiMover->position.z) > cameraFar) {
                kiMover->position.z = wasdMover->position.z;
            }

            //spheres should not go under the map
            if (kiMover->position.y < -13.0f) {
                kiMover->position.y = -13.0f;
            }
            //spheres shouldnt go faster than 9.0
            if (kiMover->vSpeed > 9.0f) {
                kiMover->vSpeed = 9.0f;
            }

            if (totalTime > kiMover->interval) {

//                kiMover->tr = rand() % 6 + 1; //from 1 to 6
                kiMover->ro = rand() % 4 + 1;

                kiMover->interval += 1;
            }

            if (totalTime > kiMover->intervalTwo) {

                kiMover->tr = rand() % 6 + 1; //from 1 to 6
//                kiMover->ro = rand() % 4 + 1;

                kiMover->intervalTwo += 5;
            }
        }



//        wasdKiMover_R->simulate(runner);
//        wasdKiMover_G->simulate(runner);
//        wasdKiMover_B->simulate(runner);

//        if (abs(wasdMover->position.x - wasdKiMover_R->position.x) > cameraFar) {
//            wasdKiMover_R->position.x = wasdMover->position.x;
//        }
//        if (abs(wasdMover->position.y - wasdKiMover_R->position.y) > cameraFar) {
//            wasdKiMover_R->position.y = wasdMover->position.y;
//        }
//        if (abs(wasdMover->position.z - wasdKiMover_R->position.z) > cameraFar) {
//            wasdKiMover_R->position.z = wasdMover->position.z;
//        }

//        if (abs(wasdMover->position.x - wasdKiMover_G->position.x) > cameraFar) {
//            wasdKiMover_G->position.x = wasdMover->position.x;
//        }
//        if (abs(wasdMover->position.y - wasdKiMover_G->position.y) > cameraFar) {
//            wasdKiMover_G->position.y = wasdMover->position.y;
//        }
//        if (abs(wasdMover->position.z - wasdKiMover_G->position.z) > cameraFar) {
//            wasdKiMover_G->position.z = wasdMover->position.z;
//        }

//        if (abs(wasdMover->position.x - wasdKiMover_B->position.x) > cameraFar) {
//            wasdKiMover_B->position.x = wasdMover->position.x;
//        }
//        if (abs(wasdMover->position.y - wasdKiMover_B->position.y) > cameraFar) {
//            wasdKiMover_B->position.y = wasdMover->position.y;
//        }
//        if (abs(wasdMover->position.z - wasdKiMover_B->position.z) > cameraFar) {
//            wasdKiMover_B->position.z = wasdMover->position.z;
//        }


        //print camera position every 3 seconds
//        float totalTime = runner.clock;
//        if (totalTime > coutAfter) {
//            std::cout << "camera position : " << wasdMover->position << std::endl;
//            std::cout << "name : " << wasdMover->name << std::endl;
//            std::cout << "node : " << wasdMover->node << std::endl;
//            std::cout << "orientation : " << wasdMover->orientation << std::endl;
//            std::cout << "aSpeed : " << wasdMover->aSpeed << std::endl;
            std::cout << "vSpeed : " << wasdMover->vSpeed << std::endl;
            std::cout << "wasdMover->position : " << wasdMover->position<< std::endl;
            std::cout << "nextBorderZn : " << nextBorderZn<< std::endl;
            std::cout << "nextBorderZp : " << nextBorderZp<< std::endl;
            std::cout << "nextBorderXn : " << nextBorderXn<< std::endl;
            std::cout << "nextBorderXp : " << nextBorderXp<< std::endl;

            if (wasdMover->position.z < nextBorderZn) {
                Node::Vec temp;
                temp.push_back(planes[2]);
                temp.push_back(planes[5]);
                temp.push_back(planes[8]);

                for (int i = 0; i < 3; ++i) {
                    Node::Ptr plane;
                    plane = temp[i];
                    plane->transform = translate(plane->transform, vec3(0, 0, planeSize * -3));
                }

                Node::Vec newPlanes;
                newPlanes.push_back(planes[2]);
                newPlanes.push_back(planes[0]);
                newPlanes.push_back(planes[1]);
                newPlanes.push_back(planes[5]);
                newPlanes.push_back(planes[3]);
                newPlanes.push_back(planes[4]);
                newPlanes.push_back(planes[8]);
                newPlanes.push_back(planes[6]);
                newPlanes.push_back(planes[7]);
                planes = newPlanes;

                nextBorderZn -= planeSize;
                nextBorderZp -= planeSize;

            } else if (wasdMover->position.z > nextBorderZp) {
                Node::Vec temp;
                temp.push_back(planes[0]);
                temp.push_back(planes[3]);
                temp.push_back(planes[6]);

                for (int i = 0; i < 3; ++i) {
                    Node::Ptr plane;
                    plane = temp[i];
                    plane->transform = translate(plane->transform, vec3(0, 0, planeSize * 3));
                }

                Node::Vec newPlanes;
                newPlanes.push_back(planes[1]);
                newPlanes.push_back(planes[2]);
                newPlanes.push_back(planes[0]);
                newPlanes.push_back(planes[4]);
                newPlanes.push_back(planes[5]);
                newPlanes.push_back(planes[3]);
                newPlanes.push_back(planes[7]);
                newPlanes.push_back(planes[8]);
                newPlanes.push_back(planes[6]);
                planes = newPlanes;

                nextBorderZp += planeSize;
                nextBorderZn += planeSize;

            } else if (wasdMover->position.x < nextBorderXn) {

                Node::Vec temp;
                temp.push_back(planes[6]);
                temp.push_back(planes[7]);
                temp.push_back(planes[8]);

                for (int i = 0; i < 3; ++i) {
                    Node::Ptr plane;
                    plane = temp[i];
                    plane->transform = translate(plane->transform, vec3(planeSize * -3, 0, 0));
                }

                Node::Vec newPlanes;
                newPlanes.push_back(planes[6]);
                newPlanes.push_back(planes[7]);
                newPlanes.push_back(planes[8]);
                newPlanes.push_back(planes[0]);
                newPlanes.push_back(planes[1]);
                newPlanes.push_back(planes[2]);
                newPlanes.push_back(planes[3]);
                newPlanes.push_back(planes[4]);
                newPlanes.push_back(planes[5]);
                planes = newPlanes;

                nextBorderXn -= planeSize;
                nextBorderXp -= planeSize;

            } else if (wasdMover->position.x > nextBorderXp) {

                Node::Vec temp;
                temp.push_back(planes[0]);
                temp.push_back(planes[1]);
                temp.push_back(planes[2]);

                for (int i = 0; i < 3; ++i) {
                    Node::Ptr plane;
                    plane = temp[i];
                    plane->transform = translate(plane->transform, vec3(planeSize * 3, 0, 0));
                }

                Node::Vec newPlanes;
                newPlanes.push_back(planes[3]);
                newPlanes.push_back(planes[4]);
                newPlanes.push_back(planes[5]);
                newPlanes.push_back(planes[6]);
                newPlanes.push_back(planes[7]);
                newPlanes.push_back(planes[8]);
                newPlanes.push_back(planes[0]);
                newPlanes.push_back(planes[1]);
                newPlanes.push_back(planes[2]);
                planes = newPlanes;

                nextBorderXp += planeSize;
                nextBorderXn += planeSize;

            }

//            coutAfter += 1.0f;
//        }

//        if (wasdMover->position.z < negativeZdist) {
//            std::cout << "negativeZdist : " << negativeZdist << std::endl;
//            negativeZdist -= planeSize;
//        }

        // Draw
        int width, height;
        glfwGetFramebufferSize(runner.window, &width, &height);

        if (drawLines) {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        } else {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        glDepthMask(GL_FALSE);
        glDisable(GL_CULL_FACE);

        skyRenderer->Draw(0);

        glDepthMask(GL_TRUE);
        glEnable(GL_CULL_FACE);

        renderer->setGlobalUniform("textureRepeat", (float) textureRepeat);
        renderer->setGlobalUniform("time", runner.clock);
        renderer->Draw(0);

//        fogRenderer->Draw(fogMaterial);
    }
};

int main(int argc, const char* argv[]) {
    CubeApp app;
    return AppRunner(argc, argv).run(app);
}
