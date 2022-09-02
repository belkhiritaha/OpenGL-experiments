#include "image.hpp"

image::image(){
    std::cout << "Image class initialized" << std::endl;
}

GLuint image::CompileShader(GLuint type, const GLchar* source){
    GLuint shaderObject;
    if(type == GL_VERTEX_SHADER){
        shaderObject = glCreateShader(GL_VERTEX_SHADER);
        std::cout << "Compiling vertex shader" << std::endl;
    }
    else if(type == GL_FRAGMENT_SHADER){
        shaderObject = glCreateShader(GL_FRAGMENT_SHADER);
        std::cout << "Compiling fragment shader" << std::endl;
    }
    glShaderSource(shaderObject, 1, &source, nullptr);
    glCompileShader(shaderObject);
    return shaderObject;
}

GLchar* image::LoadShaderSource(const char *filename){
    FILE* fp = fopen(filename, "rb");
    if(!fp){
        return nullptr;
    }
    fseek(fp, 0, SEEK_END);
    long size = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    GLchar* source = new GLchar[size + 1];
    fread(source, 1, size, fp);
    source[size] = 0;
    fclose(fp);
    return source;
}


GLuint image::CreateShaderProgram(const char* vertexshadersource, const char* fragementshadersource){
    GLuint programObject = glCreateProgram();
    GLuint myVertexShader = CompileShader(GL_VERTEX_SHADER, vertexshadersource);
    GLuint myFragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragementshadersource);
    
    glAttachShader(programObject, myVertexShader);
    glAttachShader(programObject, myFragmentShader);
    glLinkProgram(programObject);

    glValidateProgram(programObject);

    return programObject;
}




void image::CreateGraphicsPipeline(){
    GLchar* vs = LoadShaderSource("shaders/vertexshader.glsl");
    GLchar* fs = LoadShaderSource("shaders/fragmentshader.glsl");
    printf("%s\n", vs);
    gGraphicsPipelineShaderProgram = CreateShaderProgram(vs, fs);
}


void image::VertexSpecification(){
    std::cout << "Vertex Specification" << std::endl;
    fflush(stdout);
    const std::vector<GLfloat> vertexData{  -0.5f, -0.5f, 0.0f, // vertex 1
                                            1.0f, 0.0f, 0.0f, // color 1
                                            0.5f, -0.5f, 0.0f, // vertex 2
                                            0.0f, 1.0f, 0.0f, // color 3
                                            -0.5f, 0.5f, 0.0f, // vertex 3
                                            0.0f, 0.0f, 1.0f, // color 4
                                              
                                            0.5f, -0.5f, 0.0f, // vertex 4
                                            0.0f, 1.0f, 0.0f, // color 5
                                            0.5f, 0.5f, 0.0f, // vertex 5
                                            1.0f, 0.0f, 0.0f, // color 6
                                            -0.5f, 0.5f, 0.0f, // vertex 6
                                            0.0f, 0.0f, 1.0f, // color 7
                                            };

    
    glGenVertexArrays(1, &gVertexArrayObject);
    glBindVertexArray(gVertexArrayObject);

    // Vertex Data
    glGenBuffers(1, &gVertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, gVertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(GLfloat), vertexData.data(), GL_STATIC_DRAW);



    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT)*6, nullptr);

    // linking in VAO
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT)*6, (void*)(sizeof(GL_FLOAT)*3));


    glBindVertexArray(0);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}

void image::Run(){
    CreateGraphicsPipeline();
    VertexSpecification();
    glUseProgram(gGraphicsPipelineShaderProgram);
    glBindVertexArray(gVertexArrayObject);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
    glUseProgram(0);
}