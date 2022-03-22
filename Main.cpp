#include <iostream>

// ���������� ���� "math.h" ��� ������ � ���������
#include "matr.h"

// ���������� ���� "circuit.h" ��� ������ � ������ ������������� ����
#include "circuit.h"


using namespace std;
using namespace matr;
using namespace circuit;


int main()
{
	// ������������� ����� �������
	setlocale(LC_ALL, "ru");
	cout.precision(3);
	cout.setf(ios::fixed);


	// ������ �������� ������ ������������� ���� �� �����
	Circuit circuit("circuit_dc_data/circuit_dc_data_2.txt");

	// ����������� ������������� ����
	Matr IR = calculateCircuit(circuit);

	// ������� ��������� � �������
	cout << "���� � �������������� ������, �" << endl;
	cout << IR.transp() << endl;


	return 0;
}