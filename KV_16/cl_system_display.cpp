#include "cl_system_display.h"

cl_system_display::cl_system_display(cl_base* p_head_object, string s_object_name) :cl_base(p_head_object, s_object_name)    // Реализация конструктора класса сl_3
{

}

void cl_system_display::signal_for_3_class(string& massege)													  // Реализация метода сигнала класса cl_3
{
	cout << endl << "Signal from " << absolute_path();											  // Вывод характерного сообщения и абсолютного пути до объекта
	massege = massege + " (class: 3)"; 															  // Присвоение massege значенея самой перменной + "(class: 3)"
}

void cl_system_display::handler_for_3_class(string massege)													  // Реализация метода обработчика класса cl_3
{
	if (get_i_status_ready() == false) return;													  // Проверка, что статус текущего объекта  "Не готов",если да, то завершение работы метода
	cout << endl << "Signal to " << absolute_path() << " Text: " << massege;					  // Вывод характерного сообщения, абсолютного пути до объекта и значения параметра massege 
}