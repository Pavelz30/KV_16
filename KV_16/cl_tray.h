#ifndef __CL_3__H
#define __CL_3__H

#include "cl_base.h"                                      

class cl_tray : public cl_base                                // ќбъ€вление класса cl_3
{
	int max_number_of_sheet_in_tray;
	int number_of_sheet;
public:
	cl_tray(int number_of_sheet, cl_base* p_head_object, string s_object_name);    // ѕараметризирвоанный конструктор класса cl_3
	int get_number_of_sheet();
	void set_number_of_sheet(int num);
	void signal_for_tray(string& massege);			   // ћетод сигнала класса cl_3
	void signal_for_display(string& massege);			   // ћетод сигнала класса cl_3
	void handler(string num_of_list_);			   // ћетод обработчика класса cl_3
};

#endif
