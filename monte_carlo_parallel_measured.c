// Edwin Harmata, 38682
// Implementacja metodologią PCAM przy pomocy MPI

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "mpi.h"

#define DEFAULT_ITERATIONS_NUMBER 1000000

int mod(int a, int b)
{
	int r = a % b;
	return r < 0 ? r + b : r;
}

int main(int argc, char **argv)
{
	// Inicjalizujemy zmienne MPI
	int num_procs;
	int ID, j;

	// Inicjalizujemy zmienne programu
	int liczba_losowan, liczba_losowan_w_procesorze;
	long double x, y;
	int i, suma_ile_w_kole, ile_w_kole = 0;
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

	ile_w_kole = 0;

	// Inicjalizujemy środowisko do pracy współbieżnej
	MPI_Status stat;

	// MPI Setup
	if (MPI_Init(&argc, &argv) != MPI_SUCCESS)
	{
		printf("MPI_Init error\n");
	}

	MPI_Comm_size(MPI_COMM_WORLD, &num_procs); // Set the num_procs
	MPI_Comm_rank(MPI_COMM_WORLD, &ID);

	printf("Aplikacja pracuje na %d procesorach\n", num_procs);
	printf("Aktualnie pracuje procesor: %d\n", ID);

	liczba_losowan_w_procesorze = liczba_losowan / num_procs;

	// Tworzymy inny seed dla każdego procesora w celu wygenerowania innych liczb
	srand(time(NULL) * (ID + 1));

	// Generujemy w pętli losowe punkty i sprawdzamy czy mieszczą się w kole
	for (i = 0; i < liczba_losowan_w_procesorze; i++)
	{
		x = (long double)rand() / RAND_MAX;
		y = (long double)rand() / RAND_MAX;
		z = x * x + y * y;
		// Jeśli się mieszczą w kole, to inkrementujemy zmienną
		if (z <= 1)
			ile_w_kole++;
	}
	pi = (long double)ile_w_kole / liczba_losowan_w_procesorze * 4;

	printf("Dla procesora %d po %d iteracjach, liczba w kole to %d, a przyblizona liczba pi to: %Lg\n", ID, liczba_losowan_w_procesorze, ile_w_kole, pi);

	// Współbieżną część kodu realizujemy gdy mamy większą niż 1 liczbę procesów
	// W innym wypadku zwracamy rezultat pracy synchronicznego kodu
	if (num_procs != 1)
	{
		// Sumujemy częściowe wyniki obliczone w procesach
		MPI_Reduce(&ile_w_kole, &suma_ile_w_kole, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);

		// Zwracamy wynik pracy asynchonicznego kodu
		if (ID == 0)
		{
			// Obliczamy liczbę pi
			printf("Liczba trafionych asynchronicznych wyników to: %d\n", suma_ile_w_kole);
			pi = (long double)suma_ile_w_kole / liczba_losowan * 4;
			// Zwracamy wynik
			printf("Po %d próbach, szacowana liczba PI to: %Lg \n", liczba_losowan, pi);
		}
	}
	else
	{
		// Zwracamy wynik pracy synchonicznego kodu
		// Obliczamy liczbę pi
		pi = (long double)ile_w_kole / liczba_losowan * 4;
		// Zwracamy wynik
		printf("Po %d próbach, szacowana liczba PI to: %Lg \n", liczba_losowan, pi);
	}

	MPI_Finalize(); // kończymy pracę kodu współbieznego

	return 0;
}