/*!
* \copyright (C) 2014 Puzikova V.V.
* \file      simplex_non_regular.h
* \author    Puzikova Valeria (vvp) 
* \date      23.08.2014 3:41:26
* \brief     simplex_non_regular.h
* \fmtstyle  3S
*/

#ifndef _OPTIMIZATION_METHODS_SIMPLEX_NON_REGULAR_H_
#define _OPTIMIZATION_METHODS_SIMPLEX_NON_REGULAR_H_

// ================================================================== INCLUDES
#include "simplex_regular.h"
// ================================================================== SYNOPSIS
// структура, реализующая работу с нерегулярным симплексом в dimCount-мерном
// пространстве
// ===========================================================================

namespace OPT_METH
{
	struct SimplexNonRegular : SimplexRegular
	{
		SimplexNonRegular():
		SimplexRegular(),
		reflectionCoef(1.0),// коэф-т отражения
		dilatationCoef(2.0),// коэф-т растяжения
		compressionCoef(0.5)// коэф-т сжатия
		{
			;
		}
		void dilatation()
		{// растяжение симплекса
		 // координаты новой вершины симплекса после растяжения после выполнения данного метода
		 // будут записаны в auxVect. Если растяжение можно считать удачным, то нужно выполнить
		 // newVertex.set(&auxVect) и вызвать метод saveNewPoint(), чтобы записать 
		 // координаты newVertex вместо vertices[i_max]
			auxVect.set(&sumVertices);
			auxVect -= &(vertices[i_max]);
			auxVect *= dilatationFactor;
			auxVect += &newVertex;
			auxVect *= dilatationCoef;
		};
		void compression()
		{//сжатие симплекса
		 // координаты новой вершины симплекса после сжатия после выполнения этого метода
		 // будут записаны в newVertex. Если мы считаем, что сжатие симплекса прошло удачно, то нужно 
		 // вызвать метод saveNewPoint(), чтобы записать координаты newVertex вместо vertices[i_max]
			if(m_func->func(&newVertex) > fMax)
				auxVect.set(&(vertices[i_max]));
			else
				auxVect.set(&newVertex);
			auxVect *= compressionCoef;
			newVertex.set(&sumVertices);
			newVertex -= &(vertices[i_max]);
			newVertex *= compressionFactor;
			newVertex += &auxVect;
		};
	  private:
		void calcFactors()
		{
			reflectionFactor = (1.0 + reflectionCoef) * invDim;
			reflectionFactor2 = reflectionCoef + reflectionFactor;
			dilatationFactor = (1.0 - dilatationCoef) * invDim / dilatationCoef;
			compressionFactor = (1.0 - compressionCoef) * invDim;
		};
		double reflectionCoef, dilatationCoef, compressionCoef;
		double dilatationFactor, compressionFactor;
	};
}

#endif //_OPTIMIZATION_METHODS_SIMPLEX_NON_REGULAR_H_
