#include "cl_document.h"

cl_document::cl_document(int number_of_PK_for_document, string name_of_document,
	int number_of_sheet, int number_of_tact)
{
	this->number_of_PK_for_document = number_of_PK_for_document;
	this->name_of_document = name_of_document;
	this->number_of_sheet = number_of_sheet;
	this->number_of_tact = number_of_tact;
}


int cl_document::get_number_of_PK_for_document()
{
	return this->number_of_PK_for_document;
}


string cl_document::get_name_of_document()
{
	return this->name_of_document;
}


int cl_document::get_number_of_sheet()
{
	return this->number_of_sheet;
}


int cl_document::get_number_of_tact()
{
	return this->number_of_tact;
}


void cl_document::set_number_of_sheet(int num)
{
	this->number_of_sheet = num;
}


/*
* void cl_document::signal_for_5_class(string& massege)													  // ���������� ������ ������� ������ cl_5
{
	cout << endl << "Signal from " << absolute_path();											  // ����� ������������ ��������� � ����������� ���� �� �������
	massege = massege + " (class: 5)";														 	  // ���������� massege �������� ����� ��������� + "(class: 5)
}

void cl_document::handler_for_5_class(string massege)													  // ���������� ������ ����������� ������ cl_5
{
	if (get_i_status_ready() == false) return;													  // ��������, ��� ������ �������� ������� "�� �����",���� ��, �� ���������� ������ ������
	cout << endl << "Signal to " << absolute_path() << " Text: " << massege;					  // ����� ������������ ���������, ����������� ���� �� ������� � �������� ��������� massege
}
*/
