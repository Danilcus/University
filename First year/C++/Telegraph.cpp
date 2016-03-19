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
	{ 'À',"13" },{ 'Á',"3111" },{ 'Ö',"3131" },{ 'Ä',"311" },
	{ 'Å',"1" },{ 'Ô',"1131" },{ 'Ã',"331" },{ 'Õ',"1111" },
	{ 'È',"11" },{ 'É',"1333" },{ 'Ê',"313" },{ 'Ë',"1311" },
	{ 'Ì',"33" },{ 'Í',"31" },{ 'Î',"333" },{ 'Ï',"1331" },
	{ 'Ù',"3313" },{ 'Ð',"131" },{ 'Ñ',"111" },{ 'Ò',"3" },
	{ 'Ó',"113" },{ 'Æ',"1113" },{ 'Â',"133" },{ 'Ü',"3113" },
	{ 'Û',"3133" },{ 'Ç',"3311" },{ '×',"3331" },{ 'Ø',"3333" },
	{ 'Ý',"11311" },{ 'Þ',"1133" },{ 'ß',"1313" }
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

