#include "cl_application.h"
#include "iostream"


int main()										  // Реализация основной функции программы
{
	cl_application ob_cl_system(nullptr);    // Создание объекта ob_cl_application класса cl_application  с помощью парметризированного констурктора, которому параметром передается пустой указатель
	ob_cl_system.build_tree_objects();       // Вызов метода build_tree_objects объекта ob_cl_application 
	return ob_cl_system.exec_app();		  // Возврат результата работы метода exec_app объекта ob_cl_application 
}