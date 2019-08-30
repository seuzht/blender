/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

/** \file
 * \ingroup VAMR
 */

#include <algorithm>
#include <list>
#include <sstream>

#if 0
#  if defined(WITH_X11)
#    include "GHOST_ContextGLX.h"
#  elif defined(WIN32)
#    include "GHOST_ContextWGL.h"
#    include "GHOST_ContextD3D.h"
#  endif
#endif
#include "VAMR_capi.h"
#include "VAMR_intern.h"

#include "VAMR_IGraphicsBinding.h"

static bool choose_swapchain_format_from_candidates(std::vector<int64_t> gpu_binding_formats,
                                                    std::vector<int64_t> runtime_formats,
                                                    int64_t *r_result)
{
  if (gpu_binding_formats.empty()) {
    return false;
  }

  auto res = std::find_first_of(gpu_binding_formats.begin(),
                                gpu_binding_formats.end(),
                                runtime_formats.begin(),
                                runtime_formats.end());
  if (res == gpu_binding_formats.end()) {
    return false;
  }

  *r_result = *res;
  return true;
}

class VAMR_GraphicsBindingOpenGL : public VAMR_IGraphicsBinding {
 public:
  ~VAMR_GraphicsBindingOpenGL()
  {
    if (m_fbo != 0) {
      glDeleteFramebuffers(1, &m_fbo);
    }
  }

  bool checkVersionRequirements(GHOST_Context *ghost_ctx,
                                XrInstance instance,
                                XrSystemId system_id,
                                std::string *r_requirement_info) const override
  {
#if 0
#  if defined(WITH_X11)
    GHOST_ContextGLX *ctx_gl = static_cast<GHOST_ContextGLX *>(ghost_ctx);
#  else
    GHOST_ContextWGL *ctx_gl = static_cast<GHOST_ContextWGL *>(ghost_ctx);
#  endif
    XrGraphicsRequirementsOpenGLKHR gpu_requirements{XR_TYPE_GRAPHICS_REQUIREMENTS_OPENGL_KHR};
    const XrVersion gl_version = XR_MAKE_VERSION(
        ctx_gl->m_contextMajorVersion, ctx_gl->m_contextMinorVersion, 0);

    xrGetOpenGLGraphicsRequirementsKHR(instance, system_id, &gpu_requirements);

    if (r_requirement_info) {
      std::ostringstream strstream;
      strstream << "Min OpenGL version "
                << XR_VERSION_MAJOR(gpu_requirements.minApiVersionSupported) << "."
                << XR_VERSION_MINOR(gpu_requirements.minApiVersionSupported) << std::endl;
      strstream << "Max OpenGL version "
                << XR_VERSION_MAJOR(gpu_requirements.maxApiVersionSupported) << "."
                << XR_VERSION_MINOR(gpu_requirements.maxApiVersionSupported) << std::endl;

      *r_requirement_info = strstream.str();
    }

    return (gl_version >= gpu_requirements.minApiVersionSupported) &&
           (gl_version <= gpu_requirements.maxApiVersionSupported);
#endif
    return true;
  }

  void initFromGhostContext(GHOST_Context *ghost_ctx) override
  {
#if 0
#  if defined(WITH_X11)
    GHOST_ContextGLX *ctx_glx = static_cast<GHOST_ContextGLX *>(ghost_ctx);
    XVisualInfo *visual_info = glXGetVisualFromFBConfig(ctx_glx->m_display, ctx_glx->m_fbconfig);

    oxr_binding.glx.type = XR_TYPE_GRAPHICS_BINDING_OPENGL_XLIB_KHR;
    oxr_binding.glx.xDisplay = ctx_glx->m_display;
    oxr_binding.glx.glxFBConfig = ctx_glx->m_fbconfig;
    oxr_binding.glx.glxDrawable = ctx_glx->m_window;
    oxr_binding.glx.glxContext = ctx_glx->m_context;
    oxr_binding.glx.visualid = visual_info->visualid;
#  elif defined(WIN32)
    GHOST_ContextWGL *ctx_wgl = static_cast<GHOST_ContextWGL *>(ghost_ctx);

    oxr_binding.wgl.type = XR_TYPE_GRAPHICS_BINDING_OPENGL_WIN32_KHR;
    oxr_binding.wgl.hDC = ctx_wgl->m_hDC;
    oxr_binding.wgl.hGLRC = ctx_wgl->m_hGLRC;
#  endif
#endif

    /* Generate a framebuffer to use for blitting into the texture */
    glGenFramebuffers(1, &m_fbo);
  }

