

#include <GL/glut.h>
#include <cmath>
#include <cstdlib>


namespace Scene1 {

#define SCENE1_CANVAS_W 900
#define SCENE1_CANVAS_H 600
#define SCENE1_WIN_W 1280
#define SCENE1_WIN_H 800


static void drawQuad(float x, float y, float w, float h, float r, float g, float b)
{
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
        glVertex2f(x,     y);
        glVertex2f(x + w, y);
        glVertex2f(x + w, y + h);
        glVertex2f(x,     y + h);
    glEnd();
}

static void drawQuadOutline(float x, float y, float w, float h, float r, float g, float b, float thick)
{
    glColor3f(r, g, b);
    glLineWidth(thick);
    glBegin(GL_LINE_LOOP);
        glVertex2f(x,     y);
        glVertex2f(x + w, y);
        glVertex2f(x + w, y + h);
        glVertex2f(x,     y + h);
    glEnd();
}

static void drawCircle(float cx, float cy, float radius, float r, float g, float b)
{
    const int SEGMENTS = 28;
    int i;
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);
        for (i = 0; i <= SEGMENTS; i++)
        {
            float angle = 2.0f * 3.1415926f * i / SEGMENTS;
            glVertex2f(cx + radius * cosf(angle), cy + radius * sinf(angle));
        }
    glEnd();
}

static void drawCircleAlpha(float cx, float cy, float radius, float r, float g, float b, float a)
{
    const int SEGMENTS = 28;
    int i;
    glColor4f(r, g, b, a);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);
        for (i = 0; i <= SEGMENTS; i++)
        {
            float angle = 2.0f * 3.1415926f * i / SEGMENTS;
            glVertex2f(cx + radius * cosf(angle), cy + radius * sinf(angle));
        }
    glEnd();
}

static void drawEllipseAlpha(float cx, float cy, float rx, float ry, float r, float g, float b, float a)
{
    const int SEGMENTS = 28;
    int i;
    glColor4f(r, g, b, a);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);
        for (i = 0; i <= SEGMENTS; i++)
        {
            float angle = 2.0f * 3.1415926f * i / SEGMENTS;
            glVertex2f(cx + rx * cosf(angle), cy + ry * sinf(angle));
        }
    glEnd();
}

static void drawSoftShadow(float cx, float cy, float rx, float ry)
{
    drawEllipseAlpha(cx, cy, rx,        ry,        0, 0, 0, 0.10f);
    drawEllipseAlpha(cx, cy, rx * 0.7f, ry * 0.7f, 0, 0, 0, 0.12f);
}

static void drawLine(float x1, float y1, float x2, float y2, float r, float g, float b, float thick)
{
    glColor3f(r, g, b);
    glLineWidth(thick);
    glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    glEnd();
}

static void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, float r, float g, float b)
{
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glVertex2f(x3, y3);
    glEnd();
}

static void drawText(float x, float y, void *font, const char *text, float r, float g, float b)
{
    glColor3f(r, g, b);
    glRasterPos2f(x, y);
    for (; *text != '\0'; text++)
        glutBitmapCharacter(font, *text);
}


static void drawBuilding(float x, float y, float w, float h, int rows, int cols,
                          float r, float g, float b)
{
    int i, j;
    drawQuad(x, y, w, h, r, g, b);
    for (i = 0; i < rows; i++)
        for (j = 0; j < cols; j++)
            drawQuad(x + 6 + j * (w / cols), y + 8 + i * (h / rows),
                     (w / cols) * 0.5f, (h / rows) * 0.55f, 0.85f, 0.90f, 0.75f);
}


static void drawCloud(float x, float y, float scale)
{
    drawCircle(x,            y,            18 * scale, 1, 1, 1);
    drawCircle(x + 20 * scale, y + 8 * scale, 22 * scale, 1, 1, 1);
    drawCircle(x + 45 * scale, y,            16 * scale, 1, 1, 1);
}


static void drawBackground(void)
{
    int i;

    drawQuad(0, 250, SCENE1_CANVAS_W, SCENE1_CANVAS_H - 250, 0.55f, 0.78f, 0.95f);


    drawCircleAlpha(830, 545, 55, 1.0f, 0.95f, 0.65f, 0.20f);
    drawCircleAlpha(830, 545, 42, 1.0f, 0.93f, 0.6f,  0.30f);
    drawCircle(830, 545, 28, 1.0f, 0.92f, 0.55f);


    drawCloud(100, 520, 1.0f);
    drawCloud(300, 560, 0.8f);
    drawCloud(430, 500, 1.1f);
    drawCloud(560, 555, 0.7f);
    drawCloud(690, 530, 0.9f);


    #define SCENE1_GROUND_Y 258.0f
    drawBuilding(15,  SCENE1_GROUND_Y, 45, 140, 6, 2, 0.60f, 0.64f, 0.74f);
    drawBuilding(70,  SCENE1_GROUND_Y, 35, 110, 5, 2, 0.65f, 0.69f, 0.78f);
    drawBuilding(555, SCENE1_GROUND_Y, 40, 125, 5, 2, 0.62f, 0.66f, 0.76f);
    drawBuilding(600, SCENE1_GROUND_Y, 55, 165, 7, 3, 0.58f, 0.62f, 0.72f);
    drawBuilding(665, SCENE1_GROUND_Y, 40, 135, 6, 2, 0.66f, 0.70f, 0.80f);
    drawBuilding(715, SCENE1_GROUND_Y, 45, 155, 6, 3, 0.50f, 0.55f, 0.68f);
    drawBuilding(770, SCENE1_GROUND_Y, 50, 175, 7, 3, 0.55f, 0.60f, 0.72f);
    drawBuilding(830, SCENE1_GROUND_Y, 45, 145, 6, 3, 0.65f, 0.70f, 0.80f);
    drawBuilding(878, SCENE1_GROUND_Y, 22, 115, 5, 1, 0.62f, 0.66f, 0.76f);


    drawQuad(0, 250, SCENE1_CANVAS_W, 8, 0.30f, 0.55f, 0.25f);


    drawQuad(200, SCENE1_GROUND_Y, 12, 40, 0.40f, 0.25f, 0.10f);
    drawTriangle(175, SCENE1_GROUND_Y + 40, 230, SCENE1_GROUND_Y + 40, 203, SCENE1_GROUND_Y + 110, 0.15f, 0.45f, 0.20f);

    drawQuad(390, SCENE1_GROUND_Y, 10, 35, 0.40f, 0.25f, 0.10f);
    drawTriangle(370, SCENE1_GROUND_Y + 35, 420, SCENE1_GROUND_Y + 35, 395, SCENE1_GROUND_Y + 95, 0.18f, 0.50f, 0.22f);


    drawQuad(0, 170, SCENE1_CANVAS_W, 80, 0.85f, 0.75f, 0.55f);
    for (i = 0; i < SCENE1_CANVAS_W; i += 30)
        drawLine((float)i, 170, (float)i, 250, 0.70f, 0.60f, 0.40f, 1);


    drawQuad(478, 170, 5, 65, 0.20f, 0.20f, 0.20f);
    drawQuad(468, 233, 25, 8, 0.20f, 0.20f, 0.20f);
    drawCircle(480, 245, 7, 1.0f, 0.95f, 0.65f);
    drawCircleAlpha(480, 245, 14, 1.0f, 0.95f, 0.5f, 0.25f);

    drawQuad(0, 0, SCENE1_CANVAS_W, 170, 0.35f, 0.35f, 0.38f);


    drawQuad(0, 166, SCENE1_CANVAS_W, 4, 0.80f, 0.80f, 0.80f);
    for (i = 0; i < SCENE1_CANVAS_W; i += 40)
        drawQuad((float)i, 166, 20, 4, (((i / 40) % 2) == 0) ? 0.75f : 0.95f,
                                       (((i / 40) % 2) == 0) ? 0.10f : 0.95f,
                                       (((i / 40) % 2) == 0) ? 0.10f : 0.95f);


    for (i = 0; i < SCENE1_CANVAS_W; i += 60)
        drawQuad((float)i, 80, 30, 6, 1, 1, 1);
}

static void drawWheel(float cx, float cy)
{
    drawCircle(cx, cy, 24, 0.05f, 0.05f, 0.05f);
    drawCircle(cx, cy, 10, 0.75f, 0.75f, 0.75f);
    drawLine(cx - 10, cy, cx + 10, cy, 0.3f, 0.3f, 0.3f, 2);
    drawLine(cx, cy - 10, cx, cy + 10, 0.3f, 0.3f, 0.3f, 2);
}


#define SCENE1_BUS_X 30.0f
#define SCENE1_BUS_Y 24.0f
#define SCENE1_BUS_W 480.0f
#define SCENE1_BUS_H 190.0f
#define SCENE1_DOOR_X (SCENE1_BUS_X + 111.0f)

static void drawBus(void)
{
    const float bx = SCENE1_BUS_X, by = SCENE1_BUS_Y;
    const float bw = SCENE1_BUS_W, bh = SCENE1_BUS_H;
    int i;

    drawSoftShadow(bx + bw / 2.0f, by - 6, bw / 2.0f + 10, 12);

    drawQuad(bx, by, bw, bh, 0.13f, 0.45f, 0.20f);
    drawQuad(bx, by + 60, bw, 55, 0.95f, 0.95f, 0.95f);
    drawQuad(bx, by + 115, bw, 75, 0.75f, 0.10f, 0.10f);

    drawQuad(bx + 5, by + 120, 85, 55, 0.55f, 0.72f, 0.82f);
    drawQuadOutline(bx + 5, by + 120, 85, 55, 0.05f, 0.05f, 0.05f, 3);
    drawLine(bx + 47, by + 120, bx + 47, by + 175, 0.05f, 0.05f, 0.05f, 2);
    drawLine(bx + 12, by + 128, bx + 82, by + 122, 0.85f, 0.85f, 0.85f, 1);

    drawQuad(bx + 15, by + 179, 65, 9, 0.05f, 0.05f, 0.05f);
    drawText(bx + 18, by + 181, GLUT_BITMAP_HELVETICA_10, "VICTOR CLASSIC", 1, 1, 1);

    for (i = 0; i < 7; i++)
    {
        float wx = bx + 110 + i * 48;
        drawQuad(wx, by + 122, 38, 55, 0.55f, 0.75f, 0.85f);
        drawQuadOutline(wx, by + 122, 38, 55, 0.1f, 0.1f, 0.1f, 1.5f);
        drawCircle(wx + 19, by + 150, 9, 0.25f, 0.20f, 0.18f);
    }

    drawQuad(bx + 96, by + 55, 30, 65, 0.55f, 0.72f, 0.82f);
    drawQuad(bx + 96, by + 15, 30, 40, 0.12f, 0.12f, 0.14f);
    drawQuadOutline(bx + 96, by + 15, 30, 105, 0.05f, 0.05f, 0.05f, 2);
    drawLine(bx + 111, by + 15, bx + 111, by + 120, 0.05f, 0.05f, 0.05f, 1.5f);
    drawQuad(bx + 100, by + 62, 22, 3, 0.8f, 0.8f, 0.4f);

    drawText(bx + 150, by + 85, GLUT_BITMAP_TIMES_ROMAN_24, "VICTOR CLASSIC", 0.72f, 0.08f, 0.08f);

    drawQuad(bx + 5, by + 3, 55, 20, 0.10f, 0.35f, 0.15f);
    drawText(bx + 8, by + 9, GLUT_BITMAP_HELVETICA_10, "DHAKA-505", 1, 1, 1);

    drawCircle(bx + 8, by + 45, 9, 1.0f, 1.0f, 0.7f);
    drawCircle(bx + 8, by + 25, 9, 1.0f, 1.0f, 0.7f);
    drawCircle(bx + 5, by + 48, 2.5f, 1.0f, 1.0f, 1.0f);
    drawCircle(bx + 5, by + 28, 2.5f, 1.0f, 1.0f, 1.0f);

    drawQuad(bx - 2, by - 2, 22, 8, 0.55f, 0.55f, 0.58f);

    drawLine(bx, by + 55, bx, by + 15, 0.1f, 0.1f, 0.1f, 2);

    drawQuad(bx + 92, by + 178, 12, 8, 0.1f, 0.1f, 0.1f);
    drawLine(bx + 92, by + 182, bx + 85, by + 190, 0.1f, 0.1f, 0.1f, 3);
    drawLine(bx + 10, by + 122, bx + 55, by + 130, 0.15f, 0.15f, 0.15f, 2);

    drawLine(bx + 2, by + 189, bx + bw - 2, by + 189, 1.0f, 1.0f, 1.0f, 2);

    drawWheel(bx + 60, by);
    drawWheel(bx + 380, by);
}


static void drawPersonShape(void)
{
    const float x = 0, y = 0;

    drawSoftShadow(x, y - 4, 22, 6);

    drawQuad(x - 10, y, 7, 40, 0.15f, 0.15f, 0.20f);
    drawQuad(x + 3,  y, 7, 40, 0.15f, 0.15f, 0.20f);

    drawQuad(x - 13, y - 4, 12, 6, 0.95f, 0.95f, 0.95f);
    drawQuad(x + 2,  y - 4, 12, 6, 0.95f, 0.95f, 0.95f);
    drawQuadOutline(x - 13, y - 4, 12, 6, 0.1f, 0.1f, 0.1f, 1);
    drawQuadOutline(x + 2,  y - 4, 12, 6, 0.1f, 0.1f, 0.1f, 1);

    glColor3f(0.10f, 0.30f, 0.75f);
    glBegin(GL_POLYGON);
        glVertex2f(x - 16, y + 78);
        glVertex2f(x + 16, y + 78);
        glVertex2f(x + 10, y + 40);
        glVertex2f(x - 10, y + 40);
    glEnd();

    drawQuad(x + 10, y + 40, 6, 34, 0.05f, 0.10f, 0.40f);

    drawLine(x - 15, y + 72, x - 24, y + 55, 0.10f, 0.30f, 0.75f, 6);
    drawLine(x - 24, y + 55, x - 20, y + 40, 0.10f, 0.30f, 0.75f, 6);
    drawCircle(x - 20, y + 38, 4, 0.85f, 0.65f, 0.45f);

    drawLine(x + 15, y + 72, x + 25, y + 55, 0.10f, 0.30f, 0.75f, 6);
    drawLine(x + 25, y + 55, x + 21, y + 40, 0.10f, 0.30f, 0.75f, 6);
    drawCircle(x + 21, y + 38, 4, 0.85f, 0.65f, 0.45f);

    drawQuad(x - 4, y + 78, 8, 6, 0.85f, 0.65f, 0.45f);

    drawCircle(x, y + 96, 13, 0.85f, 0.65f, 0.45f);

    drawCircle(x, y + 104, 12, 0.08f, 0.06f, 0.05f);
    drawQuad(x - 12, y + 90, 24, 9, 0.85f, 0.65f, 0.45f);

    drawCircle(x - 5, y + 95, 1.5f, 0.10f, 0.10f, 0.10f);
    drawCircle(x + 5, y + 95, 1.5f, 0.10f, 0.10f, 0.10f);
    drawLine(x - 4, y + 90, x + 4, y + 90, 0.35f, 0.18f, 0.12f, 2);
}


