#include "tinyrender2d/render.hpp"
#include "tinyrender2d/texture.hpp"
#include "tinyrender2d/tool.hpp"

#include <cassert>

#include "app.hpp"

class DrawTexture: public App {
 public:
    DrawTexture() {
        cloth_ = tinyrender2d::LoadTexture("test_resources/cloth1.png");
        assert(cloth_);
        Log("cloth_ size: %d, %d", cloth_->GetSize().w, cloth_->GetSize().h);
        cube_ = tinyrender2d::LoadTexture("test_resources/cube_man.png");
        assert(cube_);
        icons_ = tinyrender2d::LoadTexture("test_resources/icons.png");
    }

    virtual ~DrawTexture() {
        tinyrender2d::DestroyTexture(cloth_);
        tinyrender2d::DestroyTexture(cube_);
        tinyrender2d::DestroyTexture(icons_);
    }

 private:
    tinyrender2d::Texture* cloth_ = nullptr;
    tinyrender2d::Texture* cube_ = nullptr;
    tinyrender2d::Texture* icons_ = nullptr;

    void step() override {
        static float angle = 0;

        tinyrender2d::Rect dst_rect = {0, 0, cloth_->GetSize().w*2, cloth_->GetSize().h*2};
        render_->DrawTexture(cloth_, nullptr, dst_rect);
        dst_rect.y = 200;
        if (angle >= 360)
            angle = 0;
        render_->DrawTexture(cloth_, nullptr, dst_rect, nullptr, angle);
        angle += 10;

        tinyrender2d::Rect src_rect = {0, 0, 90, 90};
        dst_rect.x = 600;
        dst_rect.y = 200;
        dst_rect.w = 90;
        dst_rect.h = 90;
        tinyrender2d::Color color = {0, 200, 0, 255};

        render_->DrawTexture(icons_, &src_rect, dst_rect, &color, 0, tinyrender2d::FLIP_BOTH);
        src_rect.x = 184;
        src_rect.y = 92;
        src_rect.w = 90;
        src_rect.h = 90;
        dst_rect = src_rect;
        dst_rect.x = 600;
        dst_rect.y = 400;
        render_->DrawTexture(icons_, &src_rect, dst_rect, nullptr, 0, tinyrender2d::FLIP_VERTICAL);

        // cloth_->ResetSize();
        // render_->DrawTexture(cloth_, 100, 100);
        // cloth_->Resize(100, 100);
        // render_->DrawTexture(cloth_, 200, 200);
        // cloth_->ResetSize();
        // cloth_->SetRotation(30);
        // render_->DrawTexture(cloth_, 300, 200);
        // cloth_->SetFlipVertical();
        // render_->DrawTexture(cloth_, 300, 200);

        // cube_->SetKeycolor(125, 125, 125);
        // render_->DrawTexture(cube_, 300, 200);
        // cube_->SetColor(0, 255, 0);
        // render_->DrawTexture(cube_, 300, 200);
    }
};

int main(int argc, char** argv) {
    DrawTexture app;
    app.MainLoop();
    return 0;
}