  bool chooseSwapchainFormat(const std::vector<int64_t> &runtime_formats,
                             int64_t *r_result) const override
  {
    std::vector<int64_t> gpu_binding_formats = {GL_RGBA8};
    return choose_swapchain_format_from_candidates(gpu_binding_formats, runtime_formats, r_result);
  }

  std::vector<XrSwapchainImageBaseHeader *> createSwapchainImages(uint32_t image_count) override
  {
    std::vector<XrSwapchainImageOpenGLKHR> ogl_images(image_count);
    std::vector<XrSwapchainImageBaseHeader *> base_images;

    // Need to return vector of base header pointers, so of a different type. Need to build a new
    // list with this type, and keep the initial one alive.
    for (XrSwapchainImageOpenGLKHR &image : ogl_images) {
      image.type = XR_TYPE_SWAPCHAIN_IMAGE_OPENGL_KHR;
      base_images.push_back(reinterpret_cast<XrSwapchainImageBaseHeader *>(&image));
    }

    // Keep alive.
    m_image_cache.push_back(std::move(ogl_images));

    return base_images;
  }

  void submitToSwapchain(XrSwapchainImageBaseHeader *swapchain_image,
                         const VAMR_DrawViewInfo *draw_info) override
  {
    XrSwapchainImageOpenGLKHR *ogl_swapchain_image = reinterpret_cast<XrSwapchainImageOpenGLKHR *>(
        swapchain_image);

    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);

    glFramebufferTexture2D(
        GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ogl_swapchain_image->image, 0);

    glBlitFramebuffer(draw_info->ofsx,
                      draw_info->ofsy,
                      draw_info->ofsx + draw_info->width,
                      draw_info->ofsy + draw_info->height,
                      draw_info->ofsx,
                      draw_info->ofsy,
                      draw_info->ofsx + draw_info->width,
                      draw_info->ofsy + draw_info->height,
                      GL_COLOR_BUFFER_BIT,
                      GL_LINEAR);

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }

 private:
  std::list<std::vector<XrSwapchainImageOpenGLKHR>> m_image_cache;
  GLuint m_fbo{0};
};

#ifdef WIN32
class VAMR_GraphicsBindingD3D : public VAMR_IGraphicsBinding {
 public:
  ~VAMR_GraphicsBindingD3D()
  {
    if (m_shared_resource) {
      m_ghost_ctx->disposeSharedOpenGLResource(m_shared_resource);
    }
  }

  bool checkVersionRequirements(GHOST_Context *ghost_ctx,
                                XrInstance instance,
                                XrSystemId system_id,
                                std::string *r_requirement_info) const override
  {

    GHOST_ContextD3D *ctx_dx = static_cast<GHOST_ContextD3D *>(ghost_ctx);
    XrGraphicsRequirementsD3D11KHR gpu_requirements{XR_TYPE_GRAPHICS_REQUIREMENTS_D3D11_KHR};

    xrGetD3D11GraphicsRequirementsKHR(instance, system_id, &gpu_requirements);

    if (r_requirement_info) {
      std::ostringstream strstream;
      strstream << "Min DirectX 11 Feature Level " << gpu_requirements.minFeatureLevel
                << std::endl;

      *r_requirement_info = std::move(strstream.str());
    }

    return ctx_dx->m_device->GetFeatureLevel() >= gpu_requirements.minFeatureLevel;
  }

  void initFromGhostContext(GHOST_Context *ghost_ctx) override
  {
    GHOST_ContextD3D *ctx_d3d = static_cast<GHOST_ContextD3D *>(ghost_ctx);

    oxr_binding.d3d11.type = XR_TYPE_GRAPHICS_BINDING_D3D11_KHR;
    oxr_binding.d3d11.device = ctx_d3d->m_device;
    m_ghost_ctx = ctx_d3d;
  }

