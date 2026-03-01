/*!
* \copyright (C) 2014 Puzikova V.V.
* \file      newton_method.h
* \author    Puzikova Valeria (vvp) 
* \date      25.08.2014 1:55:49
* \brief     newton_method.h
* \fmtstyle  3S
*/

#ifndef _OPTIMIZATION_METHODS_NEWTON_METHOD_H_
#define _OPTIMIZATION_METHODS_NEWTON_METHOD_H_

// ================================================================== INCLUDES
#include "optimization_method_interface.h"
// ================================================================== SYNOPSIS
// Структура, реализующая алгоритм метода Ньютона
// ===========================================================================

namespace OPT_METH
{
	struct NewtonMethod : OptimizationMethodInterface
	{
		explicit NewtonMethod(OptMethods _id = Newton, int _size = sizeof(NewtonMethod)):
		OptimizationMethodInterface(_id, _size)
		{
			;
		}
		double* findMin(FuncInformInterface* _func, double* _X0, const double _eps)
		{
			OptimizationMethodInterface::findMin(_func, _X0, _eps);
			if(m_func == NULL) { return NULL; }
			m_Hesse = m_func->pHesse;
			curValF = m_func->func(&m_sol);
			P.resize(m_dim);
			antiGrad.resize(m_dim);
			calcResidual();
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
	  protected:
		void calcResidual()
		{
			antiGrad.set(m_func->antiGrad(&m_sol));
			residualNorm = antiGrad.norm();
		};
		void calcP()
		{
			//...............
			// алгоритм
			//...............
		};
		virtual void printRes()
		{
			m_sol.print(out);
			out << curValF << " " << residualNorm << "\n";
		};
		virtual void setFileName(){ fileName = "newton"; };
		Vect P, antiGrad; // направление спуска и антиградиент
		MatrixInterface* m_Hesse;// указатель на матрицу Гессе
	};
}

#endif //_OPTIMIZATION_METHODS_NEWTON_METHOD_H_
