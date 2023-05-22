#ifndef _CL_APPLICATION_H
#define _CL_APPLICATION_H

#include "cl_base.h"                           
#include "cl_document.h"                           
#include "cl_PK.h"

class cl_application : public cl_base          			   // ���������� ������ cl_application
{
	//vector <cl_document*> request_queue;
	vector <cl_PK*> PK;
	//cl_document* current_document;
	//string status_of_printer;
	int tact = 1;
	string parametr;
	int number_of_PK_in_system;

public:
	cl_application(cl_base* p_head_object);   			   // ������������������� ����������� ������ cl_application
	void build_tree_objects();				   			   // ����� ������ cl_applicarion, ���������� �� ��������������� �������� ��������
	int exec_app();						       			   // ����� ������ cl_application, ���������� �� ����� �������� �������� �� ����� 
	void signals(string& massege);
	void signal_for_display(string& massege);			   // ����� ������� ������ cl_application
	
	void handler(string massege);			   // ����� ����������� ������ cl_application
	void handler_1(string massege);			   // ����� ����������� ������ cl_application
	void handler_2(string massege);			   // ����� ����������� ������ cl_application
	void handler_3(string massege);			   // ����� ����������� ������ cl_application
	void handler_4(string massege);			   // ����� ����������� ������ cl_application
};

#endif