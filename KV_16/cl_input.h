#ifndef __CL_7__H
#define __CL_7__H

#include "cl_base.h"                                      

class cl_input : public cl_base                                // ќбъ€вление класса cl_5
{
public:
	cl_input(cl_base* p_head_object, string s_object_name);    // ѕараметризирвоанный конструктор класса cl_5

	void signal_for_input_to_all(string& massege);			   // ћетод сигнала класса cl_5
	void handler_for_input_to_app(string massege);			   // ћетод обработчика класса cl_5
};

#endif