#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <Windows.h>
#include <conio.h>
#include <stdlib.h>
#include <dirent.h>

using namespace std;

void menu();
void listLibs();
void libChoice();
void addWords();
void play();

struct word
{
	string ang = "";
	string pol = "";
};
//word + translation

vector <string> lib;
vector <word> words;
vector <string> sWords;
//couple vectors

string toFileName(string f)
{
	string t = f + ".txt";
	return (t);
}
//express the filename
/*void getWordsFromFile(string f)
{
	string s;

	ifstream openFile(f);

	while (!openFile.eof())
	{
		openFile >> s;
		sWords.push_back(s);
	}

	openFile.close();
}
//transcripts words from file to vector
*/


int randUnique(int m, vector <int> v)
{
	srand(time(NULL));        //sets time for casting numbers
    int st = 1;
    int y;


while (st == 1)
{
    st = 0;
    y = rand() % m;
        for (int i = 0; i < v.size(); i++)
        {
            if (y == v[i])
                st = 1;
        }
}
	return y;
}

void eraseFileLine(string path, int lineNumber)
{
	string line1, line2;
	int currentLine = 0;
	ifstream fin;

    if (!fin)
        cout << "!!!";

	fin.open(path);
	ofstream temp; // contents of path must be copied to a temp file then renamed back to the path file
	temp.open("temp.txt");

	while (fin >> line1 >> line2)
        {
            currentLine++;
            cout << currentLine << " ";

                if (currentLine != lineNumber)
                   temp << line1 << " " << line2 << endl;
        }

	temp.close();
	fin.close();

	const char * p = path.c_str(); // required conversion for remove and rename functions
	remove(p);
	rename("temp.txt", p);
}

/*
void writeWordsFromVector(vector <string> v)
{
	for (int i = 0; i < v.size(); i + 2)
		cout << i + 1 << ". " << v[i] << " - " << v[i + 1] << endl;
}
//prints words from the vector
void writeWordsToFile(vector <string> wordsTemp, string f1)
{
	ofstream toFile(f1);

	for (int i = 0; i < wordsTemp.size(); i + 2)
	{
		toFile << wordsTemp[i] << " " << wordsTemp[i + 1] << endl;
	}
}
//puts the words into a file
*/
bool checkIfInFile(string f, string w)
{
	string a;
	vector <string> temp;

	ifstream readfile(f);

	while (!readfile.eof())
	{
		readfile >> a;
		temp.push_back(a);
	}

	for (int i = 0; i < temp.size(); i++)
		if (temp[i] == w)
			return true;

	return false;
}
//chekin' if there is any data in file

void listLibs()
{
	DIR* directory = opendir(".");
	struct dirent* position = 0;
	vector <string> v;
	string file;

	while (position = readdir(directory))
	{

		file = (*position).d_name;
		if (file.find(".txt") == (file.length() - 4))
		{
			file.erase(file.length() - 4);
			v.push_back(file);
		}
	}
	closedir(directory);

	for (int i = 0; i < v.size(); i++)
	{
		cout << i + 1 << ". " << v[i] << endl;
	}
}

