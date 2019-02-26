#include "Tema1.h"

#include <vector>
#include <iostream>

#include <Core/Engine.h>
#include "Transform2D.h"
#include "Object2D.h"

using namespace std;
int ok3 = 0;
int p = 0;
float scalex = 0.8f;
float scaley = 0.8f;
float xball = 640;
float yball = 70;
float depx = 2;
float depy = 4;
int time = 100;
float angle = 0;

float initx = 617;
float inity = 20;
int ok = 0;
int start = 0;
int nrlives = 3;
int power = 0;
int ok4 = 0;
std::vector<glm::vec3> used;
std::vector<glm::vec3> powerups;
std::vector<glm::vec3> dissapear;

glm::vec3 powerup = glm::vec3(100, 200, 0);
glm::mat3 modelMatrix1 = glm::mat3(1);
glm::mat3 modelMatrix2 = glm::mat3(1);
glm::vec3 colision = glm::vec3(0, 0, 0);
float xpower = 0;
float ypower = 0;
float radius = 10;

Tema1::Tema1()
{
}

Tema1::~Tema1()
{
}
Mesh* Tema1::CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned short> &indices)
{
	unsigned int VAO = 0;
	// TODO: Create the VAO and bind it
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	// TODO: Create the VBO and bind it
	unsigned int VBO = 0;
	GLuint VBO_ID;			// ID-ul (nume sau referinta) buffer-ului ce va fi cerut de la GPU
	glGenBuffers(1, &VBO_ID);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_ID);
	// TODO: Send vertices data into the VBO buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
	// TODO: Crete the IBO and bind it
	unsigned int IBO = 0;
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

	// TODO: Send indices data into the IBO buffer

	// ========================================================================
	// This section describes how the GPU Shader Vertex Shader program receives data
	// It will be learned later, when GLSL shaders will be introduced
	// For the moment just think that each property value from our vertex format needs to be send to a certain channel
	// in order to know how to receive it in the GLSL vertex shader

	// set vertex position attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

	// set vertex normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));

	// set texture coordinate attribute
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));

	// set vertex color attribute
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
	// ========================================================================

	// TODO: Unbind the VAO

	// Check for OpenGL errors
	CheckOpenGLError();

	// Mesh information is saved into a Mesh object
	meshes[name] = new Mesh(name);
	meshes[name]->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));
	return meshes[name];
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
	modelMatrix1 *= Transform2D::Translate(powerup.x, powerup.y);
	glm::vec3 corner = glm::vec3(0, 0, 0);
	glm::vec3 center = glm::vec3(100, 100, 0);
	float squareSide = 25;
	
	

	Mesh* square1 = Object2D::CreateSquare("square1", corner, squareSide, glm::vec3(1, 0, 0), true);
	AddMeshToList(square1);

	Mesh* square2 = Object2D::CreateSquare("square2", corner, squareSide, glm::vec3(1, 0, 0), true);
	AddMeshToList(square2);

	Mesh* square4 = Object2D::CreateSquare("square4", corner, 10, glm::vec3(0, 1, 0), true);
	AddMeshToList(square4);

	
}

