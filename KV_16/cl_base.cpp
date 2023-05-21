#include "cl_base.h"														       // Подключение заголовочного файла cl_base
#include <iostream>															       // Подключение библиотеки стандартного потока ввода/вывода 
#include <queue>															       // Подключение библиотеки для работы с очередью
#include <sstream>																   // Подключение библиотеки для работы с потоками данных
#include "cl_cartridge.h"																   // Подсключение заголовочного класса cl_2
#include "cl_tray.h"																   // Подсключение заголовочного класса cl_3
#include "cl_console.h"																   // Подсключение заголовочного класса cl_4
#include "cl_document.h"																   // Подсключение заголовочного класса cl_5
#include "cl_PK.h"																   // Подсключение заголовочного класса cl_6
#include "cl_application.h"														   // Подсключение заголовочного класса cl_application
#include "cl_input.h"
#include "cl_system_display.h"
using namespace std;														       // Подключение пространства имен std

cl_base::cl_base(cl_base* p_head_object, string s_object_name)                     // Реализация конструктора класса cl_base
{
	this->p_head_object = p_head_object;                                           // Присвоение полю p_head_object значения параметра p_head_object
	this->s_object_name = s_object_name;	                                       // Присвоение полю s_object_name значения параметра s_object_name

	if (p_head_object != nullptr) 	                                               // Проверка существования головного объекта 
		p_head_object->p_sub_objects.push_back(this);			                   // Добавление указателя на объект в конец вектора подчиненных объектов головного объекта p_head_object
}


cl_base::~cl_base()                                                                // Реализация деструктора класса cl_base
{
	for (int i = 0; i < p_sub_objects.size(); i++)                                 // Цикл для прохода по элементам вектора
		delete (p_sub_objects[i]);								                   // Очищение выделенной под объект динамической памяти 
}


bool cl_base::set_name(string s_new_name)                                          // Реализация метода set_name класса cl_base
{
	if (p_head_object != nullptr)								                   // Проверка на существование головного объекта 
	{
		for (int i = 0; i < p_head_object->p_sub_objects.size(); i++)              // Цикл для прохода по элементам вектора
		{
			if (p_head_object->p_sub_objects[i]->get_name() == get_name())         // Проверка на существоание имени объекта в векторе для головного объекта
				return false;												       // Возврат false
		}
	}
	this->s_object_name = s_new_name;										       // Присвоение полю s_object_name параметра s_new_name (редактировнаие имени)
	return true;															       // Возврат true 
}


string cl_base::get_name()                                                         // Реализация метода get_name класса cl_base
{
	return this->s_object_name;                                                    // Возврат наименования объекта
}


cl_base* cl_base::get_head()                                                       // Реализация метода get_head класса cl_base  
{
	return p_head_object;                                                          // Возврат указателя на головной объект
}


cl_base* cl_base::get_sub_object(string s_object_name)                             // Реализация метода get_sub_object класса cl_base 
{
	for (int i = 0; i < p_sub_objects.size(); i++)                                 // Цикл для прохода по элементам вектора
	{
		if (p_sub_objects[i]->get_name() == s_object_name)			               // Провека существования объекта с искомым наименованием s_object_name в векторе 
			return p_sub_objects[i];										       // Возврат указателя на найденный объект
	}
	return nullptr;															       // Возврат нулевого указателя 
}


cl_base* cl_base::find_object_from_current(string s_object_name)			       // Реализация метода find_object_from_current класса cl_base
{
	queue <cl_base*> q;														       // Объявление очередии типа указатель на объект базового класса
	cl_base* p_found = nullptr;												       // Инициализация указателя на объект класса cl_base p_found значением нулевого указателя

	q.push(this);															       // Добавление указателя на текущий объект в очередь

	while (!q.empty())														       // Проверка, пуста ли очередь
	{
		if (q.front()->get_name() == s_object_name)							       // Проверка, что имя объекта первого в очереди наше искомое
		{
			if (p_found == nullptr)											       // Проверка, что объект еще не был найден
				p_found = q.front();										       // Присвоение указателя на первый объект в очереди указателю p_found
			else															       // Иначе
				return nullptr;												       // Возврат нулевого указателя
		}

		for (int i = 0; i < q.front()->p_sub_objects.size(); i++)				   // Цикл для прохода по подчиненным элементам первого олбъекта в очреди
			q.push(q.front()->p_sub_objects[i]);								   // Добавление указателя на очередной подчиненный объект первого объекта в очереди  

		q.pop();															       // Удаление первого объекта в очереди
	}
	return p_found;														  		   // Возврат найденного указателя на объект
}


