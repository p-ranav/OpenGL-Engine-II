#include "cube.h"

typedef struct CubeVertexFormat {
	CubeVertexFormat(glm::vec3 vertex_position, glm::vec2 vertex_texture) :
		position(vertex_position), texture(vertex_texture) {}
	glm::vec3 position;
	glm::vec2 texture;
} CubeVertexFormat;

typedef struct Cube {
	std::vector<CubeVertexFormat> vertices; // cube vertices
	std::vector<unsigned int> indices; // indices for cube triangles
	glm::vec3 rotation, rotation_speed; // rotation speed
	glm::vec3 rotation_sin; // sine of the rotation
	GLuint program, vao, vbo, ibo; // rendering variables
	unsigned int texture_id; // bmp texture id
} Cube;

Cube cube;

void InitializeCube()
{
	cube.program = CreateShaderProgram({
		{ GL_VERTEX_SHADER, "Shaders/cube.vert" },
		{ GL_FRAGMENT_SHADER, "Shaders/cube.frag" }
	});
	cube.texture_id = SOIL_load_OGL_texture("Textures\\crate.jpg", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);

	glGenVertexArrays(1, &cube.vao);
	glBindVertexArray(cube.vao);

	cube.indices = {
		0, 1, 2, 0, 2, 3,			// Front Face
		4, 5, 6, 4, 6, 7,			// Right Face
		8, 9, 10, 8, 10, 11,		// Back Face
		12, 13, 14, 12, 14, 15,		// Left Face
		16, 17, 18, 16, 18, 19,		// Top Face
		20, 21, 22, 20, 22, 23 };	// Bottom Face

	cube.vertices.push_back(CubeVertexFormat(glm::vec3(-1.0, -1.0, 1.0), glm::vec2(0, 0)));
	cube.vertices.push_back(CubeVertexFormat(glm::vec3(1.0, -1.0, 1.0), glm::vec2(1, 0)));
	cube.vertices.push_back(CubeVertexFormat(glm::vec3(1.0, 1.0, 1.0), glm::vec2(1, 1)));
	cube.vertices.push_back(CubeVertexFormat(glm::vec3(-1.0, 1.0, 1.0), glm::vec2(0, 1)));

	cube.vertices.push_back(CubeVertexFormat(glm::vec3(1.0, 1.0, 1.0), glm::vec2(0, 0)));
	cube.vertices.push_back(CubeVertexFormat(glm::vec3(1.0, 1.0, -1.0), glm::vec2(1, 0)));
	cube.vertices.push_back(CubeVertexFormat(glm::vec3(1.0, -1.0, -1.0), glm::vec2(1, 1)));
	cube.vertices.push_back(CubeVertexFormat(glm::vec3(1.0, -1.0, 1.0), glm::vec2(0, 1)));

	cube.vertices.push_back(CubeVertexFormat(glm::vec3(-1.0, -1.0, -1.0), glm::vec2(0, 0)));
	cube.vertices.push_back(CubeVertexFormat(glm::vec3(1.0, -1.0, -1.0), glm::vec2(1, 0)));
	cube.vertices.push_back(CubeVertexFormat(glm::vec3(1.0, 1.0, -1.0), glm::vec2(1, 1)));
	cube.vertices.push_back(CubeVertexFormat(glm::vec3(-1.0, 1.0, -1.0), glm::vec2(0, 1)));

	cube.vertices.push_back(CubeVertexFormat(glm::vec3(-1.0, -1.0, -1.0), glm::vec2(0, 0)));
	cube.vertices.push_back(CubeVertexFormat(glm::vec3(-1.0, -1.0, 1.0), glm::vec2(1, 0)));
	cube.vertices.push_back(CubeVertexFormat(glm::vec3(-1.0, 1.0, 1.0), glm::vec2(1, 1)));
	cube.vertices.push_back(CubeVertexFormat(glm::vec3(-1.0, 1.0, -1.0), glm::vec2(0, 1)));

	cube.vertices.push_back(CubeVertexFormat(glm::vec3(1.0, 1.0, 1.0), glm::vec2(0, 0)));
	cube.vertices.push_back(CubeVertexFormat(glm::vec3(-1.0, 1.0, 1.0), glm::vec2(1, 0)));
	cube.vertices.push_back(CubeVertexFormat(glm::vec3(-1.0, 1.0, -1.0), glm::vec2(1, 1)));
	cube.vertices.push_back(CubeVertexFormat(glm::vec3(1.0, 1.0, -1.0), glm::vec2(0, 1)));

	cube.vertices.push_back(CubeVertexFormat(glm::vec3(-1.0, -1.0, -1.0), glm::vec2(0, 0)));
	cube.vertices.push_back(CubeVertexFormat(glm::vec3(1.0, -1.0, -1.0), glm::vec2(1, 0)));
	cube.vertices.push_back(CubeVertexFormat(glm::vec3(1.0, -1.0, 1.0), glm::vec2(1, 1)));
	cube.vertices.push_back(CubeVertexFormat(glm::vec3(-1.0, -1.0, 1.0), glm::vec2(0, 1)));

	glGenBuffers(1, &cube.vbo); 
	glBindBuffer(GL_ARRAY_BUFFER, cube.vbo); // Array Buffer Size for Vertices = Number of Vertices * size of each vertex
	glBufferData(GL_ARRAY_BUFFER, cube.vertices.size() * sizeof(CubeVertexFormat), &cube.vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &cube.ibo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cube.ibo); // Array Buffer Size for Indices = Number of Indices * size of each index (unsigned int)
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, cube.indices.size() * sizeof(unsigned int), &cube.indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(CubeVertexFormat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(CubeVertexFormat), (void*)(offsetof(CubeVertexFormat, CubeVertexFormat::texture)));
	glBindVertexArray(0);

	cube.rotation_speed = glm::vec3(90.0, 90.0, 90.0);
	cube.rotation = glm::vec3(0.0, 0.0, 0.0);
}

void RenderCube() {
	glUseProgram(cube.program);

	glActiveTexture(GL_TEXTURE0); // Bind Cube Texture
	glBindTexture(GL_TEXTURE_2D, cube.texture_id);
	unsigned int textureLocation = glGetUniformLocation(cube.program, "texture1");
	glUniform1i(textureLocation, 0);

	glUniform3f(glGetUniformLocation(cube.program, "rotation"), cube.rotation_sin.x, cube.rotation_sin.y, cube.rotation_sin.z);
	glUniformMatrix4fv(glGetUniformLocation(cube.program, "view_matrix"), 1, false, &GetViewMatrix()[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(cube.program, "projection_matrix"), 1, false, &GetProjectionMatrix()[0][0]);
	glBindVertexArray(cube.vao);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
	cube.rotation = 0.01f * cube.rotation_speed + cube.rotation;
	cube.rotation_sin = glm::vec3(cube.rotation.x * M_PI / 180, cube.rotation.y * M_PI / 180, cube.rotation.z * M_PI / 180);
}