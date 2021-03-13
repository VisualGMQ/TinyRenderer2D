#include <vector>
#include "app.hpp"

class DrawShapes: public App {
public:
    ~DrawShapes() = default;

private:
    void step() override {
        drawLine();
        drawRect();
        drawCircle();
        drawPoint();
        drawPolygon();
    }

    void drawLine() {
        render_->SetDrawColor(255, 0, 0);
        render_->DrawLine(100, 100, 100, 200);

        tinyrender2d::Point points[] = {
            {150, 50},
            {200, 100},
            {250, 50}
        };
        render_->DrawLines(points, 3);
    }

    void drawRect() {
        render_->SetDrawColor(200, 0, 100);

        render_->SetFillColor(200, 200, 0);
        render_->SetFillColorOpacity(100);
        render_->DrawRect(400, 400, 100, 50);

        render_->SetFillColor(0, 200, 200);
        render_->SetFillColorOpacity(100);
        render_->DrawRect(425, 425, 100, 50);

        render_->SetFillColorOpacity(255);

        int w = 20, h = 10;
        render_->DrawRect(2, 2, w, h);
        render_->DrawRect(WindowWidth-w+2, 2, w, h);
        render_->DrawRect(2, WindowHeight-h+2, w, h);
        render_->DrawRect(WindowWidth-w+2, WindowHeight-h+2, w, h);
    }

    void drawCircle() {
        render_->SetFillColorOpacity(100);
        render_->SetFillColor(0, 0, 255);
        render_->DrawCircle(500, 500, 50);

        render_->SetFillColorOpacity(255);
    }

    void drawPoint() {
        render_->SetPointSize(20);
        render_->SetDrawColor(0, 0, 255);
        render_->DrawPoint(50, 400);
    }

    void drawPolygon() {
        // make sure points are clockwise
        tinyrender2d::Point points[] = {
            {100, 200},
            {200, 200},
            {200, 300},
            {100, 400},
        };
        render_->SetDrawColor(0, 0, 0);
        render_->SetFillColor(0, 255, 0);
        render_->SetFillColorOpacity(255);
        render_->DrawPolygon(points, 4);

        tinyrender2d::ColorfulPoint color_points[] = {
            {{250, 200}, {255, 0, 0, 255}},
            {{350, 200}, {0, 255, 0, 255}},
            {{350, 300}, {0, 0, 255, 255}},
            {{250, 400}, {100, 100, 100, 255}}
        };
        render_->DrawPolygon(color_points, 4);
    }
};

int main(int argc, char** argv) {
    DrawShapes app;
    app.MainLoop();
    return 0;
}
