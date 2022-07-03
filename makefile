CC=mpicc

all: gol
gol:
	$(CC) monte_carlo.c -o monte_carlo
	$(CC) monte_carlo_parallel.c -o monte_carlo_parallel
	$(CC) monte_carlo_parallel_measured.c -o monte_carlo_parallel_measured
	$(CC) monte_carlo_measured.c -o monte_carlo_measured
clean:
	rm -r monte_carlo
