#include "cl_application.h"	                                                     									  // ����������� ������������� ����� cl_application
#include "cl_base.h"                                                            									  // ����������� ������������� ����� cl_base
#include "cl_cartridge.h"                                                              										  // ����������� ������������� ����� cl_2
#include "cl_tray.h"																									  // ����������� ������������� ����� cl_3
#include "cl_console.h"																									  // ����������� ������������� ����� cl_4
#include "cl_document.h"																									  // ����������� ������������� ����� cl_5
#include "cl_PK.h"																									  // ����������� ������������� ����� cl_6
#include "cl_input.h"																									  // ����������� ������������� ����� cl_6
#include <iostream>                                                              									  // ����������� ���������� ������������ ������ �����/������																										  // ����������� ���������� ��� ������ � ��������������, ������� �������� �� �������� [�������� - ����] 
#include "cl_system_display.h"
cl_application::cl_application(cl_base* p_head_object) :cl_base(p_head_object)    									  // ���������� ������������ ������ cl_application
{

}

int cl_application::exec_app()                                                   									  // ���������� ������ exec_app ������ cl_application
{
	i_status_ready_for_all();																						  // ����� ������ ��� ��������� ���� ��������
	string use_func;																								  // ���������� ����������
	cl_base* p_obj;																									  // ���������� ��������� �� ������ �������� ������
	cl_base* p_target;																								  // ���������� ��������� �� ������ �������� ������

	cout << "Object tree";														            						  // ����� �� ����� ��������� "Object tree"
	cout << endl << get_name();													 									  // ������� �� ����� ������ � ����� ����� �������� �������
	print_tree_from_current(4);																						  // ����� ������ print_tree_from_current ��� ������ ������ ��������

	while (true)																							  			  // ���� ��� ����� c ���������� �������
	{
		cin >> use_func;																							  // ���� � ���������� �������

		if (use_func == "END") break;																				  // �������� ����� ��������

		if (use_func == "EMIT")																						  // �������� ����� ��������
		{
			string path, massege;																					  // ���������� ����������

			cin >> path;																							  // ���� � ���������� �������� ��������� �������
			getline(cin, massege);																					  // ���� � ���������� ������
			p_obj = get_pointer_of_object_from_path(path);															  // ���������� �������� ��������� �� ������ � ������ �������� ����� � ������� ������

			if (p_obj != nullptr)																					  // ��������, ��� �������� ������ ����������
			{
				p_obj->emit_signal(switch_signal(p_obj->get_name_of_class()), massege);								  // ����� ������ ������ �������
				continue;																							  // ������� ��������
			}
			else
			{
				cout << endl << "Object " << path << " not found";													  // ����� ���������
				continue;																							  // ������� ��������
			}
		}

		if (use_func == "SET_CONNECT")																				  // �������� ����� ��������
		{
			string signal_path, handler_path;																		  // ���������� ����������
			cin >> signal_path >> handler_path;																		  // ���� � ���������� ���� �� ����������� ������� � �� ������� �����������
			p_obj = get_pointer_of_object_from_path(signal_path);													  // ���������� �������� ��������� �� ���������� ������ � ������ �������� ����� � ������� ������
			p_target = get_pointer_of_object_from_path(handler_path);												  // ���������� �������� ��������� �� ������� ������ � ������ �������� ����� � ������� ������

			if (p_obj != nullptr && p_target != nullptr)															  // ���������� ������ � ������� ����� ���� �������									
			{
				p_obj->set_connection(switch_signal(p_obj->get_name_of_class()), p_target, switch_handler
				(p_target->get_name_of_class()));			  // ����� ������ ������������ ����� ����� �������� �������� ������� � ������������ �������� �������.
				continue;
			}
			else if (p_obj == nullptr)																				  // ���������� ������ �� ��� ������
			{
				cout << endl << "Object " << signal_path << " not found";											  // ����� ���������
				continue;																							  // ������� ��������
			}
			else if (p_target == nullptr)																			  // ������� ������ �� ��� ������
			{
				cout << endl << "Handler object " << handler_path << " not found";									  // ����� ���������
				continue;																							  // ������� ��������
			}
		}

		if (use_func == "DELETE_CONNECT")																			  // �������� ����� ��������
		{
			string signal_path, handler_path;																		  // ���������� ����������
			cin >> signal_path >> handler_path;																		  // ���� � ���������� ���� �� ����������� ������� � �� ������� �����������
			p_obj = get_pointer_of_object_from_path(signal_path);													  // ���������� �������� ��������� �� ���������� ������ � ������ �������� ����� � ������� ������
			p_target = get_pointer_of_object_from_path(handler_path);												  // ���������� �������� ��������� �� ������� ������ � ������ �������� ����� � ������� ������

			if (p_obj != nullptr && p_target != nullptr)															  // ���������� ������ � ������� ����� ���� �������
			{
				p_obj->delete_connection(switch_signal(p_obj->get_name_of_class()), p_target,
					switch_handler(p_target->get_name_of_class()));													  // ����� ������ �������� (�������) ����� ����� �������� �������� ������� � ������������ �������� �������
				continue;
			}
			else if (p_obj == nullptr)																				  // ���������� ������ �� ��� ������
			{
				cout << endl << "Object " << signal_path << " not found";											  // ����� ���������
				continue;																							  // ������� ��������
			}
			else if (p_target == nullptr)																			  // ������� ������ �� ��� ������
			{
				cout << endl << "Handler object " << handler_path << " not found";									  // ����� ���������
				continue;																							  // ������� ��������
			}
		}

		if (use_func == "SET_CONDITION")																			  // �������� ����� ��������
		{
			string signal_path;																						  // ���������� ����������
			int i_status_ready;																						  // ���������� ����������
			cin >> signal_path >> i_status_ready;																	  // ���� �������� ���������� � ����������
			p_obj = get_pointer_of_object_from_path(signal_path);													  // ���������� �������� ��������� �� ���������� ������ � ������ �������� ����� � ������� ������

			if (p_obj != nullptr)																					  // ���������� ������ ��� ������
			{
				p_obj->set_i_status_ready(i_status_ready);															  // ����� ������ ��������� ������ ������� ��� �������
				continue;																							  // ������� ��������
			}
			else
			{
				cout << endl << "Object " << signal_path << " not found";											  // ����� ���������
				continue;																							  // ������� ��������
			}
		}
	}
	return 0;																										  // ������� ����
}