void Tema1::FrameStart()
{
	// clears the color buffer (using the previously set color) and depth buffer
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::ivec2 resolution = window->GetResolution();
	// sets the screen area where to draw
	glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds)
{
	// TODO: update steps for translation, rotation, scale, in order to create animations
	glm::vec3 corner1 = glm::vec3(0, 195, 0);
	glm::vec3 corner2 = glm::vec3(1255, 195, 0);
	glm::vec3 corner3 = glm::vec3(25, 695, 0);
	glm::vec3 corner4 = glm::vec3(607.5f, 20, 0);
	glm::vec3 arr[120];
	int x = 40;
	int y = 30;
	Mesh* circle = Object2D::CreateCircle("circle", radius, glm::vec3(0, 0, 0), false);
	AddMeshToList(circle);
	if (nrlives == 0)
	{
		nrlives = 3;
	}
	for (int i = 0; i < nrlives; i++)
	{
		RenderMesh(meshes["circle"], shaders["VertexColor"], glm::vec3(x, 30, 0));
		x += 30;
	}
	int ty = 650;
	int tx = 200;
	if (p)
	{
		p -= 1;
	}
	
	for (int k = 0;k < dissapear.size();k ++)
	{ 
		colision = glm::vec3(dissapear[k].x, dissapear[k].y, 0);
		modelMatrix2 = glm::mat3(1);
		modelMatrix2 *= Transform2D::Translate(colision.x, colision.y);
		modelMatrix2 *= Transform2D::Scale(scalex,scaley);
		RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix2);
		scalex -= 0.1f;
		scaley -= 0.1f;
		if (scalex <= 0 && scaley <= 0)
		{
			dissapear.erase(dissapear.begin() + k);
			k--;
			scalex = 0.8f;
			scaley = 0.8f;
		}
		
	}
	for (int k = 0; k < powerups.size(); k++)
	{
		colision = glm::vec3(powerups[k].x, powerups[k].y, 0);
	
	
		angle++;
		if (angle == 90)
		{
			angle = 0;
		}
		modelMatrix2 = glm::mat3(1);
		modelMatrix2 *= Transform2D::Translate(colision.x, colision.y);
		modelMatrix2 *= Transform2D::Rotate(angle);
		modelMatrix2 *= Transform2D::Translate(-12.5f, -12.5f);
		RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix2);
		powerups[k].y--;
		if (powerups[k].y <= inity + 10 && powerups[k].x + 10 >= initx && powerups[k].x - 10 <= initx + 200)
		{
			nrlives++;
			p = 200;
			powerups.erase(powerups.begin() + k );
		}
		else if(powerups[k].y <= inity)
		{
			powerups.erase(powerups.begin() + k );
		}
	}
	
	if (yball - 20 <= inity && xball + 10 >= initx && xball - 10 <= initx + 200 && start == 1)
	{	
		float a = initx + 100 - xball;
		float b = 100;
		
		

		depy = -depy;
	}	
	if (yball <= inity && (xball + 10 < initx || xball - 10 > initx + 200) && depy < 0 && start == 1)
	{
		nrlives--;
		if (depy < 0)
		{
			depy = -depy;
		}
		
		start = 0;
		xball = 640;
		yball = 70;
	}
	else if (yball + 10 < 195 && xball + 10 > 1255 && start == 1)
	{
		nrlives--;
		if (depy < 0)
		{
			depy = -depy;
		}
		start = 0;
		xball = 640;
		yball = 70;
	}
	else if (yball + 10 < 195 && xball - 10 < 0 && start == 1)
	{
		nrlives--;
		if (depy < 0)
		{
			depy = -depy;
		}
		start = 0;
		xball = 640;
		yball = 70;
	}
	
		if (xball + 10 >= 1255 && yball + 10>= 195)
		{
			depx = -depx;
		}
		else if (xball - 10 <= 25 && yball + 10>= 195)
		{
			depx = -depx;
		}
		else if (yball + 10 >= 695 && xball - 10 >= 25 && xball + 10 <= 1255)
		{
			depy = -depy;
		}
	
		if (start)
		{
			yball += depy;
			xball += depx;
			modelMatrix = glm::mat3(1);
			RenderMesh(meshes["circle"], shaders["VertexColor"], glm::vec3(xball, yball, 0), glm::vec3(1));
		}
		else
		{
			xball = initx + 100;
			modelMatrix = glm::mat3(1);
			RenderMesh(meshes["circle"], shaders["VertexColor"], glm::vec3(initx + 100, yball, 0), glm::vec3(1));
		}
	
	for (int i = 0; i < 120; i++)
	{
		if (i != 0)
		{
			if (i % 12 == 0)
			{
				tx = 200;
				ty -= 35;
			}
			else
			{
				tx += 80;
			}
		}
		arr[i] = glm::vec3(tx, ty, 0);

		if (xball + 10 >= tx && xball - 10 <= tx + 50 && ty < yball + 10 && ty + 25 >= yball - 10)
		{
			int ok1 = 0;
			for (int j = 0; j < used.size(); j++)
			{
				if (arr[i].x == used[j].x && arr[i].y == used[j].y)
				{
					ok1 = 1;
					
				}
			}
			if (!ok1)
			{
				power++;
			
				if (power == 10)
				{
					xpower = tx;
					ypower = ty;
					
					powerups.push_back(glm::vec3(xpower, ypower, 0));
					power = 0;
				
				}
				
				used.push_back(arr[i]);
				dissapear.push_back(arr[i]);
				if (!p)
				{
					if (xball + 10 >= tx && xball + 10 < tx + depx)
					{
						depx = -depx;
					}
					else if (xball - 10 <= tx + 50 && xball - 10 > tx + 50 + depx)
					{
						depx = -depx;
					}
					else if (ty < yball + 10)
					{
						depy = -depy;
					}
					else if (ty + 25 > yball - 10)
					{
						depy = -depy;
					}
				}
			}

		}
		int ok2 = 0;
		for (int j = 0; j < used.size(); j++)
		{
			if ((arr[i].x == used[j].x) && (arr[i].y == used[j].y))
			{
				ok2 = 1;
			}
		}
		if (!ok2)
		{
			modelMatrix = glm::mat3(1);
			modelMatrix *= Transform2D::Translate(arr[i].x, arr[i].y);
			modelMatrix *= Transform2D::Scale(2, 1);
			RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);
		}



	}

	
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(corner1.x, corner1.y);
	modelMatrix *= Transform2D::Scale(1, 21);

	RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);
	
	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(corner2.x, corner2.y);
	modelMatrix *= Transform2D::Scale(1, 21);
	RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(corner3.x, corner3.y);
	modelMatrix *= Transform2D::Scale(49.2f, 1);
	RenderMesh2D(meshes["square1"], shaders["VertexColor"], modelMatrix);

	modelMatrix = glm::mat3(1);
	modelMatrix *= Transform2D::Translate(initx, inity);
	modelMatrix *= Transform2D::Scale(20, 1);
	RenderMesh2D(meshes["square4"], shaders["VertexColor"], modelMatrix);

}

void Tema1::FrameEnd()
{

}

void Tema1::OnInputUpdate(float deltaTime, int mods)
{

}

void Tema1::OnKeyPress(int key, int mods)
{
	// add key press event
}

void Tema1::OnKeyRelease(int key, int mods)
{
	// add key release event
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{

	initx = mouseX - 100;

	// add mouse move event
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
	start = 1;
	// add mouse button press event
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
	// add mouse button release event
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void Tema1::OnWindowResize(int width, int height)
{
}
