#include "imgui_manager.h"

#include "imgui.h"
#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

ImGuiManager::ImGuiManager(Window& window) : window_(window) {
  // Setup Dear ImGui context
  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO& io = ImGui::GetIO();
  (void)io;
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;  // Enable Docking
  // Enable ImGui ini file saving/loading
  io.IniFilename = "imgui.ini";
  // Setup Dear ImGui style
  ImGui::StyleColorsDark();
  // Setup Platform/Renderer bindings
  ImGui_ImplGlfw_InitForOpenGL(window_.GetWindowPTR(), true);
  ImGui_ImplOpenGL3_Init("#version 130");
}

ImGuiManager::~ImGuiManager() {
  // Cleanup
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplGlfw_Shutdown();
  ImGui::DestroyContext();
}

void ImGuiManager::BeginFrame() {
  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplGlfw_NewFrame();
  ImGui::NewFrame();

  // Docking space
  ImGuiViewport* viewport = ImGui::GetMainViewport();

   // Offset to avoid menu bar
  ImGui::SetNextWindowPos(ImVec2(viewport->Pos.x, viewport->Pos.y + 20)); 
  // Adjust size
  ImGui::SetNextWindowSize(ImVec2(viewport->Size.x, viewport->Size.y - 20));
  ImGui::SetNextWindowViewport(viewport->ID);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
  ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
  ImGui::Begin("DockSpace Demo", nullptr, 
               ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | 
               ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | 
               ImGuiWindowFlags_NoBringToFrontOnFocus | 
               ImGuiWindowFlags_NoNavFocus);
  ImGui::PopStyleVar(3);

  ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
  ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f));
}

void ImGuiManager::EndFrame() {
  ImGui::End();
  ImGui::Render();
  // Update and Render additional Platform Windows
  ImGui::UpdatePlatformWindows();
  ImGui::RenderPlatformWindowsDefault();
  glfwMakeContextCurrent(window_.GetWindowPTR());
  int display_w, display_h;
  glfwGetFramebufferSize(window_.GetWindowPTR(), &display_w, &display_h);
  glViewport(0, 0, display_w, display_h);
  glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
  glClear(GL_COLOR_BUFFER_BIT);
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