  bool chooseSwapchainFormat(const std::vector<int64_t> &runtime_formats,
                             int64_t *r_result) const override
  {
    std::vector<int64_t> gpu_binding_formats = {DXGI_FORMAT_R8G8B8A8_UNORM};
    return choose_swapchain_format_from_candidates(gpu_binding_formats, runtime_formats, r_result);
  }

  std::vector<XrSwapchainImageBaseHeader *> createSwapchainImages(uint32_t image_count) override
  {
    std::vector<XrSwapchainImageD3D11KHR> d3d_images(image_count);
    std::vector<XrSwapchainImageBaseHeader *> base_images;

    // Need to return vector of base header pointers, so of a different type. Need to build a new
    // list with this type, and keep the initial one alive.
    for (XrSwapchainImageD3D11KHR &image : d3d_images) {
      image.type = XR_TYPE_SWAPCHAIN_IMAGE_D3D11_KHR;
      base_images.push_back(reinterpret_cast<XrSwapchainImageBaseHeader *>(&image));
    }

    // Keep alive.
    m_image_cache.push_back(std::move(d3d_images));

    return base_images;
  }

  void submitToSwapchain(XrSwapchainImageBaseHeader *swapchain_image,
                         const VAMR_DrawViewInfo *draw_info) override
  {
    XrSwapchainImageD3D11KHR *d3d_swapchain_image = reinterpret_cast<XrSwapchainImageD3D11KHR *>(
        swapchain_image);

#  if 0
    /* Ideally we'd just create a render target view for the OpenXR swapchain image texture and
     * blit from the OpenGL context into it. The NV_DX_interop extension doesn't want to work with
     * this though. At least not with Optimus hardware. See:
     * https://github.com/mpv-player/mpv/issues/2949#issuecomment-197262807.
     */

    ID3D11RenderTargetView *rtv;
    CD3D11_RENDER_TARGET_VIEW_DESC rtv_desc(D3D11_RTV_DIMENSION_TEXTURE2D,
                                            DXGI_FORMAT_R8G8B8A8_UNORM);

    m_ghost_ctx->m_device->CreateRenderTargetView(d3d_swapchain_image->texture, &rtv_desc, &rtv);
    if (!m_shared_resource) {
      m_shared_resource = m_ghost_ctx->createSharedOpenGLResource(
          draw_info->width, draw_info->height, rtv);
    }
    m_ghost_ctx->blitFromOpenGLContext(m_shared_resource, draw_info->width, draw_info->height);
#  else
    if (!m_shared_resource) {
      m_shared_resource = m_ghost_ctx->createSharedOpenGLResource(draw_info->width,
                                                                  draw_info->height);
    }
    m_ghost_ctx->blitFromOpenGLContext(m_shared_resource, draw_info->width, draw_info->height);

    m_ghost_ctx->m_device_ctx->OMSetRenderTargets(0, nullptr, nullptr);
    m_ghost_ctx->m_device_ctx->CopyResource(d3d_swapchain_image->texture,
                                            m_ghost_ctx->getSharedTexture2D(m_shared_resource));
#  endif
  }

 private:
  GHOST_ContextD3D *m_ghost_ctx;
  GHOST_SharedOpenGLResource *m_shared_resource;
  std::list<std::vector<XrSwapchainImageD3D11KHR>> m_image_cache;
};
#endif  // WIN32

std::unique_ptr<VAMR_IGraphicsBinding> VAMR_GraphicsBindingCreateFromType(
    VAMR_GraphicsBindingType type)
{
  switch (type) {
    case VAMR_GraphicsBindingTypeOpenGL:
      return std::unique_ptr<VAMR_GraphicsBindingOpenGL>(new VAMR_GraphicsBindingOpenGL());
#ifdef WIN32
    case VAMR_GraphicsBindingTypeD3D11:
      return std::unique_ptr<VAMR_GraphicsBindingD3D>(new VAMR_GraphicsBindingD3D());
#endif
    default:
      return nullptr;
  }
}
