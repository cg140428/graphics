#ifndef KMUVCL_GRAPHICS_MAT_HPP
#define KMUVCL_GRAPHICS_MAT_HPP

#include <iostream>
#include <cstring>
#include <cstdarg>

namespace kmuvcl {
  namespace math {

    template <unsigned int M, unsigned int N, typename T>
    class mat
    {
    public:
      mat()
      {
        set_to_zero();
      }

      mat(const T elem)
      {
        std::fill(val, val + M*N, elem);
      }

      T& operator()(unsigned int r, unsigned int c)
      {
        // TODO: Fill up this function properly 
        // Notice: The matrix is column major
        return  val[r + c*M];
      }

      const T& operator()(unsigned int r, unsigned int c) const
      {
        // TODO: Fill up this function properly 
        // Notice: The matrix is column major
        return  val[r + c*M];   
      }

      // type casting operators
      operator const T* () const
      {
        return  val;
      }

      operator T* ()
      {
        return  val;
      }

      void set_to_zero()
      {
        // TODO: Fill up this function properly 
        std::fill(val, val + M*N, 0);
      }

      void get_ith_column(unsigned int i, vec<M, T>& col) const
      {
        // TODO: Fill up this function properly 
        for(unsigned int idx = 0; idx < M; ++idx)
          col(idx) = (*this)(idx, i);
      }

      void set_ith_column(unsigned int i, const vec<M, T>& col)
      {
        // TODO: Fill up this function properly 
        for(unsigned int idx = 0; idx < M; ++idx)
          (*this)(idx, i) = col(idx);
      }

      void get_ith_row(unsigned int i, vec<N, T>& row) const
      {
       // TODO: Fill up this function properly 
        for(unsigned int idx = 0; idx < N; ++idx)
          row(idx) = (*this)(i, idx);
      }

      void set_ith_row(unsigned int i, const vec<N, T>& row)
      {
        // TODO: Fill up this function properly 
        for(unsigned int idx = 0; idx < N; ++idx)
          (*this)(i, idx) = row(idx);
      }

      mat<N, M, T> transpose() const
      {
        // TODO: Fill up this function properly 
        mat<N, M, T>  trans;
        for(unsigned int i = 0; i < N; ++i){
          for(unsigned int j = 0; j < M; ++j){
            trans(i, j) = (*this)(j, i);
          }
        }
        
        return  trans;
      }

    protected:
      T val[M*N];   // column major
    };

    typedef mat<3, 3, float>    mat3x3f;
    typedef mat<3, 3, double>   mat3x3d;

    typedef mat<4, 4, float>    mat4x4f;
    typedef mat<4, 4, double>   mat4x4d;

  } // math
} // kmuvcl

#include "operator.hpp"

#endif // #ifndef KMUVCL_GRAPHICS_MAT_HPP
