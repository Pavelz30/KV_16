#ifndef __CL_3__H
#define __CL_3__H

#include "cl_base.h"                                      

class cl_tray : public cl_base                                // ���������� ������ cl_3
{
	int max_number_of_sheet_in_tray;
	int number_of_sheet_in_tray;
public:
	cl_tray(cl_base* p_head_object, string s_object_name);    // ������������������� ����������� ������ cl_3

	void signal_for_3_class(string& massege);			   // ����� ������� ������ cl_3
	void handler_for_3_class(string massege);			   // ����� ����������� ������ cl_3
};

#endif
