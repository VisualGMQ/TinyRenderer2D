#include "tinyrender2d/render.hpp"
#include "tinyrender2d/tool.hpp"

namespace tinyrender2d {

Render::Render() {
    glGenBuffers(1, &vbo_);
    glGenBuffers(1, &ebo_);
    glGenVertexArrays(1, &vao_);
    glGenTextures(1, &tex_);
    Log("buffers create OK");

    glBindTexture(GL_TEXTURE_2D, tex_);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    Log("texture configure OK");

    Shader geo_vertex_shader(ShaderType::VERTEX_SHADER, ReadShaderFile("shader/geo_shader_pure_color.vert")),
           geo_frag_shader(ShaderType::FRAGMENT_SHADER, ReadShaderFile("shader/geo_shader_pure_color.frag"));
    geo_pure_color_program_ = new Program(geo_vertex_shader, geo_frag_shader);
    Log("geometry pure color program create OK");

    Shader geo_colorful_vert(ShaderType::VERTEX_SHADER, ReadShaderFile("shader/geo_colorful_shader.vert")),
           geo_colorful_frag(ShaderType::FRAGMENT_SHADER, ReadShaderFile("shader/geo_colorful_shader.frag"));
    geo_colorful_program_ = new Program(geo_colorful_vert, geo_colorful_frag);
    Log("geometry colorful program create OK");

    Shader tex_vertex_shader(ShaderType::VERTEX_SHADER, ReadShaderFile("shader/tex_shader.vert")),
           tex_frag_shader(ShaderType::FRAGMENT_SHADER, ReadShaderFile("shader/tex_shader.frag"));
    texture_program_ = new Program(tex_vertex_shader, tex_frag_shader);
    Log("texture program create OK");

    // Shader test_vertex_shader(ShaderType::VERTEX_SHADER, ReadShaderFile("shader/test.vert")),
    //        test_frag_shader(ShaderType::FRAGMENT_SHADER, ReadShaderFile("shader/test.frag"));
    // test_program_ = new Program(test_vertex_shader, test_frag_shader);
    // Log("texture program create OK");

    clear_color_.r = 0;
    clear_color_.g = 0;
    clear_color_.b = 0;
    clear_color_.a = 255;

    SetFillColorOpacity(255);
    SetDrawColorOpacity(255);

    glEnable(GL_BLEND);
    glEnable(GL_PROGRAM_POINT_SIZE);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
};

void Render::SetClearColor(const Color& color) {
    SetClearColor(color.r, color.g, color.b, color.a);
}

void Render::SetClearColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    glClearColor(r/255.0, g/255.0, b/255.0, a/255.0);
}

void Render::SetDrawColor(uint8_t r, uint8_t g, uint8_t b) {
    draw_color_.r = r;
    draw_color_.g = g;
    draw_color_.b = b;
}

void Render::SetDrawColorOpacity(uint8_t opacity) {
    draw_color_.a = opacity;
}

void Render::SetFillColor(uint8_t r, uint8_t g, uint8_t b) {
    fill_color_.r = r;
    fill_color_.g = g;
    fill_color_.b = b;
}

void Render::SetFillColorOpacity(uint8_t opacity) {
    fill_color_.a = opacity;
}

void Render::SetViewport(int x, int y, int w, int h) {
    glViewport(x, y, w, h);
}

void Render::ClearScreen() {
    glClear(GL_COLOR_BUFFER_BIT);
}

void Render::SetDrawableSize(int w, int h) {
    proj_ = glm::ortho(0.0f, static_cast<float>(w), static_cast<float>(h), 0.0f, -1.0f, 1.0f);
    drawable_size_.w = w;
    drawable_size_.h = h;
}

void Render::SetPointSize(uint32_t size) {
    glPointSize(size);
}

void Render::DrawLine(int x1, int y1, int x2, int y2) {
    Point data[2];
    data[0].x = x1;
    data[0].y = y1;
    data[1].x = x2;
    data[1].y = y2;

    DrawLines(data, 2);
}

void Render::DrawLine(const Point& p1, const Point& p2) {
    DrawLine(p1.x, p1.y, p2.x, p2.y);
}

void Render::DrawLines(const vector<Point>& points) {
    DrawLines(points.data(), points.size());
}

void Render::DrawLines(const Point* points, int num) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBindVertexArray(vao_);
    glBufferData(GL_ARRAY_BUFFER, num*sizeof(Point), points, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Point), (void*)0);
    glEnableVertexAttribArray(0);

    useGeomentryPureColorProgram();
    geo_pure_color_program_->UniformMat4f("proj", proj_);
    geo_pure_color_program_->UniformVec4i("fragColor256", draw_color_);
    
    glDrawArrays(GL_LINE_STRIP, 0, num);
}

void Render::DrawRect(int x, int y, int w, int h) {
    Point points[4];
    points[0].x = x;
    points[0].y = y;
    points[1].x = x+w;
    points[1].y = y;
    points[2].x = x+w;
    points[2].y = y+h;
    points[3].x = x;
    points[3].y = y+h;

    DrawPolygon(points, 4);
}
void Render::DrawRect(const Rect& rect) {
    DrawRect(rect.x, rect.y, rect.w, rect.h);
}

void Render::DrawPolygon(vector<Point>& points) {
    DrawPolygon(points.data(), points.size());
}

void Render::DrawPolygon(Point* points, int num) {
    if (num <= 2)
        return;

    useGeomentryPureColorProgram();

    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBindVertexArray(vao_);
    geo_pure_color_program_->UniformMat4f("proj", proj_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Point)*num, points, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Point), (void*)0);
    glEnableVertexAttribArray(0);

    // fill polygon
    if (fill_color_.a != 0) {
        geo_pure_color_program_->UniformVec4i("fragColor256", fill_color_);
        glDrawArrays(GL_TRIANGLE_FAN, 0, num);
    }
    
    // draw outline
    geo_pure_color_program_->UniformVec4i("fragColor256", draw_color_);
    glDrawArrays(GL_LINE_LOOP, 0, num);
}


