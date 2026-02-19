#include <iostream>
using namespace std;

int main () 
{
	int array[] = {4, 17, 3, 28, 10, 15, 32, 7, 23, 9};

	int n = sizeof(array) /  sizeof(array[0]);
	
	int *ptArray;
	ptArray = array;
	
	//cetak elemen array
	cout << "======= Elemen Array =======" << endl;
	for (int i = 0; i < n; i++)
	{
	cout << "Elemen ke-" << i << " = " << *(ptArray + i) << endl;
	}
	
	//nilai min maks
	int maks = *(ptArray);
	int min  = *(ptArray);
	
	for (int i = 1; i < n; i++)
	{
		if (*(ptArray + i) > maks)
			maks = *(ptArray + i);
			
		if (*(ptArray + i) < min)
			min = *(ptArray + i);
	}
	
	cout << "\n===== Maksimum dan Minimum ====" << endl;
	
	cout << "Nilai Maksimum : " << maks << endl;
	cout << "Nilai Minimum  : " << min << endl;
	
	int jumlah = 0;
	
	for (int i = 0; i < n; i++)
	{
		jumlah = jumlah + *(ptArray + i);
	}
	
	double rataRata = (double)jumlah / n;
	
	//Memunculkan hasil jumlah dan rataRata
	cout << "\n======= Jumlah dan Rata-rata =======" << endl;
	cout << "Jumlah		: " << jumlah << endl;
	cout << "Rata-rata	: " << rataRata << endl; 
	
	return 0;
	}
