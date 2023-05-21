#include "cl_cartridge.h"																			 

cl_cartridge::cl_cartridge(int number_of_sheets,cl_base* p_head_object, string s_object_name) :cl_base(p_head_object, s_object_name)    // Реализация конструктора класса сl_2
{
	this->max_number_of_sheets_in_cartridge = number_of_sheets;
	this->number_of_sheets = number_of_sheets;
}

void cl_cartridge::signal_for_cartridge(string& massege)													  // Реализация метода сигнала класса cl_2
{}

void cl_cartridge::signal_for_display(string& massege)													  // Реализация метода сигнала класса cl_2
{}

void cl_cartridge::handler(string num_of_list_)													  // Реализация метода обработчика класса cl_2
{
	int num_of_list = stoi(num_of_list_);
	if (this->number_of_sheets == 0)
		this->number_of_sheets = max_number_of_sheets_in_cartridge - num_of_list;
	else
	{
		this->number_of_sheets = number_of_sheets - num_of_list;
		if (number_of_sheets <= 0)
		{
			string list = to_string(abs(number_of_sheets));
			number_of_sheets = 0;
			emit_signal(SIGNAL_D(cl_cartridge::signal_for_cartridge), list);
		}
	}
}