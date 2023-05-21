#include "cl_PK.h"

cl_PK::cl_PK(cl_base* p_head_object, string s_object_name) :cl_base(p_head_object, s_object_name)    // ���������� ������������ ������ �l_6
{

}

void cl_PK::signal_for_6_class(string& massege)													  // ���������� ������ ������� ������ cl_6
{
	cout << endl << "Signal from " << absolute_path();											  // ����� ������������ ��������� � ����������� ���� �� �������
	massege = massege + " (class: 6)";															  // ���������� massege �������� ����� ��������� + "(class: 6)"
}

void cl_PK::handler_for_6_class(string massege)													  // ���������� ������ ����������� ������ cl_6
{
	if (get_i_status_ready() == false) return;													  // ��������, ��� ������ �������� ������� "�� �����",���� ��, �� ���������� ������ ������
	cout << endl << "Signal to " << absolute_path() << " Text: " << massege;					  // ����� ������������ ���������, ����������� ���� �� ������� � �������� ��������� massege
}