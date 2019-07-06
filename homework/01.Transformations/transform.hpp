#ifndef KMUCS_GRAPHICS_TRANSFORM_HPP
#define KMUCS_GRAPHICS_TRANSFORM_HPP

#include <cmath>
#include "vec.hpp"
#include "mat.hpp"
#include "operator.hpp"

namespace kmuvcl
{
    namespace math
    {
#ifndef M_PI
        const float M_PI = 3.14159265358979323846f;
#endif

        template <typename T>
        mat<4, 4, T> translate(T dx, T dy, T dz)
        {
            mat<4, 4, T> translateMat;

            // TODO: Fill up this function properly 
            for(int i = 0; i < 4; i++)
                translateMat(i, i) = 1;
            
            translateMat(0, 3) = dx;
            translateMat(1, 3) = dy;
            translateMat(2, 3) = dz;

            return translateMat;
        }

        template <typename T>
        mat<4, 4, T> rotate(T angle, T x, T y, T z)
        {
            mat<4, 4, T> rotateMat;

            // TODO: Fill up this function properly 
            T radian = (M_PI/180) * angle;
            double Sin = sin(radian);
            double Cos = cos(radian);

            double mag = sqrt(x*x + y*y + z*z);
            double X = x / mag;
            double Y = y / mag;
            double Z = z / mag;

            rotateMat(0, 0) = Cos + X*X*(1 - Cos);
            rotateMat(1, 0) = Y*X*(1 - Cos) + Z*Sin;
            rotateMat(2, 0) = Z*X*(1 - Cos) - Y*Sin;

            rotateMat(0, 1) = X*Y*(1 - Cos) - Z*Sin;
            rotateMat(1, 1) = Cos + Y*Y*(1 - Cos);
            rotateMat(2, 1) = Z*Y*(1 - Cos) + X*Sin;
            
            rotateMat(0, 2) = X*Z*(1 - Cos) + Y*Sin;
            rotateMat(1, 2) = Y*Z*(1 - Cos) - X*Sin;
            rotateMat(2, 2) = Cos + Z*Z*(1 - Cos);

            rotateMat(3, 3) = 1;

            return rotateMat;
        }

        template<typename T>
        mat<4, 4, T> scale(T sx, T sy, T sz)
        {
            mat<4, 4, T> scaleMat;

            // TODO: Fill up this function properly 
            scaleMat(0, 0) = sx;
            scaleMat(1, 1) = sy;
            scaleMat(2, 2) = sz;
            scaleMat(3, 3) = 1;

            return scaleMat;
        }

        template<typename T>
        mat<4, 4, T> lookAt(T eyeX, T eyeY, T eyeZ, T centerX, T centerY, T centerZ, T upX, T upY, T upZ)
        {
            mat<4, 4, T> viewMat;

            // TODO: Fill up this function properly 
            mat<4, 4, T> A;
            mat<4, 4, T> B;

            for(int i = 0; i < 4; i++)
                B(i, i) = 1;
            B(0, 3) = -eyeX;
            B(1, 3) = -eyeY;
            B(2, 3) = -eyeZ;

            vec<3, T> cam_z_axis(centerX - eyeX, centerY - eyeY, centerZ - eyeZ);
            vec<3, T> mag(sqrt(dot(cam_z_axis, cam_z_axis)) * -1);
            for(int i = 0; i < 3; i++)
                cam_z_axis(i) /= mag(i);

            vec<3, T> up(upX, upY, upZ);
            vec<3, T> cam_x_axis(cross(up, cam_z_axis));
            mag = sqrt(dot(cam_x_axis, cam_x_axis));
            for(int i = 0; i < 3; i++)
                cam_x_axis(i) /= mag(i);

            vec<3, T> cam_y_axis(cross(cam_z_axis, cam_x_axis));
            mag = sqrt(dot(cam_y_axis, cam_y_axis));
            for(int i = 0; i < 3; i++)
                cam_y_axis(i) /= mag(i);

            for(int i = 0; i < 3; i++){
                A(0, i) = cam_x_axis(i);
                A(1, i) = cam_y_axis(i);
                A(2, i) = cam_z_axis(i);
            }
            A(3, 3) = 1;

            viewMat = A * B;

            return viewMat;
        }

        template<typename T>
        mat<4, 4, T> ortho(T left, T right, T bottom, T top, T nearVal, T farVal)
        {
            mat<4, 4, T> orthoMat;
            
            // TODO: Fill up this function properly 
            orthoMat(0, 0) = 2 / (right - left);
            orthoMat(1, 1) = 2 / (top - bottom);
            orthoMat(2, 2) = -(2 / (farVal - nearVal));
            orthoMat(3, 3) = 1;

            orthoMat(3, 0) = -((right + left)/(right - left));
            orthoMat(3, 1) = -((top + bottom)/(top - bottom));
            orthoMat(3, 2) = -((farVal + nearVal)/(farVal - nearVal));

            return orthoMat;
        }

        template<typename T>
        mat<4, 4, T> frustum(T left, T right, T bottom, T top, T nearVal, T farVal)
        {
           mat<4, 4, T> frustumMat;

           // TODO: Fill up this function properly 
           frustumMat(0, 0) = (2*nearVal) / (right - left);

           frustumMat(1, 1) = (2*nearVal) / (top - bottom);

           frustumMat(0, 2) = (right + left) / (right - left);
           frustumMat(1, 2) = (top + bottom) / (top - bottom);
           frustumMat(2, 2) = -((farVal + nearVal) / (farVal - nearVal));
           frustumMat(3, 2) = -1;

           frustumMat(2, 3) = -((2*farVal*nearVal) / (farVal - nearVal));

           return frustumMat;
        }

        template<typename T>
        mat<4, 4, T> perspective(T fovy, T aspect, T zNear, T zFar)
        {
          T  right = 0;
          T  top = 0;

          // TODO: Fill up this function properly 
          fovy = (M_PI/180)*fovy / 2;
          top = tan(fovy) * zNear;
          right = top * aspect;

          return frustum(-right, right, -top, top, zNear, zFar);
        }
    }
}
#endif
