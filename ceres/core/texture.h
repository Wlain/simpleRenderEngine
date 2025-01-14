//
// Created by william on 2022/5/22.
//

#ifndef GRAPHICRENDERENGINE_TEXTURE_H
#define GRAPHICRENDERENGINE_TEXTURE_H
#include "resource.h"

#include <cstdlib>
#include <map>
#include <string>
#include <string_view>
#include <vector>

namespace ceres
{
class Texture : public std::enable_shared_from_this<Texture>
{
public:
    enum class PixelFormat : uint8_t
    {
        RGBA,
        RGB
    };

    enum class SamplerColorspace : uint8_t
    {
        Linear,
        Gamma
    };

    enum class CubeMapSide : uint8_t
    {
        PositiveX,
        NegativeX,
        PositiveY,
        NegativeY,
        PositiveZ,
        NegativeZ
    };

    enum class DepthPrecision
    {
        I16,          // 16 bit integer
        I24,          // 24 bit integer
        I32,          // 32 bit integer
        F32,          // 32 bit float
        I24_STENCIL8, // 24 bit integer 8 bit stencil
        F32_STENCIL8, // 32 bit float 8 bit stencil
        STENCIL8,     // 8 bit stencil
        None
    };

    enum class Wrap
    {
        Repeat,
        ClampToEdge,
        Mirror
    };

    struct Info
    {
        PixelFormat format = PixelFormat::RGBA;
        SamplerColorspace colorspace = SamplerColorspace::Linear;
        ResourceType resourceType = ResourceType::File;
        Wrap warp = Wrap::Repeat;
        std::string name;
        int width = 0;
        int height = 0;
        int channels = 0;
        uint32_t id = 0;
        uint32_t target = 0;
        bool transparent; // 透明纹理
        bool generateMipmap = false;
        bool filterSampling = true;
    };

public:
    class TextureBuilder
    {
    public:
        TextureBuilder(const TextureBuilder&) = delete;
        ~TextureBuilder();
        TextureBuilder& withGenerateMipmaps(bool enable);
        // if true texture sampling is filtered (bi-linear or tri-linear sampling) otherwise use point sampling.
        TextureBuilder& withFilterSampling(bool enable);
        TextureBuilder& withFile(std::string_view filename, bool premultiplyAlpha = true);
        TextureBuilder& withFileCubeMap(std::string_view filename, CubeMapSide side);
        TextureBuilder& withWrapUV(Wrap wrap);
        TextureBuilder& withRGBAData(const char* data, int width, int height);
        TextureBuilder& withWhiteData(int width = 1, int height = 1);
        TextureBuilder& withSamplerColorspace(SamplerColorspace samplerColorspace);
        TextureBuilder& withDepth(int width, int height, DepthPrecision precision = DepthPrecision::I16); // Creates a depth texture.
        TextureBuilder& withName(std::string_view name);
        std::shared_ptr<Texture> build();

    private:
        TextureBuilder();

    public:
        Info m_info{};
        DepthPrecision m_depthPrecision = DepthPrecision::None;
        friend class Texture;
    };

public:
    static TextureBuilder create();
    static std::shared_ptr<Texture> getWhiteTexture();
    static std::shared_ptr<Texture> getFontTexture();
    static std::shared_ptr<Texture> getSphereTexture();
    static std::shared_ptr<Texture> getCubeMapTexture();
    ~Texture();

public:
    inline int width() const { return m_info.width; }
    inline int height() const { return m_info.height; }
    inline const std::string& name() const { return m_info.name; }
    inline bool isFilterSampling() const { return m_info.filterSampling; }
    inline Wrap warpUv() const { return m_info.warp; }
    bool isCubeMap() const;
    bool isMipMapped() const; // has texture mipmapped enabled
    bool isTransparent() const;
    void invokeGenerateMipmap();
    // get size of the texture in bytes on GPU
    size_t getDataSize() const;
    SamplerColorspace getSamplerColorSpace() const;
    bool isDepthTexture() const;
    DepthPrecision getDepthPrecision() const;

private:
    Texture(int32_t id, int width, int height, uint32_t target, std::string string);
    void updateTextureSampler(bool filterSampling, Wrap warp) const;

private:
    inline static std::shared_ptr<Texture> s_whiteTexture{ nullptr };
    inline static std::shared_ptr<Texture> s_fontTexture{ nullptr };
    inline static std::shared_ptr<Texture> s_sphereTexture{ nullptr };
    inline static std::shared_ptr<Texture> s_cubeMapTexture{ nullptr };

private:
    Info m_info{};
    DepthPrecision m_depthPrecision = DepthPrecision::None;
    friend class Shader;
    friend class UniformSet;
    friend class RenderPass;
    friend class FrameBuffer;
    friend class Inspector;
    friend class Sprite;
};
} // namespace ceres

#endif // GRAPHICRENDERENGINE_TEXTURE_H