void cl_application::build_tree_objects()										 									  // ���������� ������ build_tree_objects ������ cl_application
{
	cl_base* p_sub = this;
	string msg;

	set_name("System");

	p_sub = new cl_input(this, "Input");
	p_sub = new cl_console(this, "Console");
	p_sub = new cl_tray(get_sub_object("Console"), "Tary");
	p_sub = new cl_cartridge(get_sub_object("Console"), "Cartridge");
	this->current_document = nullptr;
	p_sub = new cl_system_display(this, "Display");
	i_status_ready_for_all();
	
	string parametr = "";
	this->set_connection(switch_signal(1), get_sub_object("Input"), switch_handler(7));
	get_sub_object("Input")->set_connection(switch_signal(7), this, switch_handler(1));
	
	while (cl_application::parametr != "End of settings")
		emit_signal(switch_signal(1), msg);

	this->set_connection(switch_signal(1), get_sub_object("Console"), switch_handler(4));
	this->set_connection(switch_signal(1), get_sub_object("Display"), switch_handler(8));
}


void cl_application::signal_for_app_to_input(string& massege)															  // ���������� ������ ������� ������ cl_application
{
	cout << endl << "Signal from " << absolute_path();																  // ����� ������������ ��������� � ����������� ���� �� �������																			  // ���������� massege �������� ����� ��������� + "(class: 1)"
}

void cl_application::handler_for_app_to_input(string massege)															  // ���������� ������ ����������� ������ cl_application
{
	if (massege == "End of settings")
		cl_application::parametr = "End of settings";
	
	else if (massege.find(' ') == string::npos)
	{
		number_of_PK_in_system = stoi(massege);
		for (int i = 0; i < number_of_PK_in_system; i++)
		{
			PK.push_back(new cl_PK(this, to_string(i + 1)));
			set_connection(switch_signal(1), get_sub_object(to_string(i + 1)), switch_handler(6));
		}	
	}
}