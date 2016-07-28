
// aviophobia headers
#include "LogManager.h"
#include "Shape.h"

av::Shape::Shape() {
    this->shape_initialized = false;

    av::LogManager &log_manager = av::LogManager::getInstance();

    this->programId = glCreateProgram();

    // Vertex shader stuff
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const GLchar* vertexShaderSource[] =
    {
        "#version 140\nin vec2 LVertexPos2D; void main() { gl_Position = vec4( LVertexPos2D.x, LVertexPos2D.y, 0, 1 ); }"
    };

    //Set vertex source
    glShaderSource(vertexShader, 1, vertexShaderSource, NULL);

    //Compile vertex source
    glCompileShader(vertexShader);

    //Check vertex shader for errors
    GLint vShaderCompiled = GL_FALSE;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vShaderCompiled);
    if (vShaderCompiled != GL_TRUE) {
        log_manager.writeLog(4, "av::GraphicsManager::startUp(): Unable to compile vertex shader. %d\n", vertexShader);
        // printShaderLog(vertexShader);
        return;
    }

    // Attach vertex shader to program
    glAttachShader(this->programId, vertexShader);

    // Create fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    // Get fragment source
    const GLchar* fragmentShaderSource[] =
    {
        "#version 140\nout vec4 LFragment; void main() { LFragment = vec4( 1.0, 0.5, 0.5, 1.0 ); }"
    };
    //Set fragment source
    glShaderSource(fragmentShader, 1, fragmentShaderSource, NULL);

    // Compile fragment source
    glCompileShader(fragmentShader);

    // Check fragment shader for errors
    GLint fShaderCompiled = GL_FALSE;
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &fShaderCompiled);
    if (fShaderCompiled != GL_TRUE) {
        log_manager.writeLog(4, "av::GraphicsManager::startUp(): Unable to compile fragment shader. %d\n", fragmentShader);
        // printShaderLog(vertexShader);
        return;
    }

    //Attach fragment shader to program
    glAttachShader(this->programId, fragmentShader);


    //Link program
    glLinkProgram(this->programId);

    //Check for errors
    GLint programSuccess = GL_TRUE;
    glGetProgramiv(this->programId, GL_LINK_STATUS, &programSuccess);
    if (programSuccess != GL_TRUE) {
        log_manager.writeLog(4, "av::GraphicsManager::startUp(): Unable to link program. %d\n", this->programId);
        // printProgramLog(gProgramID);
        return;
    }

    /////////////////////////////////////////////
    // Get vertex attribute location
    std::string glslProgramVar = "LVertexPos2D";
    this->vertexAttribLoc = glGetAttribLocation(this->programId, glslProgramVar.c_str());
    if (this->vertexAttribLoc == -1) {
        log_manager.writeLog(4, "av::GraphicsManager::startUp(): %s is not a valid glsl program variable\n", glslProgramVar.c_str());
        return;
    }

    //Initialize clear color
    glClearColor(0.f, 0.f, 0.f, 1.f);

    //VBO data
    GLfloat vertexData[] =
    {
        -0.5f, -0.5f,
        0.5f, -0.5f,
        0.5f,  0.5f,
        -0.5f,  0.5f
    };

    //IBO data
    GLuint indexData[] = { 0, 1, 2, 3 };

    this->vbo = 0;
    this->ibo = 0;
    //Create VBO
    glGenBuffers(1, &this->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glBufferData(GL_ARRAY_BUFFER, 2 * 4 * sizeof(GLfloat), vertexData, GL_STATIC_DRAW);

    //Create IBO
    glGenBuffers(1, &this->ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), indexData, GL_STATIC_DRAW);

    this->shape_initialized = true;
}

av::Shape::~Shape() {
    // Deallocate GL program
    glDeleteProgram(this->programId);
}

int av::Shape::update() {
    return 0;
}

int av::Shape::render() {
    if (!this->shape_initialized) {
        return -1;
    }
    //Clear color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    //Bind program
    glUseProgram(this->programId);

    //Enable vertex position
    glEnableVertexAttribArray(this->vertexAttribLoc);

    //Set vertex data
    glBindBuffer(GL_ARRAY_BUFFER, this->vbo);
    glVertexAttribPointer(this->vertexAttribLoc, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), NULL);

    //Set index data and render
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->ibo);
    glDrawElements(GL_TRIANGLE_FAN, 4, GL_UNSIGNED_INT, NULL);

    //Disable vertex position
    glDisableVertexAttribArray(this->vertexAttribLoc);

    //Unbind program
    glUseProgram(NULL);

    return 1;
}