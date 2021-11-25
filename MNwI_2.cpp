// Program: MNwI_zadanie1, 21.11.2021
// Autor: Szynal Lukasz, 150063, 2021/2022, Informatyka, D2, II semestr

#include <iostream>
#include <cmath>

using namespace std;

/* 
Proszę przygotować program do obliczania wyznacznika macierzy do stopnia (co najmniej) piątego. 
*/

int** Submatrix(int** matrix, int n, unsigned int x, unsigned int y) { // Podmacierze macierzy wejsciowej
    int** submatrix = new int* [n - 1];
    int subi = 0;
    for (int i = 0; i < n; i++) {
        submatrix[subi] = new int[n - 1];
        int subj = 0;
        if (i == y) {
            continue;
        }
        for (int j = 0; j < n; j++) {
            if (j == x) {
                continue;
            }
            submatrix[subi][subj] = matrix[i][j];
            subj++;
        }
        subi++;
    }
    return submatrix;
}

int Determinant(int** matrix, int n) { // Funkcja licząca wyznacznik
    int det = 0;
    if (n == 1) return matrix[0][0]; // Wyznacznik macierzy jednoelementowej jest równy jej elementowi
    if (n == 2) {
        return matrix[0][0] * matrix[1][1] - matrix[1][0] * matrix[0][1]; // Dla macierzy 2x2 wykonujemy ta czesc kodu
    }
    for (int x = 0; x < n; ++x) { // Dla większych macierzy liczymy ich wyznaczniki i używamy je do wyliczenia dopełnień algebraicznych elementów macierzy na wyższym poziomie.
        det += ((x % 2 == 0 ? 1 : -1) * matrix[0][x] * Determinant(Submatrix(matrix, n, x, 0), n - 1)); // Rekurencja kończy się, gdy dojdziemy do podmacierzy jednoelementowych.
    }
    return det;
}

void WyswietlMacierz(int** matrix, int n) // Graficznie wyswietlamy macierz
{
    int max = 0;
    int min = 0;
    for (int row = 0; row < n; row++)
        for (int collumn = 0; collumn < n; collumn++) {
            if (matrix[row][collumn] > max) max = matrix[row][collumn];
            if (matrix[row][collumn] < min) min = matrix[row][collumn];
        }

    int strmax = to_string(max).length();
    int strmin = to_string(min).length();
    int cyfry = strmax;
    if (cyfry < strmin) cyfry = strmin;
    cout << "\n\n";
    if (cyfry < 6) {
        cout << "+";
        for (int i = 0; i < n; i++) cout << "------+";
        cout << "\n";
        for (int row = 0; row < n; row++)
            for (int collumn = 0; collumn < n; collumn++) {
                int liczba = to_string(matrix[row][collumn]).length();
                switch (liczba) {
                case 1:     cout << "| " << matrix[row][collumn] << "    "; break;
                case 2:     cout << "| " << matrix[row][collumn] << "   "; break;
                case 3:     cout << "| " << matrix[row][collumn] << "  "; break;
                case 4:     cout << "| " << matrix[row][collumn] << " "; break;
                case 5:     cout << "| " << matrix[row][collumn] << " "; break;
                }
                if (collumn == n - 1) {
                    cout << "|\n";
                    cout << "+";
                    for (int i = 0; i < n; i++) cout << "------+";
                    cout << "\n";
                }
            }
        cout << "\n";
    }
}

void Wyznacznik() {
    int n;

    cout << "|| WYZNACZNIK MACIERZY ||\n\n";
    cout << "Podaj stopien macierzy: ";
    cin >> n;

    if (n > 0) {
        cout << "\nWprowadz dane do macierzy:" << endl;
        int** matrix = new int* [n]; // Tworzymy tablice dynamiczna
        for (int i = 0; i < n; ++i) {
            matrix[i] = new int[n];
            for (int j = 0; j < n; ++j) { // Wprowadzamy dane do macierzy
                cout << "Macierz " << n << " stopnia A[" << i + 1 << j + 1 << "]: ";
                cin >> matrix[i][j];
            }
        }
        WyswietlMacierz(matrix, n);
        cout << "Wyznacznik macierzy obliczony za pomoca reguly Laplace'a\n";
        cout << "det A = " << Determinant(matrix, n) << endl;
    }
    else cout << "Nie mozna obliczyc wyznacznika macierzy, ktora nie istnieje!\n";
}

/*
Proszę stworzyć narzędzie do znajdowania przybliżonych pierwiastków równania nieliniowego, co najmniej dwoma różnymi metodami,
a następnie dokonać analizy porównawczej tych metod na przykładach konkretnych równań.
*/

double Funkcja(int f, double x) // 2 funkcje do wyboru
{
    switch (f) {
    case 1: return (x * x * x) - (x * x) - x + 2;
    case 2: return sin(x * x - x + 1 / 3.0) + 0.5 * x;
    }    
}

