#include "camera.h"
#include <GL/gl.h>
#include <math.h>

void init_camera(Camera* camera)
{
    camera->position.x = 0.0;
    camera->position.y = 0.0;
    camera->position.z = 2.0;
    camera->rotation.x = 0.0;
    camera->rotation.y = 0.0;
    camera->rotation.z = 0.0;
    camera->speed.x = 0.0;
    camera->speed.y = 0.0;
    camera->speed.z = 0.0;
}

void update_camera(Camera* camera, double time)
{
    double angle;
    double side_angle;

    angle = degree_to_radian(camera->rotation.z);
    side_angle = degree_to_radian(camera->rotation.z + 90.0);

    camera->position.x += cos(angle) * camera->speed.y * time;
    camera->position.y += sin(angle) * camera->speed.y * time;
    camera->position.x += cos(side_angle) * camera->speed.x * time;
    camera->position.y += sin(side_angle) * camera->speed.x * time;
    camera->position.z += camera->speed.z * time;  // Q és E mozgatás
}

void handle_camera_input(Camera* camera, int key)
{
    switch (key) {
        case 'q': camera->speed.z = 1.0; break;
        case 'e': camera->speed.z = -1.0; break;
        case 'j': camera->rotation.z -= 2.0; break;
        case 'l': camera->rotation.z += 2.0; break;
    }
}

void render_scene(const Scene* scene)
{
    draw_origin();
    draw_colored_triangle();
    draw_tessellated_sphere();
    draw_chessboard();
    draw_cylinder();
    draw_cone();
}

void draw_colored_triangle()
{
    glBegin(GL_TRIANGLES);
    glColor3f(1, 1, 0);
    glVertex3f(-0.5, -0.5, 0);
    glColor3f(0, 1, 1);
    glVertex3f(0.5, -0.5, 0);
    glColor3f(1, 0, 1);
    glVertex3f(0, 0.5, 0);
    glEnd();
}

void draw_tessellated_sphere()
{
    int slices = 10;
    int stacks = 10;
    double radius = 0.5;
    for (int i = 0; i < slices; i++) {
        for (int j = 0; j < stacks; j++) {
            double theta1 = i * (M_PI / slices);
            double theta2 = (i + 1) * (M_PI / slices);
            double phi1 = j * (2 * M_PI / stacks);
            double phi2 = (j + 1) * (2 * M_PI / stacks);
            glBegin(GL_TRIANGLE_STRIP);
            glColor3f(0.5, 0.5, 0.5);
            glVertex3f(radius * sin(theta1) * cos(phi1), radius * cos(theta1), radius * sin(theta1) * sin(phi1));
            glVertex3f(radius * sin(theta2) * cos(phi1), radius * cos(theta2), radius * sin(theta2) * sin(phi1));
            glVertex3f(radius * sin(theta1) * cos(phi2), radius * cos(theta1), radius * sin(theta1) * sin(phi2));
            glVertex3f(radius * sin(theta2) * cos(phi2), radius * cos(theta2), radius * sin(theta2) * sin(phi2));
            glEnd();
        }
    }
}

void draw_chessboard()
{
    int size = 8;
    for (int x = 0; x < size; x++) {
        for (int y = 0; y < size; y++) {
            glBegin(GL_QUADS);
            glColor3f((x + y) % 2, (x + y) % 2, (x + y) % 2);
            glVertex3f(x, y, 0);
            glVertex3f(x + 1, y, 0);
            glVertex3f(x + 1, y + 1, 0);
            glVertex3f(x, y + 1, 0);
            glEnd();
        }
    }
}

void draw_cylinder()
{
    int segments = 20;
    double radius = 0.3;
    double height = 1.0;
    glBegin(GL_TRIANGLE_STRIP);
    for (int i = 0; i <= segments; i++) {
        double angle = (i * 2 * M_PI) / segments;
        glVertex3f(radius * cos(angle), radius * sin(angle), 0);
        glVertex3f(radius * cos(angle), radius * sin(angle), height);
    }
    glEnd();
}

void draw_cone()
{
    int segments = 20;
    double radius = 0.3;
    double height = 1.0;
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(0, 0, height);
    for (int i = 0; i <= segments; i++) {
        double angle = (i * 2 * M_PI) / segments;
        glVertex3f(radius * cos(angle), radius * sin(angle), 0);
    }
    glEnd();
}

void set_view(const Camera* camera)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(-(camera->rotation.x + 90), 1.0, 0, 0);
    glRotatef(-(camera->rotation.z - 90), 0, 0, 1.0);
    glTranslatef(-camera->position.x, -camera->position.y, -camera->position.z);
}

void rotate_camera(Camera* camera, double horizontal, double vertical)
{
    camera->rotation.z += horizontal;
    camera->rotation.x += vertical;

    if (camera->rotation.z < 0) {
        camera->rotation.z += 360.0;
    }

    if (camera->rotation.z > 360.0) {
        camera->rotation.z -= 360.0;
    }

    if (camera->rotation.x < 0) {
        camera->rotation.x += 360.0;
    }

    if (camera->rotation.x > 360.0) {
        camera->rotation.x -= 360.0;
    }
}

void set_camera_speed(Camera* camera, double speed)
{
    camera->speed.y = speed;
}

void set_camera_side_speed(Camera* camera, double speed)
{
    camera->speed.x = speed;
}

