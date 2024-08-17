// 作者：luuyiran
// 链接：https://www.zhihu.com/question/344133077/answer/2217310411
// 来源：知乎
// 著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

/* gcc x11opengl.c -lGL -lX11 -ldl */

#include <GL/gl.h>
#include <GL/glx.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dlfcn.h>

// 返回值和参数需要与OpenGL提供的函数起来
////////////////////////////////////////////////////////////////////////////////////////////////
// GLAD 加载函数指针
typedef const GLubyte * (APIENTRYP PFNGLGETSTRINGPROC)(GLenum name);
PFNGLGETSTRINGPROC glad_glGetString = NULL;
#define glGetString glad_glGetString

typedef GLuint (APIENTRYP PFNGLCREATESHADERPROC)(GLenum type);
PFNGLCREATESHADERPROC glad_glCreateShader = NULL;
#define glCreateShader glad_glCreateShader

typedef void (APIENTRYP PFNGLSHADERSOURCEPROC)(GLuint shader, GLsizei count, const GLchar *const*string, const GLint *length);
PFNGLSHADERSOURCEPROC glad_glShaderSource = NULL;
#define glShaderSource glad_glShaderSource

typedef void (APIENTRYP PFNGLCOMPILESHADERPROC)(GLuint shader);
PFNGLCOMPILESHADERPROC glad_glCompileShader = NULL;
#define glCompileShader glad_glCompileShader

typedef void (APIENTRYP PFNGLGETSHADERIVPROC)(GLuint shader, GLenum pname, GLint *params);
PFNGLGETSHADERIVPROC glad_glGetShaderiv = NULL;
#define glGetShaderiv glad_glGetShaderiv

