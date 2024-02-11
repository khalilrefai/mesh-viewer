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
    void Subdivide
    (
        Eigen::MatrixXd & V,
        Eigen::MatrixXi & F,
        int & methodIdx,
        int & subdivisions
    )
    {
        if (methodIdx == 0)
        {
            igl::upsample(Eigen::MatrixXd(V), Eigen::MatrixXi(F), V, F, subdivisions);
        }
        else if (methodIdx == 1)
        {
            igl::loop(Eigen::MatrixXd(V), Eigen::MatrixXi(F), V, F, subdivisions);
        }
        else
        {
            while(subdivisions > 0)
            {
                igl::false_barycentric_subdivision(Eigen::MatrixXd(V), Eigen::MatrixXi(F), V, F);
                subdivisions--;
            }
        }
    }
}