static void drawAIUBSign(void)
{
    const float px = 700, py = 150;

    drawQuad(px, py, 8, 130, 0.3f, 0.3f, 0.3f);
    drawQuad(px - 10, py - 5, 28, 8, 0.2f, 0.2f, 0.2f);

    drawQuad(px - 55, py + 90, 150, 100, 0.08f, 0.16f, 0.4f);
    drawQuadOutline(px - 55, py + 90, 150, 100, 0.9f, 0.9f, 0.9f, 2);

    drawText(px - 40, py + 160, GLUT_BITMAP_TIMES_ROMAN_24, "AIUB", 1, 1, 1);
    drawText(px - 45, py + 138, GLUT_BITMAP_HELVETICA_12, "American", 1, 1, 1);
    drawText(px - 45, py + 122, GLUT_BITMAP_HELVETICA_12, "International", 1, 1, 1);
    drawText(px - 45, py + 106, GLUT_BITMAP_HELVETICA_12, "University-", 1, 1, 1);
    drawText(px - 45, py + 94,  GLUT_BITMAP_HELVETICA_12, "Bangladesh", 1, 1, 1);

    drawQuad(px - 55, py + 50, 150, 35, 0.08f, 0.16f, 0.4f);
    drawQuadOutline(px - 55, py + 50, 150, 35, 0.9f, 0.9f, 0.9f, 2);

    drawQuad(px - 10, py + 62, 90, 10, 1, 1, 1);
    drawTriangle(px - 10, py + 78, px - 10, py + 55, px - 40, py + 67, 1, 1, 1);
}



typedef enum { STATE_ARRIVING, STATE_IDLE, STATE_WALKING, STATE_DRIVING } SceneState;

#define SCENE1_BUS_START_OFFSET 950.0f

static SceneState sceneState = STATE_ARRIVING;
static float personX     = 300.0f;
static float busOffsetX  = SCENE1_BUS_START_OFFSET;
static const float WALK_SPEED   = 2.2f;
static const float DRIVE_SPEED  = 4.0f;
static const float ARRIVE_SPEED = 5.0f;

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawBackground();
    drawAIUBSign();

    glPushMatrix();
        glTranslatef(busOffsetX, 0, 0);
        drawBus();
    glPopMatrix();


    if (sceneState != STATE_DRIVING)
    {
        glPushMatrix();
            glTranslatef(personX, 0, 0);
            drawPersonShape();
        glPopMatrix();
    }


    if (sceneState == STATE_ARRIVING)
        drawText(20, SCENE1_CANVAS_H - 25, GLUT_BITMAP_HELVETICA_18, "The bus is arriving...", 0.1f, 0.1f, 0.1f);
    else if (sceneState == STATE_IDLE)
        drawText(20, SCENE1_CANVAS_H - 25, GLUT_BITMAP_HELVETICA_18, "Press S to board the bus", 0.1f, 0.1f, 0.1f);

    glutSwapBuffers();
}

static void reshape(int w, int h)
{
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, SCENE1_CANVAS_W, 0, SCENE1_CANVAS_H);
    glMatrixMode(GL_MODELVIEW);
}


static void update(int value)
{
    (void)value;

    if (sceneState == STATE_ARRIVING)
    {
        busOffsetX -= ARRIVE_SPEED;
        if (busOffsetX <= 0.0f)
        {
            busOffsetX = 0.0f;
            sceneState = STATE_IDLE;
        }

        glutPostRedisplay();
    }
    else if (sceneState == STATE_WALKING)
    {
        personX -= WALK_SPEED;
        if (personX <= SCENE1_DOOR_X)
            sceneState = STATE_DRIVING;

        glutPostRedisplay();
    }
    else if (sceneState == STATE_DRIVING)
    {
        busOffsetX -= DRIVE_SPEED;
        if (busOffsetX < -(SCENE1_BUS_X + SCENE1_BUS_W + 50))
        {

            sceneState = STATE_ARRIVING;
            busOffsetX = SCENE1_BUS_START_OFFSET;
            personX = 300.0f;
        }

        glutPostRedisplay();
    }

}

static void keyboard(unsigned char key, int x, int y)
{
    (void)x; (void)y;
    if (key == 27) exit(0);

    if ((key == 's' || key == 'S') && sceneState == STATE_IDLE)
    {
        sceneState = STATE_WALKING;
    }
}

static void init(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

}
namespace Scene2 {

#define SCENE2_CANVAS_W 900
#define SCENE2_CANVAS_H 600
#define SCENE2_WIN_W 1280
#define SCENE2_WIN_H 800


static void drawQuad(float x, float y, float w, float h, float r, float g, float b)
{
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
        glVertex2f(x,     y);
        glVertex2f(x + w, y);
        glVertex2f(x + w, y + h);
        glVertex2f(x,     y + h);
    glEnd();
}

static void drawQuadOutline(float x, float y, float w, float h, float r, float g, float b, float thick)
{
    glColor3f(r, g, b);
    glLineWidth(thick);
    glBegin(GL_LINE_LOOP);
        glVertex2f(x,     y);
        glVertex2f(x + w, y);
        glVertex2f(x + w, y + h);
        glVertex2f(x,     y + h);
    glEnd();
}

static void drawCircle(float cx, float cy, float radius, float r, float g, float b)
{
    const int SEGMENTS = 32;
    int i;
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);
        for (i = 0; i <= SEGMENTS; i++)
        {
            float angle = 2.0f * 3.1415926f * i / SEGMENTS;
            glVertex2f(cx + radius * cosf(angle), cy + radius * sinf(angle));
        }
    glEnd();
}

static void drawCircleOutline(float cx, float cy, float radius, float r, float g, float b, float thick)
{
    const int SEGMENTS = 32;
    int i;
    glColor3f(r, g, b);
    glLineWidth(thick);
    glBegin(GL_LINE_LOOP);
        for (i = 0; i < SEGMENTS; i++)
        {
            float angle = 2.0f * 3.1415926f * i / SEGMENTS;
            glVertex2f(cx + radius * cosf(angle), cy + radius * sinf(angle));
        }
    glEnd();
}

static void drawEllipseAlpha(float cx, float cy, float rx, float ry, float r, float g, float b, float a)
{
    const int SEGMENTS = 28;
    int i;
    glColor4f(r, g, b, a);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);
        for (i = 0; i <= SEGMENTS; i++)
        {
            float angle = 2.0f * 3.1415926f * i / SEGMENTS;
            glVertex2f(cx + rx * cosf(angle), cy + ry * sinf(angle));
        }
    glEnd();
}

static void drawSoftShadow(float cx, float cy, float rx, float ry)
{
    drawEllipseAlpha(cx, cy, rx,        ry,        0, 0, 0, 0.10f);
    drawEllipseAlpha(cx, cy, rx * 0.7f, ry * 0.7f, 0, 0, 0, 0.12f);
}

static void drawLine(float x1, float y1, float x2, float y2, float r, float g, float b, float thick)
{
    glColor3f(r, g, b);
    glLineWidth(thick);
    glBegin(GL_LINES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    glEnd();
}

static void drawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, float r, float g, float b)
{
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLES);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
        glVertex2f(x3, y3);
    glEnd();
}

static void drawText(float x, float y, void *font, const char *text, float r, float g, float b)
{
    glColor3f(r, g, b);
    glRasterPos2f(x, y);
    for (; *text != '\0'; text++)
        glutBitmapCharacter(font, *text);
}

static void drawArc(float cx, float cy, float rx, float ry, float startDeg, float endDeg, float r, float g, float b)
{
    const int SEGMENTS = 24;
    int i;
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);
        for (i = 0; i <= SEGMENTS; i++)
        {
            float t = startDeg + (endDeg - startDeg) * i / SEGMENTS;
            float rad = t * 3.1415926f / 180.0f;
            glVertex2f(cx + rx * cosf(rad), cy + ry * sinf(rad));
        }
    glEnd();
}

static void drawArcOutline(float cx, float cy, float rx, float ry, float startDeg, float endDeg, float r, float g, float b, float thick)
{
    const int SEGMENTS = 24;
    int i;
    glColor3f(r, g, b);
    glLineWidth(thick);
    glBegin(GL_LINE_STRIP);
        for (i = 0; i <= SEGMENTS; i++)
        {
            float t = startDeg + (endDeg - startDeg) * i / SEGMENTS;
            float rad = t * 3.1415926f / 180.0f;
            glVertex2f(cx + rx * cosf(rad), cy + ry * sinf(rad));
        }
    glEnd();
}


static void drawBackground(void)
{
    int i;

    drawQuad(0, 420, SCENE2_CANVAS_W, SCENE2_CANVAS_H - 420, 0.42f, 0.68f, 0.92f);
    drawQuad(0, 250, SCENE2_CANVAS_W, 170,            0.62f, 0.82f, 0.96f);


    drawEllipseAlpha(815, 520, 50, 50, 1.0f, 0.95f, 0.65f, 0.20f);
    drawEllipseAlpha(815, 520, 38, 38, 1.0f, 0.93f, 0.6f,  0.30f);
    drawCircle(815, 520, 26, 1.0f, 0.92f, 0.55f);


    drawCircle(120, 555, 18, 1, 1, 1);
    drawCircle(140, 563, 22, 1, 1, 1);
    drawCircle(165, 555, 16, 1, 1, 1);

    drawCircle(430, 560, 14, 1, 1, 1);
    drawCircle(448, 566, 18, 1, 1, 1);
    drawCircle(468, 560, 13, 1, 1, 1);

    drawCircle(250, 500, 13, 1, 1, 1);
    drawCircle(267, 506, 17, 1, 1, 1);
    drawCircle(286, 500, 12, 1, 1, 1);

    drawCircle(590, 575, 14, 1, 1, 1);
    drawCircle(608, 582, 18, 1, 1, 1);
    drawCircle(628, 575, 13, 1, 1, 1);

    drawCircle(690, 500, 12, 1, 1, 1);
    drawCircle(705, 505, 15, 1, 1, 1);
    drawCircle(721, 500, 11, 1, 1, 1);


    #define SCENE2_BG_GROUND_Y 250.0f

    drawQuad(300, SCENE2_BG_GROUND_Y, 40, 130, 0.62f, 0.66f, 0.76f);
    drawQuad(350, SCENE2_BG_GROUND_Y, 50, 155, 0.58f, 0.62f, 0.72f);
    drawQuad(412, SCENE2_BG_GROUND_Y, 42, 115, 0.65f, 0.70f, 0.80f);

    drawQuad(650, SCENE2_BG_GROUND_Y, 40, 150, 0.62f, 0.66f, 0.76f);
    drawQuad(700, SCENE2_BG_GROUND_Y, 50, 185, 0.60f, 0.65f, 0.75f);
    drawQuad(762, SCENE2_BG_GROUND_Y, 45, 205, 0.50f, 0.55f, 0.68f);
    drawQuad(820, SCENE2_BG_GROUND_Y, 48, 175, 0.58f, 0.62f, 0.72f);
    drawQuad(875, SCENE2_BG_GROUND_Y, 22, 140, 0.65f, 0.70f, 0.80f);

    {
        int r, c;

        for (r = 0; r < 5; r++)
            for (c = 0; c < 2; c++)
                drawQuad(306 + c * 16, SCENE2_BG_GROUND_Y + 10 + r * 22, 8, 12, 0.85f, 0.90f, 0.75f);
        for (r = 0; r < 6; r++)
            for (c = 0; c < 3; c++)
                drawQuad(356 + c * 15, SCENE2_BG_GROUND_Y + 10 + r * 23, 8, 12, 0.85f, 0.90f, 0.75f);
        for (r = 0; r < 4; r++)
            for (c = 0; c < 2; c++)
                drawQuad(418 + c * 16, SCENE2_BG_GROUND_Y + 10 + r * 24, 8, 12, 0.85f, 0.90f, 0.75f);


        for (r = 0; r < 6; r++)
            for (c = 0; c < 2; c++)
                drawQuad(656 + c * 16, SCENE2_BG_GROUND_Y + 10 + r * 22, 8, 12, 0.85f, 0.90f, 0.75f);
        for (r = 0; r < 7; r++)
            for (c = 0; c < 3; c++)
                drawQuad(706 + c * 15, SCENE2_BG_GROUND_Y + 10 + r * 22, 8, 12, 0.85f, 0.90f, 0.75f);
        for (r = 0; r < 8; r++)
            for (c = 0; c < 3; c++)
                drawQuad(768 + c * 14, SCENE2_BG_GROUND_Y + 10 + r * 22, 8, 12, 0.85f, 0.90f, 0.75f);
        for (r = 0; r < 6; r++)
            for (c = 0; c < 3; c++)
                drawQuad(825 + c * 14, SCENE2_BG_GROUND_Y + 10 + r * 24, 8, 12, 0.85f, 0.90f, 0.75f);
    }

    for (i = 0; i < 14; i++)
    {
        float px = 20 + i * 20;
        float colors[3][3] = { {0.3f,0.3f,0.5f}, {0.5f,0.2f,0.2f}, {0.2f,0.4f,0.3f} };
        int c = i % 3;
        drawQuad(px, 255, 6, 14, colors[c][0], colors[c][1], colors[c][2]);
        drawCircle(px + 3, 273, 4, 0.75f, 0.55f, 0.4f);
    }


    drawQuad(600, SCENE2_BG_GROUND_Y, 14, 45, 0.35f, 0.22f, 0.10f);
    drawCircle(607, SCENE2_BG_GROUND_Y + 80, 42, 0.20f, 0.50f, 0.22f);
    drawCircle(575, SCENE2_BG_GROUND_Y + 65, 30, 0.22f, 0.55f, 0.25f);
    drawCircle(640, SCENE2_BG_GROUND_Y + 65, 30, 0.22f, 0.55f, 0.25f);

    drawQuad(0, 170, SCENE2_CANVAS_W, 80, 0.85f, 0.75f, 0.55f);
    for (i = 0; i < SCENE2_CANVAS_W; i += 30)
        drawLine((float)i, 170, (float)i, 250, 0.70f, 0.60f, 0.40f, 1);
    for (i = 0; i < 6; i++)
        drawQuad(20.0f + i * 18, 170, 10, 12, 0.9f, 0.9f, 0.9f);

    drawQuad(0, 0, SCENE2_CANVAS_W, 170, 0.35f, 0.35f, 0.38f);
    for (i = 0; i < SCENE2_CANVAS_W; i += 60)
        drawQuad((float)i, 80, 30, 6, 1, 1, 1);
}

