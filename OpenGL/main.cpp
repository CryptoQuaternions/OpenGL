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
int camera_speed = 50;

void keyboardInput(double a_Time);

int main()
{
	glfwInit();
	//Crashes laptop for absolutely no reason at all.
	//glfwOpenWindowHint( GLFW_OPENGL_VERSION_MAJOR, 3 );
	//glfwOpenWindowHint( GLFW_OPENGL_VERSION_MINOR, 2 );
	//glfwOpenWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );
	glfwOpenWindowHint( GLFW_WINDOW_NO_RESIZE, GL_TRUE );
	glfwOpenWindow( 800, 600, 0, 0, 0, 0, 0, 0, GLFW_WINDOW );
	glfwSetWindowTitle( "S A O" );
	glEnable(GL_DEPTH_TEST);

	glewExperimental = GL_TRUE;
	glewInit();

	VertexDeclaration * vertexDeclaration = new VertexDeclaration();
	vertexDeclaration->AddVertexAttribute(new VertexAttribute("position", 3, GL_FLOAT, GL_FALSE, 11 * sizeof( float ), 0));
	vertexDeclaration->AddVertexAttribute(new VertexAttribute("normal", 3, GL_FLOAT, GL_FALSE, 11 * sizeof( float ), (void*)(3 * sizeof(float))));
	vertexDeclaration->AddVertexAttribute(new VertexAttribute("color", 3, GL_FLOAT, GL_FALSE, 11 * sizeof( float ), (void*)(6 * sizeof(float))));
	vertexDeclaration->AddVertexAttribute(new VertexAttribute("uv", 2, GL_FLOAT, GL_FALSE, 11 * sizeof( float ), (void*)(9 * sizeof(float))));

	Terrain * terrain = new Terrain();
	terrain->GenerateTerrain(128, 32.0f, 32.0f, "riemer.png");
	terrain->Build();

	Texture2D * tex = new Texture2D();
	tex->Load("grass.png");
	tex->Bind();

	ShaderProgram * program = new ShaderProgram();
	program->AddShader(new Shader("frag.shader", GL_FRAGMENT_SHADER));
	program->AddShader(new Shader("vert.shader", GL_VERTEX_SHADER));
	program->BindFragDataLocation(0, "outColor");
	program->Link();
	program->SetVertexDeclaration(vertexDeclaration);

	camera = new Camera();
	camera->SetupCamera(45, 800.0 / 600.0, 0.1, 1000);
	camera->Position = glm::vec3(0, 0, 250);

	program->Bind();
	double start_time = glfwGetTime();

	glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

	while( glfwGetWindowParam( GLFW_OPENED ) && game_running)
	{
		double new_time = glfwGetTime();
		double elapsed_time = new_time - start_time;
		start_time = new_time;

		glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

		camera->Update();

		camera->Draw(terrain, program);

		glfwSwapBuffers();
		
		keyboardInput(elapsed_time);
		
	}
	
	program->Unbind();

	glfwTerminate();
	return 1;
}

 void keyboardInput(double a_Time)
 {
	if ( glfwGetKey( GLFW_KEY_ESC ) == GLFW_PRESS )
		game_running = false;

	//Camera movement
	if ( glfwGetKey( GLFW_KEY_LEFT ) == GLFW_PRESS )
		camera->Position.x -= camera_speed * a_Time;
	if ( glfwGetKey( GLFW_KEY_RIGHT ) == GLFW_PRESS )
		camera->Position.x += camera_speed * a_Time;
	if ( glfwGetKey( GLFW_KEY_UP ) == GLFW_PRESS )
		camera->Position.y += camera_speed * a_Time;
	if ( glfwGetKey( GLFW_KEY_DOWN ) == GLFW_PRESS )
		camera->Position.y -= camera_speed * a_Time;
	if( glfwGetKey( GLFW_KEY_SPACE ) == GLFW_PRESS )
		camera->Position.z += camera_speed * a_Time;
	if( glfwGetKey( GLFW_KEY_LCTRL ) == GLFW_PRESS )
		camera->Position.z -= camera_speed * a_Time;
 }