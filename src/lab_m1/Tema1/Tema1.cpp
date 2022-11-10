# include "lab_m1/Tema1/Tema1.h"


#include "core/engine.h"
#include "utils/gl_utils.h"

#include "lab_m1/lab3/transform2D.h"
#include "lab_m1/lab3/object2D.h"

#include <vector>
#include <iostream>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);


    resolutionX = resolution.x; //limita din dreapta
    resolutionY = resolution.y; //limita de sus
    translateX = 0; //legea de miscare coord x
    translateY = 0; //legea de miscare coord y
    counter = 0;
    angularStep = 0;
    angularStep2 = 0;
    unghi = rand() % (25 - 75 + 1) + 25; //inclinarea initiala a ratei + directia de mers
    centruAripaX = 0;
    centruAripaY = 0;
    counter2 = 0;
    centruAripa2X = 0;
    centruAripa2Y = 0;
    scale = 8; //cu cat este scalata rata
    speedX = 50; 
    speedY = 50;
    countEscape = 0;
    countEscape = 0;
    numarRate = 1;

    {
        //aripa din stanga a unei rate
        vector<VertexFormat> verticesA1
        {
            VertexFormat(glm::vec3(0, 4, 0), glm::vec3(0.48, 0.31, 0.19), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(-3, 0, 0), glm::vec3(0.48, 0.31, 0.19), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(3, 0, 0), glm::vec3(0.48, 0.31, 0.19), glm::vec3(0.2, 0.8, 0.6)),
        };
        vector<unsigned int> indicesA1 =
        {
            0, 1, 2,
        };
        CreateMesh("aripa1", verticesA1, indicesA1);

        //aripa din dreapta a unei rate
        vector<VertexFormat> verticesA2
        {
            VertexFormat(glm::vec3(0, -4, 0), glm::vec3(0.48, 0.31, 0.19), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(-3, 0, 0), glm::vec3(0.48, 0.31, 0.19), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(3, 0, 0), glm::vec3(0.48, 0.31, 0.19), glm::vec3(0.2, 0.8, 0.6)),
        };
        vector<unsigned int> indicesA2 =
        {
            0, 1, 2,
        };
        CreateMesh("aripa2", verticesA2, indicesA2);

        //corpul unei rate
        vector<VertexFormat> verticesCorp
        {
            VertexFormat(glm::vec3(5, 0, 0), glm::vec3(0.48, 0.31, 0.19), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(-5, 3, 0), glm::vec3(0.48, 0.31, 0.19), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(-5, -3, 0), glm::vec3(0.48, 0.31, 0.19), glm::vec3(0.2, 0.8, 0.6)),
        };
        vector<unsigned int> indicesCorp =
        {
            0, 1, 2,
        };
        CreateMesh("corp", verticesCorp, indicesCorp);

        //capul unei rate(cerc)
        vector <VertexFormat> verticesCap;
        int x = 0, y = 0, z = 0;
        float radius = 1.4;//raza cercului(lungimea unei laturi a unui triunghi)
        verticesCap.push_back(VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0.26, 0.45, 0.29), glm::vec3(0.2, 0.6, 0.8)));//varful tuturor triunghiurilor ce vor forma cercul
        for (int i = 0; i <= 30; i++) { //vom forma un cerc cu ajutorul a 30 de triunghiuri
            verticesCap.push_back(VertexFormat( glm::vec3(x + (radius * cos((float)i * 2 * M_PI / 30)), y + (radius * sin((float)i * 2 * M_PI / 30)), 0), glm::vec3(0.26, 0.45, 0.29), glm::vec3(0.2, 0.8, 0.6)));
        }

        vector<unsigned int> indicesCap;
        for (int i = 0; i <= 30; i++) {
            indicesCap.push_back(0);
            indicesCap.push_back(i + 1);
            indicesCap.push_back(i + 2);
        }
        CreateMesh("cap", verticesCap, indicesCap);

        //ciocul unei rate
        vector<VertexFormat> verticesCioc
        {
            VertexFormat(glm::vec3(8, 0, 0), glm::vec3(0.48, 0.41, 0.11), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(5, 1, 0), glm::vec3(0.48, 0.41, 0.11), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(5, -1, 0), glm::vec3(0.48, 0.41, 0.11), glm::vec3(0.2, 0.8, 0.6)),
        };
        vector<unsigned int> indicesCioc =
        {
            0, 1, 2,
        };
        CreateMesh("cioc", verticesCioc, indicesCioc);

        //iarba
        vector<VertexFormat> verticesIarba
        {
            VertexFormat(glm::vec3(0, 0, 0), glm::vec3(0, 1, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(0, 8, 0), glm::vec3(0, 1, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(50, 8, 0), glm::vec3(0, 1, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(50, 0, 0), glm::vec3(0, 1, 0), glm::vec3(0.2, 0.8, 0.6))
        };
        vector<unsigned int> indicesIarba =
        {
            0, 1, 2,
            0, 2, 3,
        };
        CreateMesh("iarba", verticesIarba, indicesIarba);

        vector<VertexFormat> verticesHit
        {
            VertexFormat(glm::vec3(-5, -4, 0), glm::vec3(0, 1, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(-5, 4, 0), glm::vec3(0, 1, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(8, 4, 0), glm::vec3(0, 1, 0), glm::vec3(0.2, 0.8, 0.6)),
            VertexFormat(glm::vec3(8, -4, 0), glm::vec3(0, 1, 0), glm::vec3(0.2, 0.8, 0.6))
        };
        vector<unsigned int> indicesHit =
        {
            0, 1, 2,
            0, 2, 3,
        };
        CreateMesh("hitbox", verticesHit, indicesHit);
    }
}

//functia care creaza obiectele
void Tema1::CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices)
{
    unsigned int VAO = 0;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    // TODO(student): Create the VAO and bind it

    unsigned int VBO = 0;
    // TODO(student): Create the VBO and bind it
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // TODO(student): Send vertices data into the VBO buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    unsigned int IBO = 0;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

    // ========================================================================
    // This section demonstrates how the GPU vertex shader program
    // receives data. It will be learned later, when GLSL shaders will be
    // introduced. For the moment, just think that each property value from
    // our vertex format needs to be sent to a certain channel, in order to
    // know how to receive it in the GLSL vertex shader.

    // Set vertex position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

    // Set vertex normal attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

    // Set texture coordinate attribute
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

    // Set vertex color attribute
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
    // ========================================================================

    // TODO(student): Unbind the VAO
    glEnableVertexAttribArray(0);

    // Check for OpenGL errors
    if (GetOpenGLError() == GL_INVALID_OPERATION)
    {
        cout << "\t[NOTE] : For students : DON'T PANIC! This error should go away when completing the tasks." << std::endl;
        cout << "\t[NOTE] : For developers : This happens because OpenGL core spec >=3.1 forbids null VAOs." << std::endl;
    }

    // Mesh information is saved into a Mesh object
    meshes[name] = new Mesh(name);
    meshes[name]->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));
}