static void drawSigns(void)
{
    const float px = 90, py = 175;


    drawSoftShadow(px + 3, py - 6, 24, 7);

    drawQuad(px, py, 7, 140, 0.35f, 0.35f, 0.35f);
    drawQuad(px - 12, py - 7, 31, 10, 0.20f, 0.20f, 0.20f);


    drawQuad(px - 55, py + 195, 150, 65, 0.05f, 0.45f, 0.15f);
    drawQuadOutline(px - 55, py + 195, 150, 65, 1, 1, 1, 3);
    drawText(px - 45, py + 230, GLUT_BITMAP_TIMES_ROMAN_24, "KURATOLI", 1, 1, 1);
    drawLine(px - 45, py + 215, px + 70, py + 215, 1, 1, 1, 1.5f);


    drawQuad(px - 55, py + 138, 150, 52, 0.08f, 0.16f, 0.4f);
    drawQuadOutline(px - 55, py + 138, 150, 52, 1, 1, 1, 2);
    drawText(px - 32, py + 158, GLUT_BITMAP_TIMES_ROMAN_24, "AIUB", 1, 1, 1);


    drawQuad(px - 55, py + 92, 150, 40, 0.08f, 0.16f, 0.4f);
    drawQuadOutline(px - 55, py + 92, 150, 40, 1, 1, 1, 2);
    {
        const float tipX = px - 45, baseX = px - 10, shaftRightX = px + 85;
        drawQuad(baseX, py + 108, shaftRightX - baseX, 8, 1, 1, 1);
        drawTriangle(tipX, py + 112, baseX, py + 100, baseX, py + 124, 1, 1, 1);
    }
}



#define SCENE2_FRONT_R 36.0f
#define SCENE2_REAR_R  46.0f
#define SCENE2_FRONT_X (-260.0f)
#define SCENE2_FRONT_Y SCENE2_FRONT_R
#define SCENE2_REAR_X  0.0f
#define SCENE2_REAR_Y  SCENE2_REAR_R

static void drawWheel(float cx, float cy, float radius, int chrome)
{
    drawCircle(cx, cy, radius, 0.06f, 0.06f, 0.06f);
    if (chrome)
        drawCircleOutline(cx, cy, radius - 4, 0.75f, 0.76f, 0.78f, 2.5f);
    else
        drawCircleOutline(cx, cy, radius - 4, 0.25f, 0.25f, 0.30f, 2);
    drawCircle(cx, cy, 7, 0.80f, 0.80f, 0.82f);
    {
        int s;
        for (s = 0; s < 12; s++)
        {
            float ang = s * 3.1415926f / 6.0f;
            drawLine(cx, cy, cx + (radius - 5) * cosf(ang), cy + (radius - 5) * sinf(ang),
                     0.75f, 0.75f, 0.78f, 1.0f);
        }
    }

    drawArcOutline(cx, cy, radius + 14, radius + 6, 205, 260, 0.4f, 0.4f, 0.4f, 2);
}

static void drawRickshaw(void)
{
    drawSoftShadow((SCENE2_REAR_X + SCENE2_FRONT_X) / 2.0f, 4, 200, 14);


    drawWheel(SCENE2_FRONT_X, SCENE2_FRONT_Y, SCENE2_FRONT_R, 1);
    drawWheel(SCENE2_REAR_X,  SCENE2_REAR_Y,  SCENE2_REAR_R,  1);


    drawLine(SCENE2_FRONT_X, SCENE2_FRONT_Y, SCENE2_REAR_X - 30, SCENE2_REAR_Y - 20, 0.05f, 0.05f, 0.05f, 5);
    drawLine(SCENE2_FRONT_X, SCENE2_FRONT_Y + 10, SCENE2_REAR_X - 60, SCENE2_REAR_Y + 60, 0.05f, 0.05f, 0.05f, 5);
    drawLine(SCENE2_FRONT_X + 55, SCENE2_FRONT_Y + 25, SCENE2_FRONT_X + 55, SCENE2_FRONT_Y + 68, 0.05f, 0.05f, 0.05f, 4);

    drawLine(SCENE2_FRONT_X, SCENE2_FRONT_Y, SCENE2_FRONT_X - 4, SCENE2_FRONT_Y + 78, 0.05f, 0.05f, 0.05f, 5);
    drawLine(SCENE2_FRONT_X - 4, SCENE2_FRONT_Y + 78, SCENE2_FRONT_X - 34, SCENE2_FRONT_Y + 76, 0.05f, 0.05f, 0.05f, 5);
    drawLine(SCENE2_FRONT_X - 34, SCENE2_FRONT_Y + 76, SCENE2_FRONT_X - 34, SCENE2_FRONT_Y + 64, 0.05f, 0.05f, 0.05f, 4);
    drawLine(SCENE2_FRONT_X - 4, SCENE2_FRONT_Y + 78, SCENE2_FRONT_X + 18, SCENE2_FRONT_Y + 76, 0.05f, 0.05f, 0.05f, 5);


    drawCircle(SCENE2_FRONT_X + 30, SCENE2_FRONT_Y - 5, 5, 0.15f, 0.15f, 0.15f);
    drawQuad(SCENE2_FRONT_X + 20, SCENE2_FRONT_Y - 17, 20, 13, 0.10f, 0.10f, 0.10f);
    drawLine(SCENE2_FRONT_X + 30, SCENE2_FRONT_Y - 5, SCENE2_REAR_X - 30, SCENE2_REAR_Y - 20, 0.20f, 0.20f, 0.20f, 3);
    drawLine(SCENE2_FRONT_X + 30, SCENE2_FRONT_Y - 9, SCENE2_REAR_X - 30, SCENE2_REAR_Y - 24, 0.20f, 0.20f, 0.20f, 3);


    drawQuad(SCENE2_FRONT_X + 45, SCENE2_FRONT_Y + 65, 24, 8, 0.10f, 0.10f, 0.10f);
    drawQuadOutline(SCENE2_FRONT_X + 45, SCENE2_FRONT_Y + 65, 24, 8, 0.35f, 0.35f, 0.35f, 1);

    glColor3f(0.10f, 0.10f, 0.12f);
    glBegin(GL_POLYGON);
        glVertex2f(SCENE2_REAR_X - 95, SCENE2_REAR_Y - 5);
        glVertex2f(SCENE2_REAR_X - 85, SCENE2_REAR_Y + 70);
        glVertex2f(SCENE2_REAR_X - 15, SCENE2_REAR_Y + 95);
        glVertex2f(SCENE2_REAR_X + 38, SCENE2_REAR_Y + 52);
        glVertex2f(SCENE2_REAR_X + 32, SCENE2_REAR_Y + 4);
    glEnd();


    glColor3f(0.75f, 0.70f, 0.55f);
    glBegin(GL_POLYGON);
        glVertex2f(SCENE2_REAR_X - 78, SCENE2_REAR_Y + 8);
        glVertex2f(SCENE2_REAR_X - 25, SCENE2_REAR_Y + 62);
        glVertex2f(SCENE2_REAR_X - 68, SCENE2_REAR_Y + 68);
    glEnd();


    drawQuad(SCENE2_REAR_X - 78, SCENE2_REAR_Y + 18, 75, 16, 0.62f, 0.10f, 0.10f);
    drawQuadOutline(SCENE2_REAR_X - 78, SCENE2_REAR_Y + 18, 75, 16, 0.20f, 0.05f, 0.05f, 1.5f);


    {
        const float hubX = SCENE2_REAR_X - 5, hubY = SCENE2_REAR_Y + 158;
        const float rimRx = 108, rimRy = 88;
        const int SPOKES = 8;
        int s;


        drawLine(SCENE2_REAR_X - 15, SCENE2_REAR_Y + 95, hubX, hubY, 0.05f, 0.05f, 0.05f, 4);


        drawArcOutline(hubX, hubY, rimRx, rimRy, 8, 172, 0.05f, 0.05f, 0.05f, 4);


        for (s = 0; s <= SPOKES; s++)
        {
            float t = 8.0f + (172.0f - 8.0f) * s / SPOKES;
            float rad = t * 3.1415926f / 180.0f;
            drawLine(hubX, hubY, hubX + rimRx * cosf(rad), hubY + rimRy * sinf(rad),
                     0.05f, 0.05f, 0.05f, 3);
        }


        drawCircle(hubX, hubY, 5, 0.1f, 0.1f, 0.1f);
    }
}


static void drawFace(float cx, float cy, float hairR, float hairG, float hairB)
{
    drawCircle(cx, cy, 12, 0.85f, 0.65f, 0.45f);
    drawCircle(cx, cy + 7, 11, hairR, hairG, hairB);
    drawQuad(cx - 11, cy - 6, 22, 8, 0.85f, 0.65f, 0.45f);
    drawCircle(cx - 4, cy - 2, 1.4f, 0.1f, 0.1f, 0.1f);
    drawCircle(cx + 4, cy - 2, 1.4f, 0.1f, 0.1f, 0.1f);
}



static void drawDriver(void)
{
    const float HX = SCENE2_FRONT_X + 55, HY = SCENE2_FRONT_Y + 65;
    drawSoftShadow(SCENE2_FRONT_X + 30, 2, 40, 6);


    drawLine(HX, HY, HX - 5, HY - 45, 0.35f, 0.28f, 0.16f, 7);
    drawLine(HX - 5, HY - 45, HX + 8, HY - 65, 0.35f, 0.28f, 0.16f, 7);
    drawLine(HX, HY, HX - 20, HY - 30, 0.35f, 0.28f, 0.16f, 7);
    drawLine(HX - 20, HY - 30, HX - 27, HY - 60, 0.35f, 0.28f, 0.16f, 7);


    drawQuad(HX + 3, HY - 68, 12, 5, 0.55f, 0.35f, 0.20f);
    drawQuad(HX - 34, HY - 63, 12, 5, 0.55f, 0.35f, 0.20f);


    glColor3f(0.50f, 0.16f, 0.16f);
    glBegin(GL_POLYGON);
        glVertex2f(HX - 8,  HY + 3);
        glVertex2f(HX + 8,  HY + 3);
        glVertex2f(HX - 4,  HY + 62);
        glVertex2f(HX - 26, HY + 58);
    glEnd();


    drawLine(HX - 8, HY + 55, HX + 2, HY + 38, 0.95f, 0.75f, 0.20f, 4);


    drawLine(HX - 16, HY + 60, HX - 45, HY + 48, 0.50f, 0.16f, 0.16f, 6);
    drawLine(HX - 45, HY + 48, HX - 70, HY + 22, 0.50f, 0.16f, 0.16f, 6);
    drawCircle(HX - 70, HY + 20, 3.5f, 0.85f, 0.65f, 0.45f);


    drawLine(HX - 4, HY + 58, HX - 20, HY + 40, 0.50f, 0.16f, 0.16f, 6);
    drawLine(HX - 20, HY + 40, HX - 30, HY + 22, 0.50f, 0.16f, 0.16f, 6);
    drawCircle(HX - 30, HY + 20, 3.5f, 0.85f, 0.65f, 0.45f);

    \
    drawQuad(HX - 20, HY + 58, 10, 16, 0.85f, 0.65f, 0.45f);


    drawFace(HX - 15, HY + 82, 0.40f, 0.22f, 0.12f);
    drawLine(HX - 22, HY + 74, HX - 15, HY + 77, 0.30f, 0.16f, 0.08f, 2.5f);
    drawLine(HX - 15, HY + 77, HX - 8,  HY + 74, 0.30f, 0.16f, 0.08f, 2.5f);
}


static void drawPassenger(void)
{
    const float PX = SCENE2_REAR_X - 45, PY = SCENE2_REAR_Y + 34;


    drawLine(PX - 6, PY, PX - 20, PY - 22, 0.02f, 0.02f, 0.03f, 11);
    drawLine(PX - 20, PY - 22, PX - 24, PY - 40, 0.02f, 0.02f, 0.03f, 11);
    drawLine(PX + 6, PY, PX - 6, PY - 24, 0.02f, 0.02f, 0.03f, 11);
    drawLine(PX - 6, PY - 24, PX - 10, PY - 42, 0.02f, 0.02f, 0.03f, 11);

    drawLine(PX - 6, PY, PX - 20, PY - 22, 0.14f, 0.14f, 0.18f, 8);
    drawLine(PX - 20, PY - 22, PX - 24, PY - 40, 0.14f, 0.14f, 0.18f, 8);
    drawLine(PX + 6, PY, PX - 6, PY - 24, 0.14f, 0.14f, 0.18f, 8);
    drawLine(PX - 6, PY - 24, PX - 10, PY - 42, 0.14f, 0.14f, 0.18f, 8);

    drawQuad(PX - 30, PY - 44, 13, 6, 0.95f, 0.95f, 0.95f);
    drawQuad(PX - 16, PY - 46, 13, 6, 0.95f, 0.95f, 0.95f);
    drawQuadOutline(PX - 30, PY - 44, 13, 6, 0.1f, 0.1f, 0.1f, 1);
    drawQuadOutline(PX - 16, PY - 46, 13, 6, 0.1f, 0.1f, 0.1f, 1);


    glColor3f(0.03f, 0.03f, 0.05f);
    glBegin(GL_POLYGON);
        glVertex2f(PX - 15, PY + 1);
        glVertex2f(PX + 15, PY + 1);
        glVertex2f(PX + 22, PY + 80);
        glVertex2f(PX - 12, PY + 77);
    glEnd();
    glColor3f(0.12f, 0.34f, 0.80f);
    glBegin(GL_POLYGON);
        glVertex2f(PX - 12, PY + 4);
        glVertex2f(PX + 12, PY + 4);
        glVertex2f(PX + 18, PY + 77);
        glVertex2f(PX - 9,  PY + 74);
    glEnd();


    drawQuad(PX + 14, PY + 10, 6, 60, 0.05f, 0.10f, 0.40f);


    drawLine(PX - 8, PY + 72, PX - 16, PY + 42, 0.02f, 0.02f, 0.03f, 10);
    drawLine(PX - 16, PY + 42, PX - 6, PY + 8, 0.02f, 0.02f, 0.03f, 10);
    drawLine(PX + 14, PY + 75, PX + 20, PY + 45, 0.02f, 0.02f, 0.03f, 10);
    drawLine(PX + 20, PY + 45, PX + 8, PY + 8, 0.02f, 0.02f, 0.03f, 10);

    drawLine(PX - 8, PY + 72, PX - 16, PY + 42, 0.12f, 0.34f, 0.80f, 6);
    drawLine(PX - 16, PY + 42, PX - 6, PY + 8, 0.12f, 0.34f, 0.80f, 6);
    drawLine(PX + 14, PY + 75, PX + 20, PY + 45, 0.12f, 0.34f, 0.80f, 6);
    drawLine(PX + 20, PY + 45, PX + 8, PY + 8, 0.12f, 0.34f, 0.80f, 6);
    drawCircle(PX - 6, PY + 6, 4, 0.02f, 0.02f, 0.03f);
    drawCircle(PX + 8, PY + 6, 4, 0.02f, 0.02f, 0.03f);
    drawCircle(PX - 6, PY + 6, 3.5f, 0.85f, 0.65f, 0.45f);
    drawCircle(PX + 8, PY + 6, 3.5f, 0.85f, 0.65f, 0.45f);



    drawQuad(PX, PY + 76, 10, 16, 0.85f, 0.65f, 0.45f);


    drawFace(PX + 5, PY + 98, 0.08f, 0.06f, 0.05f);
}


