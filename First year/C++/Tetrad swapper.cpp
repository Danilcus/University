#include <iostream>
using namespace std;

int main()
{
	unsigned int x;
	int mask_1, mask_2, shi_i, shi_j;
	cout << "Enter the number ";
	cin >> x;

	cout << "Swapping tetrad 1 is" << endl;
	cin >> shi_i;
	cout << "Swapping tetrad 2 is" << endl;
	cin >> shi_j;

	if (shi_i>shi_j)
	{
		mask_1 = 0x00000000F;
		mask_2 = mask_1 << ((shi_j - 1) * 4);
		mask_1 = mask_1 << ((shi_i - shi_j) * 4);
		mask_1 = x&mask_1;
		mask_2 = x&mask_2;
		x = x^mask_1^mask_2;
		x = x | mask_1 >> ((shi_i - shi_j) * 4);
		x = x | mask_2 << ((shi_i - shi_j) * 4);
		cout << x;

	}

	else
	{
		mask_1 = 0x00000000F;
		mask_2 = mask_1 << ((shi_i - 1) * 4);
		mask_1 = mask_1 << ((shi_j - shi_i) * 4);
		mask_1 = x&mask_1;
		mask_2 = x&mask_2;
		x = x^mask_1^mask_2;
		x = x | mask_1 >> ((shi_j - shi_i) * 4);
		x = x | mask_2 << ((shi_j - shi_i) * 4);
		cout << x;
	}
}