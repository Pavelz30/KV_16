#ifndef _CL_BASE_H
#define _CL_BASE_H

#include <string> 									  			 								// Подключение библиотеки для работы со строками
#include <vector>  									  			 								// Подключение библиотеки для рабты с векторами
#include <iostream>
using namespace std;								  			 								// Подключение пространства имен std

#define SIGNAL_D(signal_f) (TYPE_SIGNAL)(&signal_f);			 								// Параметризированное макроопределение препроцессора для приведения указателя на метод сигнала 
#define HANDLER_D(handler_f) (TYPE_HANDLER)(&handler_f);		 								// Параметризированное макроопределение препроцессора Для приведения указателя на метод обработчика

class cl_base;													 								// Предобъявление класса cl_base

typedef void (cl_base::* TYPE_SIGNAL) (string& massege);		 								// Определение нового типа данных, название нового типа - TYPE_SIGNAL, для определения указателя на метод сигнала 
typedef void (cl_base::* TYPE_HANDLER) (string massege);		 								// Определение нового типа данных, название нового типа - TYPE_HANDLER, Для определения указателя на метод обработчика

struct o_sh														 								// Объявление стурктуры o_sh
{
	TYPE_SIGNAL p_signal;										 								// Поле p_signal типа указатель на метод сигнала для храчения указтеля на метод сигнала
	cl_base* p_target;																			// Поле p_target типа указтель на объект базового класса для хранения указетля на целевой объекта
	TYPE_HANDLER p_handler;																		// Поле p_handler типа указатель на метод обработчика целевого объекта для храчения указтеля на метод обработчика целевого объекта
};

class cl_base                                         			 								// Объявление класса cl_base                
{
	string s_object_name;                             			 								// Объявление строкового поля s_object_name 
	cl_base* p_head_object;							  			 								// Объявление поля типа указатель p_head_object на объект базового класса 
	vector <cl_base*> p_sub_objects;				 		 	 								// Объявление вектора p_sub_objects типа указатель на объект базового класса

	vector <o_sh*> connects;																	// Вектор connects типа указатель на объект стурктуры o_sh, для хранеия связей сигнал - обработчик
	bool i_status = false;							  			 								// Инициализация поля логического типа значением false
	int i_class;												 								// Объявление целочисленного поля i_class для хранения номера класса, объект которого был создан
public:
	cl_base(cl_base* p_head_object,
		string s_object_name = "Base_object");            		   	 								// Параметризирвоанный конструктор базового класса cl_base
	~cl_base();										  			 								// Деструктор класса cl_base
	bool set_name(string s_new_name);				  											// Метод класса cl_base, отвечающий за редактирование имени объекта
	string get_name();								  											// Метод класса cl_base, отвечающий за получение имени объекта
	cl_base* get_head();							  											// Метод класса cl_base, отвечающий за получение указателя на головной элемент объекта
	cl_base* get_sub_object(string s_object_name);    											// Метод класса cl_base, отвечающий за возврат указателя на подчиненный объект из вектора по его имени (если он там есть)

	cl_base* find_object_from_current(string s_object_name);    								// Метод класса cl_base, отвечающий за поиск объекта по его имени от текущего по ветке
	cl_base* find_object_from_root(string s_object_name);										// Метод класса cl_base, отвечающий за поиск объекта на всем дереве
	void print_tree_from_current(int num);														// Метод класса cl_base, отвечающий за вывод дерева иерархии от текущего объекта
	void print_tree_from_current_readiness(int num);											// Метод класса cl_base, отвечающий за вывод деерва со статусом готовности
	void object_readiness(int i_status);														// Метод класса cl_base, отвечающий за установку готовности объекта

	bool head_name_redefinition(cl_base* p_new_head);											// Метод класса cl_base, отвечающий за изменение головного объекта для текущего
	void delete_object_from_name(string sub_name_for_delete);   								// Метод класса cl_base, отвечающий за удаление подчиненного объекта у текущего
	cl_base* get_pointer_of_object_from_path(string path);	   									// Метод класса cl_base, отвечающий за поиск любого объекта в иерархии

	void set_connection(TYPE_SIGNAL p_signal, cl_base* p_target, TYPE_HANDLER p_handler);		// Метод класса cl_base, отвечающий за установление связи между сигналом текущего объекта и обработчиком целевого объекта
	void delete_connection(TYPE_SIGNAL p_signal, cl_base* p_target, TYPE_HANDLER p_handler);    // Метод класса cl_base, отвечающий за удаление (разрыва) связи между сигналом текущего объекта и обработчиком целевого объекта.
	void emit_signal(TYPE_SIGNAL p_signal, string s_massege);									// Метод класса cl_base, отвечающий за выдачу сигнала от текущего объекта с передачей строковой переменной.
	string absolute_path();																		// Метод класса cl_base, отвечающий за получение абсолютного пути до объекта
	void i_status_ready_for_all();																// Метод класса cl_base, отвечающий за установку статуса готовности кажого объекта в режи "Готов"
	void set_i_status_ready(bool i_status_ready);												// Метод класса cl_base, отвечающий за установку статуса готовности объекта
	int get_i_status_ready();																	// Метод класса cl_base, отвечающий за получения статуса готовности объекта

	TYPE_SIGNAL switch_signal(int i_class);														// Метод класса cl_base, отвечающий за опредление метода сигнала для требуемого класса
	TYPE_HANDLER switch_handler(int i_class);													// Метод класса cl_base, отвечающий за опредление метода обработчика для требуемого класса
	int get_name_of_class();																	// Метод класса cl_base, отвечающий за получение номера класса, объект которого был создан 
	void set_name_of_class(int num);															// Метод класса cl_base, отвечающий за установка номера класса, объект которого был создан
};

#endif