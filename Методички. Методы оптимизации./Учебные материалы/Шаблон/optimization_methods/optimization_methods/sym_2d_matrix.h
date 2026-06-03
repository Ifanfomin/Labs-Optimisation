/*!
* \copyright (C) 2014 Puzikova V.V.
* \file      sym_2d_matrix.h
* \author    Puzikova Valeria (vvp) 
* \date      22.08.2014 0:26:53
* \brief     sym_2d_matrix.h
* \fmtstyle  3S
*/

#ifndef _OPTIMIZATION_METHODS_SYM_2D_MATRIX_H_
#define _OPTIMIZATION_METHODS_SYM_2D_MATRIX_H_

// ================================================================== INCLUDES
#include "matrix_interface.h"
// ================================================================== SYNOPSIS
// симметрична€ матрица 2х2: {{elem[0], elem[2]}, {elem[2], elem[1]}}
// ===========================================================================

namespace OPT_METH
{
	struct Sym2DMatrix : MatrixInterface
	{
		static const int COUNT_DIF_ELEM = 3;
		Sym2DMatrix():
		MatrixInterface(Sym2D, sizeof(Sym2DMatrix)),
		delta(1.0)// отступ от границы при подборе eta
		{
			for(int i = 0; i < COUNT_DIF_ELEM; i++)
				elem[i] = 0.0;
		}
		double det()
		{
			double aux = elem[0] * elem[1] - elem[2] * elem[2];
			return aux;
		};
		bool isPositivelyDefinite()
		{// м-ца сим-на€ => используем критерий —ильвестра
			if((elem[0] > 0.0) && (det() > 0.0)) { return true; }
			return false;
		};
		void solve(double* rightMember, double* solution)
		{
			double aux = 1.0 / det();
			solution[0] = (elem[1] * rightMember[0] - elem[2] * rightMember[1]) * aux;
			solution[1] = (elem[0] * rightMember[1] - elem[2] * rightMember[0]) * aux;
		};
		void supplementToPositiveDefinite()
		{// дополн€ем матрицей вида eta * I до положительно определенной
			if(!isPositivelyDefinite())
			{
				// 1. подбираем eta (так, чтобы выполн€лс€ критерий —ильвестра)
				double eta = (elem[0] > 0.0) ? 0.0 : (delta - elem[0]);
				double trace = elem[0] + elem[1];// условие на второй минор приводит к решению квадратного ур-ни€
				double discr = trace * trace - 4.0 * det();// нетрудно показать, что оно всегда имеет действит.корни
				double aux = sqrt(discr);
				double etaMin = 0.5 * (aux - trace);
				double etaMax  = -0.5 * (aux + trace);
				if(etaMin > etaMax)
				{
					aux = etaMin;
					etaMin = etaMax;
					etaMax = aux;
				}// 2-й минор > 0 при (eta < etaMin) || (eta > etaMax)
				etaMin -= delta;
				etaMax += delta;
				if((eta > etaMin) && (eta < etaMax)) eta = etaMax;
				// 2. += eta * I
				elem[0] += eta;
				elem[1] += eta;
			}
		};
		double elem[COUNT_DIF_ELEM];
	private:
		double delta;
	};
}

#endif //_OPTIMIZATION_METHODS_SYM_2D_MATRIX_H_
