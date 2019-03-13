#pragma once

#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h>
#include <memory>

namespace pt
{

class game_object;
class movable_object;
class input_manager;

class engine
{
public:
    engine();
    ~engine();

    bool init_engine();

    bool run();

    game_object* add_object(std::unique_ptr<game_object> object);

    template <typename T>
    game_object* add_object()
    {
        return add_object(std::make_unique<T>());
    }

    input_manager& get_input_manager();

    void set_title(const std::string& title);

    /** time from the start of the game */
    float time() const;

    /** duration of the previous frame */
    float delta_time() const;

    movable_object& get_camera();

    movable_object& get_light();

    void enable_wireframe(bool state);

    void set_light_model(const class model& model);

    btDiscreteDynamicsWorld* get_dynamics_world();

private:
    std::unique_ptr<class engine_pimpl> impl;

    void set_game_running(bool is_game_running);

    void start_objects();

    void update_objects();

    void render_objects();

    void render_objects_gui();

    // TODO move physics to a separate component
private:
    void init_physics();

    void update_physics();

    void render_lights();
};

std::unique_ptr<engine> make_engine();

} // namespace pt