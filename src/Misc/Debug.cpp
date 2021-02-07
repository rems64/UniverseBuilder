#include <UB/Debug.hpp>

void GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << ")" << std::endl;
        return false;
    }
    return true;
}

void INFO(std::initializer_list<const char*> info)
{
    std::cout << "[INFO] ";
    std::initializer_list<const char*>::iterator it;
    for (it = info.begin(); it != info.end(); it++)
    {
        std::cout << *it;
    }
    std::cout << std::endl;
}
