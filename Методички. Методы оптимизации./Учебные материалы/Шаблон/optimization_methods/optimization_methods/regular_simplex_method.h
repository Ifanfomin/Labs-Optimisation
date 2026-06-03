/*!
* \copyright (C) 2014 Puzikova V.V.
* \file      regular_simplex_method.h
* \author    Puzikova Valeria (vvp) 
* \date      25.08.2014 2:01:42
* \brief     regular_simplex_method.h
* \fmtstyle  3S
*/

#ifndef _OPTIMIZATION_METHODS_REGULAR_SIMPLEX_METHOD_H_
#define _OPTIMIZATION_METHODS_REGULAR_SIMPLEX_METHOD_H_

// ================================================================== INCLUDES
#include "optimization_method_interface.h"
#include "simplex_regular.h"
// ================================================================== SYNOPSIS
// Структура, реализующая алгоритм метода симплексного поиска при помощи
// регулярного симплекса
// ===========================================================================

namespace OPT_METH
{
	struct RegularSimplexMethod : OptimizationMethodInterface
	{
		RegularSimplexMethod():
		OptimizationMethodInterface(RegularSimplex, sizeof(RegularSimplexMethod)),
		lengthEdgeInit(1.0)// начальная длина ребра симплекса
		{
			;
		}
		double* findMin(FuncInformInterface* _func, double* _X0, const double _eps)
		{
			OptimizationMethodInterface::findMin(_func, _X0, _eps);
			if(m_func == NULL) { return NULL; }
			simplex.set(m_func, &m_sol, lengthEdgeInit);
			residualNorm = lengthEdgeInit;
			curValF = m_func->func(&m_sol);
			printRes();
			while((residualNorm > m_eps) && (iter < MAX_ITER_COUNT))
			{
				//...............
				// алгоритм
				//...............
			}
			coutRes();
			closeOut();
			return &m_sol;
		};
	  private:
		void printRes()
		{
			m_sol.print(out);
			simplex.print(out);
			out << curValF << " " << residualNorm << "\n";
		};
		void setFileName(){ fileName = "regSimplex"; };
		SimplexRegular simplex;
		double lengthEdgeInit;
	};
}

#endif //_OPTIMIZATION_METHODS_REGULAR_SIMPLEX_METHOD_H_
