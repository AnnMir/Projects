#include <iostream>
#include <cstdlib>
#include <vector>
#include <fstream>

namespace Life{
	class Cell{
	private:
		char state;//"." - пустая или мертвая, "*" - живая
	public:
		Cell(char);
		char get_state();
		void set_state(char);
	};
}