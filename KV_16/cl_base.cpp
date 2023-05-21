#include "cl_base.h"														       // ����������� ������������� ����� cl_base
#include <iostream>															       // ����������� ���������� ������������ ������ �����/������ 
#include <queue>															       // ����������� ���������� ��� ������ � ��������
#include <sstream>																   // ����������� ���������� ��� ������ � �������� ������
#include "cl_cartridge.h"																   // ������������ ������������� ������ cl_2
#include "cl_tray.h"																   // ������������ ������������� ������ cl_3
#include "cl_console.h"																   // ������������ ������������� ������ cl_4
#include "cl_document.h"																   // ������������ ������������� ������ cl_5
#include "cl_PK.h"																   // ������������ ������������� ������ cl_6
#include "cl_application.h"														   // ������������ ������������� ������ cl_application
#include "cl_input.h"
#include "cl_system_display.h"
using namespace std;														       // ����������� ������������ ���� std

cl_base::cl_base(cl_base* p_head_object, string s_object_name)                     // ���������� ������������ ������ cl_base
{
	this->p_head_object = p_head_object;                                           // ���������� ���� p_head_object �������� ��������� p_head_object
	this->s_object_name = s_object_name;	                                       // ���������� ���� s_object_name �������� ��������� s_object_name

	if (p_head_object != nullptr) 	                                               // �������� ������������� ��������� ������� 
		p_head_object->p_sub_objects.push_back(this);			                   // ���������� ��������� �� ������ � ����� ������� ����������� �������� ��������� ������� p_head_object
}


cl_base::~cl_base()                                                                // ���������� ����������� ������ cl_base
{
	for (int i = 0; i < p_sub_objects.size(); i++)                                 // ���� ��� ������� �� ��������� �������
		delete (p_sub_objects[i]);								                   // �������� ���������� ��� ������ ������������ ������ 
}


bool cl_base::set_name(string s_new_name)                                          // ���������� ������ set_name ������ cl_base
{
	if (p_head_object != nullptr)								                   // �������� �� ������������� ��������� ������� 
	{
		for (int i = 0; i < p_head_object->p_sub_objects.size(); i++)              // ���� ��� ������� �� ��������� �������
		{
			if (p_head_object->p_sub_objects[i]->get_name() == get_name())         // �������� �� ������������ ����� ������� � ������� ��� ��������� �������
				return false;												       // ������� false
		}
	}
	this->s_object_name = s_new_name;										       // ���������� ���� s_object_name ��������� s_new_name (�������������� �����)
	return true;															       // ������� true 
}


string cl_base::get_name()                                                         // ���������� ������ get_name ������ cl_base
{
	return this->s_object_name;                                                    // ������� ������������ �������
}


cl_base* cl_base::get_head()                                                       // ���������� ������ get_head ������ cl_base  
{
	return p_head_object;                                                          // ������� ��������� �� �������� ������
}


cl_base* cl_base::get_sub_object(string s_object_name)                             // ���������� ������ get_sub_object ������ cl_base 
{
	for (int i = 0; i < p_sub_objects.size(); i++)                                 // ���� ��� ������� �� ��������� �������
	{
		if (p_sub_objects[i]->get_name() == s_object_name)			               // ������� ������������� ������� � ������� ������������� s_object_name � ������� 
			return p_sub_objects[i];										       // ������� ��������� �� ��������� ������
	}
	return nullptr;															       // ������� �������� ��������� 
}


cl_base* cl_base::find_object_from_current(string s_object_name)			       // ���������� ������ find_object_from_current ������ cl_base
{
	queue <cl_base*> q;														       // ���������� �������� ���� ��������� �� ������ �������� ������
	cl_base* p_found = nullptr;												       // ������������� ��������� �� ������ ������ cl_base p_found ��������� �������� ���������

	q.push(this);															       // ���������� ��������� �� ������� ������ � �������

	while (!q.empty())														       // ��������, ����� �� �������
	{
		if (q.front()->get_name() == s_object_name)							       // ��������, ��� ��� ������� ������� � ������� ���� �������
		{
			if (p_found == nullptr)											       // ��������, ��� ������ ��� �� ��� ������
				p_found = q.front();										       // ���������� ��������� �� ������ ������ � ������� ��������� p_found
			else															       // �����
				return nullptr;												       // ������� �������� ���������
		}

		for (int i = 0; i < q.front()->p_sub_objects.size(); i++)				   // ���� ��� ������� �� ����������� ��������� ������� �������� � ������
			q.push(q.front()->p_sub_objects[i]);								   // ���������� ��������� �� ��������� ����������� ������ ������� ������� � �������  

		q.pop();															       // �������� ������� ������� � �������
	}
	return p_found;														  		   // ������� ���������� ��������� �� ������
}


