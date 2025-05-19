#ifndef CAMERA_H
#define CAMERA_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include "model.h"
#include <stdbool.h>


typedef struct {
   Vec3 position;
    Vec3 rotation;
    Vec3 speed;
   bool is_preview_visible;
} Camera;

void init_camera(Camera* camera);
void update_camera(Camera* camera, double time);
void set_view(const Camera* camera);
void rotate_camera(Camera* camera, double horizontal, double vertical);
void set_camera_speed(Camera* camera, double speed);
void set_camera_side_speed(Camera* camera, double speed);
void show_texture_preview();

#endif



