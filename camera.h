#ifndef CAMERA_H
#define CAMERA_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "utils.h"
#include <stdbool.h>

typedef struct Camera{
    vec3 position;
    vec3 rotation;
    vec3 speed;

    bool is_preview_visible;
} Camera;


void initCamera(Camera *camera);

void updateCamera(Camera *camera, const SDL_Event *event);

void set_view(const Camera* camera);

void setProjection(const Camera *camera, int width, int height);

void rotate_camera(Camera* camera, double horizontal, double vertical);

void set_camera_speed(Camera* camera, double speed);

void set_camera_side_speed(Camera* camera, double speed);

#endif