cl_base* cl_base::find_object_from_root(string s_object_name)				       // ���������� ������ find_object_from_root ������ cl_base
{
	cl_base* p_root = this;													       // ������������� ��������� p_root �� ������ �������� ������ ��������� ��������� �� ������� ������

	while (p_root->get_head() != nullptr)									       // ���� ��� ������ ��������� �������
		p_root = p_root->get_head();										       // ���������� ��������� p_root �������� ��� ��������� ������� 

	return p_root->find_object_from_current(s_object_name);					       // ������� ���������� ������ ������ find_object_from_current  ��� ������� c ���������� �� ���� p_root
}


void cl_base::print_tree_from_current(int num)								       // ���������� ������ find_object_from_root ������ cl_base
{
	if (p_sub_objects.size() != 0)											 	   // ��������, ��� � �������� ������� ���� �����������
	{
		for (int i = 0; i < p_sub_objects.size(); i++)							   // ���� ��� ������� �� ����������� ��������
		{
			cout << endl << string(num, ' ') << p_sub_objects[i]->get_name();	   // ����� �������� ������� � ������ ��������
			p_sub_objects[i]->print_tree_from_current(num + 4);					   // ����������� ����� ����� �� ������ ��� ������� ����������� ������� � ��������� ������
		}
	}
}


void cl_base::object_readiness(int i_status)								 	   // ���������� ������ object_readiness ������ cl_base
{
	bool flag = false;														       // ������������� ��������� flag ����������� ���� ��������� false
	cl_base* search_obj = this;												       // ������������� ��������� �� ������ �������� ������ �������� ��������� �� ������� ������
	queue <cl_base*> q;														       // ���������� ������� ���� ��������� �� ������ �������� ������

	if (i_status != 0)															   // �������� i_status ������� �� ����
	{
		while (search_obj->get_head() != nullptr)			       				   // ���� ��� ��������, ��� ��� ����������� �� ����� ������� ��������
		{
			if ((search_obj->get_head())->i_status == 0)					 	   // ���������, ��� ���� i_status ��������� ������� ������� search_obj ����� �������� 0 
			{
				flag = true;													   // ���������� ���������� flag �������� true
				break;															   // ����� �� �����
			}
			search_obj = search_obj->get_head();									   // ���������� ��������� search_obj �������� ��������� �� ��� �������� ������
		}
		if (flag == false) this->i_status = i_status;							   // ��������, ��� �� ���� �������� ������������ ������� � ���������� ���� i_status �������� ������� �������� �������� i_status
	}
	else																		   // �����
	{
		q.push(this);														 	   // ���������� � ������� ��������� �� ������� ������

		while (!q.empty())													       // �������� �� ������� �������
		{
			q.front()->i_status = i_status;									 	   // ����������� ���� i_status ������� ������� � ������� �������� �������� i_status

			for (int i = 0; i < q.front()->p_sub_objects.size(); i++)			   // ���� ��� ������� �� ����������� ��������� ������� �������� � ������
				q.push(q.front()->p_sub_objects[i]);							   // ���������� ��������� �� ��������� ����������� ������ ������� ������� � �������

			q.pop();														       // �������� ������� ������� �� �������
		}
	}
}

void cl_base::print_tree_from_current_readiness(int num)					       // ���������� print_tree_from_current_readiness ������ cl_base
{

	if (p_sub_objects.size() != 0)											       // ��������, ��� � �������� ������� ���� �����������
	{
		for (int i = 0; i < p_sub_objects.size(); i++)							   // ���� ��� ������� �� ����������� ��������
		{
			cout << endl << string(num, ' ') << p_sub_objects[i]->get_name();	   // ����� �������� ������� � ������ ��������

			if (p_sub_objects[i]->i_status == true)								   // ��������, ��� ������ ������������ ������� �� ����� ����
				cout << " is ready";										       // ����� ��������� �� ����� " is ready"
			else															       // �����
				cout << " is not ready";									       // ����� ��������� �� ����� " is not ready"

			p_sub_objects[i]->print_tree_from_current_readiness(num + 4);		   // ����������� ����� ����� �� ������ ��� ������� ����������� ������� � ���������� �������
		}
	}
}


