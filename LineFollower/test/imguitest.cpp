#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_glfw.h>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

// Include your specific classes here
#include "MockDCMotor.h"
#include "MockEncoder.h"
#include "MecanumDriveOdometry.h"
#include "PIDController.h"
#include "MecanumDrive.h"

int main()
{
    // Set up your objects here
    MockDCMotor motorFL, motorFR, motorBL, motorBR;
    MockEncoder encoderFL, encoderFR, encoderBL, encoderBR;
    MecanumDriveOdometry odometry(&encoderFL, &encoderFR, &encoderBL, &encoderBR);
    PIDController controller;
    MecanumDrive drive(&motorFL, &motorFR, &motorBL, &motorBR);

    // Setup ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    // Setup Platform/Renderer bindings
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(1280, 720, "ImGui Window", NULL, NULL);
    glfwMakeContextCurrent(window);
    gl3wInit();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // Define colors
    ImGui::StyleColorsDark();

    // Variables for GUI
    float setpoints[3] = {0, 0, 0};
    bool driveByKeyboard = false;

    while (!glfwWindowShouldClose(window))
    {
        // Update your objects here

        // Start ImGui frame
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Main ImGui window
        ImGui::Begin("Robot Controller");

        // Display controls
        ImGui::InputFloat3("Setpoints", setpoints);
        ImGui::Checkbox("Drive by Keyboard", &driveByKeyboard);

        // Update robot based on controls
        if (driveByKeyboard)
        {
            // TODO: Update drive speeds based on keyboard input
        }
        else
        {
            // TODO: Update drive speeds based on setpoints
        }

        // TODO: Display robot state

        ImGui::End();

        // Rendering
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}