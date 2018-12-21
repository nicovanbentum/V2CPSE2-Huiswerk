#ifndef COMMANDS_H
#define COMMANDS_H
#include <iostream>

enum class turns {NONE, X, O};

inline std::ostream & operator<<(std::ostream & out, turns & turn)
{
	switch (turn)
	{
	case turns::NONE:
		out << " ";
		break;
	case turns::O:
		out << "O";
		break;
	case turns::X:
		out << "X";
		break;
	}

	return out;
}

struct command
{
	int x;
	int y;

	virtual ~command() {}
	virtual void execute(turns(&b)[3][3], turns & turn) = 0;
};

struct Xcommand : command
{
	Xcommand(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	void execute(turns(&b)[3][3], turns & turn) override
	{
		b[this->y][this->x] = turn;
		turn = turns::O;
	}
};

struct Ocommand : command
{
	Ocommand(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	void execute(turns(&b)[3][3], turns & turn) override
	{
		b[this->y][this->x] = turn;
		turn = turns::X;
	}
};

#endif //COMMANDS_H