void Pobierz_Dane(int& f, double& a, double& b, double& x1, double& x2, double& d) // Pobieramy potrzebne dane
{
    cout << "FUNKCJE:\n";
    cout << "1: f(x) = (x * x * x) - (x * x) - x + 2\n";
    cout << "2: f(x) = sin(x * x - x + 1 / 3.0) + 0.5 * x\n";
    while (f != 1 && f != 2) {
        cout << "Wybierz: ";
        cin >> f;
    }
    cout << "\nPodaj zakres poszukiwan pierwiastka dla metody bisekcji\n";
    cout << "Podaj poczatek zakresu: "; 
    cin >> a;
    cout << "Podaj koniec zakresu: "; 
    cin >> b;
    while (Funkcja(f, a) * Funkcja(f, b) > 0 ) { //Sprawdzamy, czy na krańcach przedziału [a,b] wartości funkcji mają różne znaki
        cout << "Ta funkcja dla tego zakresu nie ma miejsca zerowego. Podaj inne dane!\n"; 
        cout << "Podaj poczatek zakresu: ";
        cin >> a;
        cout << "Podaj koniec zakresu: ";
        cin >> b;
    }
    cout << "\nPodaj krancowe punkty poszukiwan pierwiastka dla metody siecznych\n";
    cout << "Podaj poczatek przedzialu: "; 
    cin >> x1;
    cout << "Podaj koniec przedzialu: "; 
    cin >> x2;
    cout << "\nPodaj dokladnosc wyniku: "; 
    cin >> d; // Dokladnosc wyznaczania pierwiastka
}

double Miejsce_Zerowe_Bisekcja(int f, double a, double b, double d, int& i)
{
    double x0 = (a + b) / 2; // Wyznaczamy środek przedziału
    while (fabs(Funkcja(f, x0)) >= d) { // Sprawdzamy, czy szerokosc przedziału [a,b] jest mniejsza od dokladnosci
        if ((Funkcja(f, a) * Funkcja(f, x0)) < 0) b = x0; // Za nowy przedział [a,b] przyjmujemy tą z polowek, w której funkcja ma różne znaki na krańcach
        else a = x0;
        x0 = (a + b) / 2;
        i += 1; // Liczymy ilosc iteracji
    }
    return x0;   // Zwracamy wynik
}

void Metoda_Bisekcji(int f, double a, double b, double d, int i)
{
    double wynik;
    i = 0; // Zerujemy licznik iteracji
    cout << "\n|| MIEJSCE ZEROWE FUNKCJI METODA POLOWIENIA PRZEDZIALU ||\n";
    wynik = Miejsce_Zerowe_Bisekcja(f, a, b, d, i); // Zapisujemy wynik do zmiennej
    cout << "Pierwiastek x0 wynosi:         " << setw(18) << setprecision(10) << fixed << wynik << endl;
    cout << "Wartosc funkcji f(x0) wynosi:  " << setw(18) << setprecision(10) << fixed << Funkcja(f, wynik) << endl;
    cout << "Dokladnosc wyniku wynosi:      " << setw(18) << setprecision(10) << fixed << d << endl;
    cout << "Liczba iteracji:               " << setw(18) << i << endl;
}

double Miejsce_Zerowe_Sieczne(int f, double x1, double x2, double d, int& i)
{
    double x0 = 0, f0, f1, f2;
    bool result = false; // Zmienna informująca o poprawnym zakończeniu metody

    f1 = Funkcja(f, x1); // Wartosc funkcji na poczatku przedzialu
    f2 = Funkcja(f, x2); // Wartosc funkcji na koncu przedzialu
    while (--i) {
        x0 = (f1 * x2 - f2 * x1) / (f1 - f2); // Punkt przecięcia siecznej z osią X
        f0 = Funkcja(f, x0); // Wartość funkcji w punkcie przecięcia
        if ((fabs(f0) < d) || fabs(x0 - x2) < d) // Sprawdzamy warunki zakończenia
        {
            result = true;
            break;
        }
        x1 = x2; // Uaktualnie przyblizen
        f1 = f2;
        x2 = x0;
        f2 = f0;
    }
    if (!result) cout << "!! PRZEKROCZONO LICZBE OBIEGOW !!\n";
    return x0;
}

void Metoda_Siecznych(int f, double x1, double x2, double d, int i)
{
    double wynik;
    int n = i = 100; // Maksymalna liczba obiegow
    cout << "\n|| MIEJSCE ZEROWE FUNKCJI METODA SIECZNYCH ||\n";
    wynik = Miejsce_Zerowe_Sieczne(f, x1, x2, d, i); // Zapisujemy wynik do zmiennej
    cout << "Pierwiastek x0 wynosi:         " << setw(18) << setprecision(10) << fixed << wynik << endl;
    cout << "Wartosc funkcji f(x0) wynosi:  " << setw(18) << setprecision(10) << fixed << Funkcja(f, wynik) << endl;
    cout << "Dokladnosc wyniku wynosi:      " << setw(18) << setprecision(10) << fixed << d << endl;
    cout << "Liczba iteracji:               " << setw(18) << n - i << endl;
}

void Pierwiastki()
{
    double a = 0, b = 0, d = 0, x1 = 0, x2 =0;
    int i = 0, f =0;
    cout << "\n|| PIERWIASTKI FUNKCJI NIELINIOWYCH ||\n\n";
    Pobierz_Dane(f, a, b, x1, x2, d);
    Metoda_Bisekcji(f, a, b, d, i);
    Metoda_Siecznych(f, x1, x2, d, i);
}

/*Blok glowny programu*/

int main()
{
    cout << "Program obliczajacy wyznacznik macierzy oraz znajdujacy przyblizone pierwiastki rownania nieliniowego" << endl;
    cout << "Autor: Lukasz Szynal, 150063, 2021/2022, Informatyka, D2, II semestr" << endl;
    cout << "====================================================================" << endl << endl;
    Wyznacznik();
    Pierwiastki();
}