void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{
    //initializare matrici
    modelMatrix = glm::mat3(1);  //matricea ratei
    modelMatrixCap = glm::mat3(1);
    modelMatrixA1 = glm::mat3(1);
    modelMatrixA2 = glm::mat3(1);
    modelMatrixIarba = glm::mat3(26);
    modelMatrixVieti = glm::mat3(20);
    modelMatrixVieti *= transform2D::Translate(3, 33);
    modelMatrixHit = glm::mat3(1);


    //ciocniri rata
    if(translateX * scale > resolutionX) {
        unghi = (180 - unghi);
        modelMatrix *= transform2D::Rotate(RADIANS(unghi));
        cout << "lovit dreapta" << endl;
    }
    if (translateX < 0) {;
        unghi = (180 - unghi);
        modelMatrix *= transform2D::Rotate(RADIANS(unghi));
        cout << "lovit stanga " << endl;
    }
    if (translateY * scale > resolutionY) {
        if (countEscape < 30) {
            unghi = -unghi;
            modelMatrix *= transform2D::Rotate(RADIANS(unghi));
            cout << "lovit sus" << endl;
        }
    }
    if (translateY < 0) {
        unghi = -unghi;
        modelMatrix *= transform2D::Rotate(RADIANS(unghi));
        cout << "lovit jos" << endl;
    }

    //escape
    countEscape += deltaTimeSeconds;
    if (countEscape >= 5) {
        speedX = 0;
        unghi = 90;
        if (translateY * scale > resolutionY + 10) {
            countEscape = 0;
            translateX = 0;
            translateY = 0;
            speedX = 50;
            unghi = rand() % (25 - 75 + 1) + 25;
            numarRate++;
            //cout << unghi << " UNG" << endl;
        }
    }
    /*cout << translateX << " translateX" << endl;
    cout << translateY << " translatey" << endl;*/
 
    //miscarea ratei
    modelMatrix *= transform2D::Scale(scale, scale);
    translateX += speedX * deltaTimeSeconds * cos(RADIANS(unghi));
    translateY += speedY * deltaTimeSeconds * sin(RADIANS(unghi));
    modelMatrix *= transform2D::Translate(translateX, translateY);
    modelMatrix *= transform2D::Rotate(RADIANS(unghi));

    //hitbox
    modelMatrixHit *= modelMatrix;

    //pozitionare cap
    modelMatrixCap *= modelMatrix;
    modelMatrixCap *= transform2D::Translate(5, 0); 
    
    //miscare aripa stanga
    modelMatrixA1 *= modelMatrix;
    angularStep += deltaTimeSeconds * 10;
    counter += deltaTimeSeconds;
    if (counter >= 0.8) {
        angularStep = -angularStep;
        counter = 0.0;
        counter += deltaTimeSeconds;
    }
    centruAripaX = 0;
    centruAripaY = 4/3;
    centruAripaX += deltaTimeSeconds*5;
    centruAripaY += deltaTimeSeconds*5;
    modelMatrixA1 *= transform2D::Translate(centruAripaX, centruAripaY);
    modelMatrixA1 *= transform2D::Rotate(RADIANS(angularStep));
    modelMatrixA1 *= transform2D::Translate(-centruAripaX, -centruAripaY);

    //miscare aripa dreapta
    modelMatrixA2 *= modelMatrix;
    angularStep2 -= deltaTimeSeconds * 10;
    counter2 += deltaTimeSeconds;
    if (counter2 >= 0.8) {
        angularStep2 = -angularStep;
        counter2 = 0.0;
        counter2 += deltaTimeSeconds;
    }
    centruAripa2X = 0;
    centruAripa2Y = -4/3;
    centruAripa2X += deltaTimeSeconds * 5;
    centruAripa2Y += deltaTimeSeconds * 5;
    modelMatrixA2 *= transform2D::Translate(centruAripa2X, centruAripa2Y);
    modelMatrixA2 *= transform2D::Rotate(RADIANS(angularStep2));
    modelMatrixA2 *= transform2D::Translate(-centruAripa2X, -centruAripa2Y);

    //randare obiecte
    //RenderMesh2D(meshes["iarba"], shaders["VertexColor"], modelMatrixIarba);
    RenderMesh2D(meshes["aripa1"], shaders["VertexColor"], modelMatrixA1);
    RenderMesh2D(meshes["aripa2"], shaders["VertexColor"], modelMatrixA2);
    RenderMesh2D(meshes["cap"], shaders["VertexColor"], modelMatrixCap);
    RenderMesh2D(meshes["corp"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["cioc"], shaders["VertexColor"], modelMatrix);
    RenderMesh2D(meshes["cap"], shaders["VertexColor"], modelMatrixVieti);
    RenderMesh2D(meshes["hitbox"], shaders["VertexColor"], modelMatrixHit);
}


void Tema1::FrameEnd()
{

}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    if (button == 1) {
        cout << "mouseX " << mouseX;
        cout << " mouseY " << mouseY << endl;
        cout << " translateX " << scale * translateX;
        cout << " translateY " << scale * translateY << endl;
    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}