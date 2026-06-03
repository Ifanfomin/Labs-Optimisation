/*!
* \copyright (C) 2014 Puzikova V.V.
* \file      optimization_method_interface.h
* \author    Puzikova Valeria (vvp) 
* \date      25.08.2014 0:29:28
* \brief     optimization_method_interface.h
* \fmtstyle  3S
*/

#ifndef _OPTIMIZATION_METHODS_OPTIMIZATION_METHOD_INTERFACE_H_
#define _OPTIMIZATION_METHODS_OPTIMIZATION_METHOD_INTERFACE_H_

// ================================================================== INCLUDES
// ================================================================== SYNOPSIS
// базовая структура-интерфейс, в производных структурах реализуются алгоритмы
// численных методов многомерной безусловной минимизации
// ===========================================================================

namespace OPT_METH
{
	struct OptimizationMethodInterface
	{
		static const int MAX_ITER_COUNT = 500;// ограничение на макс.число итераций на случай зацикливания
		enum OptMethods
		{// перечисление идентификаторов производных структур
			Unknown = -1,                   // метод не задан
			GradientDescentWithSpallingStep,// метод градиентного спуска с дроблением шага
			Newton,                         // метод Ньютона
			NewtonWithSpallingStep,         // модификация метода Ньютона (спуск с дроблением шага)
			RegularSimplex,                 // метод симплексного поиска при помощи регулярного симплекса
			NonRegularSimplex               // метод Нелдера-Мида
		};
		explicit OptimizationMethodInterface(OptMethods _id = Unknown, 
											 int _size = sizeof(OptimizationMethodInterface)):
		id(_id),
		size(_size),
		residualNorm(0.0),
		iter(0),
		m_dim(0)
		{
			fileName = "";
		}
		~OptimizationMethodInterface()
		{
			closeOut();
		};
		virtual double* findMin(FuncInformInterface* _func, double* _X0, const double _eps)
		{// функция возращает значение точки минимума функции _func, найденное с точностью _eps
		 // _X0 --- начальное приближение
			m_func = _func;
			m_eps = _eps;
			if(m_func != NULL)
			{
				m_dim = m_func->variableCount;// размерность пространства
				m_sol.resize(m_dim);
				m_sol.set(_X0);// m_sol = _X0
				iter = 0;
				setFileName();// задаем имя файла вывода
				fileName += ".dat";
				closeOut();
				out.open(fileName.c_str());// открываем поток вывода
			}
			else std::cout << "Целевая функция не задана!\n";
			return NULL;
		};
	  protected:
		void closeOut(){ if(out.is_open()) out.close(); };
		virtual void setFileName(){ fileName = "results"; };
		virtual void printRes(){};
		void coutRes()
		{
			std::cout << "Решение получено за " << iter << " итер.: ( ";
			for(int i = 0; i < m_dim; i++)
				std::cout << m_sol[i] << ", ";
			std::cout << ")\n";
		};
		Vect m_sol;// координаты точки минимума
		std::string fileName;// имя файла, в который выводим результаты
		std::ofstream out;   // поток вывода результатов в файл
		double m_eps, curValF;
		FuncInformInterface* m_func;// указатель на целевую функцию
	  public:
		double residualNorm;// норма невязки
		OptMethods id;      // идентификатор метода
		int size;           // размер структуры
		int iter;           // число итераций
	  protected:
		int m_dim;
	};
}

#endif //_OPTIMIZATION_METHODS_OPTIMIZATION_METHOD_INTERFACE_H_
