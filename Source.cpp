#include "tst.h"


struct
{



	string name;
	string  s;
	int n1;
	int n2;
	int dependednstr;
	int dependednend;
	double val;

};

void lists()
{

	bool exit = false;


	while (!exit)
	{
		string name;
		string  s;
		int n1;
		int n2;
		int dependednstr;
		int dependednend;
		double val;
		cin >> s;
		if (s == "r" || s == "idc" || s == "idv" || s == "E" || s == "ccvs" || s == "cccs" || s == "vcvs" || s == "vccs")
		{
			if (s == "E")
			{
				break;
				exit = true;
			}
			cin >> name;


			{

				cin >> n1 >> n2 >> val >> dependednstr >> dependednstr;



				cout << "       ****        \n";
			}


		}

	}

}



int main()
{










	cout << "\n***********************************\n" <<
		"         welcome to netlist solver    "
		"\n***********************************\n";
	bool exit = false;


	nodeEqs nq;
	nq.lists();
	cout << "\n****************************\n";
	nq.printEq();
	cout << "\n****************************\n";
	nq.circuitsolve2(nq.circuitMat, nq.constants);
	nq.Currents();
	cout << "\n****************************\n";
	nq.printNames();


	return 0;
}