static int   heading = 0;
static float rickshawOffsetX = 0.0f;
static const float RICKSHAW_START_X = 620.0f;
static const float HEAD_SPEED = 3.5f;


static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawBackground();
    drawSigns();

    glPushMatrix();
        glTranslatef(RICKSHAW_START_X + rickshawOffsetX, 40, 0);
        drawRickshaw();
        drawDriver();
        drawPassenger();
    glPopMatrix();

    if (!heading)
        drawText(20, SCENE2_CANVAS_H - 25, GLUT_BITMAP_HELVETICA_18, "Press Y - heading towards AIUB", 0.1f, 0.1f, 0.1f);

    glutSwapBuffers();
}

static void reshape(int w, int h)
{
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, SCENE2_CANVAS_W, 0, SCENE2_CANVAS_H);
    glMatrixMode(GL_MODELVIEW);
}

static void update(int value)
{
    (void)value;
    if (!heading) return;

    rickshawOffsetX -= HEAD_SPEED;
    if (rickshawOffsetX < -(RICKSHAW_START_X + 300.0f))
    {

        heading = 0;
        rickshawOffsetX = 0.0f;
    }

    glutPostRedisplay();
}

static void keyboard(unsigned char key, int x, int y)
{
    (void)x; (void)y;
    if (key == 27) exit(0);

    if ((key == 'y' || key == 'Y') && !heading)
    {
        heading = 1;
    }
}

static void init(void)
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

}
namespace Scene3 {

bool clockRunning  = false;

bool cloudsRunning = false;

bool rainOn        = false;

float clockAngle = 0;

float cloudX     = 0;

float rainOffset = 0;

const int   NUM_DROPS = 24;

float rainDropX[NUM_DROPS];

float rainDropY[NUM_DROPS];

void initRain()

{

    for (int i = 0; i < NUM_DROPS; i++)

    {

        rainDropX[i] = 20 + rand() % 240;

        rainDropY[i] = rand() % 190;

    }

}

// draw a circle

void draw_circle(float cx, float cy, float r)

{

    glBegin(GL_TRIANGLE_FAN);

    glVertex2f(cx, cy);

    for (int i = 0; i <= 360; i += 10)

    {

        float angle = i * 3.14159f / 180;

        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));

    }

    glEnd();

}


void drawQuad(float x, float y, float w, float h, float r, float g, float b)

{

    glColor3f(r, g, b);

    glBegin(GL_QUADS);

        glVertex2f(x,     y);

        glVertex2f(x + w, y);

        glVertex2f(x + w, y + h);

        glVertex2f(x,     y + h);

    glEnd();

}

void drawQuadOutline(float x, float y, float w, float h, float r, float g, float b, float lineWidth)

{

    glColor3f(r, g, b);

    glLineWidth(lineWidth);

    glBegin(GL_LINE_LOOP);

        glVertex2f(x,     y);

        glVertex2f(x + w, y);

        glVertex2f(x + w, y + h);

        glVertex2f(x,     y + h);

    glEnd();

    glLineWidth(1);

}

void drawLine(float x1, float y1, float x2, float y2, float r, float g, float b, float lineWidth)

{

    glColor3f(r, g, b);

    glLineWidth(lineWidth);

    glBegin(GL_LINES);

        glVertex2f(x1, y1);

        glVertex2f(x2, y2);

    glEnd();

    glLineWidth(1);

}

void drawCircle(float cx, float cy, float radius, float r, float g, float b)

{

    glColor3f(r, g, b);

    glBegin(GL_TRIANGLE_FAN);

        glVertex2f(cx, cy);

        for (int i = 0; i <= 360; i += 10)

        {

            float angle = i * 3.14159f / 180;

            glVertex2f(cx + radius * cos(angle), cy + radius * sin(angle));

        }

    glEnd();

}

void drawSoftShadow(float cx, float cy, float w, float h)

{

    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor4f(0, 0, 0, 0.22f);

    glBegin(GL_TRIANGLE_FAN);

        glVertex2f(cx, cy);

        for (int i = 0; i <= 360; i += 10)

        {

            float angle = i * 3.14159f / 180;

            glVertex2f(cx + w * cos(angle), cy + h * sin(angle));

        }

    glEnd();

    glDisable(GL_BLEND);

}

void drawRoom()

{

    // wall

    glColor3f(0.91f, 0.87f, 0.77f);

    glBegin(GL_QUADS);

        glVertex2i(0, 140);

        glVertex2i(800, 140);

        glVertex2i(800, 600);

        glVertex2i(0, 600);

    glEnd();

    // floor

    glColor3f(0.79f, 0.59f, 0.37f);

    glBegin(GL_QUADS);

        glVertex2i(0, 0);

        glVertex2i(800, 0);

        glVertex2i(800, 140);

        glVertex2i(0, 140);

    glEnd();

    // ceiling

    glColor3f(0.11f, 0.24f, 0.43f);

    glBegin(GL_QUADS);

        glVertex2i(0, 570);

        glVertex2i(800, 570);

        glVertex2i(800, 600);

        glVertex2i(0, 600);

    glEnd();

}

void drawWindow()

{

    if (rainOn)

        glColor3f(0.55f, 0.58f, 0.62f);

    else

        glColor3f(0.75f, 0.89f, 0.95f);

    glBegin(GL_QUADS);

        glVertex2i(20, 365);

        glVertex2i(260, 365);

        glVertex2i(260, 555);

        glVertex2i(20, 555);

    glEnd();

    // Do not use a fixed-pixel scissor rectangle here. Scene 3 uses an
    // 800x600 logical coordinate system, so a fixed screen-pixel scissor
    // can clip the clouds out of the window on a larger GLUT window.
    if (rainOn)

    {

        glColor3f(0.7f, 0.8f, 0.95f);

        glLineWidth(2);

        glBegin(GL_LINES);

        for (int i = 0; i < NUM_DROPS; i++)

        {

            float fallen = fmod(rainDropY[i] + rainOffset, 190.0f);

            float dx = rainDropX[i];

            float topY = 555 - fallen;

            glVertex2f(dx, topY);

            glVertex2f(dx - 4, topY - 12);

        }

        glEnd();

        glLineWidth(1);

    }

    else

    {

        // clouds - multiple visible groups
        glColor3f(1, 1, 1);

        // Upper-left cloud
        draw_circle(60 + cloudX, 505, 18);
        draw_circle(82 + cloudX, 515, 24);
        draw_circle(108 + cloudX, 505, 18);

        // Upper-right cloud
        draw_circle(165 + cloudX, 500, 18);
        draw_circle(190 + cloudX, 512, 25);
        draw_circle(217 + cloudX, 500, 18);

        // Lower cloud group
        draw_circle(85 + cloudX, 425, 16);
        draw_circle(108 + cloudX, 435, 21);
        draw_circle(132 + cloudX, 425, 16);

    }

    // window cross bars

    glColor3f(0.2f, 0.2f, 0.2f);

    glBegin(GL_LINES);

        glVertex2i(140, 365); glVertex2i(140, 555);

        glVertex2i(20, 460);  glVertex2i(260, 460);

    glEnd();

    // window frame outline

    glBegin(GL_LINE_LOOP);

        glVertex2i(20, 365);

        glVertex2i(260, 365);

        glVertex2i(260, 555);

        glVertex2i(20, 555);

    glEnd();

}

// clock with rotating hands

void drawClock()

{

    float cx = 730, cy = 505, r = 40;

    glColor3f(1, 1, 1);

    draw_circle(cx, cy, r);

    glColor3f(0.13f, 0.13f, 0.13f);

    glBegin(GL_LINE_LOOP);

    for (int i = 0; i <= 360; i += 10)

    {

        float angle = i * 3.14159f / 180;

        glVertex2f(cx + r * cos(angle), cy + r * sin(angle));

    }

    glEnd();

    // 12 tick marks

    glBegin(GL_LINES);

    for (int i = 0; i < 12; i++)

    {

        float a = i * 30 * 3.14159f / 180;

        glVertex2f(cx + sin(a) * (r - 6), cy + cos(a) * (r - 6));

        glVertex2f(cx + sin(a) * (r - 2), cy + cos(a) * (r - 2));

    }

    glEnd();

    // hour hand

    float hourRad = clockAngle * 0.4f * 3.14159f / 180;

    glLineWidth(3);

    glBegin(GL_LINES);

        glVertex2f(cx, cy);

        glVertex2f(cx + sin(hourRad) * r * 0.5f, cy + cos(hourRad) * r * 0.5f);

    glEnd();

    // minute hand

    float minRad = clockAngle * 3.14159f / 180;

    glLineWidth(2);

    glBegin(GL_LINES);

        glVertex2f(cx, cy);

        glVertex2f(cx + sin(minRad) * r * 0.8f, cy + cos(minRad) * r * 0.8f);

    glEnd();

    glLineWidth(1);

    draw_circle(cx, cy, 3);

}

void drawBoard()

{

    glColor3f(1, 1, 1);

    glBegin(GL_QUADS);

        glVertex2i(290, 355);

        glVertex2i(630, 355);

        glVertex2i(630, 545);

        glVertex2i(290, 545);

    glEnd();

    glColor3f(0.2f, 0.2f, 0.2f);

    glBegin(GL_LINE_LOOP);

        glVertex2i(290, 355);

        glVertex2i(630, 355);

        glVertex2i(630, 545);

        glVertex2i(290, 545);

    glEnd();

}

// person shape

void drawPersonShape(float shirtR, float shirtG, float shirtB, bool pointing)

{

    const float x = 0, y = 0;

    drawSoftShadow(x, y - 4, 22, 6);

    drawQuad(x - 10, y, 7, 40, 0.15f, 0.15f, 0.20f);

    drawQuad(x + 3,  y, 7, 40, 0.15f, 0.15f, 0.20f);

    drawQuad(x - 13, y - 4, 12, 6, 0.95f, 0.95f, 0.95f);

    drawQuad(x + 2,  y - 4, 12, 6, 0.95f, 0.95f, 0.95f);

    drawQuadOutline(x - 13, y - 4, 12, 6, 0.1f, 0.1f, 0.1f, 1);

    drawQuadOutline(x + 2,  y - 4, 12, 6, 0.1f, 0.1f, 0.1f, 1);

    glColor3f(shirtR, shirtG, shirtB);

    glBegin(GL_POLYGON);

        glVertex2f(x - 16, y + 78);

        glVertex2f(x + 16, y + 78);

        glVertex2f(x + 10, y + 40);

        glVertex2f(x - 10, y + 40);

    glEnd();

    drawQuad(x + 10, y + 40, 6, 34, shirtR * 0.35f, shirtG * 0.35f, shirtB * 0.55f);

    // left arm always relaxed

    drawLine(x - 15, y + 72, x - 24, y + 55, shirtR, shirtG, shirtB, 6);

    drawLine(x - 24, y + 55, x - 20, y + 40, shirtR, shirtG, shirtB, 6);

    drawCircle(x - 20, y + 38, 4, 0.85f, 0.65f, 0.45f);

    if (pointing)

    {

        // right arm raised if pointing

        drawLine(x + 15, y + 72, x + 34, y + 68, shirtR, shirtG, shirtB, 6);

        drawLine(x + 34, y + 68, x + 58, y + 62, shirtR, shirtG, shirtB, 6);

        drawCircle(x + 60, y + 62, 4, 0.85f, 0.65f, 0.45f);

    }

    else

    {

        // right arm relaxed

        drawLine(x + 15, y + 72, x + 25, y + 55, shirtR, shirtG, shirtB, 6);

        drawLine(x + 25, y + 55, x + 21, y + 40, shirtR, shirtG, shirtB, 6);

        drawCircle(x + 21, y + 38, 4, 0.85f, 0.65f, 0.45f);

    }

    drawQuad(x - 4, y + 78, 8, 6, 0.85f, 0.65f, 0.45f);

    drawCircle(x, y + 96, 13, 0.85f, 0.65f, 0.45f);

    drawCircle(x, y + 104, 12, 0.08f, 0.06f, 0.05f);

    drawQuad(x - 12, y + 90, 24, 9, 0.85f, 0.65f, 0.45f);

    drawCircle(x - 5, y + 95, 1.5f, 0.10f, 0.10f, 0.10f);

    drawCircle(x + 5, y + 95, 1.5f, 0.10f, 0.10f, 0.10f);

    drawLine(x - 4, y + 90, x + 4, y + 90, 0.35f, 0.18f, 0.12f, 2);

}

void placePerson(float px, float py, float scale, float shirtR, float shirtG, float shirtB, bool pointing)

{

    glPushMatrix();

        glTranslatef(px, py, 0);

        glScalef(scale, scale, 1);

        drawPersonShape(shirtR, shirtG, shirtB, pointing);

    glPopMatrix();

}

void drawTeacher()

{

    placePerson(150, 200, 0.85f, 0.10f, 0.30f, 0.75f, true);

}

void drawDesk(float x, float y)

{

    glColor3f(0.54f, 0.35f, 0.17f);

    glBegin(GL_QUADS);

        glVertex2f(x - 35, y - 55); glVertex2f(x + 55, y - 55);

        glVertex2f(x + 55, y - 65); glVertex2f(x - 35, y - 65);

    glEnd();

    glColor3f(0.36f, 0.23f, 0.10f);

    glBegin(GL_QUADS);

        glVertex2f(x - 30, y - 65); glVertex2f(x - 24, y - 65); glVertex2f(x - 24, y - 90); glVertex2f(x - 30, y - 90);

        glVertex2f(x + 40, y - 65); glVertex2f(x + 46, y - 65); glVertex2f(x + 46, y - 90); glVertex2f(x + 40, y - 90);

    glEnd();

    // book

    glColor3f(0.60f, 0.40f, 0.80f);

    glBegin(GL_QUADS);

        glVertex2f(x - 15, y - 45); glVertex2f(x + 25, y - 45);

        glVertex2f(x + 25, y - 55); glVertex2f(x - 15, y - 55);

    glEnd();

}

void drawStudents()

{

    float pos[8][2] = {

        {310, 360}, {450, 360}, {590, 360}, {720, 360},

        {270, 220}, {450, 220}, {590, 220}, {730, 220}

    };

    float shirt[8][3] = {

        {0.18f, 0.36f, 0.23f},

        {0.48f, 0.23f, 0.23f},

        {0.23f, 0.23f, 0.23f},

        {0.48f, 0.23f, 0.23f},

        {0.20f, 0.20f, 0.20f},

        {0.13f, 0.33f, 0.67f},

        {0.23f, 0.23f, 0.23f},

        {0.48f, 0.23f, 0.23f}

    };

    for (int i = 0; i < 8; i++)

    {

        drawDesk(pos[i][0], pos[i][1]);

        placePerson(pos[i][0], pos[i][1] - 45, 0.7f, shirt[i][0], shirt[i][1], shirt[i][2], false);

    }

}

