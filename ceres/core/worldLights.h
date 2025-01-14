//
// Created by william on 2022/5/26.
//

#ifndef GRAPHICRENDERENGINE_WORLDLIGHTS_H
#define GRAPHICRENDERENGINE_WORLDLIGHTS_H
#include "commonMacro.h"
#include "light.h"

#include <glm/glm.hpp>
#include <vector>
namespace ceres
{
class Light;

struct WorldLights
{
    WorldLights();
    inline size_t addLight(const Light& light)
    {
        lights.push_back(light);
        return lights.size() - 1;
    }

    inline void removeLight(int index)
    {
        ASSERT(index < lights.size());
        lights.erase(lights.cbegin() + index);
    }

    inline void removeAllLight()
    {
        lights.clear();
        lights.shrink_to_fit();
    }

    inline Light* getLight(int index)
    {
        if (index >= lights.size())
        {
            return nullptr;
        }
        return &lights[index];
    }
    [[nodiscard]] inline size_t lightCount() const { return lights.size(); }
    inline void setAmbientLight(const glm::vec3& light)
    {
        ambientLight = glm::vec4(light, 0.0f);
    }
    [[nodiscard]] inline glm::vec3 getAmbientLight() const
    {
        return { ambientLight.x, ambientLight.y, ambientLight.z };
    }
    void clear();

    glm::vec4 ambientLight{};
    std::vector<Light> lights;
};
} // namespace ceres

#endif // GRAPHICRENDERENGINE_WORLDLIGHTS_H
