#include "cl_PK.h"

cl_PK::cl_PK(cl_base* p_head_object, string s_object_name) :cl_base(p_head_object, s_object_name)    // Реализация конструктора класса сl_6
{

}

void cl_PK::signal_for_6_class(string& massege)													  // Реализация метода сигнала класса cl_6
{
	cout << endl << "Signal from " << absolute_path();											  // Вывод характерного сообщения и абсолютного пути до объекта
	massege = massege + " (class: 6)";															  // Присвоение massege значенея самой перменной + "(class: 6)"
}

void cl_PK::handler_for_6_class(string massege)													  // Реализация метода обработчика класса cl_6
{
	if (get_i_status_ready() == false) return;													  // Проверка, что статус текущего объекта "Не готов",если да, то завершение работы метода
	cout << endl << "Signal to " << absolute_path() << " Text: " << massege;					  // Вывод характерного сообщения, абсолютного пути до объекта и значения параметра massege
}