void addWords()
{
	int c;
	string input, libname;
	string temps1, temps2;
	string w1, w2;

	system("CLS");

	cout << "Dostepne biblioteki:" << endl;

	listLibs();

	cout << endl;

	cout << "Wybierz biblioteke, w ktorej zostanie zapisane slowo (wprowadz jej nazwe):" << endl;

	cout << "> ";
	cin >> input;

	if (input == "wstecz")
	{
		menu();
		return;
	}

	libname = toFileName(input);
	ifstream libCheck(libname);


	if (!libCheck)
	{
		char choice;
		cout << "Wybrana biblioteka nie istnieje! Czy chcesz utworzyc nowa o takiej nazwie (t/n)?" << endl;


		while (true) {
			cout << "> ";
			cin >> choice;

			switch (choice)
			{
			case 't':
			{
				ofstream toFile(libname);
				toFile << "";
				system("PAUSE");
				addWords();
				break;
			}
			case 'n':
			{
				addWords();
				break;
			}
			default:
			{
				cout << "Prosze wybrac poprawna opcje!" << endl;
				system("PAUSE");
				break;
			}
			}
		}
	}
	else
	{
		ifstream readWords(libname);

		cout << endl << "Slowa aktualnie znajdujace sie w bibliotece:" << endl;

		vector <word> wordsFromFile;


		while (!readWords.eof())
		{
			word w;
			readWords >> temps1;
			readWords >> temps2;
			w.ang = temps1;
			w.pol = temps2;
			wordsFromFile.push_back(w);
		}

		readWords.close();

		int c = 1;

		for (int i = 0; i < wordsFromFile.size() - 1; i++)
		{
			cout << c << ". " << wordsFromFile[i].pol << " - " << wordsFromFile[i].ang << endl;
			c++;
		}


		cout << endl;

		cout << "Podaj slowo po polsku:" << endl;
		cout << "> ";
		cin >> w1;


		cout << "Podaj angielskie tlumaczenie slowa:" << endl;
		cout << "> ";
		cin >> w2;

		word w;
		w.pol = w1;
		w.ang = w2;

		cout << endl << "Czy na pewno chcesz dodac slowo " << w1 << " - " << w2 << " do biblioteki " << input << " (t/n)?" << endl;

		char choice;
		while (true)
		{
			cout << endl << "> ";
			cin >> choice;

			switch (choice)
			{
			case 't':
			{
				ofstream toFile(libname, ios_base::out | ios_base::app);
				toFile << w.pol << " " << w.ang << " " << endl;
				toFile.close();

				cout << "Slowo dodane!" << endl;
				system("PAUSE");
				addWords();
				break;
			}
			case 'n':
			{
				addWords();
				break;
			}
			default:
			{
				cout << "Prosze wybrac poprawna opcje!" << endl;
				break;
			}
			}
		}
	}
	libCheck.close();
}

void removeWords()
{
	string input, libname;

	system("CLS");

	cout << "Dostepne biblioteki:" << endl;

	listLibs();

	cout << endl << "Wybierz biblioteke, w ktorej znajduje sie slowo do usuniecia:" << endl << "> ";
	cin >> input;

    if (input == "wstecz")
        menu();

	libname = toFileName(input);

	fstream fin (libname);

	if (!fin)
    {
        cout << "Blad! Taka biblioteka nie istnieje!" << endl;
        system("PAUSE");
        fin.close();
        removeWords();
    }


	cout << "Slowa aktualnie znajdujace sie w bibliotece:" << endl;

	int c = 1;

    string temp1, temp2;

	while (fin >> temp1 >> temp2)
    {
        cout << c << ". " << temp1 << " - " << temp2 << endl;
        c++;
    }

    fin.close();

    int line;

    cout << endl << "Wybierz numer slowa, ktore ma zostac usuniete:" << endl << "> ";
    cin >> line;

    eraseFileLine(libname, line);

    cout << "Slowo usuniete pomyslnie!" << endl;
    system("PAUSE");
    removeWords();

}
//adds words to word files

