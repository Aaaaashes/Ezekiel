#include "window.h"

Window window; // global window

u32 scrWidth = 800;
u32 scrHeight = 600;

void _errorCallback(int error, const char* description) {
    fatalError("GLFW Error: %s\n", description);
}

void _keyCallback(GLFWwindow* handle, int key, int scancode, int action, int mods) {
    if (key < 0) {
        return;
    }

    switch (action) {
    case GLFW_PRESS:
        window.keyboard.keys[key].down = true;
        break;
    case GLFW_RELEASE:
        window.keyboard.keys[key].down = false;
        break;
    default:
        break;
    }
}

static void _mouseCallback(GLFWwindow* handle, int button, int action, int mods) {
    if (button < 0) {
        return;
    }

    switch (action) {
    case GLFW_PRESS:
        window.mouse.buttons[button].down = true;
        break;
    case GLFW_RELEASE:
        window.mouse.buttons[button].down = false;
        break;
    default:
        break;
    }
}

static void _resizeCallback() {
    int width, height;
    glfwGetFramebufferSize(window.handle, &width, &height);
    glViewport(0, 0, width, height);
    scrWidth = width;
    scrHeight = height;
}


void createWindow(callback_t init, callback_t destroy, callback_t tick, callback_t update, callback_t render) {
    window.init = init;
    window.destroy = destroy;
    window.tick = tick;
    window.update = update;
    window.render = render;



    assertErr(glfwInit(), "Failed to init glfw.", 0);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    glfwSetErrorCallback(_errorCallback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    window.handle = glfwCreateWindow(scrWidth, scrHeight, "3D Engine", NULL, NULL);
    assertErr(window.handle, "Failed to create window.", glfwTerminate);

    glfwSetKeyCallback(window.handle, _keyCallback);
    glfwSetMouseButtonCallback(window.handle, _mouseCallback);

    glfwSetFramebufferSizeCallback(window.handle, _resizeCallback);

    glfwMakeContextCurrent(window.handle);
    glfwSwapInterval(1);

    assertErr(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to initialise OpenGL context.", glfwTerminate);

    initRenderer();

    windowLoop();

    glfwDestroyWindow(window.handle);
    glfwTerminate();
}

void windowLoop() {
    while (!glfwWindowShouldClose(window.handle))
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        _render();
        glfwSwapBuffers(window.handle);
        glfwPollEvents();
        showFPS();
    }
}

void showFPS()
{
    // Measure speed
    window.currentTime = (f64)glfwGetTime();
    f64 delta = window.currentTime - window.lastTime;
    window.frameCount++;
    if (delta >= 1.0) { // If last cout was more than 1 sec ago
        f64 fps = (f64)window.frameCount / delta;

        printf("FPS: %f\n", fps);

        window.frameCount = 0;
        window.lastTime = window.currentTime;
    }
}

void _init() {
    window.init();
}

void _destroy() {
    window.destroy();
}

void _update() {
    buttonArrayUpdate(GLFW_MOUSE_BUTTON_LAST, window.mouse.buttons);
    buttonArrayUpdate(GLFW_KEY_LAST, window.keyboard.keys);
    window.update();

    // reset update delta
    glm_vec2_zero(window.mouse.delta);
}

void _tick() {
    window.tickCount++;
    buttonArrayTick(GLFW_MOUSE_BUTTON_LAST, window.mouse.buttons);
    buttonArrayTick(GLFW_KEY_LAST, window.keyboard.keys);
    window.tick();
}

void update

