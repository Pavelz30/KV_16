#ifndef __CL_6__H
#define __CL_6__H

#include "cl_base.h"                                      
#include "cl_document.h"

class cl_PK : public cl_base                                // ���������� ������ cl_6
{
	int number_of_PK;
	vector <cl_document*> queue_of_documents;
	bool status_PK;
public:
	cl_PK(cl_base* p_head_object, string s_object_name);    // ������������������� ����������� ������ cl_6

	void signal_for_6_class(string& massege);			   // ����� ������� ������ cl_6
	void handler_for_6_class(string massege);			   // ����� ����������� ������ cl_6
};

#endif
