// Edwin Harmata, 38682

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#define SEED 35791246
#define DEFAULT_ITERATIONS_NUMBER 1000000

int main(int argc, char **argv)
{
	// Inicjalizujemy zmienne programu
	int liczba_losowan;
	long double x, y;
	int i, ile_w_kole = 0;
	long double z;
	long double pi;

	// Odczytujemy parametry linii komend
	if (argc == 1)
	{
		liczba_losowan = DEFAULT_ITERATIONS_NUMBER;
	}
	else if (argc == 2)
	{
		liczba_losowan = atoi(argv[1]);
	}
	else
	{
		printf("Usage: ./monte_carlo <liczba_losowan 1..N> \n");
		exit(1);
	}

	srand(SEED);
	ile_w_kole = 0;

	// Generujemy w pętli randomowe punkty i sprawdzamy czy mieszczą się w kole
	for (i = 0; i < liczba_losowan; i++)
	{
		x = (long double)rand() / RAND_MAX;
		y = (long double)rand() / RAND_MAX;
		z = x * x + y * y;
		// Jeśli się mieszczą w kole, to inkrementujemy zmienną
		if (z <= 1)
			ile_w_kole++;
	}
	// Obliczamy liczbę pi
	pi = (long double)ile_w_kole / liczba_losowan * 4;
	// Zwracamy wynik
	printf("Po %d próbach, szacowana liczba PI to: %Lg \n", liczba_losowan, pi);

	return 0;
}