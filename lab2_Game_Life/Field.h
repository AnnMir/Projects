#pragma once
#include "Cell.h"
#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>
#include <string>



namespace Life{
	class Field{
	private:
		int height;
		int width;
		Cell **prev;
		Cell **cell;
	public:
		Field(int, int);
		char check_neighbors(int, int);
		void print_field();
		int count_cells();
		void step_back();
		void delete_all_cells();
		void create_cell(int, int);
		void delete_cell(int, int);
		void random_creation();
		std::string next();
		void load_to_file(std::ofstream*);
		void get_from_file(std::ifstream*);
		~Field();
	};
}