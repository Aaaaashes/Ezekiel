#include "renderer.h"
#include "state.h"

vec3 cubePositions[] = {
	{0.0f,  0.0f,  0.0f},
	{2.0f,  5.0f, -15.0f},
	{-1.5f, -2.2f, -2.5f},
	{-3.8f, -2.0f, -12.3f},
	{2.4f, -0.4f, -3.5f},
	{-1.7f,  3.0f, -7.5f},
	{1.3f, -2.0f, -2.5f},
	{1.5f,  2.0f, -2.5f},
	{1.5f,  0.2f, -1.5f},
	{-1.3f,  1.0f, -1.5f}
};

void initRenderer() {
	glEnable(GL_DEPTH_TEST);

	state.renderer.shaderProgram = shaderCreate("vertex.glsl", "fragment.glsl");

	float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	texCreateGl(&state.renderer.texture1);
	texBindGl(state.renderer.texture1, GL_TEXTURE0);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	texLoadFromFile(&state.renderer.texture1, "container.jpg", GL_RGB);
	if (state.renderer.texture1.success)
	{
		texGlLoadData(state.renderer.texture1);
	}
	else
	{
		fatalError("Failed to load texture");
	}
	texFreeData(&state.renderer.texture1);

	glUseProgram(state.renderer.shaderProgram);

	glUniform1i(glGetUniformLocation(state.renderer.shaderProgram, "texture1"), 0);

	state.renderer.VAO = vaoCreate();
	state.renderer.VBO = vboCreate();
	state.renderer.EBO = eboCreate();

	vaoBind(state.renderer.VAO);

	vboBind(state.renderer.VBO);
	vboBuffer(state.renderer.VBO, vertices, 0, sizeof(vertices));

	//eboBind(state.renderer.EBO);
	//eboBuffer(state.renderer.EBO, indices, 0, sizeof(indices));

	// position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// uv attribute
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	vboUnbind(); // We can unbind our VBO now as it is registered
				 // as the vertex attribute's bound vertex buffer objrdfect

	vaoUnbind(); // Unbind VAO so other VAO calls won't modify it.
}

void rectangle() {
	texBindGl(state.renderer.texture1, GL_TEXTURE0);

	glUseProgram(state.renderer.shaderProgram);


	f32 timeValue = glfwGetTime();
	f32 sinTimeValue = (sin(timeValue) + 1) / 2.0f;
	shaderSetFloat(state.renderer.shaderProgram, "sinTime", sinTimeValue);

	shaderSetMat4(state.renderer.shaderProgram, "view", player.cam.view_proj.view);
	shaderSetMat4(state.renderer.shaderProgram, "projection", player.cam.view_proj.proj);

	vaoBind(state.renderer.VAO);
	for (int i = 0; i < 10; i++)
	{
		// calculate the model matrix for each object and pass it to shader before drawing
		mat4 model;
		glm_mat4_identity(&model);
		glm_translate(&model, cubePositions[i]);
		float angle = 20.0f * i;
		float vMod = sin(i * 10);
		glm_rotate(model, (float)glfwGetTime() / (vMod ? vMod : 1) + glm_rad(angle), (vec3) { 1.0f, 0.3f, 0.5f });
		shaderSetMat4(state.renderer.shaderProgram, "model", model);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	vaoUnbind();
}