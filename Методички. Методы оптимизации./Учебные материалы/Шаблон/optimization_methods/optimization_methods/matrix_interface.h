/*!
* \copyright (C) 2014 Puzikova V.V.
* \file      matrix_interface.h
* \author    Puzikova Valeria (vvp) 
* \date      22.08.2014 0:13:38
* \brief     matrix_interface.h
* \fmtstyle  3S
*/

#ifndef _OPTIMIZATION_METHODS_MATRIX_INTERFACE_H_
#define _OPTIMIZATION_METHODS_MATRIX_INTERFACE_H_

// ================================================================== INCLUDES
#include "math.h"
// ================================================================== SYNOPSIS
// ===========================================================================

namespace OPT_METH
{
	struct MatrixInterface
	{
		enum matrixType
		{
			UnknownMatrixType = -1,
			Sym2D,
			SymND
		};
		explicit MatrixInterface(matrixType _id = UnknownMatrixType, int _size = sizeof(MatrixInterface)):
		id(_id),
		size(_size)
		{
			;
		}
		virtual double det(){ return 0.0; };
		virtual bool isPositivelyDefinite(){ return false; };
		virtual void solve(double* rightMember, double* solution){};
		virtual void supplementToPositiveDefinite(){};
		matrixType id;
		int size;
	};
}

#endif //_OPTIMIZATION_METHODS_MATRIX_INTERFACE_H_
