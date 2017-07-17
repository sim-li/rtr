#ifndef FLYMOVER_H
#define FLYMOVER_H

#include <jet/jet.h>
using namespace jet;


///
/// \brief The FlySimpleWasd class implements an interactive mover with the common WASD keyboard mapping.
/// The following keys are used:
///
/// + `<W>` - Move forward (Moves in the viewing direction)
/// + `<A>` - Strafe left (Moves perpendicular to the viewing direction)
/// + `<S>` - Move backwards
/// + `<D>` - Strafe right
///
/// + `<Q>` - Strafe up
/// + `<E>` - Strafe down
///
/// + `<up>` - Look up (Rotates viewing direction upwards)
/// + `<down>` - Look down
/// + `<left>` - Look left
/// + `<right>` - Look right
///
class FlySimpleWasd : public Mover {
public: typedef std::shared_ptr<FlySimpleWasd> Ptr;

    glm::mat4 orientation;
    glm::vec3 position;
    float aSpeed;
    float vSpeed;

    FlySimpleWasd(const std::string& name, Node::Ptr node, glm::vec3 position, glm::mat4 orientation);
    virtual void simulate(AppRunner& runner);

    static FlySimpleWasd::Ptr make(const std::string& name, Node::Ptr node = Node::Ptr(), glm::vec3 position = glm::vec3(), glm::mat4 orientation = glm::mat4());
};

class FlyRandom : public Mover {
public: typedef std::shared_ptr<FlyRandom> Ptr;

    glm::mat4 orientation;
    glm::vec3 position;
    float aSpeed;
    float vSpeed;
    int tr;
    int ro;
    int interval;
    int intervalTwo;

    FlyRandom(const std::string& name, Node::Ptr node, glm::vec3 position, glm::mat4 orientation);
    virtual void simulate(AppRunner& runner);

    static FlyRandom::Ptr make(const std::string& name, Node::Ptr node = Node::Ptr(), glm::vec3 position = glm::vec3(), glm::mat4 orientation = glm::mat4());
};


#endif // FLYMOVER_H
