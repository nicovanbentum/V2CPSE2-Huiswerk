#ifndef COMMANDS_H
#define COMMANDS_H

struct command
{
	int x;
	int y;

	virtual ~command() {}
	virtual void execute(char(&b)[3][3], char & turn) = 0;
};

struct Xcommand : command
{
	Xcommand(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	void execute(char(&b)[3][3], char & turn) override
	{
		b[this->y][this->x] = turn;
		turn = 'O';
	}
};

struct Ocommand : command
{
	Ocommand(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	void execute(char(&b)[3][3], char & turn) override
	{
		b[this->y][this->x] = turn;
		turn = 'X';
	}
};

#endif //COMMANDS_H
