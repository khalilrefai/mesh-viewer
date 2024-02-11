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
    std::tuple<Eigen::MatrixXd, Eigen::MatrixXi> BoundingBox
    (
        Eigen::MatrixXd & V
    )
    {
        Eigen::Vector3d m = V.colwise().minCoeff();
        Eigen::Vector3d M = V.colwise().maxCoeff();

        // Corners of the bounding box
        Eigen::MatrixXd Vbox(8,3);
        Vbox <<
        m(0), m(1), m(2),
        M(0), m(1), m(2),
        M(0), M(1), m(2),
        m(0), M(1), m(2),
        m(0), m(1), M(2),
        M(0), m(1), M(2),
        M(0), M(1), M(2),
        m(0), M(1), M(2);

        // Edges of the bounding box
        Eigen::MatrixXi Ebox(12,2);
        Ebox <<
        0, 1,
        1, 2,
        2, 3,
        3, 0,
        4, 5,
        5, 6,
        6, 7,
        7, 4,
        0, 4,
        1, 5,
        2, 6,
        7 ,3;

        return std::make_tuple(Vbox, Ebox);
    }
}
