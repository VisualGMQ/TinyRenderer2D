#ifndef RENDER_HPP
#define RENDER_HPP

#include <vector>
#include <array>
#include <cmath>

#define GLEW_STATIC
#include "GL/glew.h"

#include "vmath.hpp"
#include "program.hpp"
#include "tool.hpp"
#include "texture.hpp"
#include "log.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

namespace tinyrender2d {

using std::vector;

class Render final {
 public:
    Render(int window_width, int window_height);
    ~Render();
    // some setter and getter function
    Color GetClearColor() const { return clear_color_; }
    void SetClearColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a = 255);
    void SetClearColor(const Color& color);

    Color GetDrawColor() const { return draw_color_; }
    void SetDrawColor(uint8_t r, uint8_t g, uint8_t b);
    void SetDrawColorOpacity(uint8_t opacity);

    Color GetFillColor() const {return fill_color_; }
    void SetFillColor(uint8_t r, uint8_t g, uint8_t b);
    void SetFillColorOpacity(uint8_t opacity);

    void SetViewport(int x, int y, int w, int h);
    void SetDrawableSize(int w, int h);

    void SetPointSize(uint32_t size);
    
    // some draw function
    void DrawLine(int x1, int y1, int x2, int y2);
    void DrawLine(const Point& p1, const Point& p2);

    void DrawLines(const Point* points, int num);
    void DrawLines(const vector<Point>& points);

    void DrawRect(int x, int y, int w, int h);
    void DrawRect(const Rect& rect);
    
    void DrawPolygon(Point* points, int num);
    void DrawPolygon(vector<Point>& points);
    void DrawPolygon(ColorfulPoint* points, int num);
    void DrawPolygon(vector<ColorfulPoint>& points);

    void DrawCircle(int x, int y, int radius);

    void DrawPoint(int x, int y);

    void DrawTexture(Texture* texture, const Rect* src_rect, const Rect* dst_rect, const Color* color = nullptr, float degree = 0, FlipType flip = FLIP_NONE);

    // some other functions
    void Clear();
    void SetTarget(Texture* texture);

 private:
    GLuint vbo_ = 0;
    GLuint ebo_ = 0;
    GLuint vao_ = 0;

    glm::mat4 screen_proj_ = glm::mat4(1.0f);
    glm::mat4 current_proj_ = glm::mat4(1.0f);
    bool is_at_default_framebuffer = true;

    Color draw_color_;
    Color fill_color_;
    Color clear_color_;

    Size drawable_size_;
    Size window_size_;

    Program* geo_pure_color_program_ = nullptr;
    Program* geo_colorful_program_ = nullptr;
    Program* texture_program_ = nullptr;

    // Program* test_program_ = nullptr;

    void useGeomentryPureColorProgram() {
        glUseProgram(geo_pure_color_program_->GetProgram());
    }

    void useGeomentryColorfulProgram() {
        glUseProgram(geo_colorful_program_->GetProgram());
    }

    void useTextureProgram() {
        glUseProgram(texture_program_->GetProgram());
    }

    void destroy();
};

Render* CreateRender(int window_width, int window_height);
void DestroyRender(Render* render);

}; // NAMESPACE tinyrender2d

#endif
