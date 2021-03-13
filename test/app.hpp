#ifndef APP_HPP
#define APP_HPP

#include "tinyrender2d/render.hpp"

#include "SDL.h"
#define GLEW_STATIC
#include "GL/glew.h"

constexpr int WindowWidth = 800;
constexpr int WindowHeight = 600;

class App {
 public:
    App() {
        initSDL();
        Log("inited SDL");
        createRender();
        Log("created render");
    }

    void MainLoop() {
        while (!should_quit_) {
            render_->SetClearColor(120, 120, 120, 255);
            render_->Clear();
            while (SDL_PollEvent(&event_)) {
                if (event_.type == SDL_QUIT)
                    Exit();
            }
            step();
            SDL_GL_SwapWindow(window_);
            SDL_Delay(30);
        }
    }

    void Exit() {
        should_quit_ = true;
        Log("want quit app");
    }

    virtual ~App() {
        destroyRender();
        Log("destroyed render");
        quitSDL();
        Log("quit sdl");
    }

 protected:
    SDL_Window* window_ = nullptr;
    tinyrender2d::Render* render_;

 private:
    SDL_Event event_;
    bool should_quit_ = false;

    void initSDL() {
        SDL_Init(SDL_INIT_EVERYTHING);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
        window_ = SDL_CreateWindow(
                "hello world",
                SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                WindowWidth, WindowHeight,
                SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL);
        if (!window_)
            throw std::runtime_error("window create failed");
        SDL_GL_CreateContext(window_);
        glewInit();
    }

    virtual void step() {

    }

    void createRender() {
        render_ = tinyrender2d::CreateRender(WindowWidth, WindowHeight);
    }

    void destroyRender() {
        tinyrender2d::DestroyRender(render_);
    }

    void quitSDL() {
        SDL_Quit();
    }
};

#endif
