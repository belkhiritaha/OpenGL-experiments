#include "app.hpp"

app::app(){
    Run();
}


void app::InitializeProgram()
{
    srand(time(NULL));
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

    int ydirection = myScene.myPlayer.Keys[0] - myScene.myPlayer.Keys[1];
    int xdirection = myScene.myPlayer.Keys[2] - myScene.myPlayer.Keys[3];

    // auto transformMatrix = mat::translationMatrix(myScene.myPlayer.x * 0.1f, myScene.myPlayer.y * 0.1f, myScene.myPlayer.z * 0.1f);

    auto transformMatrix = mat::viewMatrix(myScene.myPlayer.x * 0.1f, myScene.myPlayer.y * 0.1f, myScene.myPlayer.z * 0.1f, 0.2f, 0.2f, time);

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
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    //glDrawElements(GL_TRIANGLES, myScene.indexBufferData.size()/3 , GL_UNSIGNED_INT, 0);
    glDrawArrays(GL_TRIANGLES, 0, myScene.vertexData.size()/3);
}

void app::Input()
{
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

            case SDLK_z:
                std::cout << "W pressed" << std::endl;
                myScene.myPlayer.Keys[0] = 0;
                continue;

            case SDLK_s:
                std::cout << "S pressed" << std::endl;
                myScene.myPlayer.Keys[1] = 0;
                continue;

            case SDLK_q:
                std::cout << "A pressed" << std::endl;
                myScene.myPlayer.Keys[2] = 0;
                continue;

            case SDLK_d:
                std::cout << "D pressed" << std::endl;
                myScene.myPlayer.Keys[3] = 0;
                continue;
            default:
                break;
            }

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_z:
                std::cout << "W pressed" << std::endl;
                myScene.myPlayer.Keys[0] = 1;
                continue;

            case SDLK_s:
                std::cout << "S pressed" << std::endl;
                myScene.myPlayer.Keys[1] = 1;
                continue;

            case SDLK_q:
                std::cout << "A pressed" << std::endl;
                myScene.myPlayer.Keys[2] = 1;
                continue;

            case SDLK_d:
                std::cout << "D pressed" << std::endl;
                myScene.myPlayer.Keys[3] = 1;
                continue;

            default:
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

        myScene.Update();
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
    gGraphicsPipelineShaderProgram = CreateShaderProgram(vs, fs);
}


void app::VertexSpecification(){
    std::cout << "Vertex Specification" << std::endl;
    fflush(stdout);
    
    glGenVertexArrays(1, &gVertexArrayObject);
    glBindVertexArray(gVertexArrayObject);

    // Vertex Data
    glGenBuffers(1, &gVertexBufferObject);
    glBindBuffer(GL_ARRAY_BUFFER, gVertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, myScene.vertexData.size() * sizeof(GLfloat), myScene.vertexData.data(), GL_STATIC_DRAW);

    // Index Buffer
    glGenBuffers(1, &gIndexBufferObject);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gIndexBufferObject);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(myScene.indexBufferData)*sizeof(GLuint), myScene.indexBufferData.data(), GL_STATIC_DRAW);


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
    CreateGraphicsPipeline();
    VertexSpecification();
    MainLoop();
    CleanUp();
}