#include "app.hpp"
#include "tinyrenderer2d/tool.hpp"

using namespace tinyrenderer2d;

class Snapshot: public App {
 public:
    Snapshot() {
        house_ = LoadTexture(render_, tinyrenderer2d::TEXTURE_TYPE_STATIC, "test_resources/house.png");
    }

    virtual ~Snapshot() {
        DestroyTexture(house_);
    }

 private:
    Texture* house_ = nullptr;

    void step() override {
        Rect rect = {100, 10, house_->GetSize().w, house_->GetSize().h};
        render_->DrawTexture(house_, nullptr, &rect);
        rect.x = 400;
        Color color = {100, 100, 0, 255};
        render_->DrawTexture(house_, nullptr, &rect, &color);
        rect.x = 100;
        rect.y = 400;
        rect.w = rect.w*0.5;
        rect.h = rect.h*0.5;
        render_->DrawTexture(house_, nullptr, &rect);
        rect.x = 300;
        render_->DrawTexture(house_, nullptr, &rect, nullptr, 30);
        rect.x = 500;
        render_->DrawTexture(house_, nullptr, &rect, nullptr, 0, FLIP_VERTICAL);
    }
};

int main(int argc, char** argv) {
    Snapshot app;
    app.MainLoop();
    return 0;
}
