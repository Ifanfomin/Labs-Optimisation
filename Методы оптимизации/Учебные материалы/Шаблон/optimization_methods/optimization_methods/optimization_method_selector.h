/*!
* \copyright (C) 2014 Puzikova V.V.
* \file      optimization_method_selector.h
* \author    Puzikova Valeria (vvp) 
* \date      25.08.2014 2:09:17
* \brief     optimization_method_selector.h
* \fmtstyle  3S
*/

#ifndef _OPTIMIZATION_METHODS_OPTIMIZATION_METHOD_SELECTOR_H_
#define _OPTIMIZATION_METHODS_OPTIMIZATION_METHOD_SELECTOR_H_

// ================================================================== INCLUDES
#include "gradient_descent_with_spalling_step_method.h"
#include "newton_with_spalling_step_method.h"
#include "regular_simplex_method.h"
#include "non_regular_simplex_method.h"
// ================================================================== SYNOPSIS
// в OptimizationMethodSelector по выбранному идентификатору метода
// выбираетс€ структура, реализующа€ алгоритм данного метода,
// и указатель на неЄ присваиваетс€ m_method.
// “аким образом извне к структурам, производным от OptimizationMethodInterface
// мы всегда обращаемс€ по указателю m_method, не обраща€ внимани€, на какую 
// именно производную структуру указывает этот указатель
// ===========================================================================

namespace OPT_METH
{
	struct OptimizationMethodSelector
	{
		typedef OptimizationMethodInterface::OptMethods method;
		void setMethod(const method _id)
		{// по идентификатору метода делаем m_method указателем на структуру, реализующую этот метод
			switch(_id)
			{
			  case method::GradientDescentWithSpallingStep:
				m_method = (OptimizationMethodInterface*)(&gradDescWithSpalStep);
				break;
			  case method::Newton:
				m_method = (OptimizationMethodInterface*)(&newton);
				break;
			  case method::NewtonWithSpallingStep:
				m_method = (OptimizationMethodInterface*)(&newtonWithSpalStep);
				break;
			  case method::RegularSimplex:
				m_method = (OptimizationMethodInterface*)(&regSimplex);
				break;
			  case method::NonRegularSimplex:
				m_method = (OptimizationMethodInterface*)(&nonRegSimplex);
				break;
			  default:
				std::cout << "«адан неправильный идентификатор метода!\n";
				m_method = NULL;
			}
		};
	  private:// структуры, реализующие алгоритмы некоторых методов оптимизации
		GradientDescentWithSpallingStepMethod gradDescWithSpalStep;
		NewtonMethod newton;
		NewtonWithSpallingStepMethod newtonWithSpalStep;
		RegularSimplexMethod regSimplex;
		NonRegularSimplexMethod nonRegSimplex;
	  public:// извне к структурам обращаемс€ только по указателю на базовую структуру
		OptimizationMethodInterface* m_method;
	};
}

#endif //_OPTIMIZATION_METHODS_OPTIMIZATION_METHOD_SELECTOR_H_
