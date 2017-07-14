#include "skybox.h"

Skybox skybox;

void InitializeSkybox() {
	skybox.program = CreateShaderProgram({
		{ GL_VERTEX_SHADER, "Shaders/skybox.vert" },
		{ GL_FRAGMENT_SHADER, "Shaders/skybox.frag" }
	});

	std::vector<std::string> faces = {
		"Textures\\SkyboxPositiveX.png",
		"Textures\\SkyboxNegativeX.png",
		"Textures\\SkyboxPositiveY.png",
		"Textures\\SkyboxNegativeY.png",
		"Textures\\SkyboxPositiveZ.png",
		"Textures\\SkyboxNegativeZ.png"
	};
	skybox.texture_id = LoadCubeMapTexture(faces);

	GLuint vao, vbo, ibo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	skybox.indices = {
		0, 1, 2, 0, 2, 3,			// Front Face
		4, 5, 6, 4, 6, 7,			// Right Face
		8, 9, 10, 8, 10, 11,		// Back Face
		12, 13, 14, 12, 14, 15,		// Left Face
		16, 17, 18, 16, 18, 19,		// Top Face
		20, 21, 22, 20, 22, 23 };	// Bottom Face

	skybox.vertices.push_back(glm::vec3(-1.0, -1.0, 1.0));
	skybox.vertices.push_back(glm::vec3(1.0, -1.0, 1.0));
	skybox.vertices.push_back(glm::vec3(1.0, 1.0, 1.0));
	skybox.vertices.push_back(glm::vec3(-1.0, 1.0, 1.0));
	skybox.vertices.push_back(glm::vec3(1.0, 1.0, 1.0));
	skybox.vertices.push_back(glm::vec3(1.0, 1.0, -1.0));
	skybox.vertices.push_back(glm::vec3(1.0, -1.0, -1.0));
	skybox.vertices.push_back(glm::vec3(1.0, -1.0, 1.0));
	skybox.vertices.push_back(glm::vec3(-1.0, -1.0, -1.0));
	skybox.vertices.push_back(glm::vec3(1.0, -1.0, -1.0));
	skybox.vertices.push_back(glm::vec3(1.0, 1.0, -1.0));
	skybox.vertices.push_back(glm::vec3(-1.0, 1.0, -1.0));
	skybox.vertices.push_back(glm::vec3(-1.0, -1.0, -1.0));
	skybox.vertices.push_back(glm::vec3(-1.0, -1.0, 1.0));
	skybox.vertices.push_back(glm::vec3(-1.0, 1.0, 1.0));
	skybox.vertices.push_back(glm::vec3(-1.0, 1.0, -1.0));
	skybox.vertices.push_back(glm::vec3(1.0, 1.0, 1.0));
	skybox.vertices.push_back(glm::vec3(-1.0, 1.0, 1.0));
	skybox.vertices.push_back(glm::vec3(-1.0, 1.0, -1.0));
	skybox.vertices.push_back(glm::vec3(1.0, 1.0, -1.0));
	skybox.vertices.push_back(glm::vec3(-1.0, -1.0, -1.0));
	skybox.vertices.push_back(glm::vec3(1.0, -1.0, -1.0));
	skybox.vertices.push_back(glm::vec3(1.0, -1.0, 1.0));
	skybox.vertices.push_back(glm::vec3(-1.0, -1.0, 1.0));

	// Bind vbo
	glGenBuffers(1, &vbo);
	// Array Buffer Size for Vertices = Number of Vertices * size of each vertex 
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, skybox.vertices.size() * sizeof(glm::vec3), &skybox.vertices[0], GL_STATIC_DRAW);

	// Bind ibo
	glGenBuffers(1, &ibo);
	// Array Buffer Size for Indices = Number of Indices * size of each index (unsigned int)
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, skybox.indices.size() * sizeof(unsigned int), &skybox.indices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);

	glBindVertexArray(0);
	skybox.vao = vao;
}

void RenderSkybox() {
	glDisable(GL_DEPTH_TEST);
	glDepthMask(false);
	// assume we're working with the modelview
	glPushMatrix();

	// inverseModelView is a 4x4 matrix with no translation and a transposed 
	// upper 3x3 portion from the regular modelview
	glLoadIdentity();

	// Map shader variables
	glUseProgram(skybox.program);

	glBindVertexArray(skybox.vao);
	// Bind Texture
	glBindTexture(GL_TEXTURE_CUBE_MAP_SEAMLESS, skybox.texture_id);

	glm::mat4 view = glm::mat4(glm::mat3(GetViewMatrix()));
	glUniformMatrix4fv(glGetUniformLocation(skybox.program, "view"), 1, false, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(skybox.program, "projection"), 1, false, glm::value_ptr(GetProjectionMatrix()));

	glDrawElements(GL_TRIANGLE_STRIP, 36, GL_UNSIGNED_INT, 0);

	glPopMatrix();
	glDepthMask(true);
	glEnable(GL_DEPTH_TEST);
}
