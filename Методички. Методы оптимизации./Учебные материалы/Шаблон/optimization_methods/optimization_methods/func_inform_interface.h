/*!
* \copyright (C) 2014 Puzikova V.V.
* \file      func_inform_interface.h
* \author    Puzikova Valeria (vvp) 
* \date      19.08.2014 13:00:08
* \brief     func_inform_interface.h
* \fmtstyle  3S
*/

#ifndef _OPTIMIZATION_METHODS_FUNC_INFORM_INTERFACE_H_
#define _OPTIMIZATION_METHODS_FUNC_INFORM_INTERFACE_H_

// ================================================================== INCLUDES
#include "vect.h"
#include "matrix_interface.h"
// ================================================================== SYNOPSIS
// интерфейс структуры, содержащей м-ды, возвращающие значение заданной функции
// в точке, её антиградиент и т.д.
// ===========================================================================

namespace OPT_METH
{
	struct FuncInformInterface
	{
		// vvp в базовых струтурах-интерфейсах удобно использовать явные конструкторы,
		// которые вызываются из производных структур с нужными параметрами
		// см. в google Гомоморфное наследование С++, Инкапсуляция, Полиморфизм, Наследование
		explicit FuncInformInterface(MatrixInterface* _pHesse = NULL, int _variableCount = 0):
		pHesse(_pHesse),// по умолчанию _pHesse = NULL, _variableCount = 0
		variableCount(_variableCount)
		{
			;
		}
		// vvp виртуальные методы могут переопределяться в производных структурах
		virtual double func(double* point){ return 0.0; };// возвращает значение ф-ции в т. point
		virtual double* antiGrad(double* point){ return NULL; };// возвращает указатель на антиградиент ф-ции в т. point
		virtual void calcHesse(double* point){};// вычисляем м-цу Гессе в т. point, обращаемся к м-це по указателю pHesse
		MatrixInterface* pHesse;// в интерфейсе храним только указатель на матрицу, сама матрица --- в производной структуре
		int variableCount;      // число переменных
	};
}

#endif //_OPTIMIZATION_METHODS_FUNC_INFORM_INTERFACE_H_
