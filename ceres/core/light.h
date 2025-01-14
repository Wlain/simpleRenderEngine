//
// Created by william on 2022/5/22.
//

#ifndef GRAPHICRENDERENGINE_LIGHT_H
#define GRAPHICRENDERENGINE_LIGHT_H
#include "color.h"

#include <glm/glm.hpp>
namespace ceres
{
struct Light
{
    enum class Type
    {
        Point,
        Directional,
        Unused
    };
    class LightBuilder
    {
    public:
        ~LightBuilder();
        LightBuilder& withPointLight(glm::vec3 position);
        LightBuilder& withDirectionalLight(glm::vec3 direction);
        // light color.
        LightBuilder& withColor(Color color, float intensity = 1.0);
        // range only valid using point light
        LightBuilder& withRange(float range);
        Light& build();

    private:
        LightBuilder();

    private:
        Type m_type{ Type::Unused };
        glm::vec3 m_position{};
        glm::vec3 m_direction{};
        glm::vec3 m_color{};
        Light* m_light{};
        float m_range{}; // the range of a point light (due to attenuation),range == 0 means no attenuation
        friend class Light;
    };

    static LightBuilder create();
    Light();
    Type type{ Type::Unused };
    glm::vec3 position{ 0.0f };
    glm::vec3 direction{ 0.0f };
    glm::vec3 color{ 1.0f };
    // 0 : means no attenuation
    float range{ 100.0f };
};
} // namespace ceres

#endif // GRAPHICRENDERENGINE_LIGHT_H
