//
// Created by cwb on 2022/6/21.
//
#include "core/skybox.h"

#include "engineTestSimple.h"
#include "guiCommonDefine.h"

#include <core/modelImporter.h>
#include <glm/glm.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtx/transform.hpp>

class SkyBoxExample : public CommonInterface
{
public:
    using CommonInterface::CommonInterface;
    ~SkyBoxExample() override = default;
    void initialize() override
    {
        m_camera.setLookAt(m_eye, m_at, m_up);
        m_camera.setPerspectiveProjection(60, 0.1, 100);
        m_material = Shader::getStandardPBR()->createMaterial();
        m_material->setColor({ 1.0f, 1.0f, 1.0f, 1.0f });
        m_material->setMetallicRoughness({ 0.5f, 0.5f });
        m_mesh = Mesh::create().withCube().build();
        m_cowMesh = ModelImporter::importObj("resources/objFiles/spot/spot_triangulated_good.obj");
        m_teapotMesh = ModelImporter::importObj("resources/objFiles/teapot.obj");
        m_refractionMaterial = Shader::create()
                               .withSourceFile("shaders/cubeMapping/refraction_vert.glsl", Shader::ShaderType::Vertex)
                               .withSourceFile("shaders/cubeMapping/refraction_frag.glsl", Shader::ShaderType::Fragment)
                               .withName("Unlit")
                               .build()->createMaterial();
        m_reflectionMaterial = Shader::create()
                                       .withSourceFile("shaders/cubeMapping/reflection_vert.glsl", Shader::ShaderType::Vertex)
                                       .withSourceFile("shaders/cubeMapping/reflection_frag.glsl", Shader::ShaderType::Fragment)
                                       .withName("Unlit")
                                       .build()->createMaterial();
        m_worldLights = MAKE_UNIQUE(m_worldLights);
        m_worldLights->setAmbientLight({ 0.0, 0.0, 0.0 });
        m_worldLights->addLight(Light::create().withPointLight({ 0, 3, 0 }).withColor({ 1, 0, 0 }).withRange(20).build());
        m_worldLights->addLight(Light::create().withPointLight({ 3, 0, 0 }).withColor({ 0, 1, 0 }).withRange(20).build());
        m_worldLights->addLight(Light::create().withPointLight({ 0, -3, 0 }).withColor({ 0, 0, 1 }).withRange(20).build());
        m_worldLights->addLight(Light::create().withPointLight({ -3, 0, 0 }).withColor({ 1, 1, 1 }).withRange(20).build());
        auto tex = Texture::create()
                       .withFileCubeMap("resources/skybox/park3Med/px.jpg", Texture::CubeMapSide::PositiveX)
                       .withFileCubeMap("resources/skybox/park3Med/nx.jpg", Texture::CubeMapSide::NegativeX)
                       .withFileCubeMap("resources/skybox/park3Med/py.jpg", Texture::CubeMapSide::PositiveY)
                       .withFileCubeMap("resources/skybox/park3Med/ny.jpg", Texture::CubeMapSide::NegativeY)
                       .withFileCubeMap("resources/skybox/park3Med/pz.jpg", Texture::CubeMapSide::PositiveZ)
                       .withFileCubeMap("resources/skybox/park3Med/nz.jpg", Texture::CubeMapSide::NegativeZ)
                       .withWrapUV(Texture::Wrap::ClampToEdge)
                       .build();
        m_skybox = Skybox::create();
        m_skybox->getMaterial()->setTexture(tex);
        m_refractionMaterial->setTexture(tex);
        m_reflectionMaterial->setTexture(tex);
    }
    void render() override
    {
        auto renderPass = RenderPass::create()
                              .withCamera(m_camera)
                              .withWorldLights(m_worldLights.get())
                              .withSkybox(m_skybox)
                              .withName("Skybox Frame")
                              .build();
        auto modelMatrix = glm::eulerAngleY(glm::radians(30 * m_totalTime));
        renderPass.draw(m_teapotMesh, glm::translate(glm::vec3(-4, 0, 0)) * glm::eulerAngleY(glm::radians(30 * m_totalTime)) * glm::mat4(1.0), m_refractionMaterial);
        renderPass.draw(m_mesh,  glm::translate(glm::vec3(0, 1, 0)) * modelMatrix, m_reflectionMaterial);
        renderPass.draw(m_cowMesh, glm::translate(glm::vec3(4, 1, 0)) * modelMatrix, m_material);
        ImGui::DragFloat3("eye", &m_eye.x);
        ImGui::DragFloat3("at", &m_at.x);
        ImGui::DragFloat3("up", &m_up.x);
        m_camera.setLookAt(m_eye, m_at, m_up);
    }
    void setTitle() override
    {
        m_title = "SkyBoxExample";
    }

private:
    std::shared_ptr<Mesh> m_teapotMesh;
    std::shared_ptr<Mesh> m_cowMesh;
    std::shared_ptr<Material> m_refractionMaterial;
    std::shared_ptr<Material> m_reflectionMaterial;
    std::shared_ptr<Skybox> m_skybox;
    glm::vec3 m_eye{ 0, 0, 10.0f };
    glm::vec3 m_at{ 0, 0, 0 };
    glm::vec3 m_up{ 0, 1, 0 };
};

void skyboxTest()
{
    GLFWRenderer renderer{};
    EngineTestSimple test(renderer);
    auto sceneNodeEffect = std::make_shared<SkyBoxExample>(&renderer);
    auto effect = std::make_shared<EffectManager>();
    effect->insertEffect(sceneNodeEffect);
    test.setEffect(effect);
    test.run();
}