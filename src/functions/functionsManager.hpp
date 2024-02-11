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
#include <limits.h>

#include <Eigen/Core>

#include <igl/avg_edge_length.h>
#include <igl/barycenter.h>
#include <igl/boundary_loop.h>
#include <igl/centroid.h>
#include <igl/circumradius.h>
#include <igl/facet_components.h>
#include <igl/fast_winding_number.h>
#include <igl/find.h>
#include <igl/is_edge_manifold.h>
#include <igl/is_vertex_manifold.h>
#include <igl/per_face_normals.h>
#include <igl/per_vertex_normals.h>
#include <igl/slice_mask.h>
#include <igl/volume.h>
#include <igl/unique_simplices.h>

#include <igl/upsample.h>
#include <igl/loop.h>
#include <igl/false_barycentric_subdivision.h>

#include <igl/gaussian_curvature.h>
#include <igl/massmatrix.h>
#include <igl/invert_diag.h>
#include <igl/cotmatrix.h>
#include <igl/principal_curvature.h>

namespace FunctionsManager
{
  std::tuple<Eigen::MatrixXd, Eigen::MatrixXi> BoundingBox
  (
    Eigen::MatrixXd & V
  );

  void GaussianCurvatures
  (
    Eigen::MatrixXd & V,
    Eigen::MatrixXi & F,
    Eigen::VectorXd & K
  );

  void PrincipalCurvatures
  (
    Eigen::MatrixXd & V,
    Eigen::MatrixXi & F,
    Eigen::VectorXd & H,
    Eigen::MatrixXd & PD1,
    Eigen::MatrixXd & PD2
  );
  
  void Subdivide
  (
    Eigen::MatrixXd & V,
    Eigen::MatrixXi & F,
    int & methodIdx,
    int & subdivisions
  );
}
