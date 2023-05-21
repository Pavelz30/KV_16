#ifndef _CL_BASE_H
#define _CL_BASE_H

#include <string> 									  			 								// ����������� ���������� ��� ������ �� ��������
#include <vector>  									  			 								// ����������� ���������� ��� ����� � ���������
#include <iostream>
using namespace std;								  			 								// ����������� ������������ ���� std

#define SIGNAL_D(signal_f) (TYPE_SIGNAL)(&signal_f);			 								// ������������������� ���������������� ������������� ��� ���������� ��������� �� ����� ������� 
#define HANDLER_D(handler_f) (TYPE_HANDLER)(&handler_f);		 								// ������������������� ���������������� ������������� ��� ���������� ��������� �� ����� �����������

class cl_base;													 								// �������������� ������ cl_base

typedef void (cl_base::* TYPE_SIGNAL) (string& massege);		 								// ����������� ������ ���� ������, �������� ������ ���� - TYPE_SIGNAL, ��� ����������� ��������� �� ����� ������� 
typedef void (cl_base::* TYPE_HANDLER) (string massege);		 								// ����������� ������ ���� ������, �������� ������ ���� - TYPE_HANDLER, ��� ����������� ��������� �� ����� �����������

struct o_sh														 								// ���������� ��������� o_sh
{
	TYPE_SIGNAL p_signal;										 								// ���� p_signal ���� ��������� �� ����� ������� ��� �������� �������� �� ����� �������
	cl_base* p_target;																			// ���� p_target ���� �������� �� ������ �������� ������ ��� �������� �������� �� ������� �������
	TYPE_HANDLER p_handler;																		// ���� p_handler ���� ��������� �� ����� ����������� �������� ������� ��� �������� �������� �� ����� ����������� �������� �������
};

class cl_base                                         			 								// ���������� ������ cl_base                
{
	string s_object_name;                             			 								// ���������� ���������� ���� s_object_name 
	cl_base* p_head_object;							  			 								// ���������� ���� ���� ��������� p_head_object �� ������ �������� ������ 
	vector <cl_base*> p_sub_objects;				 		 	 								// ���������� ������� p_sub_objects ���� ��������� �� ������ �������� ������

	vector <o_sh*> connects;																	// ������ connects ���� ��������� �� ������ ��������� o_sh, ��� ������� ������ ������ - ����������
	bool i_status = false;							  			 								// ������������� ���� ����������� ���� ��������� false
	int i_class;												 								// ���������� �������������� ���� i_class ��� �������� ������ ������, ������ �������� ��� ������
public:
	cl_base(cl_base* p_head_object,
		string s_object_name = "Base_object");            		   	 								// ������������������� ����������� �������� ������ cl_base
	~cl_base();										  			 								// ���������� ������ cl_base
	bool set_name(string s_new_name);				  											// ����� ������ cl_base, ���������� �� �������������� ����� �������
	string get_name();								  											// ����� ������ cl_base, ���������� �� ��������� ����� �������
	cl_base* get_head();							  											// ����� ������ cl_base, ���������� �� ��������� ��������� �� �������� ������� �������
	cl_base* get_sub_object(string s_object_name);    											// ����� ������ cl_base, ���������� �� ������� ��������� �� ����������� ������ �� ������� �� ��� ����� (���� �� ��� ����)

	cl_base* find_object_from_current(string s_object_name);    								// ����� ������ cl_base, ���������� �� ����� ������� �� ��� ����� �� �������� �� �����
	cl_base* find_object_from_root(string s_object_name);										// ����� ������ cl_base, ���������� �� ����� ������� �� ���� ������
	void print_tree_from_current(int num);														// ����� ������ cl_base, ���������� �� ����� ������ �������� �� �������� �������
	void print_tree_from_current_readiness(int num);											// ����� ������ cl_base, ���������� �� ����� ������ �� �������� ����������
	void object_readiness(int i_status);														// ����� ������ cl_base, ���������� �� ��������� ���������� �������

	bool head_name_redefinition(cl_base* p_new_head);											// ����� ������ cl_base, ���������� �� ��������� ��������� ������� ��� ��������
	void delete_object_from_name(string sub_name_for_delete);   								// ����� ������ cl_base, ���������� �� �������� ������������ ������� � ��������
	cl_base* get_pointer_of_object_from_path(string path);	   									// ����� ������ cl_base, ���������� �� ����� ������ ������� � ��������

	void set_connection(TYPE_SIGNAL p_signal, cl_base* p_target, TYPE_HANDLER p_handler);		// ����� ������ cl_base, ���������� �� ������������ ����� ����� �������� �������� ������� � ������������ �������� �������
	void delete_connection(TYPE_SIGNAL p_signal, cl_base* p_target, TYPE_HANDLER p_handler);    // ����� ������ cl_base, ���������� �� �������� (�������) ����� ����� �������� �������� ������� � ������������ �������� �������.
	void emit_signal(TYPE_SIGNAL p_signal, string s_massege);									// ����� ������ cl_base, ���������� �� ������ ������� �� �������� ������� � ��������� ��������� ����������.
	string absolute_path();																		// ����� ������ cl_base, ���������� �� ��������� ����������� ���� �� �������
	void i_status_ready_for_all();																// ����� ������ cl_base, ���������� �� ��������� ������� ���������� ������ ������� � ���� "�����"
	void set_i_status_ready(bool i_status_ready);												// ����� ������ cl_base, ���������� �� ��������� ������� ���������� �������
	int get_i_status_ready();																	// ����� ������ cl_base, ���������� �� ��������� ������� ���������� �������

	TYPE_SIGNAL switch_signal(int i_class);														// ����� ������ cl_base, ���������� �� ���������� ������ ������� ��� ���������� ������
	TYPE_HANDLER switch_handler(int i_class);													// ����� ������ cl_base, ���������� �� ���������� ������ ����������� ��� ���������� ������
	int get_name_of_class();																	// ����� ������ cl_base, ���������� �� ��������� ������ ������, ������ �������� ��� ������ 
	void set_name_of_class(int num);															// ����� ������ cl_base, ���������� �� ��������� ������ ������, ������ �������� ��� ������
};

#endif