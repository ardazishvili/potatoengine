#include "program.hpp"

#include "opengl_utils.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

namespace pt
{

std::string program::load_file(const std::string& file_name)
{
    std::fstream file(file_name);

    if (!file.is_open())
    {
        throw std::runtime_error("Error: failed to open the file" + file_name);
    }

    std::stringstream ss;

    ss << file.rdbuf();

    file.close();

    return ss.str();
}

GLuint program::load_shader(const std::string& code, GLenum shader_type)
{

    GLuint shader_id;
    shader_id = glCreateShader(shader_type);
    check_gl_errors();

    glShaderSource(shader_id, 1,
                   reinterpret_cast<const GLchar* const*>(code.c_str()),
                   nullptr);
    check_gl_errors();

    GLint compilation_result;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &compilation_result);
    check_gl_errors();

    if (GL_FALSE == compilation_result)
    {
        GLsizei error_length = 0;
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &error_length);

        check_gl_errors();

        std::string message(static_cast<unsigned int>(error_length), ' ');
        glGetShaderInfoLog(shader_id, error_length, nullptr, message.data());
        check_gl_errors();

        delete_shader(shader_id);

        std::cerr << "Error compiling shader: " << code << message.data()
                  << '\n';

        throw std::runtime_error("Error: failed to compile shader");
    }

    return shader_id;
}

program::program(const std::string& vertex_path,
                 const std::string& fragment_path)
{
    auto vertex_code = load_file(vertex_path);
    auto frag_code   = load_file(fragment_path);

    auto vertex_id = load_shader(vertex_code, GL_VERTEX_SHADER);
    auto frag_id   = load_shader(frag_code, GL_FRAGMENT_SHADER);

    program_id_ = make_program(vertex_id, frag_id);

    delete_shader(vertex_id);
    delete_shader(frag_id);
}

GLuint program::make_program(GLuint vertex_id, GLuint fragment_id)
{
    GLuint result_program = glCreateProgram();
    check_gl_errors();

    glAttachShader(result_program, vertex_id);
    check_gl_errors();

    glAttachShader(result_program, fragment_id);
    check_gl_errors();

    glLinkProgram(result_program);
    check_gl_errors();

    GLint link_result;
    glGetProgramiv(result_program, GL_LINK_STATUS, &link_result);
    check_gl_errors();

    if (link_result == GL_FALSE)
    {
        GLint info_length = 0;
        glGetProgramiv(result_program, GL_INFO_LOG_LENGTH, &info_length);
        check_gl_errors();

        std::string info_log(static_cast<unsigned int>(info_length), ' ');
        glGetProgramInfoLog(result_program, info_length, nullptr,
                            info_log.data());
        check_gl_errors();

        std::cerr << "Error linking the program:" << '\n' << info_log.data();

        glDeleteProgram(result_program);
        check_gl_errors();

        throw std::runtime_error("Error: failed to link the program");
    }

    return result_program;
}

void program::delete_shader(GLuint shader_id)
{
    glDeleteShader(shader_id);
    check_gl_errors();
}

void program::use()
{
    glUseProgram(program_id_);
    check_gl_errors();
}

program::~program()
{
    glDeleteProgram(program_id_);
    check_gl_errors();
}

void program::validate()
{

    glValidateProgram(program_id_);
    check_gl_errors();

    GLint validate_result = 0;
    glGetProgramiv(program_id_, GL_VALIDATE_STATUS, &validate_result);
    check_gl_errors();

    if (validate_result == GL_FALSE)
    {
        GLint info_length = 0;

        glGetProgramiv(program_id_, GL_INFO_LOG_LENGTH, &info_length);
        check_gl_errors();

        std::string error_message(static_cast<unsigned int>(info_length), ' ');

        glGetProgramInfoLog(program_id_, info_length, nullptr,
                            error_message.data());
        check_gl_errors();

        throw std::runtime_error("Error: failed to validate the program:" +
                                 error_message);
    }
}

} // namespace pt