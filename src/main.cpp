#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "JoystickReader.hpp"
#include "StickWidget.hpp"
#include "StickState.hpp"

#include "RingBuffer.hpp"
#include "BinaryLogger.hpp"

#include <atomic>
#include <thread>
#include <iostream>


constexpr size_t BUFFER_SIZE = 40;

inline void applyEventToState(const StickEvent& evt, StickState& state) {
    const float v = evt.value / 32767.0f;

    if (evt.stick == Stick::Left) {
        if (evt.axis == AxisType::X) state.lx = v;
        else                         state.ly = v;
    } else {
        if (evt.axis == AxisType::X) state.rx = v;
        else                         state.ry = v;
    }
}


int main() {
    if (!glfwInit()) {
        std::cerr << "GLFW init failed\n";
        return -1;
    }

    GLFWwindow* window =
        glfwCreateWindow(800, 400, "FPV Stick Monitor", nullptr, nullptr);

    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    //REQUIRED when using glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    StickState state;
    std::atomic<bool> running{true};

//     JoystickReader reader("/dev/input/js0", state);
    JoystickReader reader("/dev/input/js0");
    //std::thread joystickThread(&JoystickReader::run, &reader, std::ref(running));
    
    
    RingBuffer<StickEvent, BUFFER_SIZE> buffer;
    //std::atomic<bool> running{true};
    
    BinaryLogger<BUFFER_SIZE> logger("data/boxer_sticks2.bin", buffer, running);
    std::thread loggerThread(&BinaryLogger<BUFFER_SIZE>::run, &logger);

    std::cout << "Logging stick data (Ctrl+C to stop)...\n";
    
    //std::thread joystickThread;  // declare outside
    //try {
    //    JoystickReader reader("/dev/input/js0", state);
    //    std::thread joystickThread(&JoystickReader::run, &reader, std::ref(running));
    //} 
    //    catch (const std::runtime_error &e) {
    //    std::cerr << "Joystick not available: " << e.what() << "\n";
    //}



    while (!glfwWindowShouldClose(window)) {
        StickEvent evt;
        if (reader.readEvent(evt)) {
            std::cout << " evt::: " << evt.value << std::endl;
            buffer.push(evt); // drop if full
            applyEventToState(evt, state);  //GUI update
        }
        
        glfwPollEvents();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::Begin("Sticks");
        DrawStick2D("Left Stick", state.lx, state.ly);
        ImGui::SameLine();
        DrawStick2D("Right Stick", state.rx, state.ry);
        ImGui::End();

        ImGui::Render();

        int w, h;
        glfwGetFramebufferSize(window, &w, &h);
        glViewport(0, 0, w, h);

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    running = false;
    //if (joystickThread.joinable()) {
    //    joystickThread.join();
    //}

    //joystickThread.join();
    
    loggerThread.join();
        

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
