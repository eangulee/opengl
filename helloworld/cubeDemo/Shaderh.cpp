#include "Shaderh.h"
#include <glad/glad.h>	//要用到OpenGL的函数就要包含这个头文件

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>


Shader::Shader(const GLchar* vertexPath, const GLchar* fragmentPath)
{
	//1.读取着色器代码
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	//确保文件流输出异常
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		//打开文件
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		//读取文件到流中
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		//关闭文件
		vShaderFile.close();
		fShaderFile.close();
		//将流转换为字符串
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "错误：读取文件失败，请检查文件是否存在！" << std::endl;
	}

	//2.编译着色器
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	//顶点着色器
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cout << "编译顶点着色器失败，错误信息" << infoLog << std::endl;
	}

	//片元着色器
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cout << "编译片元着色器失败，错误信息：" << infoLog << std::endl;
	}

	//着色器程序
	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	glLinkProgram(ID);
	glGetShaderiv(ID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(ID, 512, NULL, infoLog);
		std::cout << "连接着色器程序失败，错误信息：" << infoLog << std::endl;
	}

	//删除着色器
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::use()
{
	glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setMat4(const std::string& name, float value[]) const {
	/** glUniformMatrix4fv函数的参数：
		参数一：变量位置
		参数二：我们想传的矩阵个数，这里我们只设置一个，所以是1
		参数三：我们是否想转换矩阵，把行和列交换。OpenGL中的矩阵是列主序的矩阵（和DX中的不同），不过GLM中生成的矩阵也是列主序的，所以我们设置成GL_FALSE，表示不用转换。
		参数四：矩阵数组。这里我们要把矩阵转换成数组的格式传递。
	*/
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, value);
}

Shader::~Shader()
{
}
