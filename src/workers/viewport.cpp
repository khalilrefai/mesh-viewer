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

void WorkersManager::Viewport
(
  igl::opengl::glfw::Viewer & viewer,
  Eigen::RowVector4f & color,
  std::map<std::string, bool> & functionFlags,
  ImGuiTreeNodeFlags & headerFlag
)
{
    // Helper for setting viewport specific mesh options
    auto make_checkbox = [&](const char *label, unsigned int &option)
    {
      return ImGui::Checkbox(label,
        [&]() { return viewer.core().is_set(option); },
        [&](bool value) { return viewer.core().set(option, value); }
      );
    };

    if (ImGui::CollapsingHeader("Viewport", headerFlag))
    {
      // Colouring
      ImGui::ColorEdit4
      (
        "Background color",
        viewer.core().background_color.data(), 
        ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel
      );
      
      if (
        ImGui::ColorEdit4
        (
          "Mesh color", color.data(),
          ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_AlphaBar
        )
      )
      {
        viewer.data().set_colors(color.cast<double>());
      }

      ImGui::ColorEdit4
      (
        "Line color",
        viewer.data().line_color.data(),
        ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_PickerHueWheel
      );

      // Fill
      make_checkbox("Fill", viewer.data().show_faces);

      // Wireframe
      make_checkbox("Wireframe", viewer.data().show_lines);

      // Bounding Box
      if (ImGui::Checkbox("Bounding Box", & functionFlags["boundingBox"]))
      {
        Eigen::MatrixXd V = viewer.data().V;
        Eigen::MatrixXi F = viewer.data().F;
        if (V.rows() != 0)
        {
          if (functionFlags["boundingBox"] == true)
          {
            functionFlags["boundingBoxApply"] = true;
          }
          else
          {
            functionFlags["boundingBoxReset"] = true;
          }

          if (functionFlags["boundingBoxApply"])
          {
            Eigen::MatrixXd Vbox;
            Eigen::MatrixXi Ebox;
            std::tie(Vbox, Ebox) = FunctionsManager::BoundingBox(V);
            
            plotter(viewer, V, F, color);
            
            viewer.data().add_points(Vbox, Eigen::RowVector3d(1, 0, 0));

            for (int i = 0; i < Ebox.rows(); i++)
            {
              viewer.data().add_edges
              (
                Vbox.row(Ebox(i, 0)),
                Vbox.row(Ebox(i, 1)),
                Eigen::RowVector3d(1, 0, 0)
              );
            }

            functionFlags["boundingBoxApply"] = false;
          }

          if (functionFlags["boundingBoxReset"])
          {
            viewer.data().clear_points();
            viewer.data().clear_edges();

            plotter(viewer, V, F, color);

            functionFlags["boundingBoxReset"] = false;
          }
        }   
      }
    }
}
