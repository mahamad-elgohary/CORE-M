#pragma once

#pragma once
#include <iostream>
#include <vector>
#include <Eigen/Dense>
#include <cctype>
#include <cstring>
#include <iomanip>
using namespace std;
using namespace Eigen;

/**/


class nodeEqs
{

public:

	int comps;
	vector <pair<string, int>> prs;
	vector <pair< string, pair<int, int>>> dependencies;
	vector <int>str;
	vector <int>end;
	vector <double>value;
	vector<string> names;
	vector <double>currents;
	vector<string> types;
	vector <double>powers;
	vector<double> vecAns;
	int nodeStart;
	int nodeEnd;
	string type;
	int nodesNum;
	int nodesNumdfirst;
	vector <vector<double>> circuitMat;
	vector <double> constants;
	int nodestartnumber;
	nodeEqs()
	{
		comps = 0;

		cout << "please enter number of nodes\n";
		int n = 0;
		cin >> n;
		nodesNum = n;
		nodesNumdfirst = n;
		nodestartnumber = n;
		circuitMatResize(nodesNum);
		constantsResize(nodesNum);

	}



	void constantsResize(int n)
	{
		constants.resize(n);
	}

	void circuitMatResize(int n)
	{


		circuitMat.resize(n);
		for (auto& row : circuitMat)
		{
			row.resize(n);
		}

	}





