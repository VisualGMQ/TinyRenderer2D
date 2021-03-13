#ifndef TEXTURE_HPP
#define TEXTURE_HPP
#include <string>

#include "vmath.hpp"
#include "log.hpp"
#include "tool.hpp"

namespace tinyrender2d {

class Texture final {
 public:
    ~Texture();
    unsigned char* GetData() { return data_; }
    Size GetSize() const { return size_; }
    void UpdateData(unsigned char* data, int w, int h) {
        data_ = data;
        size_.w = w;
        size_.h = h;
    }

 private:
    unsigned char* data_ = nullptr;
    Size size_;
};

Texture* LoadTexture(std::string filename);
void DestroyTexture(Texture* texture);

};

#endif
