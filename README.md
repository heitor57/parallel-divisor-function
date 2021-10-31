# MPI Divisor Function

## Requirements

- MPI (e.g., Open-MPI)
- GCC
- CMake (used to facilitate the management of multiple executables, used to facilitate the management of multiple executables, which is difficult to do with Makefile)
- Python3.8 (required to the extra package, it's optional) (results checker and input generator)

## Artifacts

	.
	├── README.md
	├── data # data directory
	│   ├── t1e4.txt
	│   ├── t1e5.txt
	│   ├── t1e6.txt
	│   └── t1e7.txt
	├── Makefile # Makefile that compiles the program using CMake and also expose other functions
	├── serialdf # Serial version of the divisor function program
	├── paralleldf # Parallel version using MPI of the divisor function program
	├── src
	│   ├── dfpack.c # divisor function package
	│   ├── dfpack.h # divisor function package header
	│   ├── parallel.c # parallel program
	│   ├── serial.c # serial program
	│   ├── utils.c # utilities (e.g.,I/O)
	│   └── utils.h # utilities
	└── test # (extra package)
			├── df.py # divisor function using a Python library to check results and validity of the program
			├── random_numbers.py # random generator of inputs to the program
			├── generate_bases # generate some predefined inputs for the programs used in the documentation
			└── run_bases # execute the program in these bases and saves results

## Usage (examples)

	make
	./serialdf input.txt output_serial.txt
	mpirun -n 4 ./paralleldf input.txt output_parallel.txt
	fin=data/t1e5; ./serialdf "$fin".txt "$fin"_serial.txt
	fin=data/t1e7; mpirun --mca opal_warn_on_missing_libcuda 0 --use-hwthread-cpus -n 4 ./paralleldf "$fin".txt "$fin"_parallel.txt
