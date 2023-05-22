#ifndef __CL_8__H
#define __CL_8__H

#include "cl_base.h"                                      

class cl_system_display : public cl_base                                // ќбъ€вление класса cl_3
{
public:
	cl_system_display(cl_base* p_head_object, string s_object_name);    // ѕараметризирвоанный конструктор класса cl_3

	
	//void signal_for_3_class(string& massege);							// ћетод сигнала класса cl_3
	void handler(string massege);							// ћетод обработчика класса cl_3
};

#endif
