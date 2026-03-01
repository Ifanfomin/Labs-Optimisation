/*!
* \copyright (C) 2014 Puzikova V.V.
* \file      vect.h
* \author    Puzikova Valeria (vvp) 
* \date      15.08.2014 2:26:28
* \brief     vect.h
* \fmtstyle  3S
*/

#ifndef _OPTIMIZATION_METHODS_VECT_H_
#define _OPTIMIZATION_METHODS_VECT_H_

// ================================================================== INCLUDES
// ================================================================== SYNOPSIS
// структура vect length-мерного вектора, для которого определены
// некоторые необходимые операции (обёртка double elements[length])
//
// 1) вместо адреса vect возвращается адрес массива элементов вектора
// 2) оператор индексирования также связан с массивом элементов
// ===========================================================================

namespace OPT_METH
{
	struct Vect
	{
		Vect():
		length(0)
		{
			;
		}
		~Vect()
		{// vvp деструктор выполняется при удалении экземпляра структуры
			clear();// в частности, если в структуре создавались динамические массивы, 
			        // в деструкторе нужно освободить память, выделенную под них
		}
		void clear(){ if(length > 0) delete[] elements; };
		void resize(const int _length)
		{// создаем массив длины _length и инициализируем его нулями
			clear();
			if(_length > 0)
			{
				length = _length;
				elements = new double[length];
				setZero();
			}
		};
		void setZero()
		{// обнуляем элементы Vect
			for(int i = 0; i < length; i++)
				elements[i] = 0.0;
		};
		void set(double* vect2)
		{// Vect = vect2
			for(int i = 0; i < length; i++)
				elements[i] = vect2[i];
		};
		void set(const double* vect2)
		{// Vect = vect2
			for(int i = 0; i < length; i++)
				elements[i] = vect2[i];
		};
		void set(const int num, const double value){ if((num > -1) && (num < length)) elements[num] = value; };
		double norm()
		{// возвращает норму вектора
			double aux = 0.0;
			for(int i = 0; i < length; i++)
			{
				double aux2 = elements[i];
				double aux3 = aux2 * aux2;
				aux += aux3;
			}
			return sqrt(aux);
		};
		// некоторые операторы удобно перегрузить (см. в google Перегрузка операторов С++)
		double* operator& (){ return elements; };// удобно, чтобы указатель на vect был указателем на elements
		double operator[] (const int num) 
		{ 
			if((num > -1) && (num < length)) { return elements[num]; }
			std::cout << "Выход за пределы vect!\n";
			return 0.0;
		}
		void operator+= (double* vect2)
		{// к Vect прибавляем  vect2
			for(int i = 0; i < length; i++)
				elements[i] += vect2[i];
		};
		void operator-= (double* vect2)
		{// к Vect вычитаем  vect2
			for(int i = 0; i < length; i++)
				elements[i] -= vect2[i];
		};
		double operator* (double* vect2)
		{// возвращает скалярное произведение Vect и vect2
			double aux = 0.0;
			for(int i = 0; i < length; i++)
				aux += elements[i] * vect2[i];
			return aux;
		}
		void operator*= (const double coef)
		{// умножаем элементы Vect на число coef
			for(int i = 0; i < length; i++)
				elements[i] *= coef;
		}
		void print(std::ofstream& out)
		{
			for(int i = 0; i < length; i++)
				out << elements[i] << " ";
		};
		double* elements;// массив элементов Vect
		int length;// длина массива элементов Vect
	};
}

#endif //_OPTIMIZATION_METHODS_VECT_H_
