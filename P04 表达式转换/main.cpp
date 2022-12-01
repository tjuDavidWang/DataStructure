#define _CRT_SECURE_NO_WARNINGS 
#include"Expression.h"
using namespace std;

#define MAX_EXPREESION_SIZE 20
#define MAX_LENGTH 128
enum CHAR_TYPE { INGNORE, DIGIT, OPERATOR, DOT };


//�õ�ջ�����ȼ�,����Խ��Խ�Ƚ�ջ
int getInStackPriority(char ch) {
	switch (ch) {
	case'#':return 0;
	case'(':return 1;
	case'*':
	case'/':
	case'%':return 5;
	case'+':
	case'-':return 3;
	case')':return 6;
	default:return -1;
	}
}
//�õ�ջ�����ȼ�,����Խ��Խ�ȳ�ջ
int getInComingPriority(char ch) {
	switch (ch) {
	case'#':return 0;
	case'(':return 6;
	case'*':
	case'/':
	case'%':return 4;
	case'+':
	case'-':return 2;
	case')':return 1;
	default:return -1;
	}
}
//�ж��ַ�������
CHAR_TYPE getCharType(char ch) {
	if (ch >= '0' && ch <= '9')
		return DIGIT;
	else if (ch == '#' || ch == '(' || ch == ')' || ch == '*' || ch == '/' || ch == '%' || ch == '+' || ch == '-')
		return OPERATOR;
	else if (ch == '.')
		return DOT;
	else
		return INGNORE;
}
//�����ַ������������ж��Ƿ�������ȷ
void getInput(String& res) {
	while (1) {
		cout << "������һ�����Ȳ�����" << MAX_EXPREESION_SIZE << "����׺���ʽ:" << endl;
		res.clear();

		char input[MAX_LENGTH];
		cin.getline(input, MAX_LENGTH);
		cout << endl << "�������׺���ʽΪ��";
		cout << input << endl;

		int size = 0;
		for (; size < MAX_LENGTH; size++)
			if (input[size] == '\0')break;
		//match���ڹ۲������Ƿ�ƥ�䣬cnt���ڼ�����fail���Ƿ��зǷ��ַ���error���������������
		int match = 0, cnt = 0, j = 0;
		bool fail = 0, error = 0;
		bool reNumber = 0;//�����ֵ������������

		res[j++] = '#';
		for (int i = 0; i < size; ++i) 
		{
			//����ƥ��
			if (input[i] == '(') match++;
			if (input[i] == ')') match--;
			if (getCharType(input[i]) != INGNORE) {
				//�������
				if (getCharType(input[i]) == DIGIT) {
					//������ֵ������������
					while (getCharType(input[i]) == DIGIT || getCharType(input[i]) == DOT) {
						res[j++] = input[i];
						cnt++;
						i++;
					}
					if (input[i] == ' ' && getCharType(input[i + 1]) == DIGIT) {
						reNumber = true;
						break;
					}
					else
						i--;
				}
				//���������
				else {
					cnt++;
					res[j++] = input[i];
				}

			}
			else if (input[i] != ' ')
				fail = 1;
			if (i < size - 1 && (getCharType(input[i]) == OPERATOR && input[i] != '(' && input[i] != ')')
				&& (getCharType(input[i + 1]) == OPERATOR && input[i + 1] != '(' && input[i + 1] != ')'))
				error = 1;//��������������������������������
			
		}
		res[j++] = '#';
		res[j] = '\0';
		if (match)
			cout << "��������Ų�ƥ�䣡���������룡" << endl;
		else if (fail)
			cout << "����ı��ʽ������Ч�ַ������������룡" << endl;
		else if (error)
			cout << "����ı��ʽ����������������������ŵ���������������룡" << endl;
		else if (cnt > MAX_EXPREESION_SIZE || cnt == 0)
			cout << "����ı��ʽ������Ҫ�����������룡" << endl;
		else if (reNumber)
			cout << "����ı��ʽ�������������ţ����������룡" << endl;
		else break;
	}
}
//����׺���ʽת���ɺ�׺���ʽ�������
void TransIntoPostfix(String input, String& output)
{
	Stack<char> stack;
	char top_op, cur_op;
	stack.Push('#');//ջ�׷���һ��'#'��Ϊ���

	int pos = 1;
	for (; stack.IsEmpty() == false; pos++) {
		//�������������ֵ����
		if (getCharType(input[pos]) == DIGIT) {
			for (; getCharType(input[pos]) != OPERATOR; pos++)//����С�������
			{
				output = output + input[pos];
				cout << input[pos];
			}
			cout << ' ';
			output = output + ' ';
			pos--;//��һ�����������ջ
		}
		//���������ǲ����������
		else {
			top_op = stack.getTop();
			cur_op = input[pos];
			//����Ŀ�����'-'���Ǹ��ż�ȡ�����
			if (cur_op == '-' && (input[pos - 1] == '#' || input[pos - 1] == '(') && (input[pos + 1] >= '0' && input[pos + 1] <= '9')) {
				output = output + cur_op;
				cout << cur_op;
				continue;
			}
			//����Ŀ�����'+'
			if (cur_op == '+' && (input[pos - 1] == '#' || input[pos - 1] == '('))
				continue;
			//ջ��С��ջ�����ȼ�,��ջ
			if (getInStackPriority(top_op) < getInComingPriority(cur_op))
				stack.Push(cur_op);
			//ջ�ڴ���ջ�����ȼ�����ջ
			else if (getInStackPriority(top_op) > getInComingPriority(cur_op)) {
				stack.Pop();
				output = output + top_op + ' ';
				cout << top_op << ' ';
				pos--;//��һ����������������
			}
			//��������������ջ��������������#�����
			else {
				stack.Pop();
				if (top_op == '(' && cur_op == ')');//������������Ѿ��������ˣ�ֱ�ӽ���һ��
				else break;//��ʣ������#�������ֱ��ջ�գ��˳�
			}
		}
	}
	cout << '\b';//�������һ���ո�
	cout << endl;

}
//���ַ���ת��������
int stringToInt(String org)
{
	int res = 0;
	bool minusFlag = false;
	int i = 0;
	//��Ŀ������ж�
	if (org[0] == '-') {
		minusFlag = true;
		i++;
	}
	else if (org[0] == '+') {
		i++;
	}
	//��ֵ������
	for (; i < org.Length(); ++i)
		res = res * 10 + (org[i] - '0');
	return minusFlag ? -res : res;
}
//���ַ���ת����С��
double stringToDouble(String org)
{
	double res = 0, doublepart = 0;
	bool minusFlag = false;
	int i = 0;

	//��Ŀ������ж�
	if (org[0] == '-') {
		minusFlag = true;
		i++;
	}
	else if (org[0] == '+') {
		i++;
	}
	//��������
	for (; i < org.Length(); ++i) {
		if (org[i] == '.')
			break;
		res = res * 10 + (org[i] - '0');
	}
	//С������
	for (int j = org.Length() - 1; j > i; j--) {
		doublepart = doublepart * 0.1 + (org[j] - '0') * 0.1;
	}
	res = res + doublepart;

	return minusFlag ? -res : res;
}
//�����׺���ʽ��ֵ
void CalculatePostfix(String input)
{
	//�Ƚ��ַ����ָ��һ��һ����String
	//��ջ�Ľṹ������ÿһ����ȡֵ��֮����ջ
	//ֱ������ջ��ֻ��һ��Ԫ��

	bool doubleFlag = false;
	double result;
	Stack<double> nums;
	for (int i = 0; i < input.Length(); ++i)
	{
		//��ֵ
		if (getCharType(input[i]) == DIGIT || ((input[i] == '-' || input[i] == '+') && (i < input.Length() - 1 && getCharType(input[i + 1]) == DIGIT)))
		{
			String temp;
			//����Ŀ�����
			if (input[i] == '-' || input[i] == '+')
				temp = temp + input[i++];
			for (; input[i] != ' ' && getCharType(input[i]) != OPERATOR; i++)//����С�������
			{
				//��С�������
				if (getCharType(input[i]) == DOT)
					doubleFlag = true;
				temp = temp + input[i];
			}
			if (doubleFlag)
			{
				double tempNum = stringToDouble(temp);
				nums.Push(tempNum);
			}
			else
			{
				int tempNum = stringToInt(temp);
				nums.Push(tempNum);
			}

		}
		//�����
		else if (getCharType(input[i]) == OPERATOR)
		{
			char cal = input[i];
			double right = nums.Pop();
			double left = nums.Pop();
			double res;
			switch (cal)
			{
			case '+':
				res = left + right;
				break;
			case '-':
				res = left - right;
				break;
			case '*':
				res = left * right;
				break;
			case '/':
				res = left / right;
				break;
			case '%':
				res = (int)(left) % (int)(right);
				break;
			}
			nums.Push(res);
			result = res;
		}
		//�ո�
		else;
	}

	result = nums.getTop();
	cout << result << endl;
}
/***********************************************
* 1.�õ��ַ�����ͬʱ�ж�����
* 2.���ַ���������ջ�ͳ�ջ����
* 3.��������������ں���2��
***********************************************/
int main()
{
	String input, output;

	getInput(input);
	cout << "��Ӧ�ĺ�׺���ʽΪ��";
	TransIntoPostfix(input, output);
	cout << "������Ϊ��";
	CalculatePostfix(output);
}
