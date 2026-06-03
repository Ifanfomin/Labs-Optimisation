/*!
* \copyright (C) 2014 Puzikova V.V.
* \file      gradient_descent_with_spalling_step_method.h
* \author    Puzikova Valeria (vvp) 
* \date      25.08.2014 1:45:59
* \brief     gradient_descent_with_spalling_step_method.h
* \fmtstyle  3S
*/

#ifndef _OPTIMIZATION_METHODS_GRADIENT_DESCENT_WITH_SPALLING_STEP_METHOD_H_
#define _OPTIMIZATION_METHODS_GRADIENT_DESCENT_WITH_SPALLING_STEP_METHOD_H_

// ================================================================== INCLUDES
#include "optimization_method_interface.h"
// ================================================================== SYNOPSIS
// Стуктура, реализующая алгоритм метода градиентного спуска с дроблением шага
// ===========================================================================

namespace OPT_METH
{
	struct GradientDescentWithSpallingStepMethod : OptimizationMethodInterface
	{
		GradientDescentWithSpallingStepMethod():
		OptimizationMethodInterface(GradientDescentWithSpallingStep, sizeof(GradientDescentWithSpallingStepMethod)),
		spallingCoef(0.5),// коэффициент дробления шага
		omega(0.5),
		kappaInit(1.0)// начальное значение шага
		{
			;
		}
		double* findMin(FuncInformInterface* _func, double* _X0, const double _eps)
		{
			OptimizationMethodInterface::findMin(_func, _X0, _eps);
			if(m_func == NULL) { return NULL; }
			kappa = kappaInit;
			double prevValF = m_func->func(&m_sol);
			curValF = prevValF;
			X.resize(m_dim);
			antiGrad.resize(m_dim);
			calcResidual();
			printRes();
			while((residualNorm > m_eps) && (iter < MAX_ITER_COUNT))
			{
				aux2 = omega * residualNorm * residualNorm;
				calcX();
				while((prevValF - curValF) < aux)
				{
					kappa *= spallingCoef;// дробим шаг
					calcX();
				}
				prevValF = curValF;
				m_sol.set(&X);
				calcResidual();
				printRes();
				kappa = kappaInit;
				iter++;// счетчик итераций прибавляем
				// в консоль выводим промежуточную информацию, 
				// чтобы понимать, что программа что-то считает
				std::cout << "норма невязки = " << residualNorm << "\n";
			}
			coutRes();
			closeOut();
			return &m_sol;
		};
	  private:
		void calcX()
		{// X^{k+1} = X^k + kappa_k * W^k
			X.set(&antiGrad);
			X *= kappa;
			X += &m_sol;
			curValF = m_func->func(&X);
			aux = aux2 * kappa;
		};
		void calcResidual()
		{// вычисляем антиградиент и его норму
			antiGrad.set(m_func->antiGrad(&m_sol));
			residualNorm = antiGrad.norm();
		};
		void printRes()
		{
			m_sol.print(out);
			out << curValF << " " << kappa << " " << residualNorm << "\n";
		};
		void setFileName(){ fileName = "gradDescWithSpalStep"; };
		Vect antiGrad; // антиградиент
		Vect X;        // вспомогательный вектор
		double spallingCoef, omega, kappa, kappaInit, aux, aux2;
	};
}

#endif //_OPTIMIZATION_METHODS_GRADIENT_DESCENT_WITH_SPALLING_STEP_METHOD_H_
