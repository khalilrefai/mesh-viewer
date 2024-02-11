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

#include "workersManager.hpp"

void WorkersManager::File
(
  igl::opengl::glfw::Viewer & viewer,
  Eigen::RowVector4f & color,
  std::map<std::string, bool> & functionFlags,
  ImGuiTreeNodeFlags & headerFlag
)
{
  if (ImGui::CollapsingHeader("File                                    ", headerFlag))
  {
    float w = ImGui::GetContentRegionAvail().x;
    float p = ImGui::GetStyle().FramePadding.x;

    if (ImGui::Button("Load##File", ImVec2((w-p)/2.f, 0)))
    {
      Eigen::MatrixXd V = viewer.data().V;
      Eigen::MatrixXi F = viewer.data().F;

      viewer.data().clear();
      
      std::string fname = viewer.open_dialog_load_mesh();

      if (fname.length() != 0)
      {
        functionFlags["boundingBox"] = false;
        functionFlags["boundingBoxApply"] = false;
        functionFlags["boundingBoxReset"] = false;
        functionFlags["curvaturesApply"] = false;
        functionFlags["curvaturesReset"] = false;
        functionFlags["exit"] = false;
        functionFlags["subdivide"] = false;

        Eigen::MatrixXd V = viewer.data().V;
        Eigen::MatrixXi F = viewer.data().F;
        plotter(viewer, V, F, color);
      }
      else
      {
        plotter(viewer, V, F, color);
      } 
    }

    ImGui::SameLine(0, p);

    if (ImGui::Button("Save##File", ImVec2((w-p)/2.f, 0)))
      viewer.open_dialog_save_mesh();
  }
}