void Render::DrawPolygon(vector<ColorfulPoint>& points) {
    DrawPolygon(points.data(), points.size());
}

void Render::DrawPolygon(ColorfulPoint* points, int num) {
    if (num <= 2)
        return;
    useGeomentryColorfulProgram();
    geo_colorful_program_->UniformMat4f("proj", proj_);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBindVertexArray(vao_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ColorfulPoint)*num, points, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(ColorfulPoint), (void*)offsetof(ColorfulPoint, point));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(ColorfulPoint), (void*)offsetof(ColorfulPoint, color));
    glEnableVertexAttribArray(1);

    if (fill_color_.a != 0) {
        glDrawArrays(GL_TRIANGLE_FAN, 0, num);
    }
}

void Render::DrawCircle(int x, int y, int radius) {
    float delta_radian = 2*glm::pi<float>()/100;
    vector<Point> points;

    float radian = 0;
    while (radian <= 2*glm::pi<float>()) {
        Point p;
        p.x = x+cos(radian)*radius;
        p.y = y+sin(radian)*radius;
        points.push_back(p);
        radian += delta_radian;
    }

    useGeomentryPureColorProgram();
    geo_pure_color_program_->UniformMat4f("proj", proj_);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBindVertexArray(vao_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Point)*points.size(), points.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Point), (void*)0);
    glEnableVertexAttribArray(0);

    // fill circle
    if (fill_color_.a != 0) {
        geo_pure_color_program_->UniformVec4i("fragColor256", fill_color_);
        glDrawArrays(GL_TRIANGLE_FAN, 0, points.size());
    }
    
    // draw outline
    geo_pure_color_program_->UniformVec4i("fragColor256", draw_color_);
    glDrawArrays(GL_LINE_LOOP, 0, points.size());
}

// FIXME can't work
void Render::DrawPoint(int x, int y) {
    float data[2];
    data[0] = x;
    data[1] = y;

    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBindVertexArray(vao_);
    glBufferData(GL_ARRAY_BUFFER, 2*sizeof(float), data, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    useGeomentryPureColorProgram();
    geo_pure_color_program_->UniformMat4f("proj", proj_);
    geo_pure_color_program_->UniformVec4i("fragColor256", draw_color_);

    glDrawArrays(GL_POINTS, 0, 1);
}

void Render::DrawTexture(Texture* texture, const Rect* src_rect, const Rect& dst_rect, const Color* color, float degree, FlipType flip) {
    useTextureProgram();
    float data[] = {
        0, 0, 0, 0,
        0, 1, 0, 1,
        1, 0, 1, 0,

        0, 1, 0, 1,
        1, 0, 1, 0,
        1, 1, 1, 1
    };

    int w = texture->GetSize().w,
        h = texture->GetSize().h;
    if (src_rect) {
        Point right_top = {
            (src_rect->x+src_rect->w)/static_cast<double>(w),
            (h-src_rect->y)/static_cast<double>(h)
        },
        left_bottom = {
            (src_rect->x)/static_cast<double>(w),
            (h-src_rect->y-src_rect->h)/static_cast<double>(h)
        };

        data[2] = left_bottom.x;
        data[3] = left_bottom.y;

        data[6] = left_bottom.x;
        data[7] = right_top.y;

        data[10] = right_top.x;
        data[11] = left_bottom.y;

        data[14] = left_bottom.x;
        data[15] = right_top.y;

        data[18] = right_top.x;
        data[19] = left_bottom.y;

        data[22] = right_top.x;
        data[23] = right_top.y;
    }

    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBindVertexArray(vao_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4*sizeof(float), 0);
    glEnableVertexAttribArray(0);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(dst_rect.x, dst_rect.y, 0));
    model = glm::translate(model, glm::vec3(dst_rect.w/2.0, dst_rect.h/2, 0));
    model = glm::rotate(model, glm::radians(degree), glm::vec3(0, 0, 1));
    model = glm::translate(model, glm::vec3(-dst_rect.w/2.0, -dst_rect.h/2.0, 0));
    float scale_x = dst_rect.w,
          scale_y = dst_rect.h;
    if (flip & FLIP_HORIZONTAL) {
        scale_x = -scale_x;
    }
    if (flip & FLIP_VERTICAL) {
        scale_y = -scale_y;
    }
    model = glm::scale(model, glm::vec3(scale_x, scale_y, 1));

    texture_program_->UniformMat4f("model", model);
    texture_program_->UniformMat4f("proj", proj_);
    texture_program_->Uniform1i("Texture", 0);
    if (color) {
        texture_program_->Uniform3f("TextureColor256", color->r, color->g, color->b);
    } else {
        texture_program_->Uniform3f("TextureColor256", 255, 255, 255);
    }

    if (texture->GetData()) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->GetData());
        glActiveTexture(GL_TEXTURE0);

        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

}

Render::~Render() {
    destroy();
}

void Render::destroy() {
    delete geo_pure_color_program_;
    delete geo_colorful_program_;
    delete texture_program_;
    // delete test_program_;
    glDeleteBuffers(1, &vbo_);
    vbo_ = 0;
    glDeleteBuffers(1, &ebo_);
    ebo_ = 0;
    glDeleteVertexArrays(1, &vao_);
    vao_ = 0;
    glDeleteTextures(1, &tex_);
    tex_ = 0;
}

Render* CreateRender() {
    return new Render;
}

void DestroyRender(Render* render) {
    delete render;
}

};
