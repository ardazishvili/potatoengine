#include <game_object.hpp>

class cube : public pt::game_object
{
public:
    using pt::game_object::game_object;

    void start() override { set_model(pt::model("res/cube/cube.obj")); }

    bool is_serializable() const override { return true; }
};