typedef void (APIENTRYP PFNGLGETSHADERINFOLOGPROC)(GLuint shader, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
PFNGLGETSHADERINFOLOGPROC glad_glGetShaderInfoLog = NULL;
#define glGetShaderInfoLog glad_glGetShaderInfoLog

typedef GLuint (APIENTRYP PFNGLCREATEPROGRAMPROC)(void);
 PFNGLCREATEPROGRAMPROC glad_glCreateProgram = NULL;
#define glCreateProgram glad_glCreateProgram

typedef void (APIENTRYP PFNGLATTACHSHADERPROC)(GLuint program, GLuint shader);
PFNGLATTACHSHADERPROC glad_glAttachShader = NULL;
#define glAttachShader glad_glAttachShader

typedef void (APIENTRYP PFNGLLINKPROGRAMPROC)(GLuint program);
PFNGLLINKPROGRAMPROC glad_glLinkProgram = NULL;
#define glLinkProgram glad_glLinkProgram

typedef void (APIENTRYP PFNGLGETPROGRAMIVPROC)(GLuint program, GLenum pname, GLint *params);
 PFNGLGETPROGRAMIVPROC glad_glGetProgramiv = NULL;
#define glGetProgramiv glad_glGetProgramiv

typedef void (APIENTRYP PFNGLGETPROGRAMINFOLOGPROC)(GLuint program, GLsizei bufSize, GLsizei *length, GLchar *infoLog);
 PFNGLGETPROGRAMINFOLOGPROC glad_glGetProgramInfoLog = NULL;
#define glGetProgramInfoLog glad_glGetProgramInfoLog

typedef void (APIENTRYP PFNGLDELETESHADERPROC)(GLuint shader);
PFNGLDELETESHADERPROC glad_glDeleteShader = NULL;
#define glDeleteShader glad_glDeleteShader

typedef void (APIENTRYP PFNGLGENVERTEXARRAYSPROC)(GLsizei n, GLuint *arrays);
PFNGLGENVERTEXARRAYSPROC glad_glGenVertexArrays = NULL;
#define glGenVertexArrays glad_glGenVertexArrays

typedef void (APIENTRYP PFNGLGENBUFFERSPROC)(GLsizei n, GLuint *buffers);
PFNGLGENBUFFERSPROC glad_glGenBuffers = NULL;
#define glGenBuffers glad_glGenBuffers

typedef void (APIENTRYP PFNGLBINDVERTEXARRAYPROC)(GLuint array);
PFNGLBINDVERTEXARRAYPROC glad_glBindVertexArray;
#define glBindVertexArray glad_glBindVertexArray

typedef void (APIENTRYP PFNGLBINDBUFFERPROC)(GLenum target, GLuint buffer);
PFNGLBINDBUFFERPROC glad_glBindBuffer = NULL;
#define glBindBuffer glad_glBindBuffer

typedef void (APIENTRYP PFNGLBUFFERDATAPROC)(GLenum target, GLsizeiptr size, const void *data, GLenum usage);
PFNGLBUFFERDATAPROC glad_glBufferData = NULL;
#define glBufferData glad_glBufferData

typedef void (APIENTRYP PFNGLVERTEXATTRIBPOINTERPROC)(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void *pointer);
 PFNGLVERTEXATTRIBPOINTERPROC glad_glVertexAttribPointer = NULL;
#define glVertexAttribPointer glad_glVertexAttribPointer

typedef void (APIENTRYP PFNGLENABLEVERTEXATTRIBARRAYPROC)(GLuint index);
PFNGLENABLEVERTEXATTRIBARRAYPROC glad_glEnableVertexAttribArray = NULL;
#define glEnableVertexAttribArray glad_glEnableVertexAttribArray

typedef void (APIENTRYP PFNGLCLEARCOLORPROC)(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha);
PFNGLCLEARCOLORPROC glad_glClearColor = NULL;
#define glClearColor glad_glClearColor

typedef void (APIENTRYP PFNGLCLEARPROC)(GLbitfield mask);
PFNGLCLEARPROC glad_glClear = NULL;
#define glClear glad_glClear

typedef void (APIENTRYP PFNGLUSEPROGRAMPROC)(GLuint program);
PFNGLUSEPROGRAMPROC glad_glUseProgram = NULL;
#define glUseProgram glad_glUseProgram

typedef void (APIENTRYP PFNGLBINDVERTEXARRAYPROC)(GLuint array);
PFNGLBINDVERTEXARRAYPROC glad_glBindVertexArray = NULL;
#define glBindVertexArray glad_glBindVertexArray

typedef void (APIENTRYP PFNGLDRAWARRAYSPROC)(GLenum mode, GLint first, GLsizei count);
PFNGLDRAWARRAYSPROC glad_glDrawArrays = NULL;
#define glDrawArrays glad_glDrawArrays


void* libGL;
typedef void* (* PFNGLXGETPROCADDRESSPROC_PRIVATE)(const char*);
PFNGLXGETPROCADDRESSPROC_PRIVATE gladGetProcAddressPtr;

// 给gladGetProcAddressPtr赋值，成功返回1，失败返回0
int open_gl(void) {
    const char *NAMES[] = {"libGL.so.1", "libGL.so"};
    unsigned int index = 0;
    for(index = 0; index < (sizeof(NAMES) / sizeof(NAMES[0])); index++) {
        // 动态加载so库
        libGL = dlopen(NAMES[index], RTLD_NOW | RTLD_GLOBAL);
        if(libGL != NULL) {
            // 查找函数或者全局变量地址
            gladGetProcAddressPtr = (PFNGLXGETPROCADDRESSPROC_PRIVATE)dlsym(libGL,
                "glXGetProcAddressARB");
            return gladGetProcAddressPtr != NULL;
        }
    }
    return 0;
}

void close_gl(void) {
    if(libGL != NULL) {
        dlclose(libGL);
        libGL = NULL;
    }
}

// 根据函数名查找函数地址
void* get_proc(const char *namez) {
    void* result = NULL;
    if(libGL == NULL) return NULL;
    if(gladGetProcAddressPtr != NULL)
        result = gladGetProcAddressPtr(namez);
    if(result == NULL)
        result = dlsym(libGL, namez);
    return result;
}

// 封装函数调用，使其看起来像直接调用OpenGL函数
typedef void* (* GLADloadproc)(const char *name);
int gladLoadGLLoader(GLADloadproc load) {
    glad_glGetString = (PFNGLGETSTRINGPROC)load("glGetString");
    glad_glCreateShader = (PFNGLCREATESHADERPROC)load("glCreateShader");
    glad_glShaderSource = (PFNGLSHADERSOURCEPROC)load("glShaderSource");
    glad_glCompileShader = (PFNGLCOMPILESHADERPROC)load("glCompileShader");
    glad_glGetShaderiv = (PFNGLGETSHADERIVPROC)load("glGetShaderiv");
    glad_glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)load("glGetShaderInfoLog");
    glad_glCreateProgram = (PFNGLCREATEPROGRAMPROC)load("glCreateProgram");
    glad_glAttachShader = (PFNGLATTACHSHADERPROC)load("glAttachShader");
    glad_glLinkProgram = (PFNGLLINKPROGRAMPROC)load("glLinkProgram");
    glad_glGetProgramiv = (PFNGLGETPROGRAMIVPROC)load("glGetProgramiv");
    glad_glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)load("glGetProgramInfoLog");
    glad_glDeleteShader = (PFNGLDELETESHADERPROC)load("glDeleteShader");
    glad_glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)load("glGenVertexArrays");
    glad_glGenBuffers = (PFNGLGENBUFFERSPROC)load("glGenBuffers");
    glad_glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)load("glBindVertexArray");
    glad_glBindBuffer = (PFNGLBINDBUFFERPROC)load("glBindBuffer");
    glad_glBufferData = (PFNGLBUFFERDATAPROC)load("glBufferData");
    glad_glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)load("glVertexAttribPointer");
    glad_glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)load("glEnableVertexAttribArray");
    glad_glClearColor = (PFNGLCLEARCOLORPROC)load("glClearColor");
    glad_glClear = (PFNGLCLEARPROC)load("glClear");
    glad_glUseProgram = (PFNGLUSEPROGRAMPROC)load("glUseProgram");
    glad_glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)load("glBindVertexArray");
    glad_glDrawArrays = (PFNGLDRAWARRAYSPROC)load("glDrawArrays");
    return 0;
}