void display()

{

    glClear(GL_COLOR_BUFFER_BIT);

    drawRoom();

    drawWindow();

    drawClock();

    drawBoard();

    drawTeacher();

    drawStudents();

    glutSwapBuffers();

}

void keyboard(unsigned char key, int x, int y)

{

    if (key == 't' || key == 'T')

        clockRunning = !clockRunning;

    else if (key == 'c' || key == 'C')

        cloudsRunning = !cloudsRunning;

    else if (key == 'r' || key == 'R')

        rainOn = !rainOn;

}

void update(int value)

{

    if (clockRunning)

        clockAngle += 2;

    if (cloudsRunning)

    {

        cloudX += 1;

        if (cloudX > 60) cloudX = -60;

    }

    if (rainOn)

        rainOffset += 8;

    glutPostRedisplay();


}

void init()

{

    glClearColor(1, 1, 1, 1);

    glMatrixMode(GL_PROJECTION);

    gluOrtho2D(0, 800, 0, 600);

    initRain();

}

} // namespace Scene3

// ============================== SCENE 4 ==============================
namespace Scene4 {

const float VIRT_W = 1000.0f;

const float VIRT_H = 700.0f;

const float PI     = 3.14159265358979f;

int   windowW = 1000, windowH = 700;

bool  animating     = true;

float animTime      = 0.0f;

int   lastTimeMs    = 0;

bool  fanSpinning = true;

float fanAngle    = 0.0f;

float fanSpeed    = 8.0f;


bool  isZoomedIn  = false;

float currentZoom = 1.0f;

float targetZoom  = 1.0f;

float camX        = 0.0f;

float camY        = 0.0f;

float targetCamX  = 0.0f;

float targetCamY  = 0.0f;


const float TEACHER_START_X = 430.0f;

const float TEACHER_MIN_X   = -60.0f;

const float TEACHER_MAX_X   = 950.0f;

const float TEACHER_Y       = 78.0f;

const float TEACHER_SCALE   = 0.80f;

const float TEACHER_SPEED   = 140.0f;

float teacherX          = TEACHER_START_X;

bool  teacherFacingLeft  = false;

bool  teacherMovingLeft  = false;

bool  teacherMovingRight = false;

float teacherWalkPhase   = 0.0f;


void drawQuad(float x, float y, float w, float h, float r, float g, float b)

{

    glColor3f(r, g, b);

    glBegin(GL_QUADS);

        glVertex2f(x,     y);

        glVertex2f(x + w, y);

        glVertex2f(x + w, y + h);

        glVertex2f(x,     y + h);

    glEnd();

}

void drawQuadOutline(float x, float y, float w, float h, float r, float g, float b, float lw)

{

    glColor3f(r, g, b);

    glLineWidth(lw);

    glBegin(GL_LINE_LOOP);

        glVertex2f(x,     y);

        glVertex2f(x + w, y);

        glVertex2f(x + w, y + h);

        glVertex2f(x,     y + h);

    glEnd();

}

void drawLine(float x1, float y1, float x2, float y2, float r, float g, float b, float lw)

{

    glColor3f(r, g, b);

    glLineWidth(lw);

    glBegin(GL_LINES);

        glVertex2f(x1, y1);

        glVertex2f(x2, y2);

    glEnd();

}

void drawCircle(float cx, float cy, float radius, float r, float g, float b)

{

    glColor3f(r, g, b);

    glBegin(GL_TRIANGLE_FAN);

        glVertex2f(cx, cy);

        for (int i = 0; i <= 36; ++i) {

            float t = 2.0f * PI * i / 36.0f;

            glVertex2f(cx + radius * cosf(t), cy + radius * sinf(t));

        }

    glEnd();

}

void drawCircleOutline(float cx, float cy, float radius, float r, float g, float b, float lw)

{

    glColor3f(r, g, b);

    glLineWidth(lw);

    glBegin(GL_LINE_LOOP);

        for (int i = 0; i < 36; ++i) {

            float t = 2.0f * PI * i / 36.0f;

            glVertex2f(cx + radius * cosf(t), cy + radius * sinf(t));

        }

    glEnd();

}

void drawEllipse(float cx, float cy, float rw, float rh, float r, float g, float b, float a)

{

    glColor4f(r, g, b, a);

    glBegin(GL_TRIANGLE_FAN);

        glVertex2f(cx, cy);

        for (int i = 0; i <= 36; ++i) {

            float t = 2.0f * PI * i / 36.0f;

            glVertex2f(cx + rw * cosf(t), cy + rh * sinf(t));

        }

    glEnd();

}

void drawEllipseOutline(float cx, float cy, float rw, float rh, float r, float g, float b, float lw)

{

    glColor3f(r, g, b);

    glLineWidth(lw);

    glBegin(GL_LINE_LOOP);

        for (int i = 0; i < 36; ++i) {

            float t = 2.0f * PI * i / 36.0f;

            glVertex2f(cx + rw * cosf(t), cy + rh * sinf(t));

        }

    glEnd();

}

void drawSoftShadow(float x, float y, float w, float h)

{

    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    drawEllipse(x, y, w * 0.5f, h * 0.5f, 0.0f, 0.0f, 0.0f, 0.25f);

    glDisable(GL_BLEND);

}


void drawQuadAlpha(float x, float y, float w, float h, float r, float g, float b, float a)

{

    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor4f(r, g, b, a);

    glBegin(GL_QUADS);

        glVertex2f(x,     y);

        glVertex2f(x + w, y);

        glVertex2f(x + w, y + h);

        glVertex2f(x,     y + h);

    glEnd();

    glDisable(GL_BLEND);

}


void drawGradientQuad(float x, float y, float w, float h,

                       float rBot, float gBot, float bBot,

                       float rTop, float gTop, float bTop)

{

    glBegin(GL_QUADS);

        glColor3f(rBot, gBot, bBot); glVertex2f(x,     y);

        glColor3f(rBot, gBot, bBot); glVertex2f(x + w, y);

        glColor3f(rTop, gTop, bTop); glVertex2f(x + w, y + h);

        glColor3f(rTop, gTop, bTop); glVertex2f(x,     y + h);

    glEnd();

}

void drawGradientQuadAlpha(float x, float y, float w, float h,

                            float rBot, float gBot, float bBot, float aBot,

                            float rTop, float gTop, float bTop, float aTop)

{

    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glBegin(GL_QUADS);

        glColor4f(rBot, gBot, bBot, aBot); glVertex2f(x,     y);

        glColor4f(rBot, gBot, bBot, aBot); glVertex2f(x + w, y);

        glColor4f(rTop, gTop, bTop, aTop); glVertex2f(x + w, y + h);

        glColor4f(rTop, gTop, bTop, aTop); glVertex2f(x,     y + h);

    glEnd();

    glDisable(GL_BLEND);

}

void drawTriangleAlpha(float x1, float y1, float x2, float y2, float x3, float y3,

                        float r, float g, float b, float a)

{

    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor4f(r, g, b, a);

    glBegin(GL_TRIANGLES);

        glVertex2f(x1, y1);

        glVertex2f(x2, y2);

        glVertex2f(x3, y3);

    glEnd();

    glDisable(GL_BLEND);

}


void drawVignette()

{

    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    drawEllipse(0.0f,      0.0f,      260, 220, 0.0f, 0.0f, 0.0f, 0.16f);

    drawEllipse(VIRT_W,    0.0f,      260, 220, 0.0f, 0.0f, 0.0f, 0.16f);

    drawEllipse(0.0f,      VIRT_H,    260, 220, 0.0f, 0.0f, 0.0f, 0.16f);

    drawEllipse(VIRT_W,    VIRT_H,    260, 220, 0.0f, 0.0f, 0.0f, 0.16f);

    glDisable(GL_BLEND);

}

void drawText(float x, float y, const char* text, void* font = GLUT_BITMAP_HELVETICA_18,

              float r = 0.0f, float g = 0.0f, float b = 0.0f)

{

    glColor3f(r, g, b);

    glRasterPos2f(x, y);

    for (const char* c = text; *c; ++c) glutBitmapCharacter(font, *c);

}

struct PersonStyle

{

    float shirtR,  shirtG,  shirtB;

    float sleeveR, sleeveG, sleeveB;

    float pantsR,  pantsG,  pantsB;

    float skinR,   skinG,   skinB;