cl_base* cl_base::find_object_from_root(string s_object_name)				       // Реализация метода find_object_from_root класса cl_base
{
	cl_base* p_root = this;													       // Инициализация указателя p_root на объект базового класса значением указателя на текущий объект

	while (p_root->get_head() != nullptr)									       // Цикл для поиска корневого объекта
		p_root = p_root->get_head();										       // Присвоение указателю p_root значения его голвоного объекта 

	return p_root->find_object_from_current(s_object_name);					       // Возврат результата работы метода find_object_from_current  для объекта c указателем на него p_root
}


void cl_base::print_tree_from_current(int num)								       // Реализация метода find_object_from_root класса cl_base
{
	if (p_sub_objects.size() != 0)											 	   // Проверка, что у текущего объекта есть подчиненные
	{
		for (int i = 0; i < p_sub_objects.size(); i++)							   // Цикл для прохода по подчиненным объектам
		{
			cout << endl << string(num, ' ') << p_sub_objects[i]->get_name();	   // Вывод названия объекта с нужным отступом
			p_sub_objects[i]->print_tree_from_current(num + 4);					   // Рекурсивный вызов этого же метода для каждого подчиненнго объекта с праметром отсупа
		}
	}
}


void cl_base::object_readiness(int i_status)								 	   // Реализация метода object_readiness класса cl_base
{
	bool flag = false;														       // Инициализация пременной flag логического типа значением false
	cl_base* search_obj = this;												       // Инициализация указателя на объект базового класса значеним указателя на текущий объект
	queue <cl_base*> q;														       // Объявление очереди типа указатель на объект базового класса

	if (i_status != 0)															   // Значение i_status отлично от нуля
	{
		while (search_obj->get_head() != nullptr)			       				   // Цикл для проверки, что все вышестоящие по ветке объекты включены
		{
			if ((search_obj->get_head())->i_status == 0)					 	   // Провреака, что поле i_status головного объекта объекта search_obj имеет значение 0 
			{
				flag = true;													   // Присвоение пеерменной flag значения true
				break;															   // Выход из цикла
			}
			search_obj = search_obj->get_head();									   // Присвоение указателю search_obj значения указателя на его головной объект
		}
		if (flag == false) this->i_status = i_status;							   // Проверка, что не было найденно выключенного объекта и присовение полю i_status текущего объекта значения парамтра i_status
	}
	else																		   // Иначе
	{
		q.push(this);														 	   // Добавление в очередь укзатаеля на текущий объект

		while (!q.empty())													       // Проверка на пустоту очереди
		{
			q.front()->i_status = i_status;									 	   // Присволение полю i_status первого объекта в очереди значения парамтра i_status

			for (int i = 0; i < q.front()->p_sub_objects.size(); i++)			   // Цикл для прохода по подчиненным элементам первого олбъекта в очреди
				q.push(q.front()->p_sub_objects[i]);							   // Добавление указателя на очередной подчиненный объект первого объекта в очереди

			q.pop();														       // Удаление первого объекта из очереди
		}
	}
}

void cl_base::print_tree_from_current_readiness(int num)					       // Реализация print_tree_from_current_readiness класса cl_base
{

	if (p_sub_objects.size() != 0)											       // Проврека, что у текущего объекта есть подчиненные
	{
		for (int i = 0; i < p_sub_objects.size(); i++)							   // Цикл для прохода по подчиненным объектам
		{
			cout << endl << string(num, ' ') << p_sub_objects[i]->get_name();	   // Вывод названия объекта с нужным отступом

			if (p_sub_objects[i]->i_status == true)								   // Проврека, что статус подчиненного объекта не равен нулю
				cout << " is ready";										       // Вывод сообщения на экран " is ready"
			else															       // Иначе
				cout << " is not ready";									       // Вывод сообщения на экран " is not ready"

			p_sub_objects[i]->print_tree_from_current_readiness(num + 4);		   // Рекурсивный вызов этого же метода для каждого подчиненнго объекта с параметром отступа
		}
	}
}