bool cl_base::head_name_redefinition(cl_base* p_new_head)						   // ���������� ������ head_name_refefinition ������ cl_base
{
	if (get_head() != nullptr)													   // ��������, ��� �������� ������ ��� �������� ����������
	{
		if (p_new_head->get_sub_object(get_name()) == nullptr)					   // ��������, ��� � ������ ��������� ������� ��� ������������ ������� � ������, ��� � ��������
		{
			cl_base* current_object = p_new_head;								   // ������������� ���������������� ��������� ��������� ��������� �� ����� ��������� ������ 

			while (current_object != nullptr)									   // ���� ��� ������ ���������
			{
				if (current_object == this)										   // ��������, ��� ����� �������� ������ ��������� � ����� ��������
					return false;												   // ������� false - �������������� �� ���������
				current_object = current_object->get_head();					   					// ����������� ���������������� ��������� �������� ��������� �� ��� �������� ������
			}

			for (int i = 0; i < get_head()->p_sub_objects.size(); i++)		       					// ���� ��� ������� �� ����������� �������� ��� ��������� ��������
				if (get_head()->p_sub_objects[i] == this)					       					// ��������, ��� ����������� ������ �������� �������
					get_head()->p_sub_objects.erase(get_head()->
						p_sub_objects.begin() + i);								       					// �������� ���������� ������� �� ����������� ��� ��������� �������� �������

			get_head() == p_new_head; 										       					// ���������� ��������� �������� ������� �������� ��������� ������ ���������
			p_new_head->p_sub_objects.push_back(this);						       					// ���������� � ������ ����������� �������� ������ �������, �������� �������
			return true;													   	   					// ������� true - �������������� ��������� ������� ������ �������
		}
	}
	return false;																   					// ������� false - �������������� �� ���������
}

void cl_base::delete_object_from_name(string sub_name_for_delete)				   					// ���������� ������ delete_object_from_name ������ cl_base
{
	for (int i = 0; i < p_sub_objects.size(); i++)								   					// ���� ��� ������� �� ����������� �������� �������� �������
		if (sub_name_for_delete == p_sub_objects[i]->get_name())					   					// ��������, ��� ��� ���������� ������� ��������� � ������� ����������� 
			p_sub_objects.erase(p_sub_objects.begin() + i);						   					// �������� ������������ ������� �� ������� ����������� �������� ��� ��������

	delete (get_sub_object(sub_name_for_delete));								   					// �������� �������
}


