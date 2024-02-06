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

enum class restartCheck {
	restart = 1,
	exit = 2
};

template<typename T>
T checkInput() {
	T userInput{};
	while (!(cin >> userInput)) {
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Введены некорректные данные. Попробуйте снова." << endl;
	}
	cin.ignore(INT_MAX, '\n');
	return userInput;
}

int main() {
	setlocale(LC_CTYPE, "Russian");
	cout << "Добро пожаловать!" << endl;
	cout << "Работа #1 была выполнена студентами группы 423 Ореховым Даниилом, Беликовым Ильей и Лешуковым Никитой." << endl;
	cout << "Задача: разработать asm-вставку для подсчета суммы, разности, произведения, целой части частного и остатка от целочисленного деления двух целочисленных значений."<<endl;

	bool exitFlag = false;
	do {
		bool errFlag = false;
		bool exitCheckFlag = true;
		int firstOperand = 0;
		int secondOperand = 0;
		int result = 0;
		string opSign = "";
		cout << "=============================================="<<endl;
		cout << "Выберите операцию: " << endl
			<< "1 - сложение" << endl
			<< "2 - вычитание" << endl
			<< "3 - умножение" << endl
			<< "4 - деление" << endl
			<< "5 - найти остаток от деления" << endl
			<< "6 - выход" << endl;

		operations operation = static_cast<operations>(checkInput<int>());
		cout << "==============================================" << endl;
		if (operation != operations::exit) {
			cout << "Введите первый операнд: ";
			firstOperand = checkInput<int>();
			cout << "Введите второй операнд: ";
			secondOperand = checkInput<int>();
		}

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
			if (secondOperand == 0) {
				cout << "Деление на ноль!" << endl;
				errFlag = true;
				break;
			}
			_asm {
				MOV EAX, firstOperand	// Перемещаем первый операнд в регистр EAX.
				CDQ						// Расширяем знаковый бит содержимого регистра EAX на регистр EDX, чтобы подготовиться к делению
											//с дополнением до двойного слова (64-бита) при делении 32-битных чисел со знаком.	
				MOV EBX, secondOperand	// Перемещаем второй операнд в регистр EBX.
				IDIV EBX				// Выполняем деление значения в EAX на значение в EBX.
											//Результат будет в EAX, остаток от деления - в EDX.
				MOV result, EAX			// Перемещаем результат деления в переменную result.
			}
			break;
		case operations::remainder:
			if (secondOperand == 0) {
				cout << "Деление на ноль!" << endl;
				errFlag = true;
				break;
			}
			opSign = "%";
			_asm {
				MOV EAX, firstOperand
				CDQ
				MOV EBX, secondOperand
				IDIV EBX
				MOV result, EDX
			}
			if (result < 0) {
				result += abs(secondOperand);
			}
			break;
		case operations::exit:
			exit(0);
		default:
			cout << "Введены некорректные данные. Попробуйте снова." << endl;
			errFlag = true;
			break;
		}

		if (!errFlag && !exitFlag) {
			cout << firstOperand << " " << opSign << " " << secondOperand << " = " << result << endl;
			cout << "Запустить программу снова?" << endl;
			cout << "1. Да" << endl
				<< "2. Нет" << endl;
			exitCheckFlag = false;
		}
		else {
			exitCheckFlag = true;
			exitFlag = false;
		}

		while (!exitCheckFlag) {
			exitCheckFlag = true;
			restartCheck check = static_cast<restartCheck>(checkInput<int>());
			switch (check)
			{
			case restartCheck::restart:
				exitFlag = false;
				break;
			case restartCheck::exit:
				exitFlag = true;
				break;
			default:
				exitCheckFlag = false;
				break;
			}
		}
	} while (!exitFlag);
	return 0;
}
