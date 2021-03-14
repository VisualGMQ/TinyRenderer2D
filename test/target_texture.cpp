#include <vector>
#include "app.hpp"

constexpr int PanelWidth = 400;
constexpr int PanelHeight = 600;

class TargetTexture: public App {
public:
    TargetTexture() {
        panel_ = tinyrenderer2d::CreateTexture(render_, tinyrenderer2d::TEXTURE_TYPE_TARGET, PanelWidth, PanelHeight);

        render_->SetTarget(panel_);
        render_->SetClearColor(255, 255, 255);
        render_->Clear();

        int w = 20, h = 10;
        render_->SetFillColor(0, 200, 0);
        render_->SetDrawColor(200, 0, 100);
        render_->DrawRect(0, 0, w, h);
        render_->DrawRect(PanelWidth-w, 0, w, h);
        render_->DrawRect(0, PanelHeight-h, w, h);
        render_->DrawRect(PanelWidth-w, PanelHeight-h, w, h);
        render_->SetTarget(nullptr);

        texture_ = tinyrenderer2d::LoadTexture(render_, tinyrenderer2d::TEXTURE_TYPE_STATIC, "test_resources/cube_man.png");
    }

    ~TargetTexture() {
        tinyrenderer2d::DestroyTexture(panel_);
        tinyrenderer2d::DestroyTexture(texture_);
    }

private:
    tinyrenderer2d::Texture* panel_ = nullptr;
    tinyrenderer2d::Texture* texture_ = nullptr;

    void step() override {
        tinyrenderer2d::Rect rect = {0, 0, panel_->GetSize().w, panel_->GetSize().h};
        render_->DrawTexture(panel_, nullptr, &rect);
        rect.w = texture_->GetSize().w;
        rect.h = texture_->GetSize().h;
        rect.x = WindowWidth/2-rect.w/2;
        rect.y = WindowHeight/2-rect.h/2;
        render_->DrawTexture(texture_, nullptr, &rect);
    }
};

int main(int argc, char** argv) {
    TargetTexture app;
    app.MainLoop();
    return 0;
}
