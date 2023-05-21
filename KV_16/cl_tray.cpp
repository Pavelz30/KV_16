#include "cl_tray.h"

cl_tray::cl_tray(cl_base* p_head_object, string s_object_name) :cl_base(p_head_object, s_object_name)    // Реализация конструктора класса сl_3
{
	this->max_number_of_sheet_in_tray = 0;
	number_of_sheet_in_tray = 0;
}

void cl_tray::signal_for_3_class(string& massege)													  // Реализация метода сигнала класса cl_3
{
	cout << endl << "Signal from " << absolute_path();											  // Вывод характерного сообщения и абсолютного пути до объекта
	 															  // Присвоение massege значенея самой перменной + "(class: 3)"
}

void cl_tray::handler_for_3_class(string massege)													  // Реализация метода обработчика класса cl_3
{
	this->max_number_of_sheet_in_tray = stoi(massege);			  // Вывод характерного сообщения, абсолютного пути до объекта и значения параметра massege 
}