    float hairR,   hairG,   hairB;

};

PersonStyle mkStyle(float shR, float shG, float shB,

                     float paR, float paG, float paB,

                     float skR, float skG, float skB,

                     float haR, float haG, float haB)

{

    PersonStyle s;

    s.shirtR = shR; s.shirtG = shG; s.shirtB = shB;

    s.sleeveR = shR; s.sleeveG = shG; s.sleeveB = shB;

    s.pantsR = paR; s.pantsG = paG; s.pantsB = paB;

    s.skinR  = skR; s.skinG  = skG; s.skinB  = skB;

    s.hairR  = haR; s.hairG  = haG; s.hairB  = haB;

    return s;

}

void drawPerson(float x, float y, float scale, const PersonStyle& s,

                 float legSwingL, float legSwingR,

                 float armSwingL, float armLiftL,

                 float armSwingR, float armLiftR,

                 float headTilt, bool facingLeft,

                 bool lanyard = false, bool glasses = false)

{

    glPushMatrix();

        glTranslatef(x, y, 0.0f);

        glScalef(facingLeft ? -scale : scale, scale, 1.0f);

        drawSoftShadow(0, -4, 22, 6);


        drawQuad(-10 + legSwingL, 0, 7, 40, s.pantsR, s.pantsG, s.pantsB);

        drawQuad( 3  + legSwingR, 0, 7, 40, s.pantsR, s.pantsG, s.pantsB);

        drawLine(-6.5f + legSwingL, 2, -6.5f + legSwingL, 38, s.pantsR * 0.65f, s.pantsG * 0.65f, s.pantsB * 0.65f, 1.0f);

        drawLine( 6.5f + legSwingR, 2,  6.5f + legSwingR, 38, s.pantsR * 0.65f, s.pantsG * 0.65f, s.pantsB * 0.65f, 1.0f);


        drawQuad(-13 + legSwingL, -4, 12, 6, 0.95f, 0.95f, 0.95f);

        drawQuad( 2  + legSwingR, -4, 12, 6, 0.95f, 0.95f, 0.95f);

        drawQuad(-13 + legSwingL, -4, 12, 2, 0.55f, 0.55f, 0.58f);

        drawQuad( 2  + legSwingR, -4, 12, 2, 0.55f, 0.55f, 0.58f);

        drawQuadOutline(-13 + legSwingL, -4, 12, 6, 0.1f, 0.1f, 0.1f, 1);

        drawQuadOutline( 2  + legSwingR, -4, 12, 6, 0.1f, 0.1f, 0.1f, 1);

        glColor3f(s.shirtR, s.shirtG, s.shirtB);

        glBegin(GL_POLYGON);

            glVertex2f(-16, 78);

            glVertex2f( 16, 78);

            glVertex2f( 10, 40);

            glVertex2f(-10, 40);

        glEnd();

        drawQuad(10, 40, 6, 34, s.shirtR * 0.55f, s.shirtG * 0.55f, s.shirtB * 0.55f);

        drawTriangleAlpha(-14, 76, 2, 76, -8, 42, 1.0f, 1.0f, 1.0f, 0.16f);


        drawLine(-6, 78, 0, 71, s.shirtR * 0.5f, s.shirtG * 0.5f, s.shirtB * 0.5f, 2.0f);

        drawLine( 6, 78, 0, 71, s.shirtR * 0.5f, s.shirtG * 0.5f, s.shirtB * 0.5f, 2.0f);


        drawLine(-15, 72, -24 + armSwingL, 55 + armLiftL, s.sleeveR, s.sleeveG, s.sleeveB, 6);

        drawLine(-24 + armSwingL, 55 + armLiftL, -20 + armSwingL, 40 + armLiftL, s.sleeveR, s.sleeveG, s.sleeveB, 6);

        drawCircle(-20 + armSwingL, 38 + armLiftL, 4, s.skinR, s.skinG, s.skinB);


        drawLine(15, 72, 25 + armSwingR, 55 + armLiftR, s.sleeveR, s.sleeveG, s.sleeveB, 6);

        drawLine(25 + armSwingR, 55 + armLiftR, 21 + armSwingR, 40 + armLiftR, s.sleeveR, s.sleeveG, s.sleeveB, 6);

        drawCircle(21 + armSwingR, 38 + armLiftR, 4, s.skinR, s.skinG, s.skinB);


        drawQuad(-4, 78, 8, 6, s.skinR, s.skinG, s.skinB);

        drawCircle(0 + headTilt, 96, 13, s.skinR, s.skinG, s.skinB);

        drawTriangleAlpha(-9 + headTilt, 104, 3 + headTilt, 104, -6 + headTilt, 88, 1.0f, 1.0f, 1.0f, 0.10f);


        drawEllipse(0 + headTilt, 105, 13.5f, 11.0f, s.hairR, s.hairG, s.hairB, 1.0f);

        drawQuad(-13 + headTilt, 90, 26, 9, s.skinR, s.skinG, s.skinB);

        drawQuad(-13 + headTilt, 92, 5, 11, s.hairR, s.hairG, s.hairB);

        drawQuad( 8  + headTilt, 92, 5, 11, s.hairR, s.hairG, s.hairB);


        drawCircle(-5 + headTilt, 95, 1.5f, 0.10f, 0.10f, 0.10f);

        drawCircle( 5 + headTilt, 95, 1.5f, 0.10f, 0.10f, 0.10f);

        drawLine(-4 + headTilt, 90, 4 + headTilt, 90, 0.35f, 0.18f, 0.12f, 2);

        if (lanyard) {

            drawLine(-4, 80, -4, 55, 0.70f, 0.58f, 0.14f, 3);

            drawLine( 4, 80,  4, 55, 0.70f, 0.58f, 0.14f, 3);


            drawQuad(-3, 52, 6, 4, 0.75f, 0.75f, 0.78f);

            drawQuadOutline(-3, 52, 6, 4, 0.35f, 0.35f, 0.38f, 1);

            drawCircle(0, 54, 1.2f, 0.55f, 0.55f, 0.58f);


            drawQuadAlpha(-6, 29, 14, 22, 0.0f, 0.0f, 0.0f, 0.16f);

            drawQuad(-7, 30, 14, 22, 0.97f, 0.97f, 0.96f);

            drawQuadOutline(-7, 30, 14, 22, 0.25f, 0.25f, 0.28f, 1.2f);


            drawQuad(-7, 46, 14, 6, 0.10f, 0.18f, 0.40f);


            drawQuad(-5.5f, 36, 5, 7, 0.72f, 0.58f, 0.46f);

            drawQuadOutline(-5.5f, 36, 5, 7, 0.30f, 0.30f, 0.32f, 0.8f);

            drawLine(0.5f, 41, 6, 41, 0.50f, 0.50f, 0.52f, 1.0f);

            drawLine(0.5f, 38, 6, 38, 0.50f, 0.50f, 0.52f, 1.0f);

            drawLine(-6, 33, 6, 33, 0.55f, 0.55f, 0.58f, 1.2f);

        }


        if (glasses) {

            drawCircleOutline(-5 + headTilt, 95, 4.2f, 0.08f, 0.08f, 0.08f, 1.5f);

            drawCircleOutline( 5 + headTilt, 95, 4.2f, 0.08f, 0.08f, 0.08f, 1.5f);

            drawLine(-1 + headTilt, 95, 1 + headTilt, 95, 0.08f, 0.08f, 0.08f, 1.5f);

        }

    glPopMatrix();

}


void drawStandingIdle(float x, float y, float scale, const PersonStyle& s, float phase, float gesture,

                       bool facingLeft, bool lanyard = false, bool glasses = false)

{

    float bob   = sinf(phase) * 1.5f;

    float armL  = 5.0f * sinf(phase * 0.7f + gesture);

    float liftL = 3.0f + 4.0f * sinf(phase * 0.5f + gesture);

    float armR  = 5.0f * sinf(phase * 0.7f + gesture + 1.5f);

    float liftR = 3.0f + 4.0f * sinf(phase * 0.5f + gesture + 1.5f);

    drawPerson(x, y + bob, scale, s, 0, 0, armL, liftL, armR, liftR, 0, facingLeft, lanyard, glasses);

}


void drawWalking(float x, float y, float scale, const PersonStyle& s, float phase, bool facingLeft,

                  bool lanyard = false, bool glasses = false)

{

    float legL = sinf(phase) * 7.0f;

    float legR = -sinf(phase) * 7.0f;

    float bob  = fabsf(sinf(phase)) * 3.0f;

    drawPerson(x, y + bob, scale, s, legL, legR, -legL * 0.9f, 0.0f, -legR * 0.9f, 0.0f, 0, facingLeft, lanyard, glasses);

}


void drawThoughtBubble(float cx, float cy)

{

    drawEllipse(cx + 5.0f, cy - 7.0f, 80.0f, 48.0f, 0.0f, 0.0f, 0.0f, 0.14f);


    drawEllipse(cx, cy, 80.0f, 48.0f, 1.0f, 1.0f, 1.0f, 1.0f);

    drawEllipseOutline(cx, cy, 80.0f, 48.0f, 0.20f, 0.20f, 0.22f, 2.0f);


    drawText(cx - 36.0f, cy + 10.0f, "What should", GLUT_BITMAP_HELVETICA_18, 0.15f, 0.15f, 0.17f);

    drawText(cx - 26.0f, cy - 12.0f, "I write?",    GLUT_BITMAP_HELVETICA_18, 0.15f, 0.15f, 0.17f);

}

void drawExamStudent(float x, float y, float scale, const PersonStyle& s, float phase, bool showThoughtBubble)

{

    float deskR = 0.55f, deskG = 0.35f, deskB = 0.20f;


    drawQuad(x - 30 * scale, y, 6 * scale, 35 * scale, deskR * 0.5f, deskG * 0.5f, deskB * 0.5f);

    drawQuad(x + 24 * scale, y, 6 * scale, 35 * scale, deskR * 0.5f, deskG * 0.5f, deskB * 0.5f);

    float headTilt    = showThoughtBubble ? 4.0f : 0.0f;

    float writeWiggle = showThoughtBubble ? 0.0f : 2.0f * sinf(phase * 8.0f);

    float armSwingR   = -2.0f + writeWiggle;

    float armSwingL = showThoughtBubble ? 14.0f : 2.0f;

    float armLiftL  = showThoughtBubble ? 30.0f : -15.0f;

    drawPerson(x, y + 10 * scale, scale, s, 0, 0, armSwingL, armLiftL, armSwingR, -15.0f, headTilt, false);


    drawGradientQuad(x - 45 * scale, y + 30 * scale, 90 * scale, 15 * scale,

                      deskR * 0.85f, deskG * 0.85f, deskB * 0.85f, deskR * 1.1f, deskG * 1.1f, deskB * 1.1f);

    drawLine(x - 40 * scale, y + 34 * scale, x + 40 * scale, y + 35 * scale, deskR * 0.55f, deskG * 0.55f, deskB * 0.55f, 1.0f);

    drawLine(x - 40 * scale, y + 40 * scale, x + 40 * scale, y + 41 * scale, deskR * 0.55f, deskG * 0.55f, deskB * 0.55f, 1.0f);

    drawQuadOutline(x - 45 * scale, y + 30 * scale, 90 * scale, 15 * scale, deskR * 0.4f, deskG * 0.4f, deskB * 0.4f, 1.5f);


    drawQuad(x - 15 * scale, y + 35 * scale, 30 * scale, 15 * scale, 0.98f, 0.98f, 0.95f);

    drawQuadOutline(x - 15 * scale, y + 35 * scale, 30 * scale, 15 * scale, 0.6f, 0.6f, 0.6f, 1);

    if (!showThoughtBubble) {

        drawLine(x - 12 * scale, y + 44 * scale, x + 10 * scale, y + 44 * scale, 0.55f, 0.55f, 0.55f, 1);

        drawLine(x - 12 * scale, y + 40 * scale, x + 6  * scale, y + 40 * scale, 0.55f, 0.55f, 0.55f, 1);

    }

    if (showThoughtBubble) {

        drawThoughtBubble(x, y + 180.0f * scale);

    }

}

void drawRotatingFan(float cx, float cy, float angle)

{

    drawQuad(cx - 1.5f, cy, 3, 50, 0.15f, 0.15f, 0.16f);

    drawCircle(cx, cy, 9, 0.22f, 0.22f, 0.25f);

    drawCircle(cx - 2, cy + 2, 3, 0.45f, 0.45f, 0.5f);

    glPushMatrix();

        glTranslatef(cx, cy, 0.0f);

        glRotatef(angle, 0.0f, 0.0f, 1.0f);

        for (int i = 0; i < 3; ++i) {

            glRotatef(120.0f, 0.0f, 0.0f, 1.0f);

            drawQuad(-6, 0, 12, 60, 0.28f, 0.28f, 0.33f);

            drawQuad(-6, 0, 4, 60, 0.40f, 0.40f, 0.46f);

            drawQuadOutline(-6, 0, 12, 60, 0.10f, 0.10f, 0.10f, 1.0f);

        }

    glPopMatrix();

}

void drawWindow(float x, float y, float w, float h, bool withSun)

{

    drawGradientQuad(x, y, w, h, 0.55f, 0.78f, 0.92f, 0.72f, 0.88f, 0.98f);

    if (withSun) {

        float sx = x + w * 0.5f, sy = y + h * 0.62f, sr = w * 0.22f;

        drawEllipse(sx, sy, sr * 1.8f, sr * 1.8f, 1.0f, 0.95f, 0.55f, 0.35f);

        for (int k = 0; k < 8; ++k) {

            float ang = k * (PI / 4.0f);

            drawLine(sx + cosf(ang) * sr * 1.15f, sy + sinf(ang) * sr * 1.15f,

                     sx + cosf(ang) * sr * 1.55f, sy + sinf(ang) * sr * 1.55f,

                     0.98f, 0.80f, 0.20f, 2.0f);

        }

        drawCircle(sx, sy, sr, 0.98f, 0.85f, 0.30f);

        drawCircleOutline(sx, sy, sr, 0.85f, 0.60f, 0.10f, 1.5f);

    } else {

        drawEllipse(x + w * 0.30f, y + h * 0.68f, w * 0.24f, h * 0.07f, 1.0f, 1.0f, 1.0f, 0.85f);

        drawEllipse(x + w * 0.58f, y + h * 0.75f, w * 0.18f, h * 0.06f, 1.0f, 1.0f, 1.0f, 0.85f);

    }


    drawQuadOutline(x, y, w, h, 0.28f, 0.18f, 0.09f, 3);

    drawLine(x + w / 2, y, x + w / 2, y + h, 0.28f, 0.18f, 0.09f, 2);

    drawLine(x, y + h / 2, x + w, y + h / 2, 0.28f, 0.18f, 0.09f, 2);


    drawTriangleAlpha(x - 4, y + h + 6, x + w * 0.32f, y + h + 6, x - 4, y + h * 0.35f, 0.55f, 0.16f, 0.20f, 0.85f);

    drawTriangleAlpha(x + w + 4, y + h + 6, x + w * 0.68f, y + h + 6, x + w + 4, y + h * 0.35f, 0.55f, 0.16f, 0.20f, 0.85f);

    drawLine(x - 4, y + h + 6, x + w + 4, y + h + 6, 0.35f, 0.10f, 0.13f, 4);

}

void drawCeilingPanel(float x, float y, float w, float h)

{

    drawQuadAlpha(x - 6, y - 4, w + 12, h + 8, 1.0f, 1.0f, 0.95f, 0.20f);

    drawQuad(x, y, w, h, 0.97f, 0.97f, 0.94f);

    drawQuadOutline(x, y, w, h, 0.55f, 0.55f, 0.50f, 1.5f);

    drawLine(x + w * 0.2f, y + h * 0.5f, x + w * 0.8f, y + h * 0.5f, 0.80f, 0.80f, 0.75f, 1.0f);

}

PersonStyle styleMainBlue = mkStyle(0.10f, 0.35f, 0.80f,  0.15f, 0.15f, 0.20f,  0.85f, 0.60f, 0.38f,  0.08f, 0.06f, 0.05f);

PersonStyle styleTeacher  = mkStyle(0.60f, 0.75f, 0.90f,  0.15f, 0.15f, 0.25f,  0.80f, 0.60f, 0.40f,  0.10f, 0.08f, 0.06f);

void drawClassroomScene()

{

    const float FLOOR_H = 370.0f;

    const float WALL_Y  = FLOOR_H;

    drawGradientQuad(0, 0, VIRT_W, FLOOR_H, 0.42f, 0.28f, 0.18f, 0.58f, 0.40f, 0.25f);

    for (float px = -80; px < VIRT_W + 80; px += 65)

        drawLine(px, 0, px + 70, FLOOR_H, 0.30f, 0.18f, 0.10f, 1.0f);

    drawLine(0, FLOOR_H, VIRT_W, FLOOR_H, 0.20f, 0.12f, 0.07f, 2.0f);

    drawGradientQuad(0, WALL_Y, VIRT_W, VIRT_H - WALL_Y, 0.86f, 0.84f, 0.78f, 0.95f, 0.94f, 0.90f);

    drawQuad(205, 375, 450, 215, 0.10f, 0.28f, 0.16f);

    drawQuadOutline(205, 375, 450, 215, 0.32f, 0.20f, 0.11f, 8);

    drawQuadAlpha(205, 375, 450, 215, 1.0f, 1.0f, 1.0f, 0.04f);

    drawText(305, 550, "Mid-Term Examination", GLUT_BITMAP_HELVETICA_18, 0.92f, 0.92f, 0.85f);

    drawText(305, 500, "Room no : DS0307",     GLUT_BITMAP_HELVETICA_18, 0.92f, 0.92f, 0.85f);

    drawLine(275, 473, 595, 473, 0.85f, 0.85f, 0.80f, 1.5f);

    drawWindow(670, 380, 100, 310, true);

    drawWindow(785, 380, 100, 310, false);

    drawWindow(900, 380, 100, 310, false);

    drawQuad(30, 400, 170, 160, 0.95f, 0.95f, 0.95f);

    drawQuadOutline(30, 400, 170, 160, 0.3f, 0.3f, 0.3f, 3);

    drawText(48, 528, "EXAM HALL", GLUT_BITMAP_HELVETICA_18, 0.05f, 0.05f, 0.05f);

    drawText(60, 480, "SILENCE",   GLUT_BITMAP_HELVETICA_18, 0.75f, 0.08f, 0.08f);

    drawText(65, 450, "PLEASE",    GLUT_BITMAP_HELVETICA_18, 0.75f, 0.08f, 0.08f);

    {

        float clockCx = 205 + 450 * 0.5f;

        float clockCy = 375 + 215 + 40.0f;

        drawCircle(clockCx, clockCy, 30, 0.98f, 0.98f, 0.98f);

        drawCircleOutline(clockCx, clockCy, 30, 0.1f, 0.1f, 0.1f, 2);

        drawLine(clockCx, clockCy, clockCx, clockCy + 21, 0.1f, 0.1f, 0.1f, 2);

        drawLine(clockCx, clockCy, clockCx + 15, clockCy, 0.1f, 0.1f, 0.1f, 2);

    }

    drawCeilingPanel(90, 675, 140, 16);

    drawCeilingPanel(770, 675, 140, 16);

    drawRotatingFan(500, 655, fanAngle);

    struct Row { float y, scale, xStart, xStep; int cols; };

    Row rows[4] = {

        { 300.0f, 0.62f, -30.0f, 145.0f, 7 },

        { 225.0f, 0.72f, -40.0f, 155.0f, 7 },

        { 130.0f, 0.85f, -10.0f, 185.0f, 6 },

        {  30.0f, 1.00f, -30.0f, 195.0f, 6 },

    };

    const int focusRow = 2, focusCol = 2;

    int styleIndex = 0;

    for (int r = 0; r < 4; ++r) {

        for (int c = 0; c < rows[r].cols; ++c) {

            float sx = rows[r].xStart + c * rows[r].xStep;

            float sy = rows[r].y;

            PersonStyle altStyle = styleMainBlue;

            if (styleIndex % 2 == 1) altStyle.shirtR = 0.5f;

            ++styleIndex;

            bool isFocus = (r == focusRow && c == focusCol);

            bool showThoughtBubble = isFocus && isZoomedIn && fabsf(currentZoom - targetZoom) < 0.05f;

            drawExamStudent(sx, sy, rows[r].scale, altStyle, animTime + r * 3 + c, showThoughtBubble);

        }

    }

    bool teacherIsMoving = teacherMovingLeft || teacherMovingRight;

    if (teacherIsMoving)

        drawWalking(teacherX, TEACHER_Y, TEACHER_SCALE, styleTeacher, teacherWalkPhase, teacherFacingLeft, true, true);

    else

        drawStandingIdle(teacherX, TEACHER_Y, TEACHER_SCALE, styleTeacher, animTime * 0.8f, 0.0f, teacherFacingLeft, true, true);

}

void drawHUD()

{

    drawGradientQuadAlpha(0, VIRT_H - 36, VIRT_W, 36, 0.0f, 0.0f, 0.0f, 0.20f, 0.0f, 0.0f, 0.0f, 0.60f);

    drawLine(0, VIRT_H - 36, VIRT_W, VIRT_H - 36, 0.95f, 0.75f, 0.25f, 1.5f);

    drawGradientQuadAlpha(0, 0, VIRT_W, 22, 0.0f, 0.0f, 0.0f, 0.60f, 0.0f, 0.0f, 0.0f, 0.15f);

    drawLine(0, 22, VIRT_W, 22, 0.95f, 0.75f, 0.25f, 1.0f);

    drawText(50, VIRT_H - 23, "Classroom  -  Mid-Term Exam in Progress",

             GLUT_BITMAP_HELVETICA_18, 1.0f, 1.0f, 1.0f);

    drawText(10, 5,

        "[SPACE] Pause   [f] Fan   [v] Reverse   [x/y] Fan speed   [i/o] Zoom student   [<-/->] Move teacher   [r] Reset   [ESC] Quit",

        GLUT_BITMAP_HELVETICA_10, 0.92f, 0.92f, 0.92f);

}


void init()

{

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

}

void reshape(int w, int h)

{

    windowW = w; windowH = h;

    if (h == 0) h = 1;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluOrtho2D(0, VIRT_W, 0, VIRT_H);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

}

void display()

{

    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();


    glPushMatrix();

        glTranslatef(VIRT_W / 2.0f, VIRT_H / 2.0f, 0.0f);

        glScalef(currentZoom, currentZoom, 1.0f);

        glTranslatef(-VIRT_W / 2.0f - camX, -VIRT_H / 2.0f - camY, 0.0f);

        drawClassroomScene();

    glPopMatrix();

    drawVignette();

    drawHUD();

    glutSwapBuffers();

}

void idleFunc()

{

    int now = glutGet(GLUT_ELAPSED_TIME);

    float dt = (now - lastTimeMs) / 1000.0f;

    lastTimeMs = now;

    if (animating) {

        animTime += dt;

        if (fanSpinning) {

            fanAngle += fanSpeed;

            if (fanAngle >= 360.0f) fanAngle -= 360.0f;

            if (fanAngle <= -360.0f) fanAngle += 360.0f;

        }

    }


    currentZoom += (targetZoom - currentZoom) * 0.08f;

    camX        += (targetCamX - camX) * 0.08f;

    camY        += (targetCamY - camY) * 0.08f;

    if (animating) {

        float moveDir = 0.0f;

        if (teacherMovingLeft)  moveDir -= 1.0f;

        if (teacherMovingRight) moveDir += 1.0f;

        if (moveDir != 0.0f) {

            teacherX += moveDir * TEACHER_SPEED * dt;

            if (teacherX < TEACHER_MIN_X) teacherX = TEACHER_MIN_X;

            if (teacherX > TEACHER_MAX_X) teacherX = TEACHER_MAX_X;

            teacherFacingLeft = moveDir < 0.0f;

            teacherWalkPhase += dt * 9.0f;

        }

    }

    glutPostRedisplay();

}


float fanDir() { return fanSpeed >= 0.0f ? 1.0f : -1.0f; }


void resetView()

{

    fanSpeed    = 8.0f;

    fanSpinning = true;

    isZoomedIn  = false;

    targetZoom  = 1.0f;

    targetCamX  = 0.0f;

    targetCamY  = 0.0f;

    teacherX          = TEACHER_START_X;

    teacherFacingLeft = false;

    teacherMovingLeft  = false;

    teacherMovingRight = false;

}

void keyboard(unsigned char key, int, int)

{

    switch (key) {

        case 'f': fanSpinning = !fanSpinning; break;

        case 'v': fanSpeed = -fanSpeed; break;

        case 'y': fanSpeed += fanDir() * 2.0f; break;

        case 'x': {

            float mag = fabsf(fanSpeed) - 2.0f;

            if (mag < 0.0f) mag = 0.0f;

            fanSpeed = fanDir() * mag;

            break;

        }


        case 'i':

            isZoomedIn = true;

            targetZoom = 1.8f;

            targetCamX = -140.0f;

            targetCamY = -130.0f;

            break;

        case 'o':

            isZoomedIn = false;

            targetZoom = 1.0f;

            targetCamX = 0.0f;

            targetCamY = 0.0f;

            break;

        case 'r': resetView(); break;

        case ' ': animating = !animating; break;

        case 27:  exit(0);

        default: break;

    }

}


void specialKeyDown(int key, int, int)

{

    if      (key == GLUT_KEY_LEFT)  teacherMovingLeft  = true;

    else if (key == GLUT_KEY_RIGHT) teacherMovingRight = true;

}

void specialKeyUp(int key, int, int)

{

    if      (key == GLUT_KEY_LEFT)  teacherMovingLeft  = false;

    else if (key == GLUT_KEY_RIGHT) teacherMovingRight = false;

}

} // namespace Scene4

