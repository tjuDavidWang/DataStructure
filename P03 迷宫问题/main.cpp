#include"Maze.h"


int main()
{
	MazeProblem solution;

	int mazeType;
	cout << "��ѡ���Թ���������(1Ϊ��������Թ���2Ϊʹ�ù̶��Թ�)��";
	cin >> mazeType;

	if (mazeType == 1)
	{
		solution.getRandomMaze();
		solution.FindPath();

	}
	else if (mazeType == 2)
	{
		solution.getStaticMaze();
		solution.FindPath();
	}
	else
		cout << "�������ʹ��󣬳����˳�..." << endl;

	return 0;
}
