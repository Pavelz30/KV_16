#include "cl_console.h"

cl_console::cl_console(cl_base* p_head_object, string s_object_name) :cl_base(p_head_object, s_object_name)    // Реализация конструктора класса сl_4
{

}

void cl_console::signal_for_4_class(string& massege)													  // Реализация метода сигнала класса cl_4
{
	cout << endl << "Signal from " << absolute_path();											  // Вывод характерного сообщения и абсолютного пути до объекта
	massege = massege + " (class: 4)";															  // Присвоение massege значенея самой перменной + "(class: 4)"											
}

void cl_console::handler_for_4_class(string massege)													  // Реализация метода обработчика класса cl_4
{
	if (get_i_status_ready() == false) return;													  // Проверка, что статус текущего объекта "Не готов",если да, то завершение работы метода
	cout << endl << "Signal to " << absolute_path() << " Text: " << massege;					  // Вывод характерного сообщения, абсолютного пути до объекта и значения параметра massege
}