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

#pragma once

#include <iostream>
#include <chrono>
#include <thread>
#include <time.h>

#include <igl/avg_edge_length.h>
#include <igl/file_dialog_save.h>
#include <igl/material_colors.h>
#include <igl/png/writePNG.h>

#include "../viewer/glfw/Viewer.h"
#include "../viewer/glfw/imgui/ImGuiPlugin.h"
#include "../viewer/glfw/imgui/ImGuiMenu.h"
#include "../viewer/glfw/imgui/ImGuiHelpers.h"
#include "../viewer/glfw/imgui/ImGuizmoWidget.h"

#include "../functions/functionsManager.hpp"

namespace WorkersManager
{
  void Exit
  (
    igl::opengl::glfw::Viewer & viewer
  );

  void File
  (
    igl::opengl::glfw::Viewer & viewer,
    Eigen::RowVector4f & color,
    std::map<std::string, bool> & functionFlags,
    ImGuiTreeNodeFlags & headerFlag
  );

  void plotter
  (
    igl::opengl::glfw::Viewer & viewer,
    Eigen::MatrixXd & V,
    Eigen::MatrixXi & F,
    Eigen::RowVector4f & color
  );

  void Processing
  (
    igl::opengl::glfw::Viewer & Viewer,
    std::vector<Eigen::MatrixXd> & VList,
    std::vector<Eigen::MatrixXi> & FList,
    Eigen::RowVector4f & color,
    std::map<std::string, bool> & functionFlags,
    ImGuiTreeNodeFlags & headerFlag
  );

  void Snapshot
  (
    igl::opengl::glfw::Viewer & viewer
  );

  void Viewport
  (
    igl::opengl::glfw::Viewer & viewer,
    Eigen::RowVector4f & color,
    std::map<std::string, bool> & functionFlags,
    ImGuiTreeNodeFlags & headerFlag
  );

  void Workspace
  (
    igl::opengl::glfw::Viewer & viewer,
    ImGuiTreeNodeFlags & headerFlag
  );
}
