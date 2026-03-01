/*!
* \copyright (C) 2014 Puzikova V.V.
* \file      simplex_regular.h
* \author    Puzikova Valeria (vvp) 
* \date      23.08.2014 3:03:09
* \brief     simplex_regular.h
* \fmtstyle  3S
*/

#ifndef _OPTIMIZATION_METHODS_SIMPLEX_REGULAR_H_
#define _OPTIMIZATION_METHODS_SIMPLEX_REGULAR_H_

// ================================================================== INCLUDES
#include "func_inform_interface.h"
// ================================================================== SYNOPSIS
// структура, реализующая работу с регулярным симплексом в dimCount-мерном
// пространстве
// ===========================================================================

namespace OPT_METH
{
	struct SimplexRegular
	{
		SimplexRegular():
		reductionCoef(0.5),// коэф-т редукции
		verticesCount(0),  
		dimCount(0),
		edgeLength(0.0),
		SD(0.0),
		invDim(0.0),
		i_min(0),// номер вершины, в которой значение функции наименьшее
		i_max(0)// номер вершины, в которой значение функции наибольшее
		{
			; 
		}
		~SimplexRegular()
		{
			clear();
		}
		void clear(){ if(verticesCount > 0) delete[] vertices; };
		void set(FuncInformInterface* _func, double* _midpoint, const double _edgeLength)
		{
			m_func = _func;
			clear();
			dimCount = m_func->variableCount;
			if(dimCount > 0)
			{
				invDim = 1.0 / dimCount;
				calcFactors();
				edgeLength = _edgeLength;// длина ребра симплекса
				midPoint.resize(dimCount);
				newVertex.resize(dimCount);
				sumVertices.resize(dimCount);
				auxVect.resize(dimCount);
				sumVertices.setZero();
				midPoint.set(_midpoint);
				verticesCount = dimCount + 1;
				invVertCount = 1.0 / verticesCount;
				vertices = new Vect[verticesCount];
				// вычисляем координаты вершин симплекса по известному центру
				for(int i = 0; i < verticesCount; i++)
				{
					vertices[i].resize(dimCount);
					int num = i - 1;
					for(int j = 0; j < num; j++)
						vertices[i].set(j, midPoint[j]);
					double aux2 = (0.5 * i) / (i + 1);
					double aux = midPoint[num] + edgeLength * sqrt(aux2);// выход за гр-цы в vect контролируется
					vertices[i].set(num, aux);// выход за гр-цы в vect контролируется
					for(int j = i; j < dimCount; j++)
					{
						aux2 = 2.0  * (j + 1) * (j + 2);
						aux = midPoint[j] - (edgeLength / sqrt(aux2));
						vertices[i].set(j, aux);
					}
					sumVertices += &(vertices[i]);
				}
				defMinMax();
			}
		};
		void reduction()// редукция симплекса
		{// + полный пересчет суммы векторов вершин
			edgeLength *= reductionCoef;
			auxVect.set(&(vertices[i_min]));
			sumVertices.setZero();
			for(int i = 0; i < verticesCount; i++)
			{
				vertices[i] -= &auxVect;
				vertices[i] *= reductionCoef;
				vertices[i] += &auxVect;
				sumVertices += &(vertices[i]);
			}
		};
		void reflection()
		{// отражение вершины с номером i_max
		 // координаты отраженной вершины после выполнения этого метода будут записаны в newVertex
		 // если мы считаем, что отражение симплекса прошло удачно и хотим далее использовать 
		 // отраженный симплекс, нужно вызвать метод saveNewPoint(), чтобы записать 
		 // координаты newVertex вместо vertices[i_max]
			newVertex.set(&sumVertices);
			newVertex *= reflectionFactor;
			auxVect.set(&(vertices[i_max]));
			auxVect *= reflectionFactor2;
			newVertex -= &auxVect;
		};
		void saveNewPoint()
		{ // + обновляем сумму векторов вершин
			sumVertices -= &(vertices[i_max]);
			sumVertices += &newVertex;
			vertices[i_max].set(&newVertex); 
		};
		void defMinMax()
		{// определяем вершины симплекса, в которых функция имеет наибольшее и наименьшее значения
		 //+ рассчит.СКО значений ф-ции в вершинах симплекса
		 // !!! этот метод нужно вызывать каждый раз после изменения симплекса !!!
			i_min = 0;
			i_max = 0;
			fMin = m_func->func(&(vertices[0]));
			fMax = fMin;
			fMaxPrev = fMax;
			calcMidPoint();// пересчитываем координаты центра симплекса
			double aux2 = m_func->func(&midPoint);
			double aux = fMin - aux2;
			double aux4 = aux * aux;
			for(int i = 1; i < verticesCount; i++)
			{
				aux = m_func->func(&(vertices[i]));
				if(aux < fMin)
				{
					fMin = aux;
					i_min = i;
				}
				else
				{
					if(aux > fMax)
					{
						fMaxPrev = fMax;
						fMax = aux;
						i_max = i;
					}
					else
					{
						if(aux > fMaxPrev) fMaxPrev = aux;
					}
				}
				aux -= aux2;
				double aux3 = aux * aux;
				aux4 += aux3;
			}
			// теперь i_min --- номер вершины, в которой значение целевой функции наименьшее (fMin),
			// i_max --- номер вершины, в которой значение целевой функции наибольшее (fMax),
			// fMaxPrev --- значение функции в одной из вершин, больше него только fMax
			aux4 *= invVertCount;
			SD = sqrt(aux4);// для нерегулярного симплекса СКО можно исп-ть как residualNorm
		};
		void print(std::ofstream& out)
		{
			for(int i = 0; i < verticesCount; i++)
				vertices[i].print(out);
		};
	 private:
		void calcMidPoint()
		{
			midPoint.set(&sumVertices);
			midPoint -= &(vertices[i_max]);
			midPoint *= invDim;
		};
	  protected:
		virtual void calcFactors()
		{
			reflectionFactor = 2.0 * invDim;
			reflectionFactor2 = 1.0 + reflectionFactor;
		};
		FuncInformInterface* m_func;
	  public:
		Vect* vertices;// массив координат вершин симплекса
		Vect midPoint;// координаты центра симплекса
		Vect newVertex;// координаты новой вершины
		Vect auxVect;// вспомогательный вектор
		Vect sumVertices;// суммы координат вершин
		double edgeLength, fMin, fMax, fMaxPrev, SD;
	  protected:
		double invDim, invVertCount, reductionCoef, reflectionFactor, reflectionFactor2;
	  public:
		int i_max, i_min, dimCount, verticesCount;
	};
}

#endif //_OPTIMIZATION_METHODS_SIMPLEX_REGULAR_H_
