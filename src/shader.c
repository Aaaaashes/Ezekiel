#include "shader.h"

u32 shaderCreate(const char* vertexPath, const char* fragmentPath) {
	u32 shader;

	// Step 1: load the shaders from their corresponding source files

	char* vertexSource;
	char* fragSource;

	FILE* vertexFilePtr = fopen(vertexPath, "r");
	assertErr(vertexFilePtr, "FATAL::SHADER::VERT::FILE - Failed to open vertex shader file.", 0, true);
	FILE* fragFilePtr = fopen(fragmentPath, "r");
	assertErr(fragFilePtr, "FATAL::SHADER::FRAG::FILE - Failed to open fragment shader file.", 0, true);

	fseek(vertexFilePtr, 0, SEEK_END);
	u32 vertexFileSize = ftell(vertexFilePtr);
	fseek(vertexFilePtr, 0, SEEK_SET);

	fseek(fragFilePtr, 0, SEEK_END);
	long fragFileSize = ftell(fragFilePtr);
	fseek(fragFilePtr, 0, SEEK_SET);

	vertexSource = (char*)malloc(vertexFileSize + 1);
	if (vertexSource == NULL) {
		fclose(vertexFilePtr);
		fclose(fragFilePtr);
		fatalError("FATAL::SHADER::VERT::PREP - Unable to allocate memory for vertex shader source.", true);
	}

	fragSource = (char*)malloc(fragFileSize + 1);
	if (fragSource == NULL) {
		fclose(vertexFilePtr);
		fclose(fragFilePtr);
		fatalError("FATAL::SHADER::FRAG::PREP - Unable to allocate memory for fragment shader source.", true);
	}

	// Read the contents of the shader files into their corresponding source memory.
	usize bytesRead = fread(vertexSource, 1, vertexFileSize, vertexFilePtr);
	if (bytesRead != vertexFileSize) {
		free(vertexSource);
		fclose(vertexFilePtr);
		fclose(fragFilePtr);
		// Handle read error, e.g., the file size doesn't match what was read
		// You may want to return or handle this error appropriately.
	}
	vertexSource[vertexFileSize] = '\0'; // Null-terminate the string
	fread(fragSource, 1, fragFileSize, fragFilePtr);
	fragSource[fragFileSize] = '\0'; // Null-terminate the string

	// Step 2: Compile the shaders
	u32 vertex, fragment;

	vertex = shaderCompile(vertexSource, GL_VERTEX_SHADER, "VERTEX");
	fragment = shaderCompile(fragSource, GL_FRAGMENT_SHADER, "FRAGMENT");

	int success;
	char infoLog[512];

	shader = glCreateProgram(); // Making the shader program
	glAttachShader(shader, vertex);
	glAttachShader(shader, fragment);
	glLinkProgram(shader);

	glGetProgramiv(shader, GL_LINK_STATUS, &success); // Print linking errors if any
	if (!success)
	{
		glGetProgramInfoLog(shader, 512, NULL, infoLog);
		fatalError("ERROR::SHADER::PROGRAM::LINKING_FAILED\n%s",true,infoLog);
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
	return shader;
}

u32 shaderCompile(const char* source, u32 type, const char* name) {
	u32 shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		fatalError("ERROR::SHADER::%s::COMPILATION_FAILED\n%s", name, infoLog);
	};
	return shader;
}

void shaderUse(u32 shaderId) {
	glUseProgram(shaderId);
}

void shaderSetBool(u32 shaderId, const char* name, bool value) {
	glUniform1i(glGetUniformLocation(shaderId, name), (int)value);
}
void shaderSetInt(u32 shaderId, const char* name, i32 value) {
	glUniform1i(glGetUniformLocation(shaderId, name), value);
}
void shaderSetFloat(u32 shaderId, const char* name, f32 value) {
	glUniform1f(glGetUniformLocation(shaderId, name), value);
}
void shaderSetVec2(u32 shaderId, const char* name, vec2 value) {
	glUniform2fv(glGetUniformLocation(shaderId, name), 1, value);
}
void shaderSetVec3(u32 shaderId, const char* name, vec3 value) {
	glUniform3fv(glGetUniformLocation(shaderId, name), 1, value);
}
void shaderSetVec4(u32 shaderId, const char* name, vec4 value) {
	glUniform4fv(glGetUniformLocation(shaderId, name), 1, value);
}
void shaderSetMat2(u32 shaderId, const char* name, mat2 value) {
	glUniformMatrix2fv(glGetUniformLocation(shaderId, name), 1, GL_FALSE, value);
}
void shaderSetMat3(u32 shaderId, const char* name, mat3 value) {
	glUniformMatrix3fv(glGetUniformLocation(shaderId, name), 1, GL_FALSE, value);
}
void shaderSetMat4(u32 shaderId, const char* name, mat4 value) {
	glUniformMatrix4fv(glGetUniformLocation(shaderId, name), 1, GL_FALSE, value);
}