cl_base* cl_base::get_pointer_of_object_from_path(string path)					   					// ���������� ������ get_pointer_of_object_from_path  ������ cl_base
{
	if (path.empty() == true) return nullptr;									   					// ��������, ��� ���� ������, ���� �� ������� �������� ���������

	if (path == "/")															   					// �������� ��� ���� ����� "/"
	{
		cl_base* p_root = this;													   					// ������������� ���������������� ��������� �� ������ �������� ������ �������� ��������� �� ������� ������

		while (p_root->get_head() != nullptr)									   					// ���� ��� ������ ��������� �������
			p_root = p_root->get_head();										  					// ���������� ���������������� ��������� �������� ��� ���������
		return p_root;															   					// ������� ��������������� ���������, ����������� �� �������� ������
	}

	if (path == ".") return this; 												   					// �������� ��� ���� ����� ".", ���� ��, �� ������� ���������� �� ������� ������

	string::size_type pos = path.find("//");									   					// ������������� ����������� ������������� ���������� pos ����������� ������ ������ find, ��� ������ "//" � ����
	if (pos != string::npos)														   					// ��������, ��� ������� ���� �������
	{
		string search_object_name = path.erase(0, 2);							   					// ������������� ��������� ���������� �������� ���� ��� ������ ���� ��������
		return find_object_from_root(search_object_name);						   					// ������� ���������� ������ ������ ��� ������ ������� �� ����� ������
	}

	pos = path.find(".");														   					// ���������� ���������� ������ ������ find, ��� ������ ������� "." � ����
	if (pos != string::npos)														   					// ��������, ��� ������ ��� ������
	{
		string search_object_name = path.erase(0, 1);							   					// ������������� ��������� ���������� �������� ���� ��� ������� �������
		return find_object_from_current(search_object_name);					   					// ������� ���������� ������ ������ ��� ������ ������� �� �����
	}


	vector <string> path_for_object;											   					// ���������� ������� path_for_objet ���������� ����
	stringstream ss(path);														   					// �������� ������� ss ������ stringstream � �������� ��� � ���������� ���� � �������
	string item;																   					// ����������� ��������� ���������� item, ��� �������� � ��� ������ ����
	cl_base* p_root = this;														   					// ������������� ��������� p_root �� ������ �������� ������ ��������� ��������� �� ������� ������

	while (getline(ss, item, '/'))													   					// ���� ��� ���������� � ������ path_for_objet ������ ����, � ������������ "/",����� getlibe ����������� ��������� item �������� ���� �� ������� "/"
		path_for_object.push_back(item);										   					// ��������� ����� ���� � ������ 

	if (path_for_object[0] == "")												   					// ��������, ��� ������ ������� ������� ����� ������ ������ (���� ������, �� ��� �������, ��� ���� ��������� �� "/" � ����� ����������� �� ���������)
	{
		while (p_root->get_head() != nullptr)									   					// ���� ��� ������ ��������� 
			p_root = p_root->get_head();										   					// ���������� ��������� p_root �������� �������� �� ��� ��������
		path_for_object.erase(path_for_object.begin());							   					// �������� ������� �������� �� ������� ����,(�������� ������ ������)
	}


	queue <cl_base*> q;															   					// ���������� ������� q ���� �������� �� ������ �������� ������
	int pathIndex = 0;															   					// ������������� ������������� ���������� pathIndex ��������� 0,	�������� � ���� ������ ��� ������� � ������� ����

	for (int i = 0; i < p_root->p_sub_objects.size(); i++)						   					// ���� ��� ������� �� ����������� �������� ������� p_root 
		q.push(p_root->p_sub_objects[i]);										   					// ���������� ����������� �������� p_root � �������

	while (!q.empty())															   					// ��������, ��� ������� �� ������
	{
		cl_base* p_found = q.front();											   					// ������������� ��������� �� ������ �������� ������ �������� ��������� �� ������ ������ � �������
		q.pop();																   					// �������� ������� ������� �� �������

		if (p_found->get_name() == path_for_object[pathIndex])					   					// ��������, ��� ��� �������, �� ������� ��������� p_found ����� �������� ������� ���� ��� �������� pathIndex
		{
			while (!q.empty()) q.pop();											   					// �������� ���� �������, �������� ����� ���������� ���������

			if (pathIndex == path_for_object.size() - 1) return p_found;			  					// ��������, �������� �������� ������� ����� ������� �������, ������������ ���� �� ������� , ���� ��, �� ������� p_found 
			pathIndex++;														   					// ���������� ������� pathIndex �� 1

			for (int i = 0; i < p_found->p_sub_objects.size(); i++)				  					// ���� ��� ���������� ���� ����������� �������� ������� p_found
				q.push(p_found->p_sub_objects[i]);								   					// ���������� ����������� ������������ �������� p_found � ������� q
		}
	}
	return nullptr;																   					// ������� �������� ��������� - ������, ��� ������ ����� �� �������
}

void cl_base::set_connection(TYPE_SIGNAL p_signal, cl_base* p_target, TYPE_HANDLER p_handler)		// ���������� ������ set_connection
{
	o_sh* p_value;																					// ���������� ��������� �� ������ ��������� o_sh

	for (int i = 0; i < connects.size(); i++)														// ���� ��� ������� �� ��������, ��������� � �������
	{
		if (connects[i]->p_signal == p_signal &&
			connects[i]->p_target == p_target &&
			connects[i]->p_handler == p_handler)													// ��������, ��� ��� ������������ �������
			return;																					// ���������� ������ ������
	}

	p_value = new o_sh();																			// ���������� �������� p_value ��������� �� ��������� � ������� ��������� new ������ ��������� o_sh

	p_value->p_signal = p_signal;																	// ���������� �������� �������� ������� �������� ������������� ���������
	p_value->p_target = p_target;																	// ���������� �������� �������� ������� �������� ������������� ���������
	p_value->p_handler = p_handler;																	// ���������� �������� �������� ������� �������� ������������� ���������

	connects.push_back(p_value);																 	// ���������� ���������� ������� � ������ ����������
}

