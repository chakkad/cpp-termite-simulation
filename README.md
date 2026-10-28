# Termite Simulation in C++

A modular C++ project developed as part of the *Programmation Modulaire* coursework at Université Paris-Saclay.

The project simulates a grid-based world inhabited by two groups of termites, each building their own huts.

## Features

- **Grid-based simulation:** Represents the world using a two-dimensional grid.
- **Termite behavior:** Models termites interacting with their environment.
- **Two termite groups:** Simulates two groups building their own huts.
- **Modular design:** Separates coordinates, directions, grid management, and termite logic into distinct modules.
- **Testing:** Includes a separate test executable.
- **Automated build:** Uses a Makefile to compile and link the project.

## Technologies

- C++
- C++11
- GNU `g++`
- GNU Make

## Project Structure

| File | Description |
|---|---|
| `projet.cpp` | Main program and simulation entry point |
| `coord.cpp` / `coord.hpp` | Coordinate representation and operations |
| `grille.cpp` / `grille.hpp` | Grid representation and cell management |
| `termite.cpp` / `termite.hpp` | Termite representation and behavior |
| `test.cpp` | Test program |
| `Makefile` | Compilation, linking, and test commands |


### Prerequisites

- A C++ compiler supporting C++11
- GNU Make

### Compile the project

From the project directory, run:

```bash
make
```

### Run the simulation

On Linux or in an MSYS2 terminal:

```bash
./projet-main
```

### Run the tests

Build the test executable:

```bash
make tests
```

Then run it in the appropriate terminal:

```bash
./tests -s
```

### Clean generated files

```bash
make clean
```

## Concepts Practiced

- Modular programming in C++
- Abstract data types and encapsulation
- Classes and enumerations
- Operator overloading
- Grid and state representation
- Exception handling
- Separate compilation and linking
- Testing and build automation

## Academic Context

Developed for the *Travaux Pratiques Projet Termites* assignment in the *Programmation Modulaire* course at Université Paris-Saclay.
