//
// Created by william on 2022/5/24.
//
#include "commonMacro.h"
#include "core/mesh.h"
#include "core/renderer.h"
#include "core/shader.h"
#include "core/texture.h"

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtc/random.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace re;

static int s_canvasWidth = 640;
static int s_canvasHeight = 480;
static constexpr char* title = "particleTest";

ParticleMesh* createParticles(int size = 2500)
{
    std::vector<glm::vec3> positions;
    std::vector<glm::vec4> colors;
    std::vector<glm::vec4> uvs;
    std::vector<float> sizes;
    for (int i = 0; i < size; i++)
    {
        positions.push_back(glm::linearRand(glm::vec3(-1, -1, -1), glm::vec3(1, 1, 1)));
        colors.push_back(glm::linearRand(glm::vec4(0, 0, 0, 0), glm::vec4(1, 1, 1, 1)));
        sizes.push_back(glm::linearRand(0.0f, 500.0f));
    }
    return new ParticleMesh(positions, colors, uvs, sizes);
}

void particleTest()
{
    LOG_INFO("{}", title);
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    // glfw window creation
    auto window = glfwCreateWindow(s_canvasWidth, s_canvasHeight, title, nullptr, nullptr);
    if (window == nullptr)
    {
        glfwTerminate();
    }
    Renderer r{ window };
    r.getCamera()->setLookAt({ 0.0f, 0.0f, 4.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f });
    r.getCamera()->setPerspectiveProjection(45.0f, s_canvasWidth, s_canvasHeight, 0.1f, 100.0f);
    auto* shader = Shader::getStandard();
    shader->set("specularity", 20.0f);
    shader->set("tex", Texture::createTextureFromFile(GET_CURRENT("test/resources/test.jpg"), true), 1);
    auto* shaderParticle = Shader::getStandardParticles();
    shaderParticle->set("tex", Texture::getAlphaSphereTexture());
    auto* particleMesh = createParticles();
    Mesh* mesh = Mesh::createCube();
    r.setLight(0, { Light::Type::Point, { 0, 1, 0 }, { 0, 0, 0 }, { 1, 0, 0 }, 2 });
    r.setLight(1, { Light::Type::Point, { 1, 0, 0 }, { 0, 0, 0 }, { 0, 1, 0 }, 2 });
    r.setLight(2, { Light::Type::Point, { 0, -1, 0 }, { 0, 0, 0 }, { 0, 0, 1 }, 2 });
    r.setLight(3, { Light::Type::Point, { -1, 0, 0 }, { 0, 0, 0 }, { 1, 1, 1 }, 2 });

    while (!glfwWindowShouldClose(window))
    {
        /// 渲染
        r.clearScreen({ 1.0f, 0.0f, 0.0f, 1.0f });
        r.render(mesh, glm::eulerAngleY(glm::radians(360 * (float)glfwGetTime() * 0.1f)) * glm::scale(glm::mat4(1),{0.3f,0.3f,0.3f}), shader);
        r.render(particleMesh, glm::eulerAngleY(glm::radians(360 * (float)glfwGetTime() * 0.1f)), shaderParticle);
        r.swapWindow();
    }
    glfwTerminate();
    exit(EXIT_SUCCESS);
}