#include "cl_console.h"

cl_console::cl_console(cl_base* p_head_object, string s_object_name) :cl_base(p_head_object, s_object_name)    // ���������� ������������ ������ �l_4
{

}

void cl_console::signal_for_4_class(string& massege)													  // ���������� ������ ������� ������ cl_4
{
	cout << endl << "Signal from " << absolute_path();											  // ����� ������������ ��������� � ����������� ���� �� �������
	massege = massege + " (class: 4)";															  // ���������� massege �������� ����� ��������� + "(class: 4)"											
}

void cl_console::handler_for_4_class(string massege)													  // ���������� ������ ����������� ������ cl_4
{
	if (get_i_status_ready() == false) return;													  // ��������, ��� ������ �������� ������� "�� �����",���� ��, �� ���������� ������ ������
	cout << endl << "Signal to " << absolute_path() << " Text: " << massege;					  // ����� ������������ ���������, ����������� ���� �� ������� � �������� ��������� massege
}