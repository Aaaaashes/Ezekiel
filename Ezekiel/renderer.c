#include "renderer.h"

Renderer renderer; // global renderer struct

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

	renderer.shaderProgram = shaderCreate("vertex.glsl", "fragment.glsl");

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

	texCreateGl(&renderer.texture1);
	texBindGl(renderer.texture1, GL_TEXTURE0);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	texLoadFromFile(&renderer.texture1, "awesomeface.png", GL_RGBA);
	if (renderer.texture1.success)
	{
		texGlLoadData(renderer.texture1);
	}
	else
	{
		fatalError("Failed to load texture");
	}
	texFreeData(&renderer.texture1);

	glUseProgram(renderer.shaderProgram);

	glUniform1i(glGetUniformLocation(renderer.shaderProgram, "texture1"), 0);

	renderer.VAO = vaoCreate();
	renderer.VBO = vboCreate();
	renderer.EBO = eboCreate();

	vaoBind(renderer.VAO);

	vboBind(renderer.VBO);
	vboBuffer(renderer.VBO, vertices, 0, sizeof(vertices));

	//eboBind(renderer.EBO);
	//eboBuffer(renderer.EBO, indices, 0, sizeof(indices));

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

void updateCamDirs(vec3 lookAt) {
	glm_vec3_sub(renderer.camPos, lookAt, lookAt);
	glm_vec3_normalize_to(lookAt, renderer.camDir);
	glm_vec3_cross(GLM_YUP, renderer.camDir, renderer.camRight);
	glm_vec3_normalize(renderer.camRight);
	glm_vec3_cross(renderer.camDir, renderer.camRight, renderer.camUp);
}

void updateCamMat() {
	vec3 camFront = { 0.0f, 0.0f, -1.0f };
	glm_vec3_add(camFront, renderer.camPos, camFront);
	glm_lookat(renderer.camPos, camFront, renderer.camUp, renderer.view);
	shaderSetMat4(renderer.shaderProgram, "view", renderer.view);
}

void updateCamPos(vec3 pos) {
	renderer.camPos[0] = pos[0];
	renderer.camPos[1] = pos[1];
	renderer.camPos[2] = pos[2];
}

void addCamPos(vec3 inc) {
	glm_vec3_add(renderer.camPos, inc, renderer.camPos);
	printf("X: %f, %Y: %f, Z: %f\n", renderer.camPos[0], renderer.camPos[1], renderer.camPos[2]);
}

void updateCam(vec3 pos, vec3 lookAt) {
	updateCamPos(pos);
	updateCamDirs(lookAt);
	updateCamMat();
}

void updateProjectionMatrix(u32 w, u32 h) {
	glm_mat4_identity(&renderer.projection);
	glm_perspective(glm_rad(45.0f), (float)w / (float)h, 0.1f, 100.0f, renderer.projection);
	shaderSetMat4(renderer.shaderProgram, "projection", renderer.projection);
}

void rectangle() {
	texBindGl(renderer.texture1, GL_TEXTURE0);

	glUseProgram(renderer.shaderProgram);


	updateCam(renderer.camPos, (vec3) {0,0,0});

	//updateProjectionMatrix(window.scrWidth, window.scrHeight);

	f32 timeValue = glfwGetTime();
	f32 sinTimeValue = (sin(timeValue) + 1) / 2.0f;
	shaderSetFloat(renderer.shaderProgram, "sinTime", sinTimeValue);

	vaoBind(renderer.VAO);
	for (int i = 0; i < 10; i++)
	{
		// calculate the model matrix for each object and pass it to shader before drawing
		mat4 model;
		glm_mat4_identity(&model);
		glm_translate(&model, cubePositions[i]);
		float angle = 20.0f * i;
		float vMod = sin(i * 10);
		glm_rotate(model, (float)glfwGetTime() / (vMod ? vMod : 1) + glm_rad(angle), (vec3) { 1.0f, 0.3f, 0.5f });
		
		shaderSetMat4(renderer.shaderProgram, "model", model);

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	vaoUnbind();
}