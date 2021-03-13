#include "tinyrender2d/texture.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace tinyrender2d {

Texture::~Texture() {
    stbi_image_free(data_);
}

Texture* LoadTexture(std::string filename) {
    int w, h, channels;
    unsigned char* data =stbi_load(filename.c_str(), &w, &h, &channels, 0);
    if (!data) {
        Log("%s can't load", filename.c_str());
        return nullptr;
    }
    Texture* texture = new Texture;
    texture->UpdateData(data, w, h);
    return texture;
}

void DestroyTexture(Texture* texture) {
    delete texture;
}

};
