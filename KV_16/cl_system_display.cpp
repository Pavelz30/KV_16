#include "cl_system_display.h"

cl_system_display::cl_system_display(cl_base* p_head_object, string s_object_name) :cl_base(p_head_object, s_object_name)    // ���������� ������������ ������ �l_3
{

}

void cl_system_display::signal_for_3_class(string& massege)													  // ���������� ������ ������� ������ cl_3
{
	cout << endl << "Signal from " << absolute_path();											  // ����� ������������ ��������� � ����������� ���� �� �������
	massege = massege + " (class: 3)"; 															  // ���������� massege �������� ����� ��������� + "(class: 3)"
}

void cl_system_display::handler_for_3_class(string massege)													  // ���������� ������ ����������� ������ cl_3
{
	if (get_i_status_ready() == false) return;													  // ��������, ��� ������ �������� �������  "�� �����",���� ��, �� ���������� ������ ������
	cout << endl << "Signal to " << absolute_path() << " Text: " << massege;					  // ����� ������������ ���������, ����������� ���� �� ������� � �������� ��������� massege 
}