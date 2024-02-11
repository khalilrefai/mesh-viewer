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

#include "functionsManager.hpp"

namespace FunctionsManager
{
    void GaussianCurvatures
    (
        Eigen::MatrixXd & V,
        Eigen::MatrixXi & F,
        Eigen::VectorXd & K
    )
    {
        // Compute integral of Gaussian curvature
        igl::gaussian_curvature(V, F, K);
        
        // Compute mass matrix
        Eigen::SparseMatrix<double> M, Minv;
        igl::massmatrix(V, F, igl::MASSMATRIX_TYPE_DEFAULT, M);
        igl::invert_diag(M, Minv);
        
        // Divide by area to get integral average
        K = (Minv * K).eval();
    }

    void PrincipalCurvatures
    (
        Eigen::MatrixXd & V,
        Eigen::MatrixXi & F,
        Eigen::VectorXd & H,
        Eigen::MatrixXd & PD1,
        Eigen::MatrixXd & PD2
    )
    {
        // Alternative discrete mean curvature
        Eigen::MatrixXd HN;
        Eigen::SparseMatrix<double> L, M, Minv;
        igl::cotmatrix(V, F, L);
        igl::massmatrix(V, F, igl::MASSMATRIX_TYPE_VORONOI, M);
        igl::invert_diag(M, Minv);
        
        // Laplace-Beltrami of position
        HN = -Minv * (L * V);
        
        // Extract magnitude as mean curvature
        H = HN.rowwise().norm();

        // Compute curvature directions via quadric fitting
        Eigen::VectorXd PV1, PV2;
        igl::principal_curvature(V, F, PD1, PD2, PV1, PV2);

        // mean curvature
        H = 0.5 * (PV1 + PV2);
    }
}
