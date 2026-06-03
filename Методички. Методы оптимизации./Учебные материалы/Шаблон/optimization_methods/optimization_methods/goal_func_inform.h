/*!
* \copyright (C) 2014 Puzikova V.V.
* \file      goal_func_inform.h
* \author    Puzikova Valeria (vvp) 
* \date      15.08.2014 2:22:56
* \brief     func_inform.h
* \fmtstyle  3S
*/

#ifndef _OPTIMIZATION_METHODS_GOAL_FUNC_INFORM_H_
#define _OPTIMIZATION_METHODS_GOAL_FUNC_INFORM_H_

// ================================================================== INCLUDES
#include "func_inform_interface.h"
#include "sym_2d_matrix.h"
// ================================================================== SYNOPSIS
// структура goalFuncInform содержит методы, возращающие значение функции 
//                   alpha * (x^2 - y)^2 + (x - 1)^2
// и ее антиградиента (здесь для простоты задан явно, в общем случае
// нужна функция численного дифференцирования)
// + вычисление м-цы Гессе (обращаемся по ук-лю matrixInterface* pHesse;)
// ===========================================================================

namespace OPT_METH
{
	struct GoalFuncInform : FuncInformInterface// отнаследована от FuncInformInterface
	{
		GoalFuncInform():// в явном конструкторе передаем указатель на матрицу Гессе и число переменных
		FuncInformInterface((MatrixInterface*)(&Hesse), 2),
		alpha(1.0)
		{
			two_alpha = 2.0 * alpha;
			Hesse.elem[1] = two_alpha;
			curAntiGrad.resize(2);
		}
		double func(double* point)
		{// alpha * (x^2 - y)^2 + (x - 1)^2
			double aux2 = point[0];
			double aux3 = aux2 - 1.0;
			double aux = aux3 * aux3;
			aux3 = aux2 * aux2 - point[1];
			aux2 = alpha * aux3 * aux3;
			aux += aux2;
			return aux;// значение ф-ции в точке point
		};
		double* antiGrad(double* point)
		{
			double aux2 = point[0];
			double aux = 2.0 * alpha * (aux2 * aux2 - point[1]);
			double aux3 = 2.0 * (1.0 - aux2 * (1.0 + aux));
			curAntiGrad.set(0, aux3);
			curAntiGrad.set(1, aux);
			return curAntiGrad.elements;// антиградиент ф-ции в точке point
		};
		void calcHesse(double* point)
		{// м-ца Гессе в точке point
			double aux2 = point[0];
			Hesse.elem[0] = 2.0 * (1.0 + two_alpha * (3.0 * aux2 * aux2 - point[1]));
			Hesse.elem[2] = -2.0 * aux2 * two_alpha;
		};
	  private:
		Sym2DMatrix Hesse;
		Vect curAntiGrad;
		double alpha, two_alpha;
	};
}

#endif //_OPTIMIZATION_METHODS_GOAL_FUNC_INFORM_H_
