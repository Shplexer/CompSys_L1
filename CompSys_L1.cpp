#include <iostream>
using namespace std;

enum class operations {
	add = 1,
	subtract = 2,
	multiply = 3,
	divide = 4,
	remainder = 5,
	exit = 6
};

int main() {
	setlocale(LC_CTYPE, "Russian");

	int firstOperand = 0;
	int secondOperand = 0;
	int result = 0;
	string opSign = "";
	cout << "Выберите операцию: " << endl;
	cout << "1 - сложение" << endl 
		<< "2 - вычитание" << endl
		<< "3 - умножение" << endl
		<< "4 - деление" << endl
		<< "5 - найти остаток от деления" << endl
		<< "6 - выход" << endl
		;
	int choice = 0;
	cin >> choice;
	operations operation = static_cast<operations>(choice);

	cout << "Введите первый операнд: ";
	cin >> firstOperand;
	cout << "Введите второй операнд: ";
	cin >> secondOperand;

	switch (operation)
	{
	case operations::add:
		opSign = "+";
		_asm {
			MOV EAX, firstOperand
			MOV EBX, secondOperand
			ADD EAX, EBX
			MOV result, EAX
		}
		break;
	case operations::subtract:
		opSign = "-";
		_asm {
			MOV EAX, firstOperand
			MOV EBX, secondOperand
			SUB EAX, EBX
			MOV result, EAX
		}
		break;
	case operations::multiply:
		opSign = "*";
		_asm {
			MOV EAX, firstOperand
			MOV EBX, secondOperand
			IMUL EAX, EBX
			MOV result, EAX
		}
		break;
	case operations::divide:
		opSign = "/";
		_asm {
			MOV EAX, firstOperand
			CDQ						//распространяем знаковый бит EAX на EDX
			MOV EBX, secondOperand
			IDIV EBX
			MOV result, EAX
		}
		break;
	case operations::remainder:
		opSign = "%";
		_asm {
			MOV EAX, firstOperand
			CDQ						//распространяем знаковый бит EAX на EDX
			MOV EBX, secondOperand
			IDIV EBX
			MOV result, EDX
		}
		if (result < 0) {
			result += abs(secondOperand);
		}
		break;
	case operations::exit:
		break;
	default:
		break;
	}


	cout << firstOperand << " " << opSign << " " << secondOperand << " = " << result << endl;
	return 0;
}
