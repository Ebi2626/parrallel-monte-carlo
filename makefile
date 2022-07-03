CC=mpicc

all: gol
gol:
	$(CC) monte_carlo.c -o monte_carlo
	$(CC) monte_carlo_parallel.c -o monte_carlo_parallel
clean:
	rm -r monte_carlo