int gladLoadGL(void) {
    int status = 0;
    if(open_gl()) {
        // 初始化glad
        status = gladLoadGLLoader(&get_proc);
        close_gl();
    }
    const char *version = (const char*) glGetString(GL_VERSION);
    printf("OpenGL version: %s\n", version);
    return status;
}
// end of GLAD
////////////////////////////////////////////////////////////////////////////////////////////////






////////////////////////////////////////////////////////////////////////////////////////////////
// GLFW 创建窗口，关联 OpenGL 环境
#define WIDTH           800 
#define HEIGHT          600 
#define GLX_CONTEXT_MAJOR_VERSION_ARB 0x2091
#define GLX_CONTEXT_MINOR_VERSION_ARB 0x2092
typedef GLXContext (*glXCreateContextAttribsARBProc)(Display *, GLXFBConfig,
                                                     GLXContext, Bool,
                                                     const int *);

// Helper to check for extension string presence.  Adapted from:
//   http://www.opengl.org/resources/features/OGLextensions/
static bool isExtensionSupported(const char *extList, const char *extension) {
    const char *start;
    const char *where, *terminator;

    /* Extension names should not have spaces. */
    where = strchr(extension, ' ');
    if (where || *extension == '\0') return false;

    /* It takes a bit of care to be fool-proof about parsing the
       OpenGL extensions string. Don't be fooled by sub-strings,
       etc. */
    for (start = extList;;) {
        where = strstr(start, extension);

        if (!where) break;

        terminator = where + strlen(extension);

        if (where == start || *(where - 1) == ' ')
            if (*terminator == ' ' || *terminator == '\0') return true;

        start = terminator;
    }

    return false;
}

