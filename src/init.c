#include "init.h"
#include "app.h"

#include <stdio.h>
#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <SDL2/SDL_image.h>


// Fényforrás struktúra
    Light light;


    bool init_sdl() {
// SDL inicializálása
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            fprintf(stderr, "SDL hibas inditas: %s\n", SDL_GetError());
            return 0; // Hibás inicializálás
        }
        return 1; // Sikeres inicializálás
    }

    int init(App* app) {
// SDL inicializálása
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            fprintf(stderr, "SDL inicializálási hiba: %s\n", SDL_GetError());
            return 1;
        }

        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

        app -> window = SDL_CreateWindow("3D Jelenet", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        if (app -> window == NULL) {
            fprintf(stderr, "Ablak létrehozási hiba: %s\n", SDL_GetError());
            return 1;
        }

        app -> gl_context = SDL_GL_CreateContext(app ->window);
        if (app -> gl_context == NULL) {
            fprintf(stderr, "OpenGL kontextus létrehozási hiba: %s\n", SDL_GetError());
            return 1;
        }

// IMG inicializálás a textúrákhoz
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags)) {
            fprintf(stderr, "SDL_image inicializálási hiba: %s\n", IMG_GetError());
            return 1;
        }

// OpenGL beállítások
        glShadeModel(GL_SMOOTH);
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClearDepth(1.0f);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
        glEnable(GL_TEXTURE_2D);

// Fényezés engedélyezése és anyag beállítás
        glEnable(GL_LIGHTING);
        glEnable(GL_COLOR_MATERIAL);
        glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

// Fényforrás paraméterek beállítása
        light.id = GL_LIGHT0;
        light.position[0] = 1.0f;
        light.position[1] = 1.0f;
        //light.position[2] = 1.0f;
        //light.position[3] = 1.0f;

        light.ambient[0] = 0.2f; 
        light.ambient[1] = 0.2f; 
        //light.ambient[2] = 0.2f; 
        //light.ambient[3] = 1.0f;
        light.diffuse[0] = 1.0f; 
        light.diffuse[1] = 1.0f; 
        //light.diffuse[2] = 1.0f; 
        //light.diffuse[3] = 1.0f;
        light.specular[0] = 1.0f; 
        light.specular[1] = 1.0f; 
        //light.specular[2] = 1.0f; 
        //light.specular[3] = 1.0f;

        init_light(&light);

        return 0;
    }


    void cleanup() {
        // SDL megfelelő felszabadítása
        SDL_Quit();
    }
