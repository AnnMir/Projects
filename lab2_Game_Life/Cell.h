#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>

namespace Life{
	class Cell{
	private:
		char state;//"." - ������ ��� �������, "*" - �����
	public:
		Cell(char);
		char get_state();
		void set_state(char);
	};
}