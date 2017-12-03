#include "Field.h"

namespace Life{
	Field::Field(int width, int height) : width(width), height(height){
		cell = new Cell*[width];
		for (int i = 0; i < width; i++) {
			cell[i] = (Cell*)operator new(sizeof(Cell)* height);
			for (int j = 0; j < height; j++) {
				new(&cell[i][j]) Cell('.');
			}
		}
		prev = nullptr;
	};

	char Field::check_neighbors(int i, int j){
		int living_neighbors = 0;
		int real_n;
		int real_m;
		for (int n = i - 1; n <= i + 1; n++) {
			for (int m = j - 1; m <= j + 1; m++) {
				if (n == i && m == j) {
					continue;
				}
				real_n = n;
				real_m = m;
				if (n == -1) real_n = height - 1;
				if (n == height) real_n = 0;
				if (m == -1) real_m = width - 1;
				if (m == width) real_m = 0;

				if (cell[real_n][real_m].get_state() == '*') {
					living_neighbors++;
				}
			}
		}
		if (cell[i][j].get_state() == '.' && living_neighbors == 3) {
			return '*';
		}
		else if (cell[i][j].get_state() == '*' && (living_neighbors < 2 || living_neighbors > 3)) {
			return '*';
		}
		else {
			return cell[i][j].get_state();
		}
	};

	Field::~Field(){
		for (int i = 0; i < width; i++) {
			operator delete(cell[i]);
		}
		operator delete(cell);
		if (prev != nullptr) {
			for (int i = 0; i < width; i++) {
				operator delete(prev[i]);
			}
		}
	};

	void Field::print_field(){
		printf("\n   |");
		for (int i = 0; i < width; i++) {
			printf("%3c", 65 + i);
		}
		printf(" |");
		for (int i = 0; i < width; i++) {
			printf("   ");
		}
		printf("\n___|");
		for (int i = 0; i < width; i++) {
			printf("___");
		}
		printf("_|\n   |");
		for (int i = 0; i < width; i++) {
			printf("   ");
		}
		printf(" |\n");
		for (int i = 0; i < height; i++) {
			printf("%2d |", i);
			for (int j = 0; j < width; j++) {
				char state = cell[j][i].get_state();
				printf("%3c", state);
			}
			if (i != width - 1) {
				printf(" |\n   |");
				for (int i = 0; i < width; i++) {
					printf("   ");
				}
				printf(" |\n");
			}
			else {
				printf(" |\n___|");
				for (int i = 0; i < width; i++) {
					printf("___");
				}
				printf("_|\n");
			}
		}
		printf("\n");
	};

	int Field::count_cells(){ return width * height; };

	void Field::step_back(){
		if (prev != nullptr) {
			for (int i = 0; i < width; i++) {
				operator delete(cell[i]);
			}
			operator delete(cell);
			cell = prev;
			prev = nullptr;
		}
		else {
			std::cout << "Impossible to do step_back" << std::endl;
		}
	};

	void Field::delete_all_cells(){
		for (int i = 0; i < width; i++) {
			for (int j = 0; j < height; j++) {
				cell[i][j].set_state('.');
			}
		}
	};
	
	void Field::create_cell(int i, int j){ cell[i][j].set_state('*'); };
	
	void Field::delete_cell(int i, int j){ cell[i][j].set_state('.'); };
	
	void Field::random_creation(){
		for (;;) {
			int i = rand() % width;
			int j = rand() % height;
			if (cell[i][j].get_state() == '.') {
				cell[i][j].set_state('*');
				return;
			}
		}
	};
	
	std::string Field::next(){
		if (prev != nullptr) {
			for (int i = 0; i < width; i++) {
				operator delete(prev[i]);
			}
			operator delete(prev);
		}
		prev = cell;
		Cell** new_cell = new Cell*[width];
		for (int i = 0; i < width; i++) {
			new_cell[i] = (Cell*)operator new(sizeof(Cell)* height);
			for (int j = 0; j < height; j++) {
				new(&new_cell[i][j]) Cell('.');
			}
		}
		int void_flag = 0;
		char new_state;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				new_state = check_neighbors(i, j);
				new_cell[i][j].set_state(new_state);
				if (new_state == '*') {
					void_flag = 1;
				}
			}
		}
		int identity_flag = 0;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				if (cell[i][j].get_state() != new_cell[i][j].get_state()) {
					identity_flag = 1;
					break;
				}
			}
		}
		if (identity_flag == 1 && void_flag == 1) {
			cell = new_cell;
			return "";
		}
		else if (void_flag == 0) {
			return "There are no living cages";
		}
		else {
			return "Life configuration has not changed";
		}
	};
	
	void Field::load_to_file(std::ofstream* fout){
		*fout << width << std::endl;
		*fout << height << std::endl;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				char state = cell[j][i].get_state();
				*fout << state;
			}
			*fout << std::endl;
		}
	};

	void Field::get_from_file(std::ifstream* fin){
		std::string s;
		std::getline(*fin, s);
		int new_width = atoi(s.c_str());
		std::getline(*fin, s);
		int new_height = atoi(s.c_str());
		if (new_width == width, new_height == height) {
			for (int i = 0; i < height; i++) {
				std::getline(*fin, s);
				for (int j = 0; j < width; j++) {
					cell[j][i].set_state(s[j]);
				}
			}
		}
		else {
			for (int i = 0; i < width; i++) {
				operator delete(cell[i]);
			}
			operator delete(cell);
			width = new_width;
			height = new_height;
			cell = new Cell*[width];
			for (int i = 0; i < width; i++) {
				cell[i] = (Cell*)operator new(sizeof(Cell)* height);
				for (int j = 0; j < height; j++) {
					new(&cell[i][j]) Cell('.');
				}
			}
			for (int i = 0; i < height; i++) {
				std::getline(*fin, s);
				for (int j = 0; j < width; j++) {
					cell[j][i].set_state(s[j]);
				}
			}
		}	
	};


}