#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main()
{
	string mystr;
	short int type = 0;
	short int base = 0;
	string dump;

	cout << "If you want float enter 4, if you want double enter 8 ";
	getline(cin, mystr);
	stringstream(mystr) >> type;
	cout << "Enter base of dump for bin - 2, for oct - 8, for hex - 16 ";
	getline(cin, mystr);
	stringstream(mystr) >> base;
	cout << "Enter appropriate dump (use Upper case for hex)";
	getline(cin, dump);

	switch (type)
	{
	case 4:
	{
		union
		{
			float result;
			unsigned int buffer;
		};

		switch (base)
		{
		case 2:
		{
			buffer = stoul(dump, 0, 2); //11000000101001100110011001100110 = -5.2
			break;
		}
		case 8:
		{
			istringstream(dump) >> oct >> buffer; // 30051463146 = -5.2
			break;
		}
		case 16:
		{
			istringstream(dump) >> hex >> buffer; //C0A66666 = -5.2
			break;
		}
		}
		cout << result << endl;
		break;
	}
	case 8:
	{
		union
		{
			double result;
			unsigned int buffer[2];
		};

		switch (base)
		{
		case 2:
		{
			buffer[1] = stoul(dump.substr(0, 32), 0, 2); //1011111111110000000000000000000000000000000000000000000000000000 = -1
			buffer[0] = stoul(dump.substr(33, 64), 0, 2);
			break;
		}
		case 8:
		{
			istringstream(dump.substr(0, 11)) >> oct >> buffer[1]; //1377600000000000000000 = -1
			istringstream(dump.substr(12, 22)) >> oct >> buffer[0];
			break;
		}
		case 16:
		{
			istringstream(dump.substr(0, 8)) >> hex >> buffer[1]; //BFF0000000000000 = -1
			istringstream(dump.substr(9, 16)) >> hex >> buffer[0];
			break;
		}
		}
		cout << result << endl;
		break;
	}

	}
	return 0;
}