#include "app.hpp"

app::app(){
    Run();
}


void app::InitializeProgram()
{
    std::cout << "Initializing program" << std::endl;
    fflush(stdout);
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL could not initialize!" << std::endl;
        exit(1);
    }

    std::cout << "SDL initialized" << std::endl;
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    gGraphicsApplicationWindow = SDL_CreateWindow("SDL2 OpenGL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, gScreenWidth, gScreenHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if(gGraphicsApplicationWindow==nullptr){
        std::cout << "Window could not be created!" << std::endl;
        exit(1);
    }
    std::cout << "Window created" << std::endl;

    gOpenGlContext = SDL_GL_CreateContext(gGraphicsApplicationWindow);
    if(gOpenGlContext==nullptr){
        std::cout << "OpenGL context could not be created!" << std::endl;
        exit(1);
    }
    std::cout << "OpenGL context created" << std::endl;

    if(!gladLoadGLLoader(SDL_GL_GetProcAddress)){
        std::cout << "Failed to initialize OpenGL context" << std::endl;
        exit(1);
    }
}


void app::PreDraw(){
    float time = SDL_GetTicks() / 1000.0f;
    glUniform1f(glGetUniformLocation(gGraphicsPipelineShaderProgram, "time"), time);
    std::cout << "time: " << time << std::endl;

    auto transformMatrix = glm::mat4(cos(time), -sin(time), 0.0f, input * time * 0.1f,
                                     sin(time), cos(time), 0.0f, input * time * 0.1f,
                                     0.0f, 0.0f, 1.0f, input * time * 0.1f,
                                     0.0f, 0.0f, 0.0f, 1.0f);

    auto transLoc = glGetUniformLocation(gGraphicsPipelineShaderProgram, "transform");
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, glm::value_ptr(transformMatrix));

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);

    glViewport(0, 0, gScreenWidth, gScreenHeight);
    glClearColor(1.0f, 1.0f, 0.0f, 1.0f);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(gGraphicsPipelineShaderProgram);
}


void app::Draw(){
    glBindVertexArray(gVertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, gVertexBufferObject);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}


void app::Input(){
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            gQuit = true;
            break;

        case SDL_KEYUP:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                gQuit = true;
                break;
            
            case SDLK_w:
                std::cout << "W pressed" << std::endl;
                input = 1;
                break;
            }

        default:
            break;
        }
    }
}


void app::MainLoop()
{
    std::cout << "Main loop started" << std::endl;
    fflush(stdout);
    while(!gQuit){

        Input();

        PreDraw();

        Draw();

        // Update the screen
        SDL_GL_SwapWindow(gGraphicsApplicationWindow);
    }
}


void app::CleanUp()
{
    SDL_DestroyWindow(gGraphicsApplicationWindow);
    SDL_GL_DeleteContext(gOpenGlContext);
    SDL_Quit();
}

GLuint app::CompileShader(GLuint type, const GLchar* source){
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

GLchar* app::LoadShaderSource(const char *filename){
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


GLuint app::CreateShaderProgram(const char* vertexshadersource, const char* fragementshadersource){
    GLuint programObject = glCreateProgram();
    GLuint myVertexShader = CompileShader(GL_VERTEX_SHADER, vertexshadersource);
    GLuint myFragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragementshadersource);
    
    glAttachShader(programObject, myVertexShader);
    glAttachShader(programObject, myFragmentShader);
    glLinkProgram(programObject);

    glValidateProgram(programObject);

    return programObject;
}


void app::CreateGraphicsPipeline(){
    GLchar* vs = LoadShaderSource("shaders/vertexshader.glsl");
    GLchar* fs = LoadShaderSource("shaders/fragmentshader.glsl");
    printf("%s\n", vs);
    gGraphicsPipelineShaderProgram = CreateShaderProgram(vs, fs);
}


void app::VertexSpecification(){
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


void app::Run()
{
    InitializeProgram();
    // myImage.Run();
    CreateGraphicsPipeline();
    VertexSpecification();
    MainLoop();
    CleanUp();
}