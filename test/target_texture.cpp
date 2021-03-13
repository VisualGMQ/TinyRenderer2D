#include <vector>
#include "app.hpp"

constexpr int PanelWidth = 400;
constexpr int PanelHeight = 600;

class TargetTexture: public App {
public:
    TargetTexture() {
        panel_ = tinyrender2d::CreateTexture(render_, tinyrender2d::TEXTURE_TYPE_TARGET, PanelWidth, PanelHeight);

    }

    ~TargetTexture() {
        tinyrender2d::DestroyTexture(panel_);
    }

private:
    tinyrender2d::Texture* panel_ = nullptr;

    void step() override {
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
        tinyrender2d::Rect rect = {0, 0, panel_->GetSize().w, panel_->GetSize().h};
        render_->DrawTexture(panel_, nullptr, &rect);
    }
};

int main(int argc, char** argv) {
    TargetTexture app;
    app.MainLoop();
    return 0;
}