void play()
{
	int mode = NULL;

    system("CLS");

	if (lib.empty())
	{
		cout << "Blad: nie wybrano zadnych slow!" << endl;
		system("PAUSE");
		menu();
	}


	for (int i = 0; i < lib.size(); i++)
	{
		ifstream readWords(toFileName(lib[i]));
		string temp1, temp2;

		while (readWords >> temp1 >> temp2)
		{
			word w;

			w.pol = temp1;
			w.ang = temp2;

			words.push_back(w);
		}
	}

		cout << "Wybierz tryb gry:" << endl;
		cout << "1. Z Angielskiego na Polski" << endl;
		cout << "2. Z Polskiego na Angielski" << endl;
		cout << "3. Powrot do menu" << endl;
		cout << "> ";

		char choice;
		int status = 0;
		while (status < 1)
		{
			cin >> choice;

			switch (choice)
			{
			case '1': mode = 1; status++; break;
			case '2': mode = 2; status++; break;
			case '3': menu(); break;

			deafault:
			{
				cout << "Prosze wybrac poprawna opcje (1 lub 2)!" << endl;
				system("PAUSE");
				break;
			}
			}
		}


	string a;
	int c;
	int score = 0;
    vector <int> usedNum;

	srand(time(NULL));

	system("CLS");
	for (int i = 0; i < words.size(); i++)
	{
		if (mode == 1)
		{
			int x = randUnique(words.size(), usedNum);
			//draws random numbers
			string b;
			system("CLS");
			cout << "ENG: " << words[x].ang << endl;
			cout << "PL: ";        //gives the word name in polish
			cin >> b;                //implements word in english

			if (b == words[x].pol)//counts points earned from test
			{
				cout << "Odpowiedz poprawna!" << endl;
				Sleep(500);
				score++;
			}

			else
			{
				cout << "Odpowiedz bledna!" << endl;
				cout << "Poprawna odpowiedz: " << words[x].pol << endl;
				system("PAUSE");
				score += 0;
			}

			usedNum.push_back(x);
		}

		else
		{
			int x = randUnique(words.size(), usedNum);        //draws random numbers
			string b;
			system("CLS");
			cout << "PL: " << words[x].pol << endl;        //gives the word name in english
			cout << "ENG: ";
			cin >> b;                //implements word in polish

			if (b == words[x].ang)
			{
				cout << "Odpowiedz poprawna!" << endl;
				Sleep(500);
				score++;
			}
			//counts points earned from test
			else
			{
				cout << "Odpowiedz bledna!" << endl;
				cout << "Poprawna odpowiedz: " << words[x].ang << endl;
				system("PAUSE");
				score += 0;
			}

			usedNum.push_back(x);

		}
	}
	system("CLS");
	cout << "Test zakonczony. Twoj wynik wynosi " << score << " / " << words.size() << endl << endl; //score divided by number of words
	system("PAUSE");
	menu();
}
//testing module of the app

void libChoice()
{
	string input = "0";

	system("CLS");

	cout << "Dostepne biblioteki:" << endl;
	listLibs();
	cout << endl;

	if (!lib.empty())
	{
		cout << "Wybrane biblioteki: " << endl;

		for (int i = 0; i < lib.size(); i++)
			cout << i + 1 << ". " << lib[i] << endl;
	}
	else
		cout << "Nie wybrano zadnej biblioteki!" << endl;

	cout << endl;

	cout << "Wprowadz nazwe biblioteki, ktora chcesz dodac:" << endl;

	cout << "> ";
	cin >> input;

	if (input == "reset")
	{
		while (!lib.empty())
			for (int i = 0; i < lib.size(); i++)
				lib.pop_back();

		libChoice();
	}
	else
		if (input == "wstecz")
			menu();
		else
		{
			ifstream fileCheck(toFileName(input));

			if (!fileCheck)
			{
				cout << "Blad: wybrany plik nie istnieje!" << endl;
				system("PAUSE");
				libChoice();
			}
			else
				lib.push_back(input);
			libChoice();
		}

}

void menu()
{
	system("CLS");

	int choice = 0;

	if (!lib.empty())
	{
		cout << "Wybrane biblioteki: " << endl << endl;

		for (int i = 0; i < lib.size(); i++)
			cout << i + 1 << ". " << lib[i] << endl;
	}
	else
		cout << "Nie wybrano zadnej biblioteki!" << endl;

	cout << endl << "Menu glowne:" << endl;
	cout << "1. Rozpocznij test" << endl;
	cout << "2. Wybierz biblioteki slow" << endl;
	cout << "3. Dodaj slowa" << endl;
	cout << "4. Usun slowa" << endl;
	cout << "5. Wyjdz z programu" << endl;

	cout << "> ";
	cin >> choice;

	switch (choice)
	{
	case 1: play(); break;
	case 2: libChoice(); break;
	case 4: removeWords(); break;
	case 3: addWords(); break;
	case 5: break;

	default:
	{
		menu();
		break;
	}
	}
}
//just app menu (optional)
int main()
{
	menu();

	return 0;
}
//main function
