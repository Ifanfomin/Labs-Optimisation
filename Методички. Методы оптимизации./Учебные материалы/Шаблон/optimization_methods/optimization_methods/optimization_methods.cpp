// optimization_methods.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
// vvp подключаем необходимые файлы
#include "optimization_task.h"

using namespace OPT_METH;// vvp для избежания конфликтов имен необходимо использовать пространства имен

int main(int argc, char* argv[]) 
{ 
	setlocale(LC_ALL,"Russian");// vvp чтобы в консоли можно было выводить русские буквы

	OptimizationTask task;// главная структура, в которой хранится описание задачи и м-ды решения
	// вызываем метод, в котором реализовано решение задачи
	task.solve(OptimizationMethodInterface::OptMethods::RegularSimplex);

	system ("PAUSE");// vvp чтобы окно программы не закрылось сразу после выполнения
	return 0;
}



