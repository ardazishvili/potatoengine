#pragma once

#include <BulletDynamics/Dynamics/btDiscreteDynamicsWorld.h> // TODO find a way to remove the bullet physics header
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

    bool load_sound(const std::string& sound_name, const std::string& file_path);

    bool play_sound(const std::string& sound_name) const;

private:
    std::unique_ptr<class engine_pimpl> impl;
};

} // namespace pt