static bool ctxErrorOccurred = false;
static int ctxErrorHandler(Display *dpy, XErrorEvent *ev) {
    ctxErrorOccurred = true;
    return 0;
}
Display *display = NULL;
Window win = 0;
void glfwCreateWindowAndGLContext() {
    display = XOpenDisplay(NULL);

    if (!display) {
        printf("Failed to open X display\n");
        exit(1);
    }

    // Get a matching FB config
    static int visual_attribs[] = {
        GLX_X_RENDERABLE, True, GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
        GLX_RENDER_TYPE, GLX_RGBA_BIT, GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR,
        GLX_RED_SIZE, 8, GLX_GREEN_SIZE, 8, GLX_BLUE_SIZE, 8, GLX_ALPHA_SIZE, 8,
        GLX_DEPTH_SIZE, 24, GLX_STENCIL_SIZE, 8, GLX_DOUBLEBUFFER, True,
        // GLX_SAMPLE_BUFFERS  , 1,
        // GLX_SAMPLES         , 4,
        None};

    int glx_major, glx_minor;

    // FBConfigs were added in GLX version 1.3.
    if (!glXQueryVersion(display, &glx_major, &glx_minor) ||
        ((glx_major == 1) && (glx_minor < 3)) || (glx_major < 1)) {
        printf("Invalid GLX version");
        exit(1);
    }
    printf("GLX version: %d.%d\n", glx_major, glx_minor);

    printf("Getting matching framebuffer configs\n");
    int fbcount;
    GLXFBConfig *fbc = glXChooseFBConfig(display, DefaultScreen(display),
                                         visual_attribs, &fbcount);
    if (!fbc) {
        printf("Failed to retrieve a framebuffer config\n");
        exit(1);
    }
    printf("Found %d matching FB configs.\n", fbcount);

    // Pick the FB config/visual with the most samples per pixel
    printf("Getting XVisualInfos\n");
    int best_fbc = -1, worst_fbc = -1, best_num_samp = -1, worst_num_samp = 999;

    int i;
    for (i = 0; i < fbcount; ++i) {
        XVisualInfo *vi = glXGetVisualFromFBConfig(display, fbc[i]);
        if (vi) {
            int samp_buf, samples;
            glXGetFBConfigAttrib(display, fbc[i], GLX_SAMPLE_BUFFERS,
                                 &samp_buf);
            glXGetFBConfigAttrib(display, fbc[i], GLX_SAMPLES, &samples);

            printf(
                "  Matching fbconfig %d, visual ID 0x%2lx: SAMPLE_BUFFERS = %d,"
                " SAMPLES = %d\n",
                i, vi->visualid, samp_buf, samples);

            if (best_fbc < 0 || samp_buf && samples > best_num_samp)
                best_fbc = i, best_num_samp = samples;
            if (worst_fbc < 0 || !samp_buf || samples < worst_num_samp)
                worst_fbc = i, worst_num_samp = samples;
        }
        XFree(vi);
    }

    GLXFBConfig bestFbc = fbc[best_fbc];

    // Be sure to free the FBConfig list allocated by glXChooseFBConfig()
    XFree(fbc);

    // Get a visual
    XVisualInfo *vi = glXGetVisualFromFBConfig(display, bestFbc);
    printf("Chosen visual ID = 0x%lx\n", vi->visualid);

    printf("Creating colormap\n");
    XSetWindowAttributes swa;
    Colormap cmap;
    swa.colormap = cmap = XCreateColormap(
        display, RootWindow(display, vi->screen), vi->visual, AllocNone);
    swa.background_pixmap = None;
    swa.border_pixel = 0;
    swa.event_mask = StructureNotifyMask;

    printf("Creating window\n");
    win = XCreateWindow(display, RootWindow(display, vi->screen), 0, 0,
                               WIDTH, HEIGHT, 0, vi->depth, InputOutput, vi->visual,
                               CWBorderPixel | CWColormap | CWEventMask, &swa);
    if (!win) {
        printf("Failed to create window.\n");
        exit(1);
    }

    // Done with the visual info data
    XFree(vi);

    XStoreName(display, win, "LearnOpenGL");

    printf("Mapping window\n");
    XMapWindow(display, win);

    // Get the default screen's GLX extension list
    const char *glxExts =
        glXQueryExtensionsString(display, DefaultScreen(display));
    
    printf("glxExts: %s\n", glxExts);

    // NOTE: It is not necessary to create or make current to a context before
    // calling glXGetProcAddressARB
    glXCreateContextAttribsARBProc glXCreateContextAttribsARB = 0;
    glXCreateContextAttribsARB =
        (glXCreateContextAttribsARBProc)glXGetProcAddressARB(
            (const GLubyte *)"glXCreateContextAttribsARB");

    GLXContext ctx = 0;

    // Install an X error handler so the application won't exit if GL 3.0
    // context allocation fails.
    //
    // Note this error handler is global.  All display connections in all
    // threads of a process use the same error handler, so be sure to guard
    // against other threads issuing X commands while this code is running.
    ctxErrorOccurred = false;
    int (*oldHandler)(Display *, XErrorEvent *) =
        XSetErrorHandler(&ctxErrorHandler);

    // Check for the GLX_ARB_create_context extension string and the function.
    // If either is not present, use GLX 1.3 context creation method.
    if (!isExtensionSupported(glxExts, "GLX_ARB_create_context") ||
        !glXCreateContextAttribsARB) {
        printf(
            "glXCreateContextAttribsARB() not found"
            " ... using old-style GLX context\n");
        ctx = glXCreateNewContext(display, bestFbc, GLX_RGBA_TYPE, 0, True);
    }

    // If it does, try to get a GL 3.0 context!
    else {
        int context_attribs[] = {GLX_CONTEXT_MAJOR_VERSION_ARB, 3,
                                 GLX_CONTEXT_MINOR_VERSION_ARB, 3,
                                 // GLX_CONTEXT_FLAGS_ARB        ,
                                 // GLX_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB,
                                 None};

        printf("Creating context\n");
        ctx = glXCreateContextAttribsARB(display, bestFbc, 0, True,
                                         context_attribs);

        // Sync to ensure any errors generated are processed.
        XSync(display, False);
        if (!ctxErrorOccurred && ctx)
            printf("Created GL 3.3 context\n");
        else {
            // Couldn't create GL 3.0 context.  Fall back to old-style 2.x
            // context. When a context version below 3.0 is requested,
            // implementations will return the newest context version compatible
            // with OpenGL versions less than version 3.0.
            // GLX_CONTEXT_MAJOR_VERSION_ARB = 1
            context_attribs[1] = 1;
            // GLX_CONTEXT_MINOR_VERSION_ARB = 0
            context_attribs[3] = 0;

            ctxErrorOccurred = false;

            printf(
                "Failed to create GL 3.0 context"
                " ... using old-style GLX context\n");
            ctx = glXCreateContextAttribsARB(display, bestFbc, 0, True,
                                             context_attribs);
        }
    }

    // Sync to ensure any errors generated are processed.
    XSync(display, False);

    // Restore the original error handler
    XSetErrorHandler(oldHandler);

    if (ctxErrorOccurred || !ctx) {
        printf("Failed to create an OpenGL context\n");
        exit(1);
    }

    // Verifying that context is a direct context
    if (!glXIsDirect(display, ctx)) {
        printf("Indirect GLX rendering context obtained\n");
    } else {
        printf("Direct GLX rendering context obtained\n");
    }

    printf("Making context current\n");
    glXMakeCurrent(display, win, ctx);
}
// end of GLFW
////////////////////////////////////////////////////////////////////////////////////////////////

