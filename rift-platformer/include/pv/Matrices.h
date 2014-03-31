#ifndef _MATRICES_H_
#define _MATRICES_H_

#include "pv/types.h"

namespace PV
{
	namespace Math
	{
		/**
		 * A class for creating and managing matrices.  These matrices can be of any size and shape, and allow for
		 * column major and row major tracking.  They also have basic math operations that can performed with them too.
		 */
		template <class T>
		class Matrix
		{
		public:
			Matrix(unsigned int width, unsigned int height);
			/**
			* The operator overload for multiplication.
			*/
			Matrix operator*(Matrix<T> inputMatrix);
			/**
			* The operator overload for addition.
			*/
			Matrix operator+(Matrix<T> inputMatrix);
			/**
			* The operator overload for setting a matrix.
			*/
			Matrix operator=(const T* inputMatrix);
			/**
			* The operator overload for arrays.
			*/
			T& operator[](int subscript);
			T* getArray();
		protected:
			/**
			 * The actual matrix data.
			 */
			T* matrix;
			/**
			 * A boolean indicating whether the matrix is column major or not.
			 */
			bool columnMajor;
			/**
			 * The width of the matrix.
			 */
			unsigned int width;
			/**
			* The height of the matrix.
			*/
			unsigned int height;
		};
	};
};

#endif