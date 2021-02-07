#pragma once

#include <string>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <filesystem>

#include <UB/Debug.hpp>
#include <glm/glm.hpp>

namespace UB
{
	class Shader
	{
	public:
		Shader();
		Shader(const std::string&);
		~Shader();

		//void CreateShader(const std::string&);
		bool compile();
		void bind();
		void unbind();
		bool save();

		std::string& getVertexSource();

		GLint getUniform(const GLchar*);
		void setUniform1i(const GLchar*, GLint);

		void setUniform1ui(const GLchar*, GLuint);

		void setUniform1f(const GLchar*, GLfloat);
		void setUniform1f(GLint, GLfloat);

		void setUniform2f(const GLchar*, GLfloat, GLfloat);
		void setUniform2f(GLint, GLfloat, GLfloat);

		void setUniform3f(const char*, GLfloat, GLfloat, GLfloat);

		void setUniformMat4f(const std::string& name, const glm::mat4& matrix);
		void setUniformSampler2D(const std::string& name, const unsigned int* texture);

	private:
		std::string vertexSource;
		std::string fragmentSource;
		unsigned int program;

		//static unsigned int CreateShader(const std::string&, const std::string&);
		int GetUniformLocation(const std::string& name);
		void ParseShader(const std::string&);
		static unsigned int CompileShader(unsigned int, const std::string&);
	};
	struct ShaderProgramSource
	{
		const std::string& VertexSource;
		const std::string& FragmentSource;
	};
};