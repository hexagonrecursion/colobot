/*
 * This file is part of the Colobot: Gold Edition source code
 * Copyright (C) 2001-2022, Daniel Roux, EPSITEC SA & TerranovaTeam
 * http://epsitec.ch; http://colobot.info; http://github.com/colobot
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see http://gnu.org/licenses
 */

/**
 * \file graphics/opengl33/gl33_device.h
 * \brief OpenGL 3.3 implementation - CGL33Device class
 */

#pragma once

#include <GL/glew.h>
#include <cstddef>
#include <glm/glm.hpp>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <unordered_set>

#include "graphics/core/device.h"
#include "graphics/core/framebuffer.h"
#include "graphics/core/texture.h"

class CImage;
struct ImageData;


// Graphics module namespace
namespace Gfx
{

enum class CullFace : unsigned char;
enum class TransparencyMode : unsigned char;
class CObjectRenderer;
class CParticleRenderer;
class CShadowRenderer;
class CTerrainRenderer;
class CUIRenderer;
enum class PrimitiveType : unsigned char;
struct Color;
struct Vertex3D;

class CGL33VertexBuffer : public CVertexBuffer
{
    GLuint m_vao = 0;
    GLuint m_vbo = 0;

public:
    CGL33VertexBuffer(PrimitiveType type, size_t size);
    virtual ~CGL33VertexBuffer();

    virtual void Update() override;

    GLuint GetVAO() const
    {
        return m_vao;
    }

    GLuint GetVBO() const
    {
        return m_vbo;
    }
};

class CGL33UIRenderer;
class CGL33TerrainRenderer;
class CGL33ObjectRenderer;
class CGL33ParticleRenderer;
class CGL33ShadowRenderer;

/**
  \class CGL33Device
  \brief Implementation of CDevice interface in OpenGL 3.3

  Provides the concrete implementation of 3D device in OpenGL.

  This class should be initialized (by calling Initialize() ) only after
  setting the video mode by CApplication, once the OpenGL context is defined.
  Because of that, CGLDeviceConfig is outside the CDevice class and must be set
  in CApplication.
*/
class CGL33Device : public CDevice
{
public:
    CGL33Device(const DeviceConfig &config);
    virtual ~CGL33Device();

    std::string GetName() override;

    bool Create() override;
    void Destroy() override;

    void ConfigChanged(const DeviceConfig &newConfig) override;

    void BeginScene() override;
    void EndScene() override;

    void Clear() override;

    CUIRenderer* GetUIRenderer() override;
    CTerrainRenderer* GetTerrainRenderer() override;
    CObjectRenderer* GetObjectRenderer() override;
    CParticleRenderer* GetParticleRenderer() override;
    CShadowRenderer* GetShadowRenderer() override;

    Texture CreateTexture(CImage *image, const TextureCreateParams &params) override;
    Texture CreateTexture(ImageData *data, const TextureCreateParams &params) override;
    Texture CreateDepthTexture(int width, int height, int depth) override;
    void UpdateTexture(const Texture& texture, const glm::ivec2& offset, ImageData* data, TextureFormat format) override;
    void DestroyTexture(const Texture &texture) override;
    void DestroyAllTextures() override;

    CVertexBuffer* CreateVertexBuffer(PrimitiveType primitiveType, const Vertex3D* vertices, int vertexCount) override;
    void DestroyVertexBuffer(CVertexBuffer*) override;

    void SetViewport(int x, int y, int width, int height) override;

    void SetDepthTest(bool enabled) override;
    void SetDepthMask(bool enabled) override;

    void SetCullFace(CullFace mode) override;

    void SetTransparency(TransparencyMode mode) override;

    void SetColorMask(bool red, bool green, bool blue, bool alpha) override;

    void SetClearColor(const Color &color) override;

    void CopyFramebufferToTexture(Texture& texture, int xOffset, int yOffset, int x, int y, int width, int height) override;

    std::unique_ptr<CFrameBufferPixels> GetFrameBufferPixels() const override;

    CFramebuffer* GetFramebuffer(std::string name) override;

    CFramebuffer* CreateFramebuffer(std::string name, const FramebufferParams& params) override;

    void DeleteFramebuffer(std::string name) override;

    bool IsAnisotropySupported() override;
    int GetMaxAnisotropyLevel() override;

    int GetMaxSamples() override;

    bool IsShadowMappingSupported() override;

    int GetMaxTextureSize() override;

    bool IsFramebufferSupported() override;

private:
    //! Current config
    DeviceConfig m_config;

    //! Set of all created textures
    std::set<Texture> m_allTextures;

    //! Detected capabilities
    //! Set of vertex buffers
    std::unordered_set<CVertexBuffer*> m_buffers;

    //! Total memory allocated in VBOs
    unsigned long m_vboMemory = 0;

    //! Map of framebuffers
    std::map<std::string, std::unique_ptr<CFramebuffer>> m_framebuffers;

    //! Interface renderer
    std::unique_ptr<CGL33UIRenderer> m_uiRenderer;
    //! Terrain renderer
    std::unique_ptr<CGL33TerrainRenderer> m_terrainRenderer;
    //! Object renderer
    std::unique_ptr<CGL33ObjectRenderer> m_objectRenderer;
    //! Particle renderer
    std::unique_ptr<CGL33ParticleRenderer> m_particleRenderer;
    //! Shadow renderer
    std::unique_ptr<CGL33ShadowRenderer> m_shadowRenderer;

    //! Depth test
    bool m_depthTest = false;
    //! Depth mask
    bool m_depthMask = true;
    //! Cull face mode
    CullFace m_cullFace = {};
    //! Transparency mode
    TransparencyMode m_transparency = {};
};

} // namespace Gfx
