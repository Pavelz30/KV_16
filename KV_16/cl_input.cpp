#include "cl_input.h"
#include "cl_application.h"
#include "cl_base.h"
#include <iostream>

cl_input::cl_input(cl_base* p_head_object, string s_object_name) :cl_base(p_head_object, s_object_name)    // Реализация конструктора класса сl_5
{

}

void cl_input::signal_for_input_to_all(string& massege)													  // Реализация метода сигнала класса cl_5
{
	cout << endl << "Signal from " << absolute_path();	//ничего не делает										  // Вывод характерного сообщения и абсолютного пути до объекта
														 	  // Присвоение massege значенея самой перменной + "(class: 5)
}

void cl_input::handler_for_input_to_app(string massege)													  // Реализация метода обработчика класса cl_5
{
	string s_cmd;
	getline(cin, s_cmd);
	
	if (s_cmd == "End of settings" || s_cmd.find(' ')==string::npos)
		emit_signal(switch_signal(7), s_cmd);
	else
	{
		emit_signal(switch_signal(3), to_string(s_cmd[1]));
		emit_signal(switch_signal(2), to_string(s_cmd[3]));
	}
}