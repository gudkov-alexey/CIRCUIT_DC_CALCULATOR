// ���� "circuit.h"
// � ������ ����� ���������� ����� Circuit ��� ������ � ������ ������������� ����


#include "circuit.h"


namespace circuit
{

	// �����������
	// ��������� �������� ������ ���� �� ����� � �� �� ������ ��������� ���� ������������� ����
	Circuit::Circuit(const std::string& path)
		: branchesCount(0)
		, nodesCount(0)
	{
		std::ifstream ifl(path);

		int valuei, branchBegin, branchEnd;
		double valuef;
		char skipLine[256];

		ifl.getline(skipLine, 256);
		ifl.getline(skipLine, 256);

		while (!ifl.eof())
		{
			ifl >> branchesCount;

			ifl >> valuei;
			if ((branchBegin = valuei / 10) > nodesCount) nodesCount = branchBegin;
			if ((branchEnd = valuei % 10) > nodesCount) nodesCount = branchEnd;
			circuitBranches.push_back({ branchBegin - 1, branchEnd - 1 });

			ifl >> valuef;
			RValues.push_back(valuef);

			ifl >> valuef;
			EValues.push_back(valuef);

			ifl >> valuef;
			JValues.push_back(valuef);
		}

		ifl.close();
	}

	// ������� �������������� ������� ������� �� ����� �������� ����
	matr::Matr Circuit::getNodesMatrix() const
	{
		matr::Matr nodesMartix(nodesCount - 1, branchesCount);

		for (int i = 0; i < nodesMartix.getH(); i++)
		{
			for (int j = 0; j < nodesMartix.getW(); j++)
			{
				if (circuitBranches[j].begin == i) nodesMartix.at(i, j) = 1;
				else if (circuitBranches[j].end == i) nodesMartix.at(i, j) = -1;
				else nodesMartix.at(i, j) = 0;
			}
		}

		return nodesMartix;
	}

	// ������� ������� ���������� ���� ��� �������� ���� 
	matr::Matr Circuit::getCurrentSourcesMatrix() const
	{
		matr::Matr J(branchesCount, 1);

		for (int i = 0; i < branchesCount; i++)
		{
			J.at(i, 0) = JValues[i];
		}

		return J;
	}

	// ������� ������� ���������� ���������� ��� �������� ����
	matr::Matr Circuit::getVoltageSourcesMatrix() const
	{
		matr::Matr E(branchesCount, 1);

		for (int i = 0; i < branchesCount; i++)
		{
			E.at(i, 0) = EValues[i];
		}

		return E;
	}

	// ������� ������� ������������� ��� �������� ����
	matr::Matr Circuit::getResistorsMatrix() const
	{
		matr::Matr R(branchesCount, 1);

		for (int i = 0; i < branchesCount; i++)
		{
			R.at(i, 0) = RValues[i] < 1.0e-10 ? 1.0e-10 : RValues[i];
		}

		return R;
	}

	// ������� ������� ������������� ���� ������� ������� �����������
	matr::Matr calculateCircuit(const Circuit& circuit)
	{
		// ������ ������� � ��������� �������
		matr::Matr R = circuit.getResistorsMatrix();
		matr::Matr E = circuit.getVoltageSourcesMatrix();
		matr::Matr J = circuit.getCurrentSourcesMatrix();

		// ��������� ������������ ������� RD �� ������� R
		matr::Matr RD = diag(R);

		// ��������� ������� ���������� A ��� ����� ����
		matr::Matr A = circuit.getNodesMatrix();
		//matr::Matr A(1, 1, -1);

		// ��������� ������� ������������ G �� ������� RD
		matr::Matr G = RD.rev();

		// ��������� ���������� ���� ����� ���� �� ��������� � ��������� ����
		matr::Matr F = (A * G * A.transp()).rev() * (-A * G * E - A * J);

		// ��������� ���������� �� ���� ������ ����
		matr::Matr U = A.transp() * F;

		// ��������� ���� � �������������� ������
		matr::Matr IR = G * (U + E);

		return IR;
	}

}