void cl_base::delete_connection(TYPE_SIGNAL p_signal, cl_base* p_target, TYPE_HANDLER p_handler)	// ���������� ������ delete_connection
{
	for (int i = 0; i < connects.size(); i++)														// ���� ��� ������� �� ��������, ��������� � �������
	{
		if (connects[i]->p_signal == p_signal &&
			connects[i]->p_target == p_target &&
			connects[i]->p_handler == p_handler)													// ��������, ��� ������� ������ ������ � ������� ��������
			connects.erase(connects.begin() + i);													// �������� ���������� �������
	}
}

void cl_base::emit_signal(TYPE_SIGNAL p_signal, string s_message)									// ���������� ������ emit_signal
{
	if (get_i_status_ready() == false) return;														// ��������, ��� ������ �������� ������� "�� �����", ���� ��, �� ����� �� ������

	(this->*p_signal)(s_message);																	// ����� ������  p_signal �������� ������� � ��������� ��� ��������� s_message

	for (int i = 0; i < connects.size(); i++)														// ���� ��� ������� �� ��������, ��������� � �������
	{
		if (connects[i]->p_signal == p_signal)														// ��������, ��� ��������� ������ ��������� � �������� ������������ �������
		{
			cl_base* p_target = connects[i]->p_target;												// ������������� ��������� �� ������ �������� ������ �������� ���� p_target ����������� ������������ �������
			TYPE_HANDLER p_handler = connects[i]->p_handler;										// ������������� ��������� �� ����� ����������� �������� ���� p_target ����������� ������������ �������

			(p_target->*p_handler)(s_message);														// ����� ������ ����������� p_handler ������� p_target (��������� �������) � ��������� ��� ��������� s_message
		}
	}
}


string cl_base::absolute_path()																		// ���������� ������ absolute_path
{
	string absolute_path = "";																		// ������������� ��������� ���������� ��������� ������ ������
	cl_base* current_object = this;																	// ������������� �������� �� ������ �������� ������ �������� ��������� �� ������� ������

	if (get_head() == nullptr) return "/";															// ��������, ��� �������� ��� �������� �� ����������, ������� ����

	while (current_object->get_head() != nullptr)													// ���� ��� �������� �� ������ �� ���������
	{
		absolute_path = "/" + current_object->get_name() + absolute_path;							// ��������� ���������� ��� �������� ���� �� ������� 
		current_object = current_object->get_head();												// ���������� ���������� �������� �������� �� �� ��������
	}
	return absolute_path;																			// ������� ����������� ���� �� �������
}


void cl_base::i_status_ready_for_all()																// ���������� ������ i_status_ready_for_all
{
	i_status = true;																				// ���������� ���� i_status �������� ������ �������� true. �.� ��������� �������

	for (int i = 0; i < p_sub_objects.size(); i++)													// ���� ��� ������� �� ����������� �������� �������
		p_sub_objects[i]->i_status_ready_for_all();													// ����� ��� ������� ������������ �������� ������ 
}


void cl_base::set_i_status_ready(bool i_status_ready)												// ���������� ������ set_i_status_ready
{
	this->i_status = i_status_ready;																// ����������� ���� i_status �������� ������������� ���������

	if (i_status_ready == false)																	// �������� �������� "�� �����"
		for (int i = 0; i < p_sub_objects.size(); i++)												// ���� ��� ������� �� ����������� �������� �������
			p_sub_objects[i]->set_i_status_ready(i_status_ready);									// ����� �������� ������ ��� ������ ������������� �������� ������
}


int cl_base::get_i_status_ready()																	// ���������� ������ get_i_status_ready
{
	return i_status;																				// ������� �������� ���� i_status;
}

