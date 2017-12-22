#include "Field.h"
#include "My_exception.h"
#include <Windows.h>
#include <conio.h>

namespace Life{
	class Game{
	private:
		Field field;
		int steps;

		void start();
		void set(int, int);
		void random_set(int);
		void clear(int, int);
		void back();
		void step(int);
		void reset();
		void save(std::string);
		void load(std::string);
		void end();
	public:
		Game(int, int);
		~Game();
		void exec_command(std::string command);
	};
}