#include <Game.h>

static bool flip;

Game::Game() : window(sf::VideoMode(800, 600), "OpenGL Cube VBO")
{
}

Game::~Game() {}

void Game::run()
{

	initialize();

	sf::Event event;

	while (isRunning) {

		cout << "Game running..." << endl;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		render();
	}

}

typedef struct
{
	float coordinate[3];
	float color[3];
} Vertex;
float vertices[] = { -1.0f, -1.0f, 1.0f,
						1.0f, -1.0f, 1.0f,
						1.0f, 1.0f, 1.0f ,
						-1.0f, 1.0f, 1.0f,

						-1.0f, -1.0f, -1.0f,
						1.0f, -1.0f, -1.0f,
						1.0f, 1.0f, -1.0f,
						-1.0f, 1.0f, -1.0f };
Vertex vertex[8];
GLubyte triangles[] =	{ 0, 1, 2,
						2, 3, 0,
						2, 6, 3,
						6, 7, 3,
						7, 6, 5,
						5, 4, 7,
						5, 0, 4,
						5, 1, 0,
						1, 5, 6,
						6, 2, 1,
						4, 0, 3,
						3, 7, 4 };

/* Variable to hold the VBO identifier */
GLuint vbo[1];
GLuint index;

void Game::initialize()
{
	isRunning = true;
	
	//glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, window.getSize().x / window.getSize().y, 1.0, 500.0);
	glMatrixMode(GL_MODELVIEW);
	glTranslatef(0.0f, 0.0f, -8.0f);

	glEnable(GL_CULL_FACE);

	glewInit();

	/* Vertices counter-clockwise winding */

	vertex[0].coordinate[0] = vertices[0];
	vertex[0].coordinate[1] = vertices[1];
	vertex[0].coordinate[2] = vertices[2];

	vertex[1].coordinate[0] = vertices[3];
	vertex[1].coordinate[1] = vertices[4];
	vertex[1].coordinate[2] = vertices[5];

	vertex[2].coordinate[0] = vertices[6];
	vertex[2].coordinate[1] = vertices[7];
	vertex[2].coordinate[2] = vertices[8];

	vertex[3].coordinate[0] = vertices[9];
	vertex[3].coordinate[1] = vertices[10];
	vertex[3].coordinate[2] = vertices[11];
	
	vertex[4].coordinate[0] = vertices[12];
	vertex[4].coordinate[1] = vertices[13];
	vertex[4].coordinate[2] = vertices[14];

	vertex[5].coordinate[0] = vertices[15];
	vertex[5].coordinate[1] = vertices[16];
	vertex[5].coordinate[2] = vertices[17];

	vertex[6].coordinate[0] = vertices[18];
	vertex[6].coordinate[1] = vertices[19];
	vertex[6].coordinate[2] = vertices[20];

	vertex[7].coordinate[0] = vertices[21];
	vertex[7].coordinate[1] = vertices[22];
	vertex[7].coordinate[2] = vertices[23];
	
	vertex[0].color[0] = 0.0f;
	vertex[0].color[1] = 1.0f;
	vertex[0].color[2] = 0.0f;

	vertex[1].color[0] = 1.0f;
	vertex[1].color[1] = 0.0f;
	vertex[1].color[2] = 0.0f;

	vertex[2].color[0] = 0.0f;
	vertex[2].color[1] = 0.0f;
	vertex[2].color[2] = 1.0f;

	vertex[3].color[0] = 1.0f;
	vertex[3].color[1] = 0.0f;
	vertex[3].color[2] = 1.0f;

	vertex[4].color[0] = 0.0f;
	vertex[4].color[1] = 0.0f;
	vertex[4].color[2] = 0.0f;

	vertex[5].color[0] = 1.0f;
	vertex[5].color[1] = 1.0f;
	vertex[5].color[2] = 1.0f;

	vertex[6].color[0] = 1.0f;
	vertex[6].color[1] = 1.0f;
	vertex[6].color[2] = 0.0f;

	vertex[7].color[0] = 0.0f;
	vertex[7].color[1] = 1.0f;
	vertex[7].color[2] = 1.0f;




	/* Create a new VBO using VBO id */
	glGenBuffers(1, vbo);

	/* Bind the VBO */
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	/* Upload vertex data to GPU */
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 36, vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 36, triangles, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Game::update()
{
	elapsed = clock.getElapsedTime();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{

		for (int i = 0; i < 8; i++)
		{
			Vector3 vec = { vertex[i].coordinate[0], vertex[i].coordinate[1], vertex[i].coordinate[2] };
			vec = Matrix3::RotationX(rotationAngle) * vec;

			vertex[i].coordinate[0] = vec.x;
			vertex[i].coordinate[1] = vec.y;
			vertex[i].coordinate[2] = vec.z;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Y))
	{

		for (int i = 0; i < 8; i++)
		{
			Vector3 vec = { vertex[i].coordinate[0], vertex[i].coordinate[1], vertex[i].coordinate[2] };
			vec = Matrix3::RotationY(rotationAngle) * vec;

			vertex[i].coordinate[0] = vec.x;
			vertex[i].coordinate[1] = vec.y;
			vertex[i].coordinate[2] = vec.z;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{

		for (int i = 0; i < 8; i++)
		{
			Vector3 vec = { vertex[i].coordinate[0], vertex[i].coordinate[1], vertex[i].coordinate[2] };
			vec = Matrix3::RotationZ(rotationAngle) * vec;

			vertex[i].coordinate[0] = vec.x;
			vertex[i].coordinate[1] = vec.y;
			vertex[i].coordinate[2] = vec.z;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		for (int i = 0; i < 8; i++)
		{
			Vector3 vec = { vertex[i].coordinate[0], vertex[i].coordinate[1], vertex[i].coordinate[2] };
			vec = Matrix3::Scale3D(101) * vec;

			vertex[i].coordinate[0] = vec.x;
			vertex[i].coordinate[1] = vec.y;
			vertex[i].coordinate[2] = vec.z;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
	{
		for (int i = 0; i < 8; i++)
		{
			Vector3 vec = { vertex[i].coordinate[0], vertex[i].coordinate[1], vertex[i].coordinate[2] };
			vec = Matrix3::Scale3D(99) * vec;

			vertex[i].coordinate[0] = vec.x;
			vertex[i].coordinate[1] = vec.y;
			vertex[i].coordinate[2] = vec.z;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		for (int i = 0; i < 8; i++)
		{
			Vector3 vec = { vertex[i].coordinate[0], vertex[i].coordinate[1], vertex[i].coordinate[2] };
			float tempZ = vec.z;
			vec.z = 1;
			vec = Matrix3::Translate(0.0f, 0.01f) * vec;

			vec.z = tempZ;
			vertex[i].coordinate[0] = vec.x;
			vertex[i].coordinate[1] = vec.y;
			vertex[i].coordinate[2] = vec.z;

		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		for (int i = 0; i < 8; i++)
		{
			Vector3 vec = { vertex[i].coordinate[0], vertex[i].coordinate[1], vertex[i].coordinate[2] };
			float tempZ = vec.z;
			vec.z = 1;
			vec = Matrix3::Translate(-0.01f, 0.0f) * vec;

			vec.z = tempZ;
			vertex[i].coordinate[0] = vec.x;
			vertex[i].coordinate[1] = vec.y;
			vertex[i].coordinate[2] = vec.z;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		for (int i = 0; i < 8; i++)
		{
			Vector3 vec = { vertex[i].coordinate[0], vertex[i].coordinate[1], vertex[i].coordinate[2] };
			float tempZ = vec.z;
			vec.z = 1;
			vec = Matrix3::Translate(0.01f, 0.0f) * vec;

			vec.z = tempZ;
			vertex[i].coordinate[0] = vec.x;
			vertex[i].coordinate[1] = vec.y;
			vertex[i].coordinate[2] = vec.z;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		for (int i = 0; i < 8; i++)
		{
			Vector3 vec = { vertex[i].coordinate[0], vertex[i].coordinate[1], vertex[i].coordinate[2] };
			float tempZ = vec.z;
			vec.z = 1;
			vec = Matrix3::Translate(0.0f, -0.01f) * vec;

			vec.z = tempZ;
			vertex[i].coordinate[0] = vec.x;
			vertex[i].coordinate[1] = vec.y;
			vertex[i].coordinate[2] = vec.z;
		}
	}

	for (int i = 0, j = 0; i < 8, j < 24; i++)
	{
		vertices[j] = vertex[i].coordinate[0];
		j++;
		vertices[j] = vertex[i].coordinate[1];
		j++;
		vertices[j] = vertex[i].coordinate[2];
		j++;

	}

	

	cout << "Update up" << endl;
}

void Game::render()
{
	cout << "Drawing" << endl;

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);

	/*	As the data positions will be updated by the this program on the
		CPU bind the updated data to the GPU for drawing	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 36, vertex, GL_STATIC_DRAW);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);


	glColorPointer(3, GL_FLOAT, sizeof(Vertex), (char*)NULL + 12);

	/*	Draw Triangle from VBO	(set where to start from as VBO can contain 
		model compoents that are and are not to be drawn )	*/
	glVertexPointer(3, GL_FLOAT, sizeof(Vertex), (char*)NULL + 0);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, (char*)NULL + 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	window.display();

}

void Game::unload()
{
	cout << "Cleaning up" << endl;

	glDeleteBuffers(1, vbo);
}