bool cl_base::head_name_redefinition(cl_base* p_new_head)						   // Реализация метода head_name_refefinition класса cl_base
{
	if (get_head() != nullptr)													   // Проверка, что головной объект для текущего существует
	{
		if (p_new_head->get_sub_object(get_name()) == nullptr)					   // Проверка, что у нового головного объекта нет подчиненного объекта с именем, как у текущего
		{
			cl_base* current_object = p_new_head;								   // Инициализация вспомогательного указателя значением указателя на новый головоной объект 

			while (current_object != nullptr)									   // Цикл для поиска корневого
			{
				if (current_object == this)										   // Проверка, что новый говлоной объект находится в ветке текущего
					return false;												   // Возврат false - переопредление не произошло
				current_object = current_object->get_head();					   					// Присвеоение вспомогательному указателю значения указателя на его головной объект
			}

			for (int i = 0; i < get_head()->p_sub_objects.size(); i++)		       					// Цикл для прохода по подчиненным объектам для головного текущего
				if (get_head()->p_sub_objects[i] == this)					       					// Проверка, что подчиненный объект является текущим
					get_head()->p_sub_objects.erase(get_head()->
						p_sub_objects.begin() + i);								       					// Удаление найденного объекта из подчиненных для головного текущего объекта

			get_head() == p_new_head; 										       					// Присвоение головному текущего объекта значение указателя нового головного
			p_new_head->p_sub_objects.push_back(this);						       					// Добавление в вектор подчиненных объектов нового объекта, текщуего объекта
			return true;													   	   					// Возврат true - переопредление головного объекта прошло успешно
		}
	}
	return false;																   					// Возврат false - переопредление не произошло
}

void cl_base::delete_object_from_name(string sub_name_for_delete)				   					// Реализация метода delete_object_from_name класса cl_base
{
	for (int i = 0; i < p_sub_objects.size(); i++)								   					// Цикл для прохода по подчиненным объектам текущего объекта
		if (sub_name_for_delete == p_sub_objects[i]->get_name())					   					// Проверка, что имя удаляемого объекта совпадает с именнем подчиенного 
			p_sub_objects.erase(p_sub_objects.begin() + i);						   					// Удаление подчиненного объекта из вектора подчиненных объектов для текущего

	delete (get_sub_object(sub_name_for_delete));								   					// Удаление объекта
}


