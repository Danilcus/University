#include <iostream>
#include <bitset>
using namespace std;

int main()
{
	union
	{
		float f_num;
		unsigned int f_buffer;
	};

	cout << "Please enter your float value" << endl;
	cin >> f_num;

	union
	{
		double d_num;
		unsigned int d_buffer[2];
	};
	cout << "Please enter your double value" << endl;
	cin >> d_num;

	bool f_sign = (f_buffer >> 31) & 1;					// 10000000000000000000000000000000
	short f_exponent = (f_buffer & 0x7F800000) >> 23;	// 01111111100000000000000000000000
	int f_mantissa = f_buffer & 0x7FFFFF;				// 00000000011111111111111111111111

	cout << "int representation of float" << f_buffer << endl;
	cout << "Float sign is " << bitset<1>(f_sign) << endl
		<< "Float exponent is " << f_exponent << endl
		<< "Float mantissa is " << f_mantissa << endl << endl;

	int64_t d_int = reinterpret_cast<int64_t&>(d_num);
	bool d_sign = (d_buffer[1] >> 31) & 1;												// 1000000000000000000000000000000000000000000000000000000000000000
	short d_exponent = (d_buffer[1] & 0x7FF00000) >> 20;								// 0111111111110000000000000000000000000000000000000000000000000000
	int64_t d_mantissa = reinterpret_cast<int64_t&>(d_num) & (((int64_t)1 << 53) - 1);	// 0000000000001111111111111111111111111111111111111111111111111111

	cout << "int representation of double " << d_int << endl;
	cout << "Double sign is " << bitset<1>(d_sign) << endl
		<< "Double exponenta is " << d_exponent << endl
		<< "Double mantissa is " << d_mantissa << endl; 

	return 0;
}