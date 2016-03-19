#include <iostream>
#include <string>
#include <windows.h>
#include <map>
#include <locale>
using namespace std;

const int FREQUENCY = 500;
const int BEEP_DURATION = 150;
const int PAUSE_SYMBOL = BEEP_DURATION * 3;

map<char, string> morse_alphabet =
{
	{ 'A',"13" },{ 'B',"3111" },{ 'C',"3131" },{ 'D',"311" },
	{ 'E',"1" },{ 'F',"1131" },{ 'G',"331" },{ 'H',"1111" },
	{ 'I',"11" },{ 'J',"1333" },{ 'K',"313" },{ 'L',"1311" },
	{ 'M',"33" },{ 'N',"31" },{ 'O',"333" },{ 'P',"1331" },
	{ 'Q',"3313" },{ 'R',"131" },{ 'S',"111" },{ 'T',"3" },
	{ 'U',"113" },{ 'V',"1113" },{ 'W',"133" },{ 'X',"3113" },
	{ 'Y',"3133" },{ 'Z',"3311" },{ '1',"13333" },{ '2',"11333" },
	{ '3',"11133" },{ '4',"11113" },{ '5',"11111" },{ '6',"31111" },
	{ '7',"33111" },{ '8',"33311" },{ '9',"33331" },{ '0',"33333" },
	{ ',',"331133" },{ '.',"131313" },{ '?',"113311" },{ ';',"31313" },
	{ ':',"333111" },{ '/',"31131" },{ '-',"311113" },{ '\'',"133331" },
	{ '_',"113313" },{ '@',"133131" },{ ' ',"4" }, //for ' '(space) we use 4, because after any sign we have pause of symbol, 4+3=7
	{ 'А',"13" },{ 'Б',"3111" },{ 'Ц',"3131" },{ 'Д',"311" },
	{ 'Е',"1" },{ 'Ф',"1131" },{ 'Г',"331" },{ 'Х',"1111" },
	{ 'И',"11" },{ 'Й',"1333" },{ 'К',"313" },{ 'Л',"1311" },
	{ 'М',"33" },{ 'Н',"31" },{ 'О',"333" },{ 'П',"1331" },
	{ 'Щ',"3313" },{ 'Р',"131" },{ 'С',"111" },{ 'Т',"3" },
	{ 'У',"113" },{ 'Ж',"1113" },{ 'В',"133" },{ 'Ь',"3113" },
	{ 'Ы',"3133" },{ 'З',"3311" },{ 'Ч',"3331" },{ 'Ш',"3333" },
	{ 'Э',"11311" },{ 'Ю',"1133" },{ 'Я',"1313" }
};

int main()
{
	system("chcp 1251");
	string message;
	cout << "Enter your message " << endl;
	getline(cin, message);

	for each (char symbol in message)
	{
		string morse_code;
		try //looking for unexpected symbols
		{
			char upper_symbol = toupper(symbol, locale("rus_rus.1251"));//making all chars in upper 
			morse_code = morse_alphabet.at(upper_symbol);
		}
		catch (...) //if there are any
		{
			cout << endl << "use apropriate symbols" << endl;
			return 0;
		}

		for each (char morse_symbol in morse_code)
		{
			byte duration = int(morse_symbol) - 48;
			if (symbol == ' ')
			{
				cout << symbol;
				Sleep(BEEP_DURATION * duration);
			}
			else
			{
				Beep(FREQUENCY, BEEP_DURATION * duration);
				if (morse_symbol == '1') cout << '.';
				if (morse_symbol == '3') cout << '-';
				Sleep(BEEP_DURATION);
			}
		}
		Sleep(PAUSE_SYMBOL);
	}
	cout << endl;
	return 0;
}