TYPE_SIGNAL cl_base::switch_signal(int i_class)														// ���������� ������ switch_signal
{
	TYPE_SIGNAL signal_f = nullptr;																	// ������������� �������� �� ����� ������� ��������� �������� ��������� 

	switch (i_class)																					// ������������� �������
	{
	case 1:																							// �������� ���������� i_class ����� 1
		signal_f = SIGNAL_D(cl_application::signal_for_app_to_input);								// ���������� ��������� signal_f ���������� ������ ������� SIGNAL_D � ���������� signal_for_1_class ������ cl_1
		break;
	case 2:																							// �������� ���������� i_class ����� 2
		signal_f = SIGNAL_D(cl_cartridge::signal_for_2_class);											// ���������� ��������� signal_f ���������� ������ ������� SIGNAL_D � ���������� signal_for_2_class ������ cl_2
		break;
	case 3:																							// �������� ���������� i_class ����� 3
		signal_f = SIGNAL_D(cl_tray::signal_for_3_class);											// ���������� ��������� signal_f ���������� ������ ������� SIGNAL_D � ���������� signal_for_3_class ������ cl_3
		break;
	case 4:																							// �������� ���������� i_class ����� 4
		signal_f = SIGNAL_D(cl_console::signal_for_4_class);											// ���������� ��������� signal_f ���������� ������ ������� SIGNAL_D � ���������� signal_for_4_class ������ cl_4
		break;
	case 5:																							// �������� ���������� i_class ����� 5
		signal_f = SIGNAL_D(cl_document::signal_for_5_class);											// ���������� ��������� signal_f ���������� ������ ������� SIGNAL_D � ���������� signal_for_5_class ������ cl_5
		break;
	case 6:																							// �������� ���������� i_class ����� 6
		signal_f = SIGNAL_D(cl_PK::signal_for_6_class);											// ���������� ��������� signal_f ���������� ������ ������� SIGNAL_D � ���������� signal_for_6_class ������ cl_6
		break;
	case 7:
		signal_f = SIGNAL_D(cl_input::signal_for_input_to_all);											// ���������� ��������� signal_f ���������� ������ ������� SIGNAL_D � ���������� signal_for_6_class ������ cl_6
		break;
	case 8:
		signal_f = SIGNAL_D(cl_system_display::signal_for_3_class);											// ���������� ��������� signal_f ���������� ������ ������� SIGNAL_D � ���������� signal_for_6_class ������ cl_6
		break;
	default:
		break;
	}
	return signal_f;																				// ������� ��������� siganl_f
}


TYPE_HANDLER cl_base::switch_handler(int i_class)													// ���������� ������ switch_handler
{
	TYPE_HANDLER handler_f = nullptr;																// ������������� �������� �� ����� ����������� ��������� �������� ���������

	switch (i_class)																					// ������������� �������
	{
	case 1:																							// �������� ���������� i_class ����� 1
		handler_f = HANDLER_D(cl_application::handler_for_app_to_input);							// ���������� ��������� handler_f ���������� ������ ������� HANDLER_D � ���������� handler_for_1_class ������ cl_1
		break;
	case 2:																							// �������� ���������� i_class ����� 2
		handler_f = HANDLER_D(cl_cartridge::handler_for_2_class);										// ���������� ��������� handler_f ���������� ������ ������� HANDLER_D � ���������� handler_for_2_class ������ cl_2
		break;
	case 3:																							// �������� ���������� i_class ����� 3
		handler_f = HANDLER_D(cl_tray::handler_for_3_class);										// ���������� ��������� handler_f ���������� ������ ������� HANDLER_D � ���������� handler_for_3_class ������ cl_3
		break;
	case 4:																							// �������� ���������� i_class ����� 4
		handler_f = HANDLER_D(cl_console::handler_for_4_class);										// ���������� ��������� handler_f ���������� ������ ������� HANDLER_D � ���������� handler_for_4_class ������ cl_4
		break;
	case 5:																							// �������� ���������� i_class ����� 5
		handler_f = HANDLER_D(cl_document::handler_for_5_class);										// ���������� ��������� handler_f ���������� ������ ������� HANDLER_D � ���������� handler_for_5_class ������ cl_5
		break;
	case 6:																							// �������� ���������� i_class ����� 6
		handler_f = HANDLER_D(cl_PK::handler_for_6_class);										// ���������� ��������� handler_f ���������� ������ ������� HANDLER_D � ���������� handler_for_6_class ������ cl_6
		break;
	case 7:
		handler_f = HANDLER_D(cl_input::handler_for_input_to_app);										// ���������� ��������� handler_f ���������� ������ ������� HANDLER_D � ���������� handler_for_6_class ������ cl_6
		break;
	case 8:
		handler_f = HANDLER_D(cl_system_display::handler_for_3_class);										// ���������� ��������� handler_f ���������� ������ ������� HANDLER_D � ���������� handler_for_6_class ������ cl_6
		break;
	default:
		break;
	}
	return handler_f;																				// ������� ��������� handler_f
}


void cl_base::set_name_of_class(int num)															// ���������� ������ set_name_of_class
{
	this->i_class = num;																			// ���������� ���� i_class �������� ������� �������� ��������� num
}


int cl_base::get_name_of_class()																	// ���������� ������ get_name_of_class
{
	return i_class;																					// ������� �������� ���� i_class
}