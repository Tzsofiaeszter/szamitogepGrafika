#include "pong.h"

void init_pong(Pong* pong, int width, int height)
{
    pong->width = width;
    pong->height = height;
//új rész
    pong-> left_pad = 0;
    pong-> right_pad = 0;
//új rész vége
    init_pad(&(pong->left_pad), 0, height, RED_THEME);
    init_pad(&(pong->right_pad), width - 50, height, GREEN_THEME);
    init_ball(&(pong->ball), width / 2, height / 2);
}

void update_pong(Pong* pong, double time)
{
    update_pad(&(pong->left_pad), time);
    update_pad(&(pong->right_pad), time);
    update_ball(&(pong->ball), time);
    bounce_ball(pong);
}

void render_pong(Pong* pong)
{
    render_pad(&(pong->left_pad));
    render_pad(&(pong->right_pad));
    render_ball(&(pong->ball));
//új rész
    char score_text[50];
    sprintf(score_text, "Left: %d, Right: %d", pong->left_score, pong->right_score);
    render_text(score_text, pong->width / 2- 50, pong->height - 20);
//új rész vége
}

void set_left_pad_position(Pong* pong, float position)
{
    set_pad_position(&(pong->left_pad), position);
}

void set_left_pad_speed(Pong* pong, float speed)
{
    set_pad_speed(&(pong->left_pad), speed);
}

void set_right_pad_position(Pong* pong, float position)
{
    set_pad_position(&(pong->right_pad), position);
}

void set_right_pad_speed(Pong* pong, float speed)
{
    set_pad_speed(&(pong->right_pad), speed);
}

void bounce_ball(Pong* pong)
//újításokat tartalmaz!!
{
    Ball* ball = &(pon->ball);
    if (pong->ball.x - pong->ball.radius < 50 && ball->y >= pong->left_pad.y && ball->y <= pong->left_pad.y + pong->left_pad.height) {
        pong->ball.x = pong->ball.radius + 50;
        pong->ball.speed_x *= -1.1;
        pong->ball.rotaion_speed *= 1.2;
        {
            else if(ball->x - ball->radius < 0){
                pong->right_score++;
                init_ball(ball, pong->width / 2, pong->height / 2);
            }
        }
    }
    if (pong->ball.x + pong->ball.radius > pong->width - 50 && ball->y >= pong->right_pad.y && ball->y <= pong->right_pad.y + pong->right_pad.height) {
        pong->ball.x = pong->width - pong->ball.radius - 50;
        pong->ball->speed_x *= -1.1;
        pong->ball->rotation_speed *= 1.2;
    } else if (ball->x + ball->radius > pong->width) {
        pong->left_score++;
        init_ball(ball, pong->width / 2, pong->height / 2);
    }
        
    if (ball->y - ball->radius < 0 || ball->y + ball->radius > pong->height) {
        ball->speed_y *= -1;
    }
    
}

//új rész
void update_ball(Ball* ball, double time)
{
    ball->x += ball->speed_x * time;
    ball->y += ball->speed_y * time;
    ball->rotation += ball->rotation_speed * time;
}

void render_ball(Ball* ball)
{
    glPushMatrix();
    glTranslatef(ball->x, ball->y, 0.0);
    glRotatef(ball->rotation, 0.0, 0.0, 1.0);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0, 0.9, 0.8);
    glVertex2f(0, 0);
    for (double angle = 0; angle < 2 * M_PI; angle += 0.2) {
        glVertex2f(cos(angle) * ball->radius, sin(angle) * ball->radius);
    }
    glEnd();
    glPopMatrix();
}


