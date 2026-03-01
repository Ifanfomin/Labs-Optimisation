/*!
* \copyright (C) 2014 Puzikova V.V.
* \file      newton_with_spalling_step_method.h
* \author    Puzikova Valeria (vvp) 
* \date      25.08.2014 1:57:35
* \brief     newton_with_spalling_step_method.h
* \fmtstyle  3S
*/

#ifndef _OPTIMIZATION_METHODS_NEWTON_WITH_SPALLING_STEP_METHOD_H_
#define _OPTIMIZATION_METHODS_NEWTON_WITH_SPALLING_STEP_METHOD_H_

// ================================================================== INCLUDES
#include "newton_method.h"
// ================================================================== SYNOPSIS
// Структура, реализующая алгоритм метода Ньютона с дроблением шага
// ===========================================================================

namespace OPT_METH
{
	struct NewtonWithSpallingStepMethod : NewtonMethod
	{
		NewtonWithSpallingStepMethod():
		NewtonMethod(NewtonWithSpallingStep, sizeof(NewtonWithSpallingStepMethod)),
		spallingCoef(0.5),
		omega(0.25),
		kappaInit(1.0)
		{
			;
		}
		double* findMin(FuncInformInterface* _func, double* _X0, const double _eps)
		{
			OptimizationMethodInterface::findMin(_func, _X0, _eps);
			if(m_func == NULL) { return NULL; }
			kappa = kappaInit;
			m_Hesse = m_func->pHesse;
			curValF = m_func->func(&m_sol);
			double prevValF = curValF;
			P.resize(m_dim);
			X.resize(m_dim);
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
	private:
		void calcX()
		{
			//...............
			// алгоритм
			//...............
		};
		void printRes()
		{
			m_sol.print(out);
			out << curValF << " " << kappa << " " << residualNorm << "\n";
		};
		void setFileName(){ fileName = "newtonWithSpalStep"; };
		Vect X;        // вспомогательный вектор
		double spallingCoef, omega, kappa, kappaInit, aux, aux2;
	};
}

#endif //_OPTIMIZATION_METHODS_NEWTON_WITH_SPALLING_STEP_METHOD_H_
