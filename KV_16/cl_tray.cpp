#include "cl_tray.h"

cl_tray::cl_tray(int number_of_sheet, cl_base* p_head_object,
	string s_object_name) :cl_base(p_head_object, s_object_name)    // Реализация конструктора класса сl_3
{
	this->max_number_of_sheet_in_tray = number_of_sheet;
	this->number_of_sheet = number_of_sheet;
}

int cl_tray::get_number_of_sheet()
{
	return this->number_of_sheet;
}


void cl_tray::set_number_of_sheet(int num)
{
	this->number_of_sheet = num;
}


void cl_tray::signal_for_tray(string& massege)
{}


void cl_tray::signal_for_display(string& massege)
{}


void cl_tray::handler(string num_of_list_)
{
	int num_of_list = stoi(num_of_list_);
	if (this->number_of_sheet == 0)
		this->number_of_sheet = max_number_of_sheet_in_tray - num_of_list;
	else
	{
		this->number_of_sheet = number_of_sheet - num_of_list;
		if (number_of_sheet <= 0)
		{
			string list = to_string(abs(number_of_sheet));
			number_of_sheet = 0;
			emit_signal(SIGNAL_D(cl_tray::signal_for_tray), list);
		}
	}
}
