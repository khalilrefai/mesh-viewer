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

void WorkersManager::Processing
(
  igl::opengl::glfw::Viewer & Viewer,
  std::vector<Eigen::MatrixXd> & VList,
  std::vector<Eigen::MatrixXi> & FList,
  Eigen::RowVector4f & color,
  std::map<std::string, bool> & functionFlags,
  ImGuiTreeNodeFlags & headerFlag
)
{
    if (ImGui::CollapsingHeader("Processing", headerFlag))
    {
      // Surface subdivision
      ImGui::BulletText("Surface subdivision");
      {
        static int subdivisions = 1;
        static std::vector<std::string> subdivisionMethods = {"Barycentric", "Loop", "Butterfly"};
        static int subdivisionMethodIdx = 0;
        ImGui::Combo("Methods##Subdivision", &subdivisionMethodIdx, subdivisionMethods);
            
        if (ImGui::InputInt("Subdivisions##Subdivision", &subdivisions))
        {
          subdivisions = std::max(1, std::min(10, subdivisions));
        }

        float w = ImGui::GetContentRegionAvail().x;
        float p = ImGui::GetStyle().FramePadding.x;

        Eigen::MatrixXd V = Viewer.data().V;
        Eigen::MatrixXi F = Viewer.data().F;
        if (V.rows() != 0)
        {
          if (ImGui::Button("Apply##SurfaceSubdivision", ImVec2((w-p)/2.f, 0)))
          {
            if (VList.size() == 0)
            {
              VList.push_back(V);
              FList.push_back(F);
            }
            
            FunctionsManager::Subdivide(V, F, subdivisionMethodIdx, subdivisions);
            VList.push_back(V);
            FList.push_back(F);
            functionFlags["subdivide"] = true;
          }

          ImGui::SameLine(0, p);
          if (ImGui::Button("Reset##SurfaceSubdivision", ImVec2((w-p)/2.f, 0)))
          {
            if (VList.size() > 1)
            {
              VList.pop_back();
              FList.pop_back();
            }

            V = VList.back();
            F = FList.back();
            functionFlags["subdivide"] = true;
          }

          if (functionFlags["subdivide"])
          {
            Viewer.data().clear();
            plotter(Viewer, V, F, color);
            functionFlags["subdivide"] = false;
          }
        }
        else
        {
          if (ImGui::Button("Apply##SurfaceSubdivision", ImVec2((w-p)/2.f, 0))) {}
          ImGui::SameLine(0, p);
          if (ImGui::Button("Reset##SurfaceSubdivision", ImVec2((w-p)/2.f, 0))) {}
        }
      }
      ImGui::Separator();

      // Curvatures
      ImGui::BulletText("Curvatures");
      {
        static std::vector<std::string> curvaturesMethods = {"Gaussian", "Principal"};
        static int curvaturesMethodIdx = 0;
        ImGui::Combo("Methods##Curvatures", &curvaturesMethodIdx, curvaturesMethods);

        float w = ImGui::GetContentRegionAvail().x;
        float p = ImGui::GetStyle().FramePadding.x;

        Eigen::MatrixXd V = Viewer.data().V;
        Eigen::MatrixXi F = Viewer.data().F;
        if (V.rows() != 0)
        {
          Eigen::VectorXd K, H;
          Eigen::MatrixXd PD1, PD2;
          if (ImGui::Button("Apply##Curvatures", ImVec2((w-p)/2.f, 0)))
          {
            if (curvaturesMethodIdx == 0)
            {
              FunctionsManager::GaussianCurvatures(V, F, K);
            }
            else
            {
              FunctionsManager::PrincipalCurvatures(V, F, H, PD1, PD2);              
            } 

            functionFlags["curvaturesApply"] = true;
          }

          ImGui::SameLine(0, p);
          if (ImGui::Button("Reset##Curvatures", ImVec2((w-p)/2.f, 0)))
            functionFlags["curvaturesReset"] = true;

          if (functionFlags["curvaturesApply"])
          {
            if (curvaturesMethodIdx == 0)
            {
              Viewer.data().clear();
              Viewer.data().set_mesh(V, F);
              if (K.rows() != 0)
                Viewer.data().set_data(K);
            }
            else
            {
              const double avg = igl::avg_edge_length(V, F);
              const Eigen::RowVector3d red(0.8, 0.2, 0.2), blue(0.2, 0.2, 0.8);
              Viewer.data().clear();
              Viewer.data().set_mesh(V, F);
              if (H.rows() != 0 && PD1.rows() != 0 && PD2.rows() != 0)
              {
                Viewer.data().set_data(H);
                Viewer.data().add_edges(V + PD1 * avg, V - PD1 * avg, red);
                Viewer.data().add_edges(V + PD2 * avg, V - PD2 * avg, blue);
              }
            } 

            functionFlags["curvaturesApply"] = false;
          }

          if (functionFlags["curvaturesReset"])
          {
            Viewer.data().clear();
            plotter(Viewer, V, F, color);
            functionFlags["curvaturesReset"] = false;
          }
        }
        else
        {
          if (ImGui::Button("Apply##Curvatures", ImVec2((w-p)/2.f, 0))) {}
          ImGui::SameLine(0, p);
          if (ImGui::Button("Reset##Curvatures", ImVec2((w-p)/2.f, 0))) {}
        }
      }
      ImGui::Separator();
    }
}
