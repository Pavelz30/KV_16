#ifndef __CL_4__H
#define __CL_4__H

#include "cl_base.h"                                      

class cl_console : public cl_base                                // ���������� ������ cl_4
{
public:
	cl_console(cl_base* p_head_object, string s_object_name);    // ������������������� ����������� ������ cl_4

	void signal_for_4_class(string& massege);					// ����� ������� ������ cl_4
	void handler_for_4_class(string massege);					// ����� ����������� ������ cl_4
};

#endif