// ============================== SCENE 5 ==============================
namespace Scene5 {

const int WIN_W = 900;

const int WIN_H = 650;


float fanAngle = 0.0f;

float human1X = 360.0f;

float human2X = 660.0f;

float movementSpeed = 2.0f;

bool animationRunning = false;


void drawCircle(float cx, float cy, float r, int segments = 60)

{

    glBegin(GL_POLYGON);

    for (int i = 0; i < segments; i++)

    {

        float theta = 2.0f * 3.1415926f * i / segments;

        float x = cx + r * cosf(theta);

        float y = cy + r * sinf(theta);

        glVertex2f(x, y);

    }

    glEnd();

}

// ============================================================

// DRAW ELLIPSE

// ============================================================

void drawEllipse(float cx, float cy, float rx, float ry, int segments = 60)

{

    glBegin(GL_POLYGON);

    for (int i = 0; i < segments; i++)

    {

        float theta = 2.0f * 3.1415926f * i / segments;

        float x = cx + rx * cosf(theta);

        float y = cy + ry * sinf(theta);

        glVertex2f(x, y);

    }

    glEnd();

}


void drawText(float x, float y, const char *text, void *font = GLUT_BITMAP_HELVETICA_18)

{

    glRasterPos2f(x, y);

    for (const char *c = text; *c != '\0'; c++)

        glutBitmapCharacter(font, *c);

}


void drawRoom()

{

    glColor3f(0.90f, 0.85f, 0.70f);

    glBegin(GL_QUADS);

    glVertex2f(0, 120);

    glVertex2f(900, 120);

    glVertex2f(900, 600);

    glVertex2f(0, 600);

    glEnd();



    glColor3f(0.80f, 0.78f, 0.72f);

    glBegin(GL_QUADS);

    glVertex2f(0, 580);

    glVertex2f(900, 580);

    glVertex2f(900, 650);

    glVertex2f(0, 650);

    glEnd();



    glColor3f(0.55f, 0.40f, 0.28f);

    glBegin(GL_QUADS);

    glVertex2f(0, 0);

    glVertex2f(900, 0);

    glVertex2f(900, 120);

    glVertex2f(0, 120);

    glEnd();



    glColor3f(0.45f, 0.32f, 0.20f);

    glLineWidth(1.0f);

    glBegin(GL_LINES);

    for (int x = 0; x <= 900; x += 60)

    {

        glVertex2f((float)x, 0);

        glVertex2f((float)x, 120);

    }

    glEnd();

}

void drawLibraryView()

{

    float wx1 = 230;

    float wy1 = 120;

    float wx2 = 670;

    float wy2 = 578;


    glColor3f(0.55f, 0.75f, 0.95f);

    glBegin(GL_QUADS);

    glVertex2f(wx1, wy1);

    glVertex2f(wx2, wy1);

    glVertex2f(wx2, wy2);

    glVertex2f(wx1, wy2);

    glEnd();



    glColor3f(0.65f, 0.65f, 0.55f);

    glBegin(GL_QUADS);

    glVertex2f(wx1, wy1);

    glVertex2f(wx2, wy1);

    glVertex2f(wx2, wy1 + 45);

    glVertex2f(wx1, wy1 + 45);

    glEnd();



    glColor3f(0.60f, 0.62f, 0.65f);

    glBegin(GL_QUADS);

    glVertex2f(250, 174);

    glVertex2f(430, 174);

    glVertex2f(430, 430);

    glVertex2f(250, 430);

    glEnd();



    glColor3f(0.22f, 0.40f, 0.18f);

    glBegin(GL_QUADS);

    glVertex2f(250, 425);

    glVertex2f(430, 425);

    glVertex2f(430, 435);

    glVertex2f(250, 435);

    glEnd();



    glColor3f(0.30f, 0.45f, 0.55f);

    for (int row = 0; row < 7; row++)

    {

        for (int col = 0; col < 5; col++)

        {

            float bx = 260 + col * 33;

            float by = 190 + row * 32;

            glBegin(GL_QUADS);

            glVertex2f(bx, by);

            glVertex2f(bx + 24, by);

            glVertex2f(bx + 24, by + 20);

            glVertex2f(bx, by + 20);

            glEnd();

        }

    }

    glColor3f(0.05f, 0.05f, 0.05f);

    drawText(275, 405, "D BUILDING", GLUT_BITMAP_HELVETICA_18);



    glColor3f(0.72f, 0.72f, 0.75f);

    drawCircle(545, 305, 130);



    glColor3f(0.25f, 0.40f, 0.55f);

    for (int i = 0; i < 4; i++)

    {

        float by = 240 + i * 32;

        glBegin(GL_QUADS);

        glVertex2f(420, by);

        glVertex2f(670, by);

        glVertex2f(670, by + 16);

        glVertex2f(420, by + 16);

        glEnd();

    }



    glColor3f(0.2f, 0.2f, 0.2f);

    glBegin(GL_LINES);

    glVertex2f(545, 435);

    glVertex2f(545, 465);

    glEnd();



    glColor3f(0.35f, 0.22f, 0.12f);

    glBegin(GL_QUADS);

    glVertex2f(525, 175);

    glVertex2f(565, 175);

    glVertex2f(565, 235);

    glVertex2f(525, 235);

    glEnd();

    glColor3f(0.45f, 0.60f, 0.68f);

    glBegin(GL_QUADS);

    glVertex2f(530, 178);

    glVertex2f(560, 178);

    glVertex2f(560, 232);

    glVertex2f(530, 232);

    glEnd();



    glColor3f(0.85f, 0.75f, 0.30f);

    drawCircle(555, 205, 2.5f);

    glColor3f(0.05f, 0.05f, 0.35f);

    drawText(508, 360, "AIUB LIBRARY", GLUT_BITMAP_HELVETICA_12);



    struct TreeSpot

    {

        float x;

        float y;

        float r;

    };

    TreeSpot trees[] =

    {

        {245, 190, 16},

        {275, 185, 12},

        {440, 195, 18},

        {460, 182, 11},

        {560, 190, 15},

        {600, 185, 13},

        {630, 195, 17},

        {650, 183, 10},

        {300, 182, 10}

    };

    for (int i = 0; i < 9; i++)

    {

        glColor3f(0.35f, 0.22f, 0.12f);

        glBegin(GL_QUADS);

        glVertex2f(trees[i].x - 2, trees[i].y - trees[i].r * 0.7f);

        glVertex2f(trees[i].x + 2, trees[i].y - trees[i].r * 0.7f);

        glVertex2f(trees[i].x + 2, trees[i].y);

        glVertex2f(trees[i].x - 2, trees[i].y);

        glEnd();



        glColor3f(0.20f, 0.42f, 0.18f);

        drawCircle(trees[i].x, trees[i].y, trees[i].r);

        glColor3f(0.28f, 0.52f, 0.22f);

        drawCircle(trees[i].x - trees[i].r * 0.35f, trees[i].y + trees[i].r * 0.25f, trees[i].r * 0.65f);

    }




    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor4f(0.6f, 0.8f, 0.95f, 0.04f);

    glBegin(GL_QUADS);

    glVertex2f(wx1, wy1);

    glVertex2f(wx2, wy1);

    glVertex2f(wx2, wy2);

    glVertex2f(wx1, wy2);

    glEnd();



    glColor4f(1.0f, 1.0f, 1.0f, 0.06f);

    glBegin(GL_QUADS);

    glVertex2f(wx1 + 30, wy1);

    glVertex2f(wx1 + 45, wy1);

    glVertex2f(wx1 + 60, wy2);

    glVertex2f(wx1 + 45, wy2);

    glEnd();

    glDisable(GL_BLEND);

}


void drawFan()

{

    float cx = 175;

    float cy = 560;



    glColor3f(0.2f, 0.2f, 0.2f);

    glBegin(GL_QUADS);

    glVertex2f(cx - 3, cy);

    glVertex2f(cx + 3, cy);

    glVertex2f(cx + 3, cy + 20);

    glVertex2f(cx - 3, cy + 20);

    glEnd();

    glPushMatrix();

    glTranslatef(cx, cy, 0);

    glRotatef(fanAngle, 0, 0, 1);



    glColor3f(0.55f, 0.55f, 0.58f);

    for (int i = 0; i < 3; i++)

    {

        glPushMatrix();

        glRotatef(i * 120.0f, 0, 0, 1);

        glBegin(GL_QUADS);

        glVertex2f(-6, 0);

        glVertex2f(6, 0);

        glVertex2f(6, 55);

        glVertex2f(-6, 55);

        glEnd();

        glPopMatrix();

    }



    glColor3f(0.25f, 0.25f, 0.25f);

    drawCircle(0, 0, 10);

    glPopMatrix();

}


void drawAC()

{

    float ax = 700;

    float ay = 470;

    glColor3f(0.92f, 0.92f, 0.92f);

    glBegin(GL_QUADS);

    glVertex2f(ax, ay);

    glVertex2f(ax + 110, ay);

    glVertex2f(ax + 110, ay + 35);

    glVertex2f(ax, ay + 35);

    glEnd();



    glColor3f(0.5f, 0.5f, 0.5f);

    glBegin(GL_LINES);

    for (int i = 1; i < 6; i++)

    {

        float lx = ax + i * 16;

        glVertex2f(lx, ay + 5);

        glVertex2f(lx, ay + 30);

    }

    glEnd();



    glColor3f(0.1f, 0.8f, 0.1f);

    drawCircle(ax + 100, ay + 30, 2.5f);

}


void drawSign()

{

    glColor3f(0.75f, 0.15f, 0.15f);

    glBegin(GL_QUADS);

    glVertex2f(690, 400);

    glVertex2f(880, 400);

    glVertex2f(880, 440);

    glVertex2f(690, 440);

    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);

    drawText(715, 413, "AIUB CANTEEN", GLUT_BITMAP_HELVETICA_18);

}


void drawDoor(float x, float y, float w, float h)

