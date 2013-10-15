#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include <GL/glfw.h>
#include "Camera.h"
#include "Mesh.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Terrain.h"
#include "Texture2D.h"

Camera * camera;

bool game_running = true;
float camera_speed = 200.0f;
float camera_rot = 50.0f;

void Input(double a_Time);

int main()
{
	glfwInit();

	//Crashes laptop for absolutely no reason at all.
	//glfwOpenWindowHint( GLFW_OPENGL_VERSION_MAJOR, 3 );
	//glfwOpenWindowHint( GLFW_OPENGL_VERSION_MINOR, 2 );
	//glfwOpenWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
	
	//Create window
	glfwOpenWindowHint( GLFW_WINDOW_NO_RESIZE, GL_TRUE );
	glfwOpenWindow( 800, 600, 0, 0, 0, 0, 1, 1, GLFW_WINDOW );
	glfwSetWindowTitle( "S A O" );
	//Glew crap
	glewExperimental = GL_TRUE;
	glewInit();

	Terrain * terrain = new Terrain();
	terrain->GenerateTerrain(128, 8.0f, 8.0f, "Textures\\riemer.png");
	terrain->Build();

	VertexDeclaration * vertexDeclaration = new VertexDeclaration();
	vertexDeclaration->AddVertexAttribute(new VertexAttribute("position", 3, GL_FLOAT, GL_FALSE, 11 * sizeof( float ), 0));
	vertexDeclaration->AddVertexAttribute(new VertexAttribute("normal", 3, GL_FLOAT, GL_FALSE, 11 * sizeof( float ), (void*)(3 * sizeof(float))));
	vertexDeclaration->AddVertexAttribute(new VertexAttribute("color", 3, GL_FLOAT, GL_FALSE, 11 * sizeof( float ), (void*)(6 * sizeof(float))));
	vertexDeclaration->AddVertexAttribute(new VertexAttribute("uv", 2, GL_FLOAT, GL_FALSE, 11 * sizeof( float ), (void*)(9 * sizeof(float))));

	ShaderProgram * program = new ShaderProgram();
	program->AddShader(new Shader("Shaders\\TerrainFragment.shader", GL_FRAGMENT_SHADER));
	program->AddShader(new Shader("Shaders\\TerrainVertex.shader", GL_VERTEX_SHADER));
	program->BindFragDataLocation(0, "outColor");
	program->Link();
	program->SetVertexDeclaration(vertexDeclaration);

	Texture2D * tex = new Texture2D();
	tex->Load("Textures\\grass.png");
	tex->Bind();

	camera = new Camera();
	camera->SetupCamera(45, 800.0 / 600.0, 10.0, 1000);
	camera->Position = glm::vec3(50, 50, 250);

	program->Bind();

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);

	double start_time = glfwGetTime();
	
	while( glfwGetWindowParam( GLFW_OPENED ) && game_running)
	{
		double new_time = glfwGetTime();
		double elapsed_time = new_time - start_time;
		start_time = new_time;

		glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
		glClearDepth(1.0f);
		glClear( GL_COLOR_BUFFER_BIT );
		glClear( GL_DEPTH_BUFFER_BIT );

		camera->Update();
		camera->Draw(terrain, program);

		glfwSwapBuffers();
		
		Input(elapsed_time);
	}
	
	program->Unbind();

	glfwTerminate();
	return 1;
}
;
 void Input(double a_Time)
 {
	if ( glfwGetKey( GLFW_KEY_ESC ) == GLFW_PRESS )
		game_running = false;

	int mouse_x, mouse_y;
	glfwGetMousePos(&mouse_x, &mouse_y);

	camera->Rotation.y -= (mouse_x - 400) * (float)a_Time * camera_rot;
	camera->Rotation.x -= (mouse_y - 300) * (float)a_Time * camera_rot;

	glfwSetMousePos(400, 300);

	//Camera movement
	if ( glfwGetKey( 0x57 ) == GLFW_PRESS )
		camera->Position += camera->GetForward() * camera_speed * (float)a_Time;
	if ( glfwGetKey( 0x53 ) == GLFW_PRESS )
		camera->Position -= camera->GetForward() * camera_speed * (float)a_Time;
	if ( glfwGetKey( 0x41 ) == GLFW_PRESS )
		camera->Position -= camera->GetLeft() * camera_speed * (float)a_Time;
	if ( glfwGetKey( 0x44 ) == GLFW_PRESS )
		camera->Position += camera->GetLeft() * camera_speed * (float)a_Time;
 }