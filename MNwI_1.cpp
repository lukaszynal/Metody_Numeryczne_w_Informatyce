// Program: MNwI_zadanie1, 11.11.2021
// Autor: Szynal Lukasz, 150063, 2021/2022, Informatyka, D2, II semestr

#include <iostream>
#include <cmath>

using namespace std;

/*
Przygotować narzędzie do wyznaczania wartości interpolowanych oraz ekstrapolowanych funkcji dyskretnej, stosując interpolacje wielomianową.
Przetestować swój program na poniższym przykładzie:

Obserwowano ruch w sieci z interwałem 1 godzina. Wyniki zestawiono w poniższej tabeli.

Godzina	Mb/s	Godzina	Mb/s
1:00		0,10	12:00		8,00
2:00		0,11	13:00		3,2
3:00		0,9	    14:00		8,00
4:00		0,12	15:00		6,50
5:00		0,42	16:00		1,20
6:00		0,10	17:00		1,90
7:00		1,02	18:00		0,9
8:00		4,00	19:00		1,1
9:00		5,27	20:00		0,25
10:00		4,09	21:00		0,20
11:00		8,00	22:00		0,19
                    23:00		0,20

Przygotować narzędzie, które umożliwi wyznaczanie w miarę jak najdokładniejsze wartości obciążeń o dowolnej godzinie
(pomiędzy pomiarami), a i ułatwi inwestorom oszacowanie obciążenie sieci w najbliższej przyszłości?
Za pomocą utworzonego narzędzia wyznaczyć, jaka była wielkość używanego pasma (w Mb/s) o godz. 14:45 oraz 15:30?
*/

/*Funkcje interpolacji wielomianu wedlug wzoru Newtona*/

double Pierwszy_Rzad(double* tabX, double* tabY, int l) 
{	
	return (tabY[l + 1] - tabY[l]) / (tabX[l + 1] - tabX[l]); // Iloraz pierwszego rzędu
}

double Newton(double* tabX, double* tabY, int i, int l) // Iloraz dowolnego rzedu (i - rzad, l - index pierwszego x)
{
	if (i == 0) return 1; // Zwraca 1 na potrzeby petli ponizej.
    if (i == 1) return Pierwszy_Rzad(tabX, tabY, l);
	return	(Newton(tabX, tabY, i - 1, l + 1) - Newton(tabX, tabY, i - 1, l)) / (tabX[l + i] - tabX[l]); // Rekurencyjnie wywolanie tylko rzad nizej, 'l' ustawiane jak we wzorze

}
void Interpolacja() {

	int iloscPunktow = 23;
	double x = 1;
	
    // dane bazowe
	double tabX[] = { 1.00, 2.00, 3.00, 4.00, 5.00, 6.00, 7.00, 8.00, 9.00, 10.00, 11.00, 12.00, 13.00, 14.00, 15.00, 16.00, 17.00, 18.00, 19.00, 20.00, 21.00, 22.00, 23.00 };
	double tabY[] = { 0.10, 0.11, 0.90, 0.12, 0.42, 0.10, 1.02, 4.00, 5.27,  4.09,  8.00,  8.00,  3.20,  8.00,  6.50,  1.20,  1.90,  0.90,  1.10,  0.25,  0.20,  0.19,  0.20 };
	
    cout << "Wyznaczanie w miare jak najdokladniejszych wartosci obciazenia sieci dla dowolej godziny\n";
    cout << "za pomoca interpolacji wielomianu wedlug wzoru Newtona.\n\n";
    
    while(true) {
    cout << "Wpisz godzine(x) w formacie gg.mm, aby zakonczyc wpisz -1: ";
    cin >> x;
    if (x == -1) break;
	double result = tabY[0]; //Ustawiamy wynik na y0 
	double tmp = 0;			//Zmienna pomocnicza. Sumujemy dla kazdego N (gdzie N to liczba punktów)
	for (int i = 0; i < iloscPunktow; i++)
	{
		tmp = 0;				//Reset zmiennej pomocniczej
		for (int j = 0; j < i; j++) {	//Petla wykonywana i razy.
			if (j == 0) tmp = x - tabX[0];	//Przypisanie wartosci do zmiennej pomocniczej przy pierwszej pętli
			else tmp *= x - tabX[j];		 
		}
		result += tmp * Newton(tabX, tabY, i, 0);	//Dodajemy do wartosci koncowej wynik mnozenia oraz iloraz o i-tym rzędzie.
	}
	cout << "Obciazenie sieci w Mb/s dla godziny(x)= " << x << " to: " << result << endl << endl;
    }
}

/*
Proszę napisać program wyznaczający przybliżoną wartość całki oznaczonej za pomocą złożonego wzoru trapezów.
*/

/*Funkcje obliczania całki oznaczonej metoda trapezow*/

void Czytaj_Dane(double & a, double & b, int & n) //Pobieramy potrzebne dane
{
    cout << "Podaj liczbe podzialow n: "; cin >> n;
    cout << "Podaj poczatek odcinka z zakresu <0, 100>: "; cin >> a;
    while (a<0 || a>100) {
        cout << "Podaj poczatek odcinka w zakresie <0, 100>: "; cin >> a;
    }
    cout << "Podaj koniec odcinka: "; cin >> b;
    while (b<a || b>100) {
        cout << "Podaj koniec odcinka w zakresie <" << a << ", 100>: "; cin >> b;
    }
}

double Funkcja(double x)
{
    return sin(x); //Funkcja sinus
}

double Wynik_Calka(double & a, double & b, int & n)
{
    double dx, calka = 0;
    int i;

    Czytaj_Dane(a, b, n);
    dx = (b - a) / n; //Obliczamy odległość „dx” pomiędzy sąsiednimi punktami podziałowymi
    for(i = 1; i<n; i++) calka += Funkcja(a + i * dx); //Obliczamy calke na podstawie wczesniej zdefiniowanej funkcji i-ta ilosc razy
    calka = (calka + (Funkcja(a) + Funkcja(b)) / 2) * dx;
    return calka;
}

void Calka()
{
    double a = 0, b = 0;
    int n = 0;

    cout << "\n====================================================================\n\n";
    cout << "Obliczanie calki oznaczonej metoda trapezow dla funkcji sinus\n\n";
    double calka = Wynik_Calka(a, b, n);
    cout << "Obliczenie calki oznaczonej metoda trapezow dla funkcji sinus:\n";
    cout << "Liczba podzialow n: " << n << endl;
    cout << "Przedzial <a,b>: <" << a << ", " << b << ">" << endl;
    cout << "Przyblizona wartosc calki: " << calka << endl;
}

/*Blok glowny programu*/

int main()
{
    cout << "Program wyznaczajacy wartosc obciazenia sieci w danej godzinie na podstawie zaimplementowanych danych\n";
    cout << "oraz obliczajacy calke oznaczona metoda trapezow.\n";
    cout << "Autor: Lukasz Szynal, 150063, 2021/2022, Informatyka, D2, II semestr\n";
    cout << "====================================================================\n\n";
	Interpolacja();
    Calka();
}
