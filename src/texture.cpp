#include "tinyrender2d/texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace tinyrender2d {

Texture::Texture(Render* render, TextureType type, int w, int h) {
    if (w > 0 && h > 0) {
        glGenTextures(1, &tex_);
        glBindTexture(GL_TEXTURE_2D, tex_);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        if (type == TEXTURE_TYPE_TARGET) {
            glGenFramebuffers(1, &fbo_);
            glBindFramebuffer(GL_FRAMEBUFFER, fbo_);
            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex_, 0);
            if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
                Log("framebuffer create incomplete");
            }
            glBindFramebuffer(GL_FRAMEBUFFER, 0);
        }
        size_.w = w;
        size_.h = h;
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindTexture(GL_FRAMEBUFFER, 0);
}

void Texture::UpdateData(unsigned char* data, int w, int h, PixelFormat format) {
    glBindTexture(GL_TEXTURE_2D, tex_);
    if (format == PIXEL_FORMAT_RGB888) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    } else if (format == PIXEL_FORMAT_RGBA8888) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    } else {
        Log("Unknown image channels");
    }
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture() {
    glDeleteTextures(1, &tex_);
    glDeleteFramebuffers(1, &fbo_);
}

Texture* CreateTexture(Render* render, TextureType type, int w, int h) {
    Texture* texture = new Texture(render, type, w, h);
    return texture;
}

Texture* LoadTexture(Render* render, TextureType type, std::string filename) {
    int w, h, channels;
    unsigned char* data = stbi_load(filename.c_str(), &w, &h, &channels, 0);
    Log("channels:%d", channels);
    if (!data) {
        Log("%s can't load", filename.c_str());
        return nullptr;
    }
    Texture* texture = CreateTexture(render, type, w, h);
    if (channels == 4) {
        texture->UpdateData(data, w, h, PIXEL_FORMAT_RGBA8888);
    } else {
        texture->UpdateData(data, w, h, PIXEL_FORMAT_RGB888);
    }
    stbi_image_free(data);
    return texture;
}

void DestroyTexture(Texture* texture) {
    delete texture;
}

};
