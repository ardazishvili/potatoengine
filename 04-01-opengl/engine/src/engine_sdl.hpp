#pragma once

#include "engine.hpp"
#include "renderer/renderer.hpp"
#include <SDL2/SDL.h>
#include <imstb_truetype.h>

namespace pt
{

class engine_sdl final : public engine
{
public:
    ~engine_sdl();

    bool init() override;

    void enable_vsync(bool state) override;

    void enable_wireframe(bool state) override;

private:
    void post_render_objects() override;

    void process_keyboard_event(const SDL_KeyboardEvent& event);

    void process_mouse_motion_event(const SDL_MouseMotionEvent& event);

    void process_mouse_button_event(const SDL_MouseButtonEvent& event);

    void poll_events() override;

    void clean_up(); // TODO I really need a better name for this method

    void
    render_object(const model &model, const transformation &transformation, const ptm::vec3 &light_position) override;

    void prepare_gui_frame() override;

    void render_gui_frame() override;

    void render_lights() override;

protected:
    float get_ticks() override;

private:
    SDL_Window* window_ = nullptr;

    std::unique_ptr<renderer> renderer_;
};

} // namespace pt