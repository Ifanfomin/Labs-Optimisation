/*!
* \copyright (C) 2014 Puzikova V.V.
* \file      optimization_task.h
* \author    Puzikova Valeria (vvp) 
* \date      25.08.2014 0:25:18
* \brief     optimization_task.h
* \fmtstyle  3S
*/

#ifndef _OPTIMIZATION_METHODS_OPTIMIZATION_TASK_H_
#define _OPTIMIZATION_METHODS_OPTIMIZATION_TASK_H_

// ================================================================== INCLUDES
#include "goal_func_inform.h"
#include "optimization_method_selector.h"
// ================================================================== SYNOPSIS
// структура с описанием задачи двумерной безусловной минимизации
// и алгоритмами её решения
// ===========================================================================

namespace OPT_METH
{
	struct OptimizationTask
	{
		typedef OptimizationMethodInterface::OptMethods method;// vvp чтобы избежать длинных названий,
		// при помощи ключевого слова typedef можно определить новое, более короткое, имя типа
		OptimizationTask():// конструктор (выполняется при создании экземпляра данной структуры)
		eps(0.001)         // в нем инициализируются переменные
		{
			dimCount = goalFunction.variableCount;// размерность пространства, в котором решаем задачу
			X0.resize(dimCount);
			Xmin.resize(dimCount);
			X0.set(0, -1.0);
			X0.set(1, -2.0);
		}
		void solve(method _id)
		{
			methods.setMethod(_id);//делаем m_method указателем на структуру выбранного метода
			if(methods.m_method != NULL)// проверяем, что m_method указывает на структуру с алгоритмом, 
			{                           // а не "в никуда"
				double* aux = methods.m_method->findMin((FuncInformInterface*)(&goalFunction), &X0, eps);
				Xmin.set(aux);
			}
		};
		GoalFuncInform goalFunction;       // целевая функция
		OptimizationMethodSelector methods;// методы
		double eps;                        // точность
		int dimCount;                      // задача в dimCount-мерном пространстве
		Vect X0;                           // начальное приближение
		Vect Xmin;                         // точка минимума
	};
}

#endif //_OPTIMIZATION_METHODS_OPTIMIZATION_TASK_H_