int main(int argc, char *argv[]) {
    glfwCreateWindowAndGLContext();
    gladLoadGL();
    ////////////////////////////////////////////////////////////////////////////////////////////////
    // LearnOpenGL.com  -- hello triangle
    const char *vertexShaderSource = "#version 330 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main() {\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\n";

    const char *fragmentShaderSource = "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main() {\n"
        "   FragColor = vec4(0.8f, 0.5f, 0.2f, 1.0f);\n"
        "}\n";

    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        fprintf(stderr, "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n %s \n", infoLog);
    }
    // fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        fprintf(stderr, "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n %s \n", infoLog);
    }
    // link shaders
    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        fprintf(stderr, "ERROR::SHADER::PROGRAM::LINKING_FAILED\n %s \n", infoLog);
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glUseProgram(shaderProgram);
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f, // left  
         0.5f, -0.5f, 0.0f, // right 
         0.0f,  0.5f, 0.0f  // top   
    }; 

    GLuint VBO, VAO;
    glGenVertexArrays(1, &VAO);

    // 在GPU创建缓存
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    // 设定缓存类型
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // 拷贝顶点数据到 GPU 缓存
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 告诉 GPU 如何解析传过去的内存数据
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0); 

    /* Animation loop */ 
    while (1) { 
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw our first triangle
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glXSwapBuffers(display, win);
    } 

    return 0;
}