{

    glColor3f(0.35f, 0.22f, 0.12f);

    glBegin(GL_QUADS);

    glVertex2f(x - 4, y);

    glVertex2f(x + w + 4, y);

    glVertex2f(x + w + 4, y + h + 4);

    glVertex2f(x - 4, y + h + 4);

    glEnd();



    glColor3f(0.55f, 0.35f, 0.18f);

    glBegin(GL_QUADS);

    glVertex2f(x, y);

    glVertex2f(x + w, y);

    glVertex2f(x + w, y + h);

    glVertex2f(x, y + h);

    glEnd();



    glColor3f(0.40f, 0.25f, 0.12f);

    glLineWidth(2.0f);

    glBegin(GL_LINE_LOOP);

    glVertex2f(x + w * 0.15f, y + h * 0.55f);

    glVertex2f(x + w * 0.85f, y + h * 0.55f);

    glVertex2f(x + w * 0.85f, y + h * 0.90f);

    glVertex2f(x + w * 0.15f, y + h * 0.90f);

    glEnd();



    glBegin(GL_LINE_LOOP);

    glVertex2f(x + w * 0.15f, y + h * 0.10f);

    glVertex2f(x + w * 0.85f, y + h * 0.10f);

    glVertex2f(x + w * 0.85f, y + h * 0.45f);

    glVertex2f(x + w * 0.15f, y + h * 0.45f);

    glEnd();

    glLineWidth(1.0f);



    glColor3f(0.85f, 0.75f, 0.30f);

    drawCircle(x + w * 0.85f, y + h * 0.5f, 3.0f);

}


void drawVendor()

{

    float x = 120;

    float y = 200;



    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_QUADS);

    glVertex2f(x - 14, y);

    glVertex2f(x + 14, y);

    glVertex2f(x + 14, y + 55);

    glVertex2f(x - 14, y + 55);

    glEnd();



    glColor3f(0.05f, 0.05f, 0.05f);

    glBegin(GL_QUADS);

    glVertex2f(x - 20, y + 25);

    glVertex2f(x - 14, y + 25);

    glVertex2f(x - 14, y + 45);

    glVertex2f(x - 20, y + 45);

    glVertex2f(x + 14, y + 25);

    glVertex2f(x + 20, y + 25);

    glVertex2f(x + 20, y + 45);

    glVertex2f(x + 14, y + 45);

    glEnd();



    glColor3f(0.05f, 0.05f, 0.05f);

    drawCircle(x, y + 68, 11);



    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_QUADS);

    glVertex2f(x - 11, y + 76);

    glVertex2f(x + 11, y + 76);

    glVertex2f(x + 11, y + 90);

    glVertex2f(x - 11, y + 90);

    glEnd();

}


void drawPriceBoard()

{

    glColor3f(0.20f, 0.12f, 0.06f);

    glBegin(GL_QUADS);

    glVertex2f(35, 300);

    glVertex2f(225, 300);

    glVertex2f(225, 405);

    glVertex2f(35, 405);

    glEnd();



    glColor3f(0.90f, 0.70f, 0.20f);

    glLineWidth(4.0f);

    glBegin(GL_LINE_LOOP);

    glVertex2f(35, 300);

    glVertex2f(225, 300);

    glVertex2f(225, 405);

    glVertex2f(35, 405);

    glEnd();

    glLineWidth(1.0f);



    glColor3f(1.0f, 0.85f, 0.20f);

    drawText(70, 382, "PRICE BOARD", GLUT_BITMAP_HELVETICA_12);



    glColor3f(1.0f, 1.0f, 1.0f);

    drawText(50, 355, "Tea - 15 Taka", GLUT_BITMAP_HELVETICA_12);



    drawText(50, 335, "Boro Somossa - 50", GLUT_BITMAP_HELVETICA_12);



    drawText(50, 315, "Choto Somossa - 20", GLUT_BITMAP_HELVETICA_12);

}


void drawFoodDisplayBox()

{

    glColor3f(0.55f, 0.35f, 0.20f);

    glBegin(GL_QUADS);

    glVertex2f(20, 125);

    glVertex2f(220, 125);

    glVertex2f(220, 175);

    glVertex2f(20, 175);

    glEnd();

    float bx1 = 25;

    float by1 = 175;

    float bx2 = 215;

    float by2 = 230;

    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glColor4f(0.75f, 0.90f, 0.95f, 0.35f);

    glBegin(GL_QUADS);

    glVertex2f(bx1, by1);

    glVertex2f(bx2, by1);

    glVertex2f(bx2, by2);

    glVertex2f(bx1, by2);

    glEnd();

    glDisable(GL_BLEND);



    glColor3f(0.4f, 0.4f, 0.4f);

    glLineWidth(3.0f);

    glBegin(GL_LINE_LOOP);

    glVertex2f(bx1, by1);

    glVertex2f(bx2, by1);

    glVertex2f(bx2, by2);

    glVertex2f(bx1, by2);

    glEnd();



    glBegin(GL_LINES);

    glVertex2f(bx1, (by1 + by2) / 2);

    glVertex2f(bx2, (by1 + by2) / 2);

    glEnd();

    glLineWidth(1.0f);



    glColor3f(0.85f, 0.55f, 0.15f);

    drawCircle(55, 190, 9);

    glColor3f(0.75f, 0.15f, 0.10f);

    drawCircle(90, 190, 9);

    glColor3f(0.95f, 0.85f, 0.30f);

    drawCircle(125, 190, 9);

    glColor3f(0.55f, 0.30f, 0.15f);

    drawCircle(160, 190, 9);

    glColor3f(0.85f, 0.55f, 0.15f);

    drawCircle(195, 190, 9);



    glColor3f(0.95f, 0.95f, 0.95f);

    for (int i = 0; i < 5; i++)

    {

        float fx = 55 + i * 35;

        drawCircle(fx, 213, 7);

    }

    glColor3f(0.75f, 0.20f, 0.15f);

    for (int i = 0; i < 5; i++)

    {

        float fx = 55 + i * 35;

        drawCircle(fx, 213, 4);

    }

}


void drawSquareTable(float cx, float cy, float size)

{

    float half = size / 2;



    glColor3f(0.45f, 0.28f, 0.15f);

    glBegin(GL_QUADS);

    glVertex2f(cx - half, cy);

    glVertex2f(cx + half, cy);

    glVertex2f(cx + half, cy + 10);

    glVertex2f(cx - half, cy + 10);

    glEnd();



    glColor3f(0.30f, 0.18f, 0.10f);

    glBegin(GL_QUADS);

    glVertex2f(cx - half + 4, cy - 45);

    glVertex2f(cx - half + 10, cy - 45);

    glVertex2f(cx - half + 10, cy);

    glVertex2f(cx - half + 4, cy);

    glVertex2f(cx + half - 10, cy - 45);

    glVertex2f(cx + half - 4, cy - 45);

    glVertex2f(cx + half - 4, cy);

    glVertex2f(cx + half - 10, cy);

    glEnd();

}


void drawPerson(float x, float y, float shirtR, float shirtG, float shirtB)

{

    glColor3f(0.15f, 0.15f, 0.25f);

    glBegin(GL_QUADS);

    glVertex2f(x - 8, y);

    glVertex2f(x - 1, y);

    glVertex2f(x - 1, y + 30);

    glVertex2f(x - 8, y + 30);

    glVertex2f(x + 1, y);

    glVertex2f(x + 8, y);

    glVertex2f(x + 8, y + 30);

    glVertex2f(x + 1, y + 30);

    glEnd();


    glColor3f(shirtR, shirtG, shirtB);

    glBegin(GL_QUADS);

    glVertex2f(x - 12, y + 30);

    glVertex2f(x + 12, y + 30);

    glVertex2f(x + 12, y + 65);

    glVertex2f(x - 12, y + 65);

    glEnd();

    glBegin(GL_QUADS);

    glVertex2f(x - 18, y + 35);

    glVertex2f(x - 12, y + 35);

    glVertex2f(x - 12, y + 60);

    glVertex2f(x - 18, y + 60);

    glVertex2f(x + 12, y + 35);

    glVertex2f(x + 18, y + 35);

    glVertex2f(x + 18, y + 60);

    glVertex2f(x + 12, y + 60);

    glEnd();



    glColor3f(0.94f, 0.80f, 0.65f);

    drawCircle(x, y + 78, 11);

}


void display()

{

    glClear(GL_COLOR_BUFFER_BIT);

    drawRoom();

    drawLibraryView();

    drawFan();

    drawAC();

    drawSign();



    drawSquareTable(120, 60, 70);

    drawSquareTable(270, 60, 70);

    drawSquareTable(420, 60, 70);

    drawSquareTable(570, 60, 70);

    drawSquareTable(720, 60, 70);

    drawSquareTable(870, 60, 70);



    drawPerson(human1X, 20, 0.75f, 0.15f, 0.15f);

    drawPerson(human2X, 20, 0.15f, 0.35f, 0.70f);



    drawFoodDisplayBox();



    drawVendor();



    drawPriceBoard();



    drawDoor(700, 120, 80, 155);

    glutSwapBuffers();

}


void keyboard(unsigned char key, int x, int y)

{

    switch (key)

    {

        case 's':

        case 'S':

            animationRunning = true;

            break;



        case 'p':

        case 'P':

            animationRunning = false;

            break;

        case 'r':

        case 'R':

            animationRunning = false;

            fanAngle = 0.0f;

            human1X = 360.0f;

            human2X = 660.0f;

            movementSpeed = 2.0f;

            break;


        case 27:

            exit(0);

            break;

    }

    glutPostRedisplay();

}


void timer(int value)

{

    if (animationRunning)

    {

        fanAngle += 8.0f + movementSpeed;

        if (fanAngle > 360.0f)

            fanAngle -= 360.0f;



        human1X += movementSpeed;

        if (human1X > 500.0f)

            human1X = 300.0f;



        human2X -= movementSpeed;

        if (human2X < 500.0f)

            human2X = 720.0f;

    }

    glutPostRedisplay();


}


void reshape(int w, int h)

{

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    gluOrtho2D(0, 900, 0, 650);

    glMatrixMode(GL_MODELVIEW);

    glLoadIdentity();

}

} // namespace Scene5

// ================================================================
// MASTER GLUT CALLBACKS
// ================================================================
static int activeScene = 1;

static void setProjectionForScene(int scene, int w, int h)
{
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    switch (scene)
    {
        case 1:
            gluOrtho2D(0, SCENE1_CANVAS_W, 0, SCENE1_CANVAS_H);
            break;
        case 2:
            gluOrtho2D(0, SCENE2_CANVAS_W, 0, SCENE2_CANVAS_H);
            break;
        case 3:
            gluOrtho2D(0, 800, 0, 600);
            break;
        case 4:
            gluOrtho2D(0, Scene4::windowW, 0, Scene4::windowH);
            break;
        case 5:
            gluOrtho2D(0, Scene5::WIN_W, 0, Scene5::WIN_H);
            break;
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

static void masterDisplay()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    switch (activeScene)
    {
        case 1: Scene1::display(); break;
        case 2: Scene2::display(); break;
        case 3: Scene3::display(); break;
        case 4: Scene4::display(); break;
        case 5: Scene5::display(); break;
    }
}

static void masterReshape(int w, int h)
{
    // Use each original scene's reshape behavior where it had one.
    // Scene 3 did not have a reshape callback, so its projection is set here.
    switch (activeScene)
    {
        case 1: Scene1::reshape(w, h); break;
        case 2: Scene2::reshape(w, h); break;
        case 3: setProjectionForScene(3, w, h); break;
        case 4: Scene4::reshape(w, h); break;
        case 5: Scene5::reshape(w, h); break;
    }
}

static int scene1LastTick = 0;
static int scene2LastTick = 0;
static int scene3LastTick = 0;
static int scene5LastTick = 0;

static void masterUpdate(int value)
{
    (void)value;

    // Preserve the original animation timing as closely as possible:
    // Scene 1 = 16 ms, Scene 2 = 16 ms, Scene 3 = 25 ms, Scene 4 = idle-time, Scene 5 = 30 ms.
    int now = glutGet(GLUT_ELAPSED_TIME);

    switch (activeScene)
    {
        case 1:
            if (now - scene1LastTick >= 16)
            {
                Scene1::update(0);
                scene1LastTick = now;
            }
            break;

        case 2:
            if (now - scene2LastTick >= 16)
            {
                Scene2::update(0);
                scene2LastTick = now;
            }
            break;

        case 3:
            if (now - scene3LastTick >= 25)
            {
                Scene3::update(0);
                scene3LastTick = now;
            }
            break;

        case 4:
            Scene4::idleFunc();
            break;

        case 5:
            if (now - scene5LastTick >= 30)
            {
                Scene5::timer(0);
                scene5LastTick = now;
            }
            break;
    }

    glutPostRedisplay();
    glutTimerFunc(10, masterUpdate, 0);
}

static void masterKeyboard(unsigned char key, int x, int y)
{
    (void)x;
    (void)y;

    if (key == 27)
    {
        std::exit(0);
        return;
    }

    if (key >= '1' && key <= '5')
    {
        activeScene = key - '0';

        // Reset the projection to the coordinate system of the selected scene.
        int w = glutGet(GLUT_WINDOW_WIDTH);
        int h = glutGet(GLUT_WINDOW_HEIGHT);
        setProjectionForScene(activeScene, w, h);
        glutPostRedisplay();
        return;
    }

    switch (activeScene)
    {
        case 1: Scene1::keyboard(key, x, y); break;
        case 2: Scene2::keyboard(key, x, y); break;
        case 3: Scene3::keyboard(key, x, y); break;
        case 4: Scene4::keyboard(key, x, y); break;
        case 5: Scene5::keyboard(key, x, y); break;
    }
}

static void masterSpecialDown(int key, int x, int y)
{
    if (activeScene == 4)
        Scene4::specialKeyDown(key, x, y);
}

static void masterSpecialUp(int key, int x, int y)
{
    if (activeScene == 4)
        Scene4::specialKeyUp(key, x, y);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowSize(1280, 800);
    glutInitWindowPosition(60, 40);
    glutCreateWindow("A Life of an AIUB Student - 5 Scenes");

    // Initialize every scene once so all original state is prepared.
    Scene1::init();
    Scene2::init();
    Scene3::init();
    Scene4::init();

    // Scene 4 originally uses elapsed time in its animation.
    Scene4::lastTimeMs = glutGet(GLUT_ELAPSED_TIME);

    glutDisplayFunc(masterDisplay);
    glutReshapeFunc(masterReshape);
    glutKeyboardFunc(masterKeyboard);
    glutSpecialFunc(masterSpecialDown);
    glutSpecialUpFunc(masterSpecialUp);

    masterReshape(glutGet(GLUT_WINDOW_WIDTH),
                  glutGet(GLUT_WINDOW_HEIGHT));

    int startTime = glutGet(GLUT_ELAPSED_TIME);
    scene1LastTick = startTime;
    scene2LastTick = startTime;
    scene3LastTick = startTime;
    scene5LastTick = startTime;

    // One timer controls all five scenes. Original scene timers were removed
    // only to prevent multiple independent GLUT timer loops after merging.
    glutTimerFunc(16, masterUpdate, 0);

    glutMainLoop();
    return 0;
}
