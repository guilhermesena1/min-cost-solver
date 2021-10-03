all: min-cost-solver

min-cost-solver: min-cost-solver.cpp
	g++ -O3 -Wall -o min-cost-solver min-cost-solver.cpp -std=c++11
