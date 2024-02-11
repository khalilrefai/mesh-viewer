/*
 * MIT License
 *
 * Copyright (c) 2024 Khalil REFAI <khalil.refai.pro@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include "workers/workersManager.hpp"

int main(int argc, char *argv[])
{
  /* Initialization */
  igl::opengl::glfw::Viewer viewer;

  igl::opengl::glfw::imgui::ImGuiPlugin plugin;
  viewer.plugins.push_back(&plugin);

  igl::opengl::glfw::imgui::ImGuiMenu menu;
  plugin.widgets.push_back(&menu);

  Eigen::RowVector4f color(igl::GOLD_DIFFUSE[0], igl::GOLD_DIFFUSE[1], igl::GOLD_DIFFUSE[2], 1);

  Eigen::MatrixXd V = viewer.data().V;
  Eigen::MatrixXi F = viewer.data().F;

  std::vector<Eigen::MatrixXd> VList;
  std::vector<Eigen::MatrixXi> FList;

  auto headerFlags = std::map<std::string, ImGuiTreeNodeFlags>
  {
    {"file", ImGuiTreeNodeFlags_DefaultOpen},
    {"processing", ImGuiTreeNodeFlags_OpenOnArrow},
    {"viewport", ImGuiTreeNodeFlags_DefaultOpen},
    {"workspace", ImGuiTreeNodeFlags_OpenOnArrow}
  };

  auto functionFlags = std::map<std::string, bool>
  {
    {"boundingBox", false},
    {"boundingBoxApply", false},
    {"boundingBoxReset", false},
    {"curvaturesApply", false},
    {"curvaturesReset", false},
    {"exit", false},
    {"subdivide", false}
  };

  /* Menu window */ 
  menu.callback_draw_viewer_menu = [&]()
  {
    // Workspace
    WorkersManager::Workspace
    (
      viewer,
      headerFlags["workspace"]
    );
    
    // File
    WorkersManager::File
    (
      viewer,
      color,
      functionFlags,
      headerFlags["file"]
    );

    // Viewport
    WorkersManager::Viewport
    (
      viewer,
      color,
      functionFlags,
      headerFlags["viewport"]
    );

    // Processing
    WorkersManager::Processing
    (
      viewer,
      VList,
      FList,
      color,
      functionFlags,
      headerFlags["processing"]
    );

    // Snapshot
    WorkersManager::Snapshot
    (
      viewer
    );

    // Exit
    WorkersManager::Exit
    (
      viewer
    );
  };

  // Plot
  WorkersManager::plotter
  (
    viewer,
    V,
    F,
    color
  );
  
  viewer.launch();
}
