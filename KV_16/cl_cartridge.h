#ifndef __CL_2_H
#define __CL_2_H

#include "cl_base.h"                                      

class cl_cartridge : public cl_base                                // ���������� ������ cl_2
{
	int max_number_of_sheets_in_cartridge;
	int number_of_sheets;
public:
	//cl_cartridge(cl_base* p_head_object, string s_object_name);    // ������������������� ����������� ������ cl_2
	cl_cartridge(int number_of_sheet,cl_base* p_head_object, string s_object_name);    // ������������������� ����������� ������ cl_2

	void signal_for_cartridge(string& massege);			   // ����� ������� ������ cl_2
	void signal_for_display(string& massege);			   // ����� ����������� ������ cl_2

	void handler(string num_of_list_);
};

#endif 
