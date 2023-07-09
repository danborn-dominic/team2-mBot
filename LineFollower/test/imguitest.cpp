#include <imgui.h>
#include "../lib/imgui/bindings/imgui_impl_opengl3.h"
#include "../lib/imgui/bindings/imgui_impl_glfw.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// Include your specific classes here
#include "../src/mock/MockDCMotor.h"
#include "../src/mock/MockEncoder.h"
#include "../src/mock/MockMecanumDrive.h"
#include "../src/PositionController.h"
#include "../src/MecanumDriveOdometry.h"

void drawGrid(ImDrawList* draw_list, ImVec2 win_pos, float gridSize, int numSquares) {
    for (int i = 0; i <= numSquares; i++) {
        draw_list->AddLine(ImVec2(win_pos.x + i*gridSize, win_pos.y),
                           ImVec2(win_pos.x + i*gridSize, win_pos.y + numSquares*gridSize),
                           ImColor(ImVec4(1.0f, 1.0f, 1.0f, 0.3f)));
        draw_list->AddLine(ImVec2(win_pos.x, win_pos.y + i*gridSize),
                           ImVec2(win_pos.x + numSquares*gridSize, win_pos.y + i*gridSize),
                           ImColor(ImVec4(1.0f, 1.0f, 1.0f, 0.3f)));
    }
}

int main() {
    double wheelRaidus = 2.3622, wheelBase = 4.75, trackWidth = 5.25;
    // Set up your objects here
    MockDCMotor motorFL, motorFR, motorBL, motorBR;
    MockEncoder encoderFL(motorFL), encoderFR(motorFR), encoderBL(motorBL), encoderBR(motorBR);
    MockMecanumDrive drive(motorFL, motorFR, motorBL, motorBR);
    MecanumDriveOdometry odometry(wheelRaidus, wheelBase, trackWidth);
    PositionController controller(1, 0, 0);

    // Setup window
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    GLFWwindow* window = glfwCreateWindow(1280, 720, "Robot Drive!", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // Define colors
    ImGui::StyleColorsDark();

    // Variables for GUI
    float setpoints[3] = {0, 0, 0};
    bool driveByKeyboard = false;
    ImVec2 robotPos = ImVec2(0.0f, 0.0f); // Robot's position

    while (!glfwWindowShouldClose(window))
    {
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

        ImVec2 win_pos = ImGui::GetCursorScreenPos();
        float gridSize = 50.0f; // Change to the size you want each grid square to be
        int numSquares = 10; // Change to the number of squares in the grid

        /// Drawing grid
        ImDrawList* draw_list = ImGui::GetWindowDrawList();
        drawGrid(draw_list, win_pos, gridSize, numSquares);
        draw_list->AddRectFilled(ImVec2(win_pos.x + robotPos.x*gridSize, win_pos.y + robotPos.y*gridSize), ImVec2(win_pos.x + robotPos.x*gridSize + gridSize, win_pos.y + robotPos.y*gridSize + gridSize), IM_COL32(255, 0, 0, 255));
        ImGui::Text("Use WASD to move the robot");
        ImGui::End();

        // TODO: Update drive speeds based on keyboard input
        if (driveByKeyboard) {
            if (io.KeysDown[GLFW_KEY_UP]) robotPos.y -= 0.2f;
            if (io.KeysDown[GLFW_KEY_DOWN]) robotPos.y += 0.2f;
            if (io.KeysDown[GLFW_KEY_LEFT]) robotPos.x -= 0.2f;
            if (io.KeysDown[GLFW_KEY_RIGHT]) robotPos.x += 0.2f;
        }

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