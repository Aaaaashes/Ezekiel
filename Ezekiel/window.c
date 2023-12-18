#include "window.h"

Window window; // global window

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

static void _cursorCallback(GLFWwindow* handle, double xp, double yp) {
    vec2 p = { xp, yp };

    glm_vec2_sub(p, window.mouse.position, window.mouse.delta);
    window.mouse.delta[0] = clamp(-100.0f, 100.0f, window.mouse.delta[0]);
    window.mouse.delta[1] = clamp(-100.0f, 100.0f, window.mouse.delta[1]);
    //print_vec(window.mouse.position)
    glm_vec2_copy(p, window.mouse.position);
}

static void _resizeCallback() {
    int width, height;
    glfwGetFramebufferSize(window.handle, &width, &height);
    glViewport(0, 0, width, height);
    window.scrWidth = width;
    window.scrHeight = height;
}


void createWindow(callback_t init, callback_t destroy, callback_t tick, callback_t update, callback_t render) {
    window.init = init;
    window.destroy = destroy;
    window.tick = tick;
    window.update = update;
    window.render = render;

    window.lastFrame = NOW();
    window.lastSecond = NOW();

    window.scrHeight = 1080;
    window.scrWidth = 1920;

    assertErr(glfwInit(), "Failed to init glfw.", 0, true);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    glfwSetErrorCallback(_errorCallback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

    window.handle = glfwCreateWindow(window.scrWidth, window.scrHeight, "3D Engine", NULL, NULL);
    assertErr(window.handle, "Failed to create window.", glfwTerminate, true);

    glfwSetKeyCallback(window.handle, _keyCallback);
    glfwSetMouseButtonCallback(window.handle, _mouseCallback);
    glfwSetCursorPosCallback(window.handle, _cursorCallback);

    glfwSetInputMode(window.handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetFramebufferSizeCallback(window.handle, _resizeCallback);

    glfwMakeContextCurrent(window.handle);
    glfwSwapInterval(1);

    assertErr(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to initialise OpenGL context.", glfwTerminate, true);

    windowLoop();
}

void _init() {
    window.init();
}

void _destroy() {
    window.destroy();
    glfwTerminate();
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

void _render() {
    window.frameCount++;
    window.render();
}

void windowLoop() {
    _init();

    while (!glfwWindowShouldClose(window.handle))
    {
        const u64 now = NOW();

        window.dFrame = now - window.lastFrame;
        window.lastFrame = now;

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if (now - window.lastSecond > NSPS) {
            window.fps = window.frameCount;
            window.tps = window.tickCount;
            window.frameCount = 0;
            window.tickCount = 0;
            window.lastSecond = now;

            printf("FPS: %I64d | TPS: %I64d\n", window.fps, window.tps);
        }

        // process ticks
        const u64 NSPTICK = (NSPS / TICKSPS);
        u64 tickTime = window.dFrame + window.tickRemainder;
        while (tickTime > NSPTICK) {
            _tick();
            tickTime -= NSPTICK;
        }
        window.tickRemainder = max(tickTime, 0);

        _update();
        _render();

        glfwSwapBuffers(window.handle);
        glfwPollEvents();
    }

    _destroy();
    exit(0);
}
