#include"HeaderPS.h"

using namespace std;

int main()
{
	setlocale(LC_ALL, "");
	system("chcp 1251");     // строка для корректного отображения кириллических символов
	string curName;          //  текущее имя пользователя
	string curPassWord;      //  текущий пароль пользователя
	int messNumber = 0;      //  номер текущего сообщения (сообщения нумеруются от нуля и далее в порядке создания)
	bool persPresence = false;       //  переменная, показывающая существование пользователя с данным именем и паролем
	bool nameInChatAlready = false;  //  переменная, которая показывает при регистрации есть ли уже в чате пользователь с таким именем

	string logMess;          //  переменная для хранения сообщения для логгирования
	std::shared_mutex shared_mutex;  //  мютекс для синхронизации потоков

	string contProcNumber = "0";     // переменная, которая отвечает за продолжение программы, тип продиктован необходимостью устойчивости
	// программы при вводе некорректных данных

	Chat presChat;


	while (true)
	{
		while (persPresence == false)  // цикл продолжается пока пользователь не вошел в аккаунт или не зарегистрировался
		{
			while (contProcNumber != "1" && contProcNumber != "2" && contProcNumber != "3")  //  защита от некорректного ввода выбора дальнейших действий
			{
				cout << "Выберите действие: 1 - войти; 2 - зарегистрироваться; 3 - выход из программы." << endl;
				getline(cin, contProcNumber);
			}
			persPresence = false;
			if (contProcNumber == "1")
			{
				presChat.entrChat(persPresence, curName, curPassWord);      // войти в чат
				if (presChat.ifEmpty() && persPresence)                     // если в массиве есть сообщения и пользователь вошел в чат
				{
					presChat.showMess(curName);
				}
				contProcNumber = "0";
			}

			if (contProcNumber == "2")
			{
				presChat.regChat(nameInChatAlready, persPresence, curName, curPassWord);    // зарегистрироваться в чате
				if (presChat.ifEmpty() && persPresence)                     // если в массиве есть сообщения и пользователь успешно зарегистрировался
				{
					presChat.showMess(curName);
				}
				contProcNumber = "0";
			}

			if (contProcNumber == "3") break;  //  выход из цикла
		}
		if (contProcNumber == "3") break;      //  выход из программы
		while (true)                       // цикл продолжается пока пользователь не захочет выйти из профиля или из программы
		{
			while (contProcNumber != "1" && contProcNumber != "2" && contProcNumber != "3")  //  защита от некорректного ввода выбора дальнейших действий
			{
				cout << "Выберите действие: 1 - отправить сообщение; 2 - удалить сообщение ; 3 - выйти из профиля." << endl;
				getline(cin, contProcNumber);
			}
			if (contProcNumber == "3")     //  если выбран выход из профиля
			{
				cout << endl;              //  пустая строка для лучшего восприятия информации
				persPresence = false;      //  пользователь выходит из профиля
				contProcNumber = "0";
				break;                     //  выход из цикла
			}
			if (contProcNumber == "2")     //  если выбрано удаление сообщения
			{
				presChat.delMess();
				contProcNumber = "0";
			}

			if (contProcNumber == "1")     //  если выбрана отправка сообщения
			{
				logMess = presChat.sendMess(curName);
				thread W(logToFile, ref(shared_mutex), logMess);
				thread R(logFromFile, ref(shared_mutex)); 
				contProcNumber = "0";
				W.join();
				R.join();
			}
			if (contProcNumber == "3") break;  //  выход из программы
		}
		if (contProcNumber == "3") break;      //  выход из программы
	}
	return 0;
}

// пос. Магистральный 27.11.2024