#ifndef __CL_5__H
#define __CL_5__H

#include "cl_base.h"                                      

class cl_document                         // ���������� ������ cl_5
{
	int number_of_PK_for_document;
	string name_of_document;
	int number_of_sheet;
	int number_of_tact;
public:
	cl_document(int number_of_PK_for_document, string name_of_document,
		int number_of_sheet, int number_of_tact);    // ������������������� ����������� ������ cl_5
	int get_number_of_PK_for_document();
	string get_name_of_document();
	int get_number_of_sheet();
	int get_number_of_tact();
	void set_number_of_sheet(int num);

	/*
	* void signal_for_5_class(string& massege);			   // ����� ������� ������ cl_5
	void handler_for_5_class(string massege);			   // ����� ����������� ������ cl_5
	*/
	
};

#endif
