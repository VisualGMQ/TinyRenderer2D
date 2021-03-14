#include "app.hpp"

#include <cassert>

class DrawTexture: public App {
 public:
    DrawTexture() {
        cloth_ = tinyrenderer2d::LoadTexture(render_, tinyrenderer2d::TEXTURE_TYPE_STATIC, "test_resources/cloth1.png");
        assert(cloth_);
        Log("cloth_ size: %d, %d", cloth_->GetSize().w, cloth_->GetSize().h);
        cube_ = tinyrenderer2d::LoadTexture(render_, tinyrenderer2d::TEXTURE_TYPE_TARGET, "test_resources/cube_man.png");
        assert(cube_);
        icons_ = tinyrenderer2d::LoadTexture(render_, tinyrenderer2d::TEXTURE_TYPE_TARGET, "test_resources/icons.png");
    }

    virtual ~DrawTexture() {
        tinyrenderer2d::DestroyTexture(cloth_);
        tinyrenderer2d::DestroyTexture(cube_);
        tinyrenderer2d::DestroyTexture(icons_);
    }

 private:
    tinyrenderer2d::Texture* cloth_ = nullptr;
    tinyrenderer2d::Texture* cube_ = nullptr;
    tinyrenderer2d::Texture* icons_ = nullptr;

    void step() override {
        static float angle = 0;

        tinyrenderer2d::Rect dst_rect = {0, 0, cloth_->GetSize().w*2, cloth_->GetSize().h*2};
        render_->DrawTexture(cloth_, nullptr, &dst_rect);
        dst_rect.y = 200;
        if (angle >= 360)
            angle = 0;
        render_->DrawTexture(cloth_, nullptr, &dst_rect, nullptr, angle);
        angle += 10;

        tinyrenderer2d::Rect src_rect = {0, 0, 90, 90};
        dst_rect.x = 600;
        dst_rect.y = 200;
        dst_rect.w = 90;
        dst_rect.h = 90;
        tinyrenderer2d::Color color = {0, 200, 0, 255};

        render_->DrawTexture(icons_, &src_rect, &dst_rect, &color, 0, tinyrenderer2d::FLIP_BOTH);
        src_rect.x = 184;
        src_rect.y = 92;
        src_rect.w = 90;
        src_rect.h = 90;
        dst_rect = src_rect;
        dst_rect.x = 600;
        dst_rect.y = 400;
        render_->DrawTexture(icons_, &src_rect, &dst_rect, nullptr, 0, tinyrenderer2d::FLIP_VERTICAL);
    }
};

int main(int argc, char** argv) {
    DrawTexture app;
    app.MainLoop();
    return 0;
}
