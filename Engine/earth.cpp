#include "earth.h"

Planet earth;

// Attribute Values
#define POSITION_ATTRIBUTE 0
#define NORMAL_ATTRIBUTE 2
#define DIFFUSE_ATTRIBUTE 3
#define SPECULAR_ATTRIBUTE 4
#define TEXCOORD0_ATTRIBUTE 8
#define TEXCOORD1_ATTRIBUTE 9
#define TEXCOORD2_ATTRIBUTE 10

#define BUFFER_OFFSET(offset) ((void*)(offset))
#define MEMBER_OFFSET(s,m) ((char*)NULL + (offsetof(s,m)))

void InitializeEarth(float radius, float slices, float stacks, const char * texture_path) {

	earth.program = CreateShaderProgram({
		{ GL_VERTEX_SHADER, "Shaders/planet.vert" },
		{ GL_FRAGMENT_SHADER, "Shaders/planet.frag" }
	});
	earth.texture_id = SOIL_load_OGL_texture(texture_path, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glBindTexture(GL_TEXTURE_2D, 0);

	for (int i = 0; i <= stacks; ++i) {
		double V = i / static_cast<double>(stacks); // V texture coordinates
		double phi = V * M_PI;

		for (int j = 0; j <= slices; ++j) {
			// U texture coordinate
			double U = j / static_cast<double>(slices);
			double theta = U * M_PI * 2;

			double X = cos(theta) * sin(phi);
			double Y = cos(phi);
			double Z = sin(theta) * sin(phi);

			earth.positions.push_back(glm::vec3(X, Y, Z) * radius);
			earth.normals.push_back(glm::vec3(X, Y, Z));
			earth.texture_coordinates.push_back(glm::vec2(U, V) * glm::vec2(-1, 1));
		}
	}

	// Prepare indices for all these triangles
	for (int i = 0; i < slices * stacks + slices; ++i) {
		earth.indices.push_back(i);
		earth.indices.push_back(static_cast<GLuint>(i + slices + 1));
		earth.indices.push_back(static_cast<GLuint>(i + slices));

		earth.indices.push_back(static_cast<GLuint>(i + slices + 1));
		earth.indices.push_back(static_cast<GLuint>(i));
		earth.indices.push_back(static_cast<GLuint>(i + 1));
	}

	// Bind vao and vbos
	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbos[4];
	glGenBuffers(4, vbos);

	// Vertex Position
	glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
	glBufferData(GL_ARRAY_BUFFER, earth.positions.size() * sizeof(glm::vec3), earth.positions.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(POSITION_ATTRIBUTE, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(POSITION_ATTRIBUTE);

	// Vertex Normal
	glBindBuffer(GL_ARRAY_BUFFER, vbos[1]);
	glBufferData(GL_ARRAY_BUFFER, earth.normals.size() * sizeof(glm::vec3), earth.normals.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(NORMAL_ATTRIBUTE, 3, GL_FLOAT, GL_TRUE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(NORMAL_ATTRIBUTE);

	// Texture Coordinate
	glBindBuffer(GL_ARRAY_BUFFER, vbos[2]);
	glBufferData(GL_ARRAY_BUFFER, earth.texture_coordinates.size() * sizeof(glm::vec2), earth.texture_coordinates.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(TEXCOORD0_ATTRIBUTE, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
	glEnableVertexAttribArray(TEXCOORD0_ATTRIBUTE);

	// Triangle Indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[3]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, earth.indices.size() * sizeof(GLuint), earth.indices.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	earth.vao = vao;
}

void RenderEarth() {
	glBindVertexArray(earth.vao);
	earth.current_ticks = std::clock();
	float delta_ticks = (float)(earth.current_ticks - earth.previous_ticks);
	earth.previous_ticks = earth.current_ticks;
	float delta_time = delta_ticks / (float)CLOCKS_PER_SEC;

	earth.rotation += earth.rotation_rate * delta_time;
	earth.rotation = fmod(earth.rotation, earth.days_per_year);

	const glm::vec4 white(1);
	const glm::vec4 black(0);
	const glm::vec4 ambient(0.7f, 0.7f, 0.7f, 1.0f);

	// Map shader variables
	glUseProgram(earth.program);

	// Bind Texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, earth.texture_id);
	glUniform1i(glGetUniformLocation(earth.program, "earth_texture"), 0);

	// Properties of the Light Source
	glm::mat4 sun_model_matrix = glm::rotate(glm::radians(0.0f), glm::vec3(0, 1, 0)) *
		glm::scale(glm::vec3(100.756f));
	glUniform4fv(glGetUniformLocation(earth.program, "light_position_w"), 1, glm::value_ptr(sun_model_matrix));
	glUniform4fv(glGetUniformLocation(earth.program, "light_color"), 1, glm::value_ptr(white));
	glUniform4fv(glGetUniformLocation(earth.program, "ambient"), 1, glm::value_ptr(ambient));

	glm::mat4 modelMatrix =
		glm::rotate(glm::radians(earth.rotation), glm::vec3(0.0, 23.0, 0.0f)) * // Update Earth's Rotation
		glm::scale(glm::vec3(12.756f)); // Update Earth's Size
	glm::vec4 eyePosW = glm::vec4(camera.position, 1);
	glm::mat4 mvp = GetProjectionMatrix() * GetViewMatrix() * modelMatrix;
	glUniformMatrix4fv(glGetUniformLocation(earth.program, "model_view_projection_matrix"), 1, GL_FALSE, glm::value_ptr(mvp));
	glUniformMatrix4fv(glGetUniformLocation(earth.program, "model_matrix"), 1, GL_FALSE, glm::value_ptr(modelMatrix));
	glUniform4fv(glGetUniformLocation(earth.program, "eye_position_w"), 1, glm::value_ptr(eyePosW));

	// Material properties
	glUniform4fv(glGetUniformLocation(earth.program, "material_emissive"), 1, glm::value_ptr(black));
	glUniform4fv(glGetUniformLocation(earth.program, "material_diffuse"), 1, glm::value_ptr(white));
	glUniform4fv(glGetUniformLocation(earth.program, "material_specular"), 1, glm::value_ptr(white));
	glUniform1f(glGetUniformLocation(earth.program, "material_shininess"), 50.0f);

	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(earth.indices.size()), GL_UNSIGNED_INT, 0);
}