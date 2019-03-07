#pragma once

#include "mesh.hpp"
#include "model.hpp"
#include "ptm/vec3.hpp"
#include "transformation.hpp"
#include <memory>

namespace pt
{

class engine;

class game_object
{
public:
    virtual ~game_object();

    /** called once for each game object before the main loop */
    virtual void start(){};

    /** called every frame */
    virtual void update() = 0;

    /** add custom GUI */
    virtual void on_gui(){};

    void set_transform(const transformation& transform);

    const transformation& get_transformation() const;

    void      set_position(const ptm::vec3& position);
    ptm::vec3 get_position() const;

    void      set_scale(const ptm::vec3& scale);
    ptm::vec3 get_scale() const;

    void set_rotation(const ptm::vec3& rotation_vector, float angle);

    const model& get_model() const;
    void         set_model(const model& model);

    void load_model(const std::string& path);

protected:
    engine& get_engine();

private:
    friend class engine;

    engine* engine_ = nullptr;

    bool  has_model_ = false;
    model model_;

    transformation transformation_ = { .position        = ptm::zero_vector,
                                       .rotation_vector = ptm::up_vector,
                                       .rotation_angle  = 0.0f,
                                       .scale           = { 1.f, 1.f, 1.f } };
};

} // namespace pt