cl_base* cl_base::get_pointer_of_object_from_path(string path)					   					// Реализация метода get_pointer_of_object_from_path  класса cl_base
{
	if (path.empty() == true) return nullptr;									   					// Проверка, что путь пустой, если да возврат нулевого указателя

	if (path == "/")															   					// Проверка что путь равен "/"
	{
		cl_base* p_root = this;													   					// Инициализация вспомогательного указателя на объект базового класса значеним указателя на текущий объект

		while (p_root->get_head() != nullptr)									   					// Цикл для поиска корневого объекта
			p_root = p_root->get_head();										  					// Присвоение вспомогательному указателю значения его головного
		return p_root;															   					// Вернуть вспомогательный указатель, указывающий на корневой объект
	}

	if (path == ".") return this; 												   					// Проверка что путь равен ".", если да, то вернуть указаетель на текущий объект

	string::size_type pos = path.find("//");									   					// Инициализация беззнаковой целочисленной переменной pos результатом работы метода find, для поиска "//" в пути
	if (pos != string::npos)														   					// Проверка, что символы были найдены
	{
		string search_object_name = path.erase(0, 2);							   					// Инициализация строковой переменной значеним пути без первых двух символов
		return find_object_from_root(search_object_name);						   					// Возврат результата работы метода для поиска объекта по всему дереву
	}

	pos = path.find(".");														   					// Присвоение результата работы метода find, для поиска символа "." в пути
	if (pos != string::npos)														   					// Проверка, что символ был найден
	{
		string search_object_name = path.erase(0, 1);							   					// Инициализация строковой переменной значеним пути без первого символа
		return find_object_from_current(search_object_name);					   					// Возврат результата работы метода для поиска объекта по ветке
	}


	vector <string> path_for_object;											   					// Объявление вектора path_for_objet строкового типа
	stringstream ss(path);														   					// Создание объекта ss класса stringstream и передача ему в параметрах пути к объекту
	string item;																   					// Объявлениие строковой переменной item, для хранения в ней частей пути
	cl_base* p_root = this;														   					// Инициализация указателя p_root на объект базового класса значением указателя на текущий объект

	while (getline(ss, item, '/'))													   					// Цикл для добавления в вектор path_for_objet частей пути, с разедлителем "/",метод getlibe присваивает параметру item значение пути до символа "/"
		path_for_object.push_back(item);										   					// Добаление части пути в вектор 

	if (path_for_object[0] == "")												   					// Проверка, что первый элемент вектора равен пустой стркое (если раавен, то это означет, что путь начинался со "/" и нужно подниматься до корневого)
	{
		while (p_root->get_head() != nullptr)									   					// Цикл для поиска корневого 
			p_root = p_root->get_head();										   					// Присвоение указателю p_root значения указтеля на его головной
		path_for_object.erase(path_for_object.begin());							   					// Удаление первого элемента из вектора пути,(удаление пустой строки)
	}


	queue <cl_base*> q;															   					// Объявление очереди q типа указетль на объект базового класса
	int pathIndex = 0;															   					// Инициализация целовчиленной переменной pathIndex значением 0,	содержит в себе индекс для вектора с частями пути

	for (int i = 0; i < p_root->p_sub_objects.size(); i++)						   					// Цикл для прохода по подчиненным объектам объекта p_root 
		q.push(p_root->p_sub_objects[i]);										   					// Добавление подчиненных объектов p_root в очередь

	while (!q.empty())															   					// Проверка, что очередь не пустая
	{
		cl_base* p_found = q.front();											   					// Инициализация указателя на объект базового класса значеним указателя на первый объект в очереди
		q.pop();																   					// Удаление первого объекта из очереди

		if (p_found->get_name() == path_for_object[pathIndex])					   					// Проверка, что имя объекта, на который указывает p_found равно значению участка пути под индексом pathIndex
		{
			while (!q.empty()) q.pop();											   					// Очищение всей очереди, этономит время выполнения программы

			if (pathIndex == path_for_object.size() - 1) return p_found;			  					// Проверка, значение текущего индекса равно размеру вектора, содержащаего путь до объекта , если да, то вернуть p_found 
			pathIndex++;														   					// Увеличение индекса pathIndex на 1

			for (int i = 0; i < p_found->p_sub_objects.size(); i++)				  					// Цикл для добавления всех подчиненных объектов объекта p_found
				q.push(p_found->p_sub_objects[i]);								   					// Добавление очереденого подчиненного объеката p_found в очередь q
		}
	}
	return nullptr;																   					// Возврат нулевого укзаателя - значит, что объект найти не удалось
}

void cl_base::set_connection(TYPE_SIGNAL p_signal, cl_base* p_target, TYPE_HANDLER p_handler)		// Реализация метода set_connection
{
	o_sh* p_value;																					// Объявление указателя на объект структуры o_sh

	for (int i = 0; i < connects.size(); i++)														// Цикл для прохода по объектам, связанных с текущим
	{
		if (connects[i]->p_signal == p_signal &&
			connects[i]->p_target == p_target &&
			connects[i]->p_handler == p_handler)													// Проверка, что уже дублирование объекта
			return;																					// Завершение работы метода
	}

	p_value = new o_sh();																			// Присвоение указетлю p_value указателя на созданный с помощью оператора new объект структуры o_sh

	p_value->p_signal = p_signal;																	// Присвоение свойству текущего объекта значения передаваемого параметра
	p_value->p_target = p_target;																	// Присвоение свойству текущего объекта значения передаваемого параметра
	p_value->p_handler = p_handler;																	// Присвоение свойству текущего объекта значения передаваемого параметра

	connects.push_back(p_value);																 	// Добавление созданного объекта в вектор соединений
}

void cl_base::delete_connection(TYPE_SIGNAL p_signal, cl_base* p_target, TYPE_HANDLER p_handler)	// Реализация метода delete_connection
{
	for (int i = 0; i < connects.size(); i++)														// Цикл для прохода по объектам, связанных с текущим
	{
		if (connects[i]->p_signal == p_signal &&
			connects[i]->p_target == p_target &&
			connects[i]->p_handler == p_handler)													// Проверка, что найдеен нужный объект в векторе объектов
			connects.erase(connects.begin() + i);													// Удаление найденного объекта
	}
}

void cl_base::emit_signal(TYPE_SIGNAL p_signal, string s_message)									// Реализация метода emit_signal
{
	if (get_i_status_ready() == false) return;														// Проврека, что статус текущего объекта "Не готов", если да, то выход из метода

	(this->*p_signal)(s_message);																	// Вызов метода  p_signal текущего объекта с передачей ему параметра s_message

	for (int i = 0; i < connects.size(); i++)														// Цикл для прохода по объектам, связанных с текущим
	{
		if (connects[i]->p_signal == p_signal)														// Проверка, что перданный сигнал совпадает с сигналом соединенного объекта
		{
			cl_base* p_target = connects[i]->p_target;												// Инициализация указателя на объект базового класса значеним поля p_target подходящего соединенного объекта
			TYPE_HANDLER p_handler = connects[i]->p_handler;										// Инициализация указателя на метод обработчика значеним поля p_target подходящего соединенного объекта

			(p_target->*p_handler)(s_message);														// Вызов метода обработчика p_handler объекта p_target (целоевого объекта) с передачей ему параметра s_message
		}
	}
}


string cl_base::absolute_path()																		// Реализация метода absolute_path
{
	string absolute_path = "";																		// Инициализация строковой переменной значением пустой строки
	cl_base* current_object = this;																	// Инициализация указатея на объект базового класса значеним указателя на текущий объект

	if (get_head() == nullptr) return "/";															// Проверка, что головной для текущего не существует, вернуть слэш

	while (current_object->get_head() != nullptr)													// Цикл для поднятия по дереву до корневого
	{
		absolute_path = "/" + current_object->get_name() + absolute_path;							// Изменение переменной для хранения пути до объекта 
		current_object = current_object->get_head();												// Присвоение переменной значения укзаетля на ее головной
	}
	return absolute_path;																			// Возврат абсолютного пути до объекта
}


void cl_base::i_status_ready_for_all()																// Реализация метода i_status_ready_for_all
{
	i_status = true;																				// Присвоение полю i_status текщуего объект значения true. т.е включение объекта

	for (int i = 0; i < p_sub_objects.size(); i++)													// Цикл для прохода по подчиненным текущего объекта
		p_sub_objects[i]->i_status_ready_for_all();													// Вызов для каждого подчиненного текущего метода 
}


void cl_base::set_i_status_ready(bool i_status_ready)												// Реализация метода set_i_status_ready
{
	this->i_status = i_status_ready;																// Приисвоение полю i_status значение передаваемого параметра

	if (i_status_ready == false)																	// Значение парметра "Не готов"
		for (int i = 0; i < p_sub_objects.size(); i++)												// Цикл для прохода по подчиненным текущего объекта
			p_sub_objects[i]->set_i_status_ready(i_status_ready);									// Вызов текущего метода для кажого подчинненного текущего метода
}


int cl_base::get_i_status_ready()																	// Реализация метода get_i_status_ready
{
	return i_status;																				// Возврат значения поля i_status;
}

TYPE_SIGNAL cl_base::switch_signal(int i_class)														// Реализация метода switch_signal
{
	TYPE_SIGNAL signal_f = nullptr;																	// Инициализация укзателя на метод сигнала значенеим нулевого указателя 

	switch (i_class)																					// Переключатель классов
	{
	case 1:																							// Значение переменной i_class равно 1
		signal_f = SIGNAL_D(cl_application::signal_for_app_to_input);								// Присвоение указателю signal_f результата работы макроса SIGNAL_D с аргументом signal_for_1_class класса cl_1
		break;
	case 2:																							// Значение переменной i_class равно 2
		signal_f = SIGNAL_D(cl_cartridge::signal_for_2_class);											// Присвоение указателю signal_f результата работы макроса SIGNAL_D с аргументом signal_for_2_class класса cl_2
		break;
	case 3:																							// Значение переменной i_class равно 3
		signal_f = SIGNAL_D(cl_tray::signal_for_3_class);											// Присвоение указателю signal_f результата работы макроса SIGNAL_D с аргументом signal_for_3_class класса cl_3
		break;
	case 4:																							// Значение переменной i_class равно 4
		signal_f = SIGNAL_D(cl_console::signal_for_4_class);											// Присвоение указателю signal_f результата работы макроса SIGNAL_D с аргументом signal_for_4_class класса cl_4
		break;
	case 5:																							// Значение переменной i_class равно 5
		signal_f = SIGNAL_D(cl_document::signal_for_5_class);											// Присвоение указателю signal_f результата работы макроса SIGNAL_D с аргументом signal_for_5_class класса cl_5
		break;
	case 6:																							// Значение переменной i_class равно 6
		signal_f = SIGNAL_D(cl_PK::signal_for_6_class);											// Присвоение указателю signal_f результата работы макроса SIGNAL_D с аргументом signal_for_6_class класса cl_6
		break;
	case 7:
		signal_f = SIGNAL_D(cl_input::signal_for_input_to_all);											// Присвоение указателю signal_f результата работы макроса SIGNAL_D с аргументом signal_for_6_class класса cl_6
		break;
	case 8:
		signal_f = SIGNAL_D(cl_system_display::signal_for_3_class);											// Присвоение указателю signal_f результата работы макроса SIGNAL_D с аргументом signal_for_6_class класса cl_6
		break;
	default:
		break;
	}
	return signal_f;																				// Возврат указателя siganl_f
}


TYPE_HANDLER cl_base::switch_handler(int i_class)													// Реализация метода switch_handler
{
	TYPE_HANDLER handler_f = nullptr;																// Инициализация укзателя на метод обработчика значением нулевого указателя

	switch (i_class)																					// Переключатель классов
	{
	case 1:																							// Значение переменной i_class равно 1
		handler_f = HANDLER_D(cl_application::handler_for_app_to_input);							// Присвоение указателю handler_f результата работы макроса HANDLER_D с аргументом handler_for_1_class класса cl_1
		break;
	case 2:																							// Значение переменной i_class равно 2
		handler_f = HANDLER_D(cl_cartridge::handler_for_2_class);										// Присвоение указателю handler_f результата работы макроса HANDLER_D с аргументом handler_for_2_class класса cl_2
		break;
	case 3:																							// Значение переменной i_class равно 3
		handler_f = HANDLER_D(cl_tray::handler_for_3_class);										// Присвоение указателю handler_f результата работы макроса HANDLER_D с аргументом handler_for_3_class класса cl_3
		break;
	case 4:																							// Значение переменной i_class равно 4
		handler_f = HANDLER_D(cl_console::handler_for_4_class);										// Присвоение указателю handler_f результата работы макроса HANDLER_D с аргументом handler_for_4_class класса cl_4
		break;
	case 5:																							// Значение переменной i_class равно 5
		handler_f = HANDLER_D(cl_document::handler_for_5_class);										// Присвоение указателю handler_f результата работы макроса HANDLER_D с аргументом handler_for_5_class класса cl_5
		break;
	case 6:																							// Значение переменной i_class равно 6
		handler_f = HANDLER_D(cl_PK::handler_for_6_class);										// Присвоение указателю handler_f результата работы макроса HANDLER_D с аргументом handler_for_6_class класса cl_6
		break;
	case 7:
		handler_f = HANDLER_D(cl_input::handler_for_input_to_app);										// Присвоение указателю handler_f результата работы макроса HANDLER_D с аргументом handler_for_6_class класса cl_6
		break;
	case 8:
		handler_f = HANDLER_D(cl_system_display::handler_for_3_class);										// Присвоение указателю handler_f результата работы макроса HANDLER_D с аргументом handler_for_6_class класса cl_6
		break;
	default:
		break;
	}
	return handler_f;																				// Возврат указателя handler_f
}


void cl_base::set_name_of_class(int num)															// Реализация метода set_name_of_class
{
	this->i_class = num;																			// Присвоение полю i_class текущего объекта значения параматра num
}


int cl_base::get_name_of_class()																	// Реализация метода get_name_of_class
{
	return i_class;																					// Возврат значения поля i_class
}