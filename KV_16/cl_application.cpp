#include "cl_application.h"	                                                     									  // Подключение заголовочного файла cl_application
#include "cl_base.h"                                                            									  // Подключение заголовочного файла cl_base
#include "cl_cartridge.h"                                                              										  // Подключение заголовочного файла cl_2
#include "cl_tray.h"																									  // Подключение заголовочного файла cl_3
#include "cl_console.h"																									  // Подключение заголовочного файла cl_4
#include "cl_document.h"																									  // Подключение заголовочного файла cl_5
#include "cl_PK.h"																									  // Подключение заголовочного файла cl_6
#include "cl_input.h"																									  // Подключение заголовочного файла cl_6
#include <iostream>                                                              									  // Подключение библиотеки стандартного потока ввода/вывода																										  // Подключенеи библиотеки для работы с контейнейнером, который работает по принципу [значение - ключ] 
#include "cl_system_display.h"
cl_application::cl_application(cl_base* p_head_object) :cl_base(p_head_object)    									  // Реализация конструктора класса cl_application
{

}

int cl_application::exec_app()                                                   									  // Реализация метода exec_app класса cl_application
{
	i_status_ready_for_all();																						  // Вызов метода для включения всех объектов
	string use_func;																								  // Объявление переменной
	cl_base* p_obj;																									  // Объялвение указателя на объект базового класса
	cl_base* p_target;																								  // Объялвение указателя на объект базового класса

	cout << "Object tree";														            						  // Вывод на экран сообщения "Object tree"
	cout << endl << get_name();													 									  // Переход на новую строку и вывод имени текущего объекта
	print_tree_from_current(4);																						  // Вызов метода print_tree_from_current для вывода деерва иерархии

	while (true)																							  			  // Цикл для ввода c клавиатуры команды
	{
		cin >> use_func;																							  // Ввод с клавиатуры команды

		if (use_func == "END") break;																				  // Проверка ввода комманды

		if (use_func == "EMIT")																						  // Проверка ввода комманды
		{
			string path, massege;																					  // Объявление переменных

			cin >> path;																							  // Ввод с клавиатуры названия головного объекта
			getline(cin, massege);																					  // Ввод в переменную строки
			p_obj = get_pointer_of_object_from_path(path);															  // Присвоение укзаетлю указателя на объект в дереве введеный ранее с помощью метода

			if (p_obj != nullptr)																					  // Проверка, что головной объект существует
			{
				p_obj->emit_signal(switch_signal(p_obj->get_name_of_class()), massege);								  // Вызов метода выдачи сигнала
				continue;																							  // Пропуск итерации
			}
			else
			{
				cout << endl << "Object " << path << " not found";													  // Вывод сообщения
				continue;																							  // Пропуск итерации
			}
		}

		if (use_func == "SET_CONNECT")																				  // Проверка ввода комманды
		{
			string signal_path, handler_path;																		  // Объявление переменных
			cin >> signal_path >> handler_path;																		  // Ввод с клавиатуры пути до сигнального объекта и до объекта обработчика
			p_obj = get_pointer_of_object_from_path(signal_path);													  // Присвоение укзаетлю указателя на сигнальный объект в дереве введеный ранее с помощью метода
			p_target = get_pointer_of_object_from_path(handler_path);												  // Присвоение укзаетлю указателя на целевой объект в дереве введеный ранее с помощью метода

			if (p_obj != nullptr && p_target != nullptr)															  // Сигнальный объект и целевой обект были найдены									
			{
				p_obj->set_connection(switch_signal(p_obj->get_name_of_class()), p_target, switch_handler
				(p_target->get_name_of_class()));			  // Вызов метода установления связи между сигналом текущего объекта и обработчиком целевого объекта.
				continue;
			}
			else if (p_obj == nullptr)																				  // Сигнальный объект не был найден
			{
				cout << endl << "Object " << signal_path << " not found";											  // Вывод сообщения
				continue;																							  // Пропуск итерации
			}
			else if (p_target == nullptr)																			  // Целевой объект не был найден
			{
				cout << endl << "Handler object " << handler_path << " not found";									  // Вывод сообщения
				continue;																							  // Пропуск итерации
			}
		}

		if (use_func == "DELETE_CONNECT")																			  // Проверка ввода комманды
		{
			string signal_path, handler_path;																		  // Объявление переменных
			cin >> signal_path >> handler_path;																		  // Ввод с клавиатуры пути до сигнального объекта и до объекта обработчика
			p_obj = get_pointer_of_object_from_path(signal_path);													  // Присвоение укзаетлю указателя на сигнальный объект в дереве введеный ранее с помощью метода
			p_target = get_pointer_of_object_from_path(handler_path);												  // Присвоение укзаетлю указателя на целевой объект в дереве введеный ранее с помощью метода

			if (p_obj != nullptr && p_target != nullptr)															  // Сигнальный объект и целевой обект были найдены
			{
				p_obj->delete_connection(switch_signal(p_obj->get_name_of_class()), p_target,
					switch_handler(p_target->get_name_of_class()));													  // Вызов метода удаления (разрыва) связи между сигналом текущего объекта и обработчиком целевого объекта
				continue;
			}
			else if (p_obj == nullptr)																				  // Сигнальный объект не был найден
			{
				cout << endl << "Object " << signal_path << " not found";											  // Вывод сообщения
				continue;																							  // Пропуск итерации
			}
			else if (p_target == nullptr)																			  // Целевой объект не был найден
			{
				cout << endl << "Handler object " << handler_path << " not found";									  // Вывод сообщения
				continue;																							  // Пропуск итерации
			}
		}

		if (use_func == "SET_CONDITION")																			  // Проверка ввода комманды
		{
			string signal_path;																						  // Объявление переменной
			int i_status_ready;																						  // Объявление переменной
			cin >> signal_path >> i_status_ready;																	  // Ввод значения переменных с клавиатуры
			p_obj = get_pointer_of_object_from_path(signal_path);													  // Присвоение укзаетлю указателя на сигнальный объект в дереве введеный ранее с помощью метода

			if (p_obj != nullptr)																					  // Сигнальный объект был найден
			{
				p_obj->set_i_status_ready(i_status_ready);															  // Вызво метода установки нового статуса для объетка
				continue;																							  // Пропуск итерации
			}
			else
			{
				cout << endl << "Object " << signal_path << " not found";											  // Вывод сообщения
				continue;																							  // Пропуск итерации
			}
		}
	}
	return 0;																										  // Возврат нуля
}

void cl_application::build_tree_objects()										 									  // Реализация метода build_tree_objects класса cl_application
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


void cl_application::signal_for_app_to_input(string& massege)															  // Реализация метода сигнала класса cl_application
{
	cout << endl << "Signal from " << absolute_path();																  // Вывод характерного сообщения и абсолютного пути до объекта																			  // Присвоение massege значенея самой перменной + "(class: 1)"
}

void cl_application::handler_for_app_to_input(string massege)															  // Реализация метода обработчика класса cl_application
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