	bool list(int n1, int n2, double val, string s, string n)
	{

		if (s == "r")
		{

			if (n1 == 0)
			{
				circuitMat[n2 - 1][n2 - 1] += 1 / val;
			}
			else if (n2 == 0)
			{
				circuitMat[n1 - 1][n1 - 1] += 1 / val;
			}
			else if (n1 != 0 && n2 != 0)
			{
				circuitMat[n1 - 1][n1 - 1] += 1 / val;
				circuitMat[n2 - 1][n2 - 1] += 1 / val;
				circuitMat[n1 - 1][n2 - 1] -= 1 / val;
				circuitMat[n2 - 1][n1 - 1] -= 1 / val;
			}

		}
		else if (s == "idc")
		{
			if (n1 == 0 && n2 != 0)
			{
				constants[n2 - 1] += val;
			}
			else if
				(n2 == 0 && n1 != 0)
			{
				constants[n1 - 1] += val;
			}

			else if
				(n1 != 0 && n2 != 0)
			{
				constants[n1 - 1] -= val;
				constants[n2 - 1] += val;

			}


		}
		else if (s == "idv")
		{

			nodesNum++;
			circuitMatResize(nodesNum);
			constantsResize(nodesNum);

			if (n1 == 0 && n2 != 0)
			{
				circuitMat[nodesNum - 1][n2 - 1] -= 1;
				circuitMat[n2 - 1][nodesNum - 1] -= 1;
				constants[nodesNum - 1] += val;
			}
			else if (n1 != 0 && n2 == 0)
			{

				circuitMat[n1 - 1][nodesNum - 1] += 1;
				circuitMat[nodesNum - 1][n1 - 1] += 1;
				constants[nodesNum - 1] += val;


			}
			else if (n1 != 0 && n2 != 0)
			{
				circuitMat[n1 - 1][nodesNum - 1] += 1;
				circuitMat[n2 - 1][nodesNum - 1] -= 1;
				circuitMat[nodesNum - 1][n1 - 1] += 1;
				circuitMat[nodesNum - 1][n2 - 1] -= 1;
				constants[nodesNum - 1] += val;
			}



		}
		else if (s == "SC")
		{

			nodesNum++;
			circuitMatResize(nodesNum);
			constantsResize(nodesNum);


			if (n1 == 0 && n2 != 0)
			{

				circuitMat[n2 - 1][nodesNum - 1] -= 1;

				circuitMat[nodesNum - 1][n2 - 1] -= 1;

			}
			else if (n1 != 0 && n2 == 0)
			{
				circuitMat[n1 - 1][nodesNum - 1] += 1;

				circuitMat[nodesNum - 1][n1 - 1] += 1;




			}
			else if (n1 != 0 && n2 != 0)
			{

				circuitMat[n1 - 1][nodesNum - 1] += 1;
				circuitMat[n2 - 1][nodesNum - 1] -= 1;
				circuitMat[nodesNum - 1][n1 - 1] += 1;
				circuitMat[nodesNum - 1][n2 - 1] -= 1;
				constants[nodesNum - 1] += 0;
			}



		}
		else if (s == "vcvs")
		{
			int n1dash; int n2dash;
			nodesNum++;
			circuitMatResize(nodesNum);
			constantsResize(nodesNum);

			cout << "\n add the dependency location:    \n" <<
				"            startnode |  endnode  \n     ";
			cin >> n1dash >> n2dash;

			if (n1 != 0 && n2 != 0 && n1dash == 0 && n2dash != 0)
			{

				circuitMat[nodesNum - 1][n1 - 1] += 1;
				circuitMat[nodesNum - 1][n2 - 1] -= 1;
				circuitMat[nodesNum - 1][n2dash - 1] += val;
				circuitMat[n1 - 1][nodesNum - 1] = +1;
				circuitMat[n2 - 1][nodesNum - 1] = -1;
			}
			else if (n1 != 0 && n2 != 0 && n1dash != 0 && n2dash == 0)
			{
				circuitMat[nodesNum - 1][n1 - 1] += 1;
				circuitMat[nodesNum - 1][n2 - 1] -= 1;
				circuitMat[nodesNum - 1][n1dash - 1] -= val;
				circuitMat[n1 - 1][nodesNum - 1] = +1;
				circuitMat[n2 - 1][nodesNum - 1] = -1;

			}
			else if (n1 == 0 && n2 != 0 && n1dash != 0 && n2dash != 0)
			{
				circuitMat[nodesNum - 1][n2 - 1] -= 1;
				circuitMat[nodesNum - 1][n1dash - 1] -= val;
				circuitMat[nodesNum - 1][n2dash - 1] += val;
				circuitMat[n2 - 1][nodesNum - 1] = -1;


			}
			else if (n1 != 0 && n2 == 0 && n1dash != 0 && n2dash != 0)
			{
				circuitMat[nodesNum - 1][n1 - 1] += 1;
				circuitMat[nodesNum - 1][n1dash - 1] -= val;
				circuitMat[nodesNum - 1][n2dash - 1] += val;
				circuitMat[n1 - 1][nodesNum - 1] = +1;


			}

			else if (n1 == 0 && n2 != 0 && n1dash == 0 && n2dash != 0)
			{


				circuitMat[nodesNum - 1][n2 - 1] -= 1;

				circuitMat[nodesNum - 1][n2dash - 1] += val;

				circuitMat[n2 - 1][nodesNum - 1] = -1;


			}
			else if (n1 != 0 && n2 == 0 && n1dash != 0 && n2dash == 0)
			{


				circuitMat[nodesNum - 1][n1 - 1] += 1;
				circuitMat[nodesNum - 1][n1dash - 1] -= val;

				circuitMat[n1 - 1][nodesNum - 1] = +1;



			}
			else if (n1 == 0 && n2 != 0 && n1dash != 0 && n2dash == 0)
			{



				circuitMat[nodesNum - 1][n2 - 1] -= 1;
				circuitMat[nodesNum - 1][n1dash - 1] -= val;


				circuitMat[n2 - 1][nodesNum - 1] = -1;

			}
			else if (n1 != 0 && n2 == 0 && n1dash == 0 && n2dash != 0)
			{


				circuitMat[nodesNum - 1][n1 - 1] += 1;


				circuitMat[nodesNum - 1][n2dash - 1] += val;
				circuitMat[n1 - 1][nodesNum - 1] = +1;




			}


			else if (n1 != 0 && n2 != 0 && n1dash != 0 && n2dash != 0)
			{

				circuitMat[nodesNum - 1][n1 - 1] += 1;
				circuitMat[nodesNum - 1][n2 - 1] -= 1;
				circuitMat[nodesNum - 1][n1dash - 1] -= val;
				circuitMat[nodesNum - 1][n2dash - 1] += val;
				circuitMat[n1 - 1][nodesNum - 1] = +1;
				circuitMat[n2 - 1][nodesNum - 1] = -1;
			}

		}
		else if (s == "vccs")
		{
			int n1dash; int n2dash;

			cout << "\n add the dependency location:    \n" <<
				"            startnode |  endnode  \n     ";
			cin >> n1dash >> n2dash;
			dependencies.push_back(make_pair(n, make_pair(n1dash, n2dash)));


			if (n1 != 0 && n2 != 0 && n1dash == 0 && n2dash != 0)
			{

				circuitMat[n1 - 1][n2dash - 1] -= val;

				circuitMat[n2 - 1][n2dash - 1] += val;
			}
			else if (n1 != 0 && n2 != 0 && n1dash != 0 && n2dash == 0)
			{

				circuitMat[n1 - 1][n1dash - 1] += val;

				circuitMat[n2 - 1][n1dash - 1] -= val;

			}

			else if (n1 == 0 && n2 != 0 && n1dash != 0 && n2dash != 0)
			{


				circuitMat[n2 - 1][n1dash - 1] -= val;
				circuitMat[n2 - 1][n2dash - 1] += val;


			}
			else if (n1 != 0 && n2 == 0 && n1dash != 0 && n2dash != 0)
			{
				circuitMat[n1 - 1][n1dash - 1] += val;
				circuitMat[n1 - 1][n2dash - 1] -= val;



			}
			else if (n1 == 0 && n2 != 0 && n1dash == 0 && n2dash != 0)
			{


				circuitMat[n2 - 1][n2dash - 1] += val;

			}
			else if (n1 != 0 && n2 == 0 && n1dash != 0 && n2dash == 0)
			{

				circuitMat[n1 - 1][n1dash - 1] += val;



			}
			else if (n1 == 0 && n2 != 0 && n1dash != 0 && n2dash == 0)
			{


				circuitMat[n2 - 1][n1dash - 1] -= val;


			}
			else if (n1 != 0 && n2 == 0 && n1dash == 0 && n2dash != 0)
			{


				circuitMat[n1 - 1][n2dash - 1] -= val;



			}
			else if (n1 != 0 && n2 != 0 && n1dash != 0 && n2dash != 0)
			{

				circuitMat[n1 - 1][n1dash - 1] += val;
				circuitMat[n1 - 1][n2dash - 1] -= val;
				circuitMat[n2 - 1][n1dash - 1] -= val;
				circuitMat[n2 - 1][n2dash - 1] += val;
			}


		}
		else if (s == "cccs")
		{

			cout << "\nadd  nodes location for short circuit dependency current\n" <<
				"startnode | endnode  \n";
			int n1dash, n2dash;
			cin >> n1dash >> n2dash;
			list(n1dash, n2dash, val, "SC", n);


			if (n1 == 0 && n2 != 0)
			{
				circuitMat[n2 - 1][nodesNum - 1] -= val;
			}
			else if (n1 != 0 && n2 == 0)
			{

				circuitMat[n1 - 1][nodesNum - 1] += val;

			}
			else if (n1 != 0 && n2 != 0)
			{
				circuitMat[n1 - 1][nodesNum - 1] += val;
				circuitMat[n2 - 1][nodesNum - 1] -= val;
			}



		}


		else if (s == "ccvs")
		{



			cout << "\nadd  nodes location for short circuit dependency current\n" <<
				"startnode | endnode  \n";
			int n1dash, n2dash;
			cin >> n1dash >> n2dash;
			list(n1dash, n2dash, val, "SC", n);


			nodesNum++;
			circuitMatResize(nodesNum);
			constantsResize(nodesNum);

			if (n1 == 0 && n2 != 0)
			{
				circuitMat[nodesNum - 1][n2 - 1] -= 1;
				circuitMat[n2 - 1][nodesNum - 1] -= 1;
			}
			else if (n1 != 0 && n2 == 0)
			{

				circuitMat[n1 - 1][nodesNum - 1] += 1;
				circuitMat[nodesNum - 1][n1 - 1] += 1;
			}
			else if (n1 != 0 && n2 != 0)
			{
				circuitMat[n1 - 1][nodesNum - 1] += 1;
				circuitMat[n2 - 1][nodesNum - 1] -= 1;
				circuitMat[nodesNum - 1][n1 - 1] += 1;
				circuitMat[nodesNum - 1][n2 - 1] -= 1;
			}
			circuitMat[nodesNum - 1][nodesNum - 2] -= val;


		}
		else if (s == "E")
		{



			return true;
		}
		else {
			cout << "\n invalid input please try again\n";
			return false;
		}

		return false;


	}




	void lists()
	{

		cout << "\n*********************************************************************\n" <<
			"                         enter  your circuit details                       " <<
			"\n*********************************************************************\n" <<


			"	r:resistor  || idc: idc   ||  E:EXIT ||   idv:idv || SC:short circuit" <<


			"\n \n  vcvs:voltage controlled voltage source ||  vccs:voltage controlled current source" <<


			"\n \n  cccs:current controlled current source || ccvs : current controlled voltage source\n" <<
			"\n*********************************************************************************************\n" <<
			" remarks: \n  at idc:( startnode: startcurrent , endnode:endcurrent)      \n" <<
			"at vsvc and idv: (startnode | startnode dash:+ve ter, endnode| endnode dash: -ve terminal, val is gain )  \n\n\n \n " <<


			"  comptype | name | startnode | endnode | value \n";

		int n;
		bool exit = false;

		/**/
		while (!exit)
		{
			string name;
			string  s;
			int n1;
			int n2;
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

				if (s == "idv" || s == "vcvs" || s == "cccs")
				{
					nodesNumdfirst += 1;
					prs.push_back(make_pair(name, nodesNumdfirst));
				}
				if (s == "ccvs")
				{
					nodesNumdfirst += 2;
					prs.push_back(make_pair(name, nodesNumdfirst));
				}

				{

					cin >> n1 >> n2 >> val;

					naming(s, name, n1, n2, val);
					exit = list(n1, n2, val, s, name);

					cout << "       ****        \n";
				}


			}

		}

	}




	void resizee(int n)
	{

		str.resize(n);
		end.resize(n);
		value.resize(n);
		names.resize(n);
		currents.resize(n);
		types.resize(n);
		powers.resize(n);
	}




	void naming(string type, string name, int n1, int n2, double val)
	{
		comps++;
		resizee(comps);
		str[comps - 1] = n1;
		end[comps - 1] = n2;
		value[comps - 1] = val;
		names[comps - 1] = name;
		types[comps - 1] = type;


	}



	void Currents()
	{
		double temp = 0;
		for (int i = 0; i < comps; i++)
		{




			if (types[i] == "r")
			{

				if (str[i] != 0 && end[i] != 0)
				{

					if (vecAns[str[i] - 1] > vecAns[end[i] - 1])
					{

						temp = vecAns[str[i] - 1] - vecAns[end[i] - 1];


					}
					else if (vecAns[str[i] - 1] < vecAns[end[i] - 1])
					{

						temp = vecAns[end[i] - 1] - vecAns[str[i] - 1];

					}

				}

				else if (str[i] == 0 && end[i] != 0)
				{
					if (0 > vecAns[end[i] - 1])
					{

						temp = 0 - vecAns[end[i] - 1];


					}
					else if (0 < vecAns[end[i] - 1])
					{

						temp = vecAns[end[i] - 1] - 0;

					}

				}
				else if (str[i] != 0 && end[i] == 0)
				{


					if (vecAns[str[i] - 1] > 0)
					{

						temp = vecAns[str[i] - 1] - 0;


					}
					else if (vecAns[str[i] - 1] < 0)
					{

						temp = 0 - vecAns[str[i] - 1];

					}
				}

				currents[i] = (double)temp / (value[i] * 1.0);
				powers[i] = currents[i] * temp;
			}






			else if (types[i] == "idc")
			{
				currents[i] = ((double)value[i]);
				if (str[i] != 0 && end[i] != 0)
				{
					powers[i] = -currents[i] * (vecAns[end[i] - 1] - vecAns[str[i] - 1]);
				}

				else if (str[i] == 0 && end[i] != 0)
				{
					powers[i] = -currents[i] * (vecAns[end[i] - 1] - 0);
				}
				else if (str[i] != 0 && end[i] == 0)
				{
					powers[i] = -currents[i] * (0 - vecAns[str[i] - 1]);

				}



			}

			else if (types[i] == "idv")
			{
				for (auto& j : prs)
				{
					if (j.first == names[i])
					{
						currents[i] = -(vecAns[j.second - 1]);
						powers[i] = currents[i] * value[i];
					}

				}

			}
			else if (types[i] == "vcvs")
			{
				for (auto& j : prs)
				{
					if (j.first == names[i])
					{
						currents[i] = (-vecAns[j.second - 1]);
						if (str[i] != 0 && end[i] != 0)
						{
							powers[i] = -currents[i] * (vecAns[str[i] - 1] - vecAns[end[i] - 1]);
						}

						else if (str[i] == 0 && end[i] != 0)
						{
							powers[i] = -currents[i] * (0 - vecAns[end[i] - 1]);
						}
						else if (str[i] != 0 && end[i] == 0)
						{
							powers[i] = -currents[i] * (vecAns[str[i] - 1] - 0);

						}


					}

				}
			}
			else if (types[i] == "cccs")
			{


				for (auto& j : prs)
				{
					if (j.first == names[i])
					{
						currents[i] = (value[i] * vecAns[j.second - 1]);
						if (str[i] != 0 && end[i] != 0)
						{
							powers[i] = -currents[i] * (vecAns[end[i] - 1] - vecAns[str[i] - 1]);
						}

						else if (str[i] == 0 && end[i] != 0)
						{
							powers[i] = -currents[i] * (vecAns[end[i] - 1] - 0);
						}
						else if (str[i] != 0 && end[i] == 0)
						{
							powers[i] = -currents[i] * (0 - vecAns[str[i] - 1]);

						}


					}
				}

			}
			else if (types[i] == "vccs")
			{

				for (auto j : dependencies)
				{
					if (j.first == names[i])
					{
						currents[i] = (value[i] * (vecAns[j.second.first - 1] - vecAns[j.second.first - 1]));
						if (str[i] != 0 && end[i] != 0)
						{
							powers[i] = -currents[i] * (vecAns[end[i] - 1] - vecAns[str[i] - 1]);
						}

						else if (str[i] == 0 && end[i] != 0)
						{
							powers[i] = -currents[i] * (vecAns[end[i] - 1] - 0);

						}
						else if (str[i] != 0 && end[i] == 0)
						{
							powers[i] = -currents[i] * (0 - vecAns[str[i] - 1]);


						}


					}
				}
			}

			else if (types[i] == "ccvs")
			{


				for (auto j : prs)
				{
					if (j.first == names[i])
					{
						currents[i] = (vecAns[j.second - 1]);
						if (str[i] != 0 && end[i] != 0)
						{
							powers[i] = -(currents[i] * (vecAns[str[i] - 1] - vecAns[end[i] - 1]));
						}

						else if (str[i] == 0 && end[i] != 0)
						{
							powers[i] = -currents[i] * (0 - vecAns[end[i] - 1]);
						}
						else if (str[i] != 0 && end[i] == 0)
						{
							powers[i] = -currents[i] * (vecAns[str[i] - 1] - 0);

						}


					}
				}
			}
		}


	}




	void printNames()
	{
		//for (auto i : vecAns) { cout << i << "\n"; }
		cout << "\n components netlist :  name   |  value  | type  | strnode  | endnode  | current  | power   \n";
		for (int i = 0; i < comps; i++)
		{
			cout << names[i] << "  :  " << value[i] << " |  " << types[i] << " | " << str[i] << " |  " << end[i] << "  | " << currents[i] << "  | " << powers[i] << "\n";


		}
	}



	void printEq()
	{


		for (int i = 0; i < nodesNum; i++)
		{
			for (int j = 0; j < nodesNum; j++)
			{


				cout << setprecision(4) << circuitMat[i][j] << "  |  ";



			}

			cout << "         || " << constants[i] << endl;

		}

	}


	void  circuitsolve2(vector <vector<double>> a, vector <double> b)
	{
		int n = a.size();
		vector <double> c;

		Map <MatrixXd> x(b.data(), n, 1);

		for (int i = 0; i < n; i++)
		{



			for (int j = 0; j < n; j++)
			{


				c.push_back(a[j][i]);


			}

		}

		Map< MatrixXd > mat(c.data(), n, n);


		MatrixXd  ans = mat.inverse() * x;

		vector<double> vec(ans.data(), ans.data() + ans.size());
		vecAns = vec;int count = 1;
		for (auto i : vecAns) {
			count <= nodestartnumber ? cout << "v" << count++ << ":" : cout << "Is: ";
			cout << i << "\n";
		}
	}


};
