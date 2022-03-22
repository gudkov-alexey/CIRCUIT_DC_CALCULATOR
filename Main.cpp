#include <iostream>

// подключаем файл "math.h" для работы с матрицами
#include "matr.h"

// подключаем файл "circuit.h" для работы с графом электрической цепи
#include "circuit.h"


using namespace std;
using namespace matr;
using namespace circuit;


int main()
{
	// устанавливаем режим консоли
	setlocale(LC_ALL, "ru");
	cout.precision(3);
	cout.setf(ios::fixed);


	// читаем исходные данные электрической цепи из файла
	Circuit circuit("circuit_dc_data/circuit_dc_data_2.txt");

	// расчитываем электрическую цепь
	Matr IR = calculateCircuit(circuit);

	// выводим результат в консоль
	cout << "Токи в сопротивлениях ветвей, А" << endl;
	cout << IR.transp() << endl;


	return 0;
}