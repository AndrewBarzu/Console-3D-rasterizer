
#include <iostream>
#include <vector>
#include <windows.h>

#define PI 3.14159f

using namespace std;

struct Mat4x4
{
    float m[4][4];
};

class Vector3D
{
public:
    double x, y, z;
    Vector3D(): x{0}, y{0}, z{0} {}
    Vector3D(const Vector3D& other): x{other.x}, y{other.y}, z{other.z} {}
    Vector3D(double x, double y, double z): x{x}, y{y}, z{z} {}
    ~Vector3D() {}
};

class Triangle
{
public:
    Vector3D A, B, C;
    Triangle() {}
    Triangle(const Triangle& other) : A{ other.A }, B{ other.B }, C{ other.C } {}
    Triangle(const Vector3D& A, const Vector3D& B, const Vector3D& C) : A{ A }, B{ B }, C{ C } {}
    ~Triangle() {}
};

class Line
{
public:
    Vector3D A, B;
    Line(){ }
    Line(const Line& other) : A{ other.A }, B{ other.B } {}
    Line(const Vector3D& A, const Vector3D& B) : A{ A }, B{ B } {}
    ~Line() {}
};

class Mesh
{
public:
    vector<Triangle> mesh;
    Mesh() {}
    ~Mesh() {}
};

class Engine
{
private:
    Mesh mesh;
    Mat4x4 m;
    int fElapsedTime;
    float fTheta;

    int columns, rows;

    char m_bufScreen[100][100];

    void Multiply(const Vector3D& in, Vector3D& out, const Mat4x4& m)
    {
        out.x = in.x * m.m[0][0] + in.y * m.m[1][0] + in.z * m.m[2][0] + m.m[3][0];
        out.y = in.x * m.m[0][1] + in.y * m.m[1][1] + in.z * m.m[2][1] + m.m[3][1];
        out.z = in.x * m.m[0][2] + in.y * m.m[1][2] + in.z * m.m[2][2] + m.m[3][2];
        float w = in.x * m.m[0][3] + in.y * m.m[1][3] + in.z * m.m[2][3] + m.m[3][3];
        if (w != 0.0f)
        {
            out.x /= w;
            out.y /= w;
            out.z /= w;
        }
    }

    void Draw(int x, int y)
    {
        if (x >= 0 && x < columns && y >= 0 && y < rows)
        {
            m_bufScreen[y][x] = 'X';
        }
    }

    void DrawLine(int x1, int y1, int x2, int y2)
    {
        int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
        dx = x2 - x1; dy = y2 - y1;
        dx1 = abs(dx); dy1 = abs(dy);
        px = 2 * dy1 - dx1;	py = 2 * dx1 - dy1;
        if (dy1 <= dx1)
        {
            if (dx >= 0)
            {
                x = x1; y = y1; xe = x2;
            }
            else
            {
                x = x2; y = y2; xe = x1;
            }
            Draw(x, y);

            for (i = 0; x < xe; i++)
            {
                x = x + 1;
                if (px < 0)
                    px = px + 2 * dy1;
                else
                {
                    if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) y = y + 1; else y = y - 1;
                    px = px + 2 * (dy1 - dx1);
                }
                Draw(x, y);
            }
        }
        else
        {
            if (dy >= 0)
            {
                x = x1; y = y1; ye = y2;
            }
            else
            {
                x = x2; y = y2; ye = y1;
            }

            Draw(x, y);

            for (i = 0; y < ye; i++)
            {
                y = y + 1;
                if (py <= 0)
                    py = py + 2 * dx1;
                else
                {
                    if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) x = x + 1; else x = x - 1;
                    py = py + 2 * (dx1 - dy1);
                }
                Draw(x, y);
            }
        }
    }
    void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3)
    {
        DrawLine(x1, y1, x2, y2);
        /*system("cls");
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                cout << m_bufScreen[i][j];
            }
            cout << endl;
        }*/
        DrawLine(x2, y2, x3, y3);
        /*system("cls");
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                cout << m_bufScreen[i][j];
            }
            cout << endl;
        }*/
        DrawLine(x3, y3, x1, y1);
        /*system("cls");
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                cout << m_bufScreen[i][j];
            }
            cout << endl;
        }*/
    }
    Vector3D DirectorVector(const Line);
    void getNormalVector(const Triangle& t)
    {
        ;
    }

public:
    Engine()
    {
        this->fElapsedTime = 0;
        this->mesh.mesh = {
            //south
            Triangle{ Vector3D{0.0f, 0.0f, 0.0f}, Vector3D{0.0f, 1.0f, 0.0f}, Vector3D{1.0f, 1.0f, 0.0f} },
            Triangle{ Vector3D{0.0f, 0.0f, 0.0f}, Vector3D{1.0f, 1.0f, 0.0f}, Vector3D{1.0f, 0.0f, 0.0f} },

            //east
            Triangle{ Vector3D{1.0f, 0.0f, 0.0f}, Vector3D{1.0f, 1.0f, 0.0f}, Vector3D{1.0f, 1.0f, 1.0f} },
            Triangle{ Vector3D{1.0f, 0.0f, 0.0f}, Vector3D{1.0f, 1.0f, 1.0f}, Vector3D{1.0f, 0.0f, 1.0f} },

            //north
            Triangle{ Vector3D{1.0f, 0.0f, 1.0f}, Vector3D{1.0f, 1.0f, 1.0f}, Vector3D{0.0f, 1.0f, 1.0f} },
            Triangle{ Vector3D{1.0f, 0.0f, 1.0f}, Vector3D{0.0f, 1.0f, 1.0f}, Vector3D{0.0f, 0.0f, 1.0f} },

            //west
            Triangle{ Vector3D{0.0f, 0.0f, 1.0f}, Vector3D{0.0f, 1.0f, 1.0f}, Vector3D{0.0f, 1.0f, 0.0f} },
            Triangle{ Vector3D{0.0f, 0.0f, 1.0f}, Vector3D{0.0f, 1.0f, 0.0f}, Vector3D{0.0f, 0.0f, 0.0f} },

            //top
            Triangle{ Vector3D{0.0f, 1.0f, 0.0f}, Vector3D{0.0f, 1.0f, 1.0f}, Vector3D{1.0f, 1.0f, 1.0f} },
            Triangle{ Vector3D{0.0f, 1.0f, 0.0f}, Vector3D{1.0f, 1.0f, 1.0f}, Vector3D{1.0f, 1.0f, 0.0f} },

            //bottom
            Triangle{ Vector3D{1.0f, 0.0f, 1.0f}, Vector3D{0.0f, 0.0f, 1.0f}, Vector3D{0.0f, 0.0f, 0.0f} },
            Triangle{ Vector3D{1.0f, 0.0f, 1.0f}, Vector3D{0.0f, 0.0f, 0.0f}, Vector3D{1.0f, 0.0f, 0.0f} },


            ////south
            //Triangle{ Vector3D{-0.5f, -0.5f, -0.5f}, Vector3D{-0.5f, 0.5f, -0.5f}, Vector3D{0.5f, 0.5f, -0.5f} },
            //Triangle{ Vector3D{-0.5f, -0.5f, -0.5f}, Vector3D{1.0f, 1.0f, 0.0f}, Vector3D{0.5f, -0.5f, -0.5f} },

            ////east
            //Triangle{ Vector3D{0.5f, -0.5f, -0.5f}, Vector3D{0.5f, 0.5f, -0.5f}, Vector3D{0.5f, 0.5f, 0.5f} },
            //Triangle{ Vector3D{0.5f, -0.5f, -0.5f}, Vector3D{0.5f, 0.5f, 0.5f}, Vector3D{0.5f, -0.5f, 0.5f} },

            ////north
            //Triangle{ Vector3D{0.5f, -0.5f, 0.5f}, Vector3D{0.5f, 0.5f, 0.5f}, Vector3D{-0.5f, 0.5f, -0.5f} },
            //Triangle{ Vector3D{0.5f, -0.5f, 0.5f}, Vector3D{-0.5f, 5.5f, 0.5f}, Vector3D{-0.5f, -0.5f, 0.5f} },

            ////west
            //Triangle{ Vector3D{-0.5f, -0.5f, 0.5f}, Vector3D{-0.5f, 0.5f, 0.5f}, Vector3D{-0.5f, 0.5f, -0.5f} },
            //Triangle{ Vector3D{-0.5f, -0.5f, 0.5f}, Vector3D{-0.5f, 0.5f, -0.5f}, Vector3D{-0.5f, -0.5f, -0.5f} },

            ////top
            //Triangle{ Vector3D{-0.5f, 0.5f, -0.5f}, Vector3D{-0.5f, 0.5f, 0.5f}, Vector3D{0.5f, 0.5f, 0.5f} },
            //Triangle{ Vector3D{-0.5f, 0.5f, -0.5f}, Vector3D{0.5f, 0.5f, 0.5f}, Vector3D{0.5f, 0.5f, -0.5f} },

            ////bottom
            //Triangle{ Vector3D{0.5f, -0.5f, 0.5f}, Vector3D{-0.5f, -0.5f, 0.5f}, Vector3D{-0.5f, -0.5f, -0.5f} },
            //Triangle{ Vector3D{0.5f, -0.5f, 0.5f}, Vector3D{-0.5f, -0.5f, -0.5f}, Vector3D{0.5f, -0.5f, -0.5f} },
        };

        CONSOLE_SCREEN_BUFFER_INFO csbi;

        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        columns = 100;
        rows = 70;

        //cout << rows << " " << columns << endl;
        //this->m_bufScreen = new char[rows * columns];
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                this->m_bufScreen[i][j] = ' ';
            }
        }

        float fNear = 0.1f;
        float fFar = 1000.0f;
        float fov = 90.0f;
        float aspectRation = (float)rows / (float)columns;
        float fovRad = 1.0f / tanf(fov * 0.5f / 180.0f * PI);
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; i < 4; i++)
                this->m.m[i][j] = 0;
        }
        this->m.m[0][0] = aspectRation * fovRad;
        this->m.m[1][1] = fovRad;
        this->m.m[2][2] = fFar / (fFar - fNear);
        this->m.m[3][2] = (-fFar * fNear) / (fFar - fNear);
        this->m.m[2][3] = 1.0f;
        this->m.m[3][3] = 0.0f;

    }

    void drawMesh()
    {
        for (auto triangle : this->mesh.mesh)
        {
            Triangle projected, translated;
            translated = triangle;
            translated.A.z += 1;
            translated.B.z += 1;
            translated.C.z += 1;
            translated.A.x *= 2.f;
            translated.B.x *= 2.f;
            translated.C.x *= 2.f;
            translated.A.x -= 1.f;
            translated.B.x -= 1.f;
            translated.C.x -= 1.f;
            translated.A.y -= 0.5f;
            translated.B.y -= 0.5f;
            translated.C.y -= 0.5f;
            /*translated.A.x -= 5.f;
            translated.B.x -= 5.f;
            translated.C.x -= 5.f;*/

            this->Multiply(translated.A, projected.A, this->m);
            this->Multiply(translated.B, projected.B, this->m);
            this->Multiply(translated.C, projected.C, this->m);

            projected.A.x += 1.0f; projected.A.y += 1.0f;// projected.A.z += 1.0f;
            projected.B.x += 1.0f; projected.B.y += 1.0f;// projected.B.z += 1.0f;
            projected.C.x += 1.0f; projected.C.y += 1.0f;// projected.C.z += 1.0f;

            projected.A.x *= 0.4f * this->columns;
            projected.A.y *= 0.4f * this->rows;
            projected.B.x *= 0.4f * this->columns;
            projected.B.y *= 0.4f * this->rows;
            projected.C.x *= 0.4f * this->columns;
            projected.C.y *= 0.4f * this->rows;

            /*projected.A.x *= 0.1f * 10;
            projected.A.y *= 0.1f * 10;
            projected.B.x *= 0.1f * 10;
            projected.B.y *= 0.1f * 10;
            projected.C.x *= 0.1f * 10;
            projected.C.y *= 0.1f * 10;*/

            DrawTriangle(projected.A.x, projected.A.y,
                         projected.B.x, projected.B.y,
                         projected.C.x, projected.C.y);

        }
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                cout << m_bufScreen[i][j];
            }
            cout << endl;
        }
    }
    void update()
    {
        Mat4x4 matRotZ, matRotX;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                matRotZ.m[i][j] = 0;
                matRotX.m[i][j] = 0;
            }

        }

        fTheta += 0.1f;
        //fElapsedTime += 1;

        // Rotation Z
        matRotZ.m[0][0] = cosf(fTheta);
        matRotZ.m[0][2] = sinf(fTheta);
        matRotZ.m[1][1] = 1;
        matRotZ.m[2][0] = -sinf(fTheta);
        matRotZ.m[2][2] = cosf(fTheta);
        matRotZ.m[3][3] = 1;

        // Rotation X
        matRotX.m[0][0] = 1;
        matRotX.m[1][1] = cosf(35);
        matRotX.m[1][2] = sinf(35);
        matRotX.m[2][1] = -sinf(35);
        matRotX.m[2][2] = cosf(35);
        matRotX.m[3][3] = 1;

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                m_bufScreen[i][j] = ' ';
            }
        }

        // Draw Triangles
        for (auto triangle : this->mesh.mesh)
        {
            //cout << tri.A.x << " " << tri.A.y << " " << tri.A.z << endl;
            Triangle projected, translated, rotatedZ, rotatedZX;
            Triangle preTranslated = triangle;
            preTranslated.A.x -= 0.5;
            preTranslated.B.x -= 0.5;
            preTranslated.C.x -= 0.5;
            preTranslated.A.y -= 0.5;
            preTranslated.B.y -= 0.5;
            preTranslated.C.y -= 0.5;
            preTranslated.A.z -= 0.5;
            preTranslated.B.z -= 0.5;
            preTranslated.C.z -= 0.5;

            // Rotate in Z-Axis
            Multiply(preTranslated.A, rotatedZ.A, matRotZ);
            Multiply(preTranslated.B, rotatedZ.B, matRotZ);
            Multiply(preTranslated.C, rotatedZ.C, matRotZ);

            // Rotate in X-Axis
            Multiply(rotatedZ.A, rotatedZX.A, matRotX);
            Multiply(rotatedZ.B, rotatedZX.B, matRotX);
            Multiply(rotatedZ.C, rotatedZX.C, matRotX);

            translated = rotatedZX;
            translated.A.z += 1.5f;
            translated.B.z += 1.5f;
            translated.C.z += 1.5f;
            /*translated.A.y -= 0.5f;
            translated.B.y -= 0.5f;
            translated.C.y -= 0.5f;*/
            /*translated.A.x -= 5.f;
            translated.B.x -= 5.f;
            translated.C.x -= 5.f;*/

            this->Multiply(translated.A, projected.A, this->m);
            this->Multiply(translated.B, projected.B, this->m);
            this->Multiply(translated.C, projected.C, this->m);

            projected.A.x *= 2.5f;
            projected.B.x *= 2.5f;
            projected.C.x *= 2.5f;

            projected.A.x += 1.0f; projected.A.y += 1.0f;// projected.A.z += 1.0f;
            projected.B.x += 1.0f; projected.B.y += 1.0f;// projected.B.z += 1.0f;
            projected.C.x += 1.0f; projected.C.y += 1.0f;// projected.C.z += 1.0f;

            projected.A.x *= 0.4f * this->columns;
            projected.A.y *= 0.4f * this->rows;
            projected.B.x *= 0.4f * this->columns;
            projected.B.y *= 0.4f * this->rows;
            projected.C.x *= 0.4f * this->columns;
            projected.C.y *= 0.4f * this->rows;

            /*projected.A.x *= 0.1f * 10;
            projected.A.y *= 0.1f * 10;
            projected.B.x *= 0.1f * 10;
            projected.B.y *= 0.1f * 10;
            projected.C.x *= 0.1f * 10;
            projected.C.y *= 0.1f * 10;*/

            DrawTriangle(projected.A.x, projected.A.y,
                projected.B.x, projected.B.y,
                projected.C.x, projected.C.y);

        }
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                cout << m_bufScreen[i][j];
            }
            cout << endl;
        }
    }
    ~Engine() { }
};

int main()
{
    Engine engine;
    engine.drawMesh();
    while (true)
    {
        system("cls");
        engine.update();
        Sleep(250);
    }
}

