#include "shader.h"

GLuint g_iShader;

void Shader_LoadDefault() {
    Log_Info( "Loading default shader!\n" );

    // Vertex shader
    FILE *pVertFile = SafeOpenFile( "shaders/default.vert", "rb" );
    fseek( pVertFile, 0, SEEK_END );
    int iLength = ftell( pVertFile );
    fseek( pVertFile, 0, SEEK_SET );
    GLchar *szVertShader = malloc( iLength + 1);
    fread( szVertShader, 1, iLength, pVertFile );
    fclose( pVertFile );

    GLuint iVertexShader = glCreateShader( GL_VERTEX_SHADER );
    glShaderSource( iVertexShader, 1, (const GLchar**)&szVertShader, &iLength );
    glCompileShader( iVertexShader );

    GLint iSuccess;
    glGetShaderiv( iVertexShader, GL_COMPILE_STATUS, &iSuccess );
    if( iSuccess == GL_FALSE ) {
        GLuint iLogLength;
        glGetShaderiv(iVertexShader, GL_INFO_LOG_LENGTH, &iLogLength);
        char *szErrorLog = (char*) malloc(iLogLength);
        glGetShaderInfoLog(iVertexShader, iLogLength, &iLogLength, szErrorLog);

        ThrowError( szErrorLog );
    }

    // Fragment shader
    FILE *pFragFile = SafeOpenFile( "shaders/default.frag", "rb" );
    fseek( pFragFile, 0, SEEK_END );
    iLength = ftell( pFragFile );
    fseek( pFragFile, 0, SEEK_SET );
    GLchar *szFragShader = malloc( iLength + 1);
    fread( szFragShader, 1, iLength, pFragFile );
    fclose( pFragFile );

    GLuint iFragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
    glShaderSource( iFragmentShader, 1, (const GLchar**)&szFragShader, &iLength );
    glCompileShader( iFragmentShader );

    glGetShaderiv( iFragmentShader, GL_COMPILE_STATUS, &iSuccess );
    if( iSuccess == GL_FALSE ) {
        GLuint iLogLength;
        glGetShaderiv(iFragmentShader, GL_INFO_LOG_LENGTH, &iLogLength);
        char *szErrorLog = (char*) malloc(iLogLength);
        glGetShaderInfoLog(iFragmentShader, iLogLength, &iLogLength, szErrorLog);
        
        ThrowError( szErrorLog );
    }

    // GL Program
    g_iShader = glCreateProgram();
    glAttachShader( g_iShader, iVertexShader );
    glAttachShader( g_iShader, iFragmentShader );
    glLinkProgram( g_iShader );

    glGetShaderiv( g_iShader, GL_LINK_STATUS, &iSuccess );
    if( iSuccess == GL_FALSE ) {
        GLuint iLogLength;
        glGetShaderiv(iVertexShader, GL_INFO_LOG_LENGTH, &iLogLength);
        char *szErrorLog = (char*) malloc(iLogLength);
        glGetShaderInfoLog(iVertexShader, iLogLength, &iLogLength, szErrorLog);

        ThrowError( szErrorLog );
    }

    glDeleteShader( iVertexShader );
    glDeleteShader( iFragmentShader );
}