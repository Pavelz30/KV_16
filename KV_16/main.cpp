#include "cl_application.h"
#include "iostream"


int main()										  // ���������� �������� ������� ���������
{
	cl_application ob_cl_system(nullptr);    // �������� ������� ob_cl_application ������ cl_application  � ������� ������������������� ������������, �������� ���������� ���������� ������ ���������
	ob_cl_system.build_tree_objects();       // ����� ������ build_tree_objects ������� ob_cl_application 
	return ob_cl_system.exec_app();		  // ������� ���������� ������ ������ exec_app ������� ob_cl_application 
}