#pragma once
#include "KDeque.h"
#include "Avereger.h"
#include "stream.h"

class View {
	KOstream out;
public:
	View(HWND hwnd, int listbox_id) :out(GetDlgItem(hwnd,listbox_id)){};
	template <typename T,size_t grow_const >
	void show(const KDeque<T,grow_const>& model) {
		out << model;
	}
	template <typename T >
	void show(const T& val) {
		out << val;
	}
};



template <typename T,size_t grow_const=2>
class Controller
{
	KDeque<T,grow_const> model;
	View view;
	T get_val(HWND hwnd, int id_edit) {
		KIstream in(GetDlgItem(hwnd, id_edit));
		T a;
		in >> a;
		return a;
	}
public:
	Controller(KDeque<T,grow_const>&& model, View&& view) :model(model), view(view) {}
		
	void read(std::istream& in) {
		in >> model;
		view.show(model);
	}

	int parse_controll(HWND hwnd, short control_id, Controller<T, grow_const>& b, int id_edit, int id_list) {

		switch (control_id)
		{
			//Удаление
		case IDC_BUTTON_Pop_Front:
			pop_front();
			break;
		case IDC_BUTTON_Clear:
			clear();
			break;
		case IDC_BUTTON_Pop_Back:
			pop_back();
			break;
			//Добавление
		case IDC_PushFront:
			push_front(hwnd, id_edit);
			break;

		case IDC_Push_Back:
			push_back(hwnd, id_edit);
			break;

		case IDC_Modify:
			modify(hwnd, id_edit, id_list);
			break;

			//Actions
		case IDC_BUTTON_Plus:
			operator_plus(hwnd, IDC_LIST_Result, b);
			break;

		case IDC_BUTTON_PlusEq:
			operator_plus_eq(b);
			break;

		case IDC_BUTTON_Eq:
			operator_eq(b);
			break;

		case IDC_BUTTON_Bool_Eq:
			operator_bool_eq(hwnd, IDC_LIST_Result, b);
			break;

		case IDC_BUTTON_Swap:
			swap(b);
			break;

		case IDC_Average: {
			find_average(hwnd, IDC_LIST_Result);
			break;
		}

		default:
			return FALSE;
		}
		return TRUE;
	}
	

	void push_back(HWND hwnd, int id_edit) {
		auto a = get_val(hwnd, id_edit);
		model.push_back(a);
		view.show(model);
	}
	void push_front(HWND hwnd, int id_edit) {
		auto a = get_val(hwnd, id_edit);
		model.push_front(a);
		view.show(model);
	}
	void pop_front() {
		model.pop_front();
		view.show(model);
	}

	void pop_back() {
		model.pop_back();
		view.show(model);
	}

	void clear() {
		model.clear();
		view.show(model);
	}

	void modify(HWND hwnd,int id_edit, int id_list_box) {
		
		auto buf = get_val(hwnd,id_edit);
		int i = SendDlgItemMessage(hwnd, id_list_box, LB_GETCURSEL, 0, 0);
		model[i] = buf;
		view.show(model);
	}
	void operator_plus(HWND hwnd, int id_list_box_result,const Controller<T>& c)const {
		KOstream out(GetDlgItem(hwnd, id_list_box_result));
		out.clear();
		out << (model + c.model);
	}
	void operator_plus_eq(const Controller<T>& c) {
		model += c.model;
		view.show(model);
	}
	void operator_eq(const Controller<T>& c) {
		model = c.model;
		view.show(model);
	}
	void operator_bool_eq(HWND hwnd, int id_list_box_result, const Controller<T>& c)const {
		KOstream out(GetDlgItem(hwnd, id_list_box_result));
		out.clear();
		out << (model == c.model);
	}
	void swap(Controller<T>& a) {
		Swap(model, a.model);
		view.show(model);
		a.view.show(a.model);
	}
	void find_average(HWND hwnd, int id_list_box_result) {
		Avereger average;
		for (auto i : model) {
			i.accept(average);
		}
		KOstream out(GetDlgItem(hwnd, id_list_box_result));
		out.clear();
		out << average.get_average();
	}
};

