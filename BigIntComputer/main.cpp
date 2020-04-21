#include "Number.h"
using namespace std;
int main()
{
	vector<Integer> ints;
	vector<DEcimal> decs;
	vector<Complex> coms;
	cout << "Command : Set (Int/Dec/Com) / Print / Assign / Pow / Fac / or any expression." << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	while (1)
	{

		string in, order;
		getline(cin, in);
		istringstream ss(in);
		
		while (ss >> order)
		{
			if (order == "Set"||order=="set")
			{
				string type, name, temp;
				int t = 0;
				ss >> type;
				if (type == "Int" || type == "int")
					t = 1;
				else if (type == "Dec" || type == "dec")
					t = 2;
				else if (type == "Com" || type == "com")
					t = 3;
				ss >> name;
				if (ss >> temp)
				{
					Integer i;
					DEcimal d;
					Complex c;
					ss >> temp;
					switch (t)
					{
					case 1:
						i.name = name;
						i.setInput(temp);
						i.computInput();
						i.assign();
						ints.push_back(i);
						break;
					case 2:
						d.name = name;
						d.setInput(temp);
						d.computInput();
						d.assign();
						decs.push_back(d);
						break;
					case 3:
						c.name = name;
						c.setInput(temp);
						c.computInput();
						c.assign();
						coms.push_back(c);
						break;
					default:
						break;
					}
				}
				else
				{
					if (t == 1)
					{
						Integer newI;
						newI.name = name;
						ints.push_back(newI);
					}
					else if (t == 2)
					{
						DEcimal newD;
						newD.name = name;
						decs.push_back(newD);
					}
					else if (t == 3)
					{
						Complex newC;
						newC.name = name;
						coms.push_back(newC);
					}
				}
			}
			else if (order == "Print" || order == "print")
			{
				string name;
				ss >> name;
				bool found = false;
				for (int i = 0; i < ints.size() && !found; i++)
				{
					if (ints[i].name == name)
					{
						cout << endl << ints[i] << endl;
						cout << "=============================================================================" << endl;
						found = true;
					}
				}
				for (int i = 0; i < decs.size() && !found; i++)
				{
					if (decs[i].name == name)
					{
						cout << endl << decs[i] << endl;
						cout << "=============================================================================" << endl;
						found = true;
					}
				}
				for (int i = 0; i < coms.size() && !found; i++)
				{
					if (coms[i].name == name)
					{
						cout << endl << coms[i] << endl;
						cout << "=============================================================================" << endl;
						found = true;
					}
				}
				if (!found)
					cout << "Not found." << endl;
				
			}
			else if (order == "Assign" || order == "assign")
			{
				//name1 = name2  or  name1 << expression
				string name1, name2, temp;
				ss >> name1 >> temp >> name2;
				if (temp == "=")
				{
					bool found1, found2;
					int index1, index2, type1, type2;
					found1 = found2 = false;
					for (int i = 0; i < ints.size() && (!found1||!found2); i++)
					{
						if (ints[i].name == name1 && !found1)
						{
							index1 = i;
							type1 = 1;
							found1 = true;
						}
						if (ints[i].name == name2 && !found2)
						{
							index2 = i;
							type2 = 1;
							found2 = true;
						}
					}
					for (int i = 0; i < decs.size() && (!found1 || !found2); i++)
					{
						if (decs[i].name == name1 && !found1)
						{
							index1 = i;
							type1 = 2;
							found1 = true;
						}
						if (decs[i].name == name2 && !found2)
						{
							index2 = i;
							type2 = 2;
							found2 = true;
						}
					}
					for (int i = 0; i < coms.size() && (!found1 || !found2); i++)
					{
						if (coms[i].name == name1 && !found1)
						{
							index1 = i;
							type1 = 3;
							found1 = true;
						}
						if (coms[i].name == name2 && !found2)
						{
							index2 = i;
							type2 = 3;
							found2 = true;
						}
					}
					if (!found1 || !found2)
						cout << "Not found." << endl;
					else
					{
						if (type1 == 1)
						{
							if (type2 == 1)
								ints[index1] = ints[index2];
							else if (type2 == 2)
								ints[index1] = decs[index2];
							else if (type2 == 3)
								ints[index1] = coms[index2];
						}
						else if (type1 == 2)
						{
							if (type2 == 1)
								decs[index1] = ints[index2];
							else if (type2 == 2)
								decs[index1] = decs[index2];
							else if (type2 == 3)
								decs[index1] = coms[index2];
						}
						else if (type1 == 3)
						{
							if (type2 == 1)
								coms[index1] = ints[index2];
							else if (type2 == 2)
								coms[index1] = decs[index2];
							else if (type2 == 3)
								coms[index1] = coms[index2];
						}
					}
				}
				else if (temp == "<<")
				{
					bool found = false;
					for (int i = 0; i < ints.size() && !found; i++)
					{
						if (ints[i].name == name1)
						{
							ints[i].setInput(name2);
							ints[i].computInput();
							ints[i].assign();
							found = true;
						}
					}
					for (int i = 0; i < decs.size() && !found; i++)
					{
						if (decs[i].name == name1)
						{
							decs[i].setInput(name2);
							decs[i].computInput();
							decs[i].assign();
							found = true;
						}
					}
					for (int i = 0; i < coms.size() && !found; i++)
					{
						if (coms[i].name == name1)
						{
							coms[i].setInput(name2);
							coms[i].computInput();
							coms[i].assign();
							found = true;
						}
					}
					if (!found)
						cout << "Not found." << endl;
				}
			}
			else if (order == "Pow" || order == "pow") //Pow a , b  or Pow a ^ b
			{
				Complex out;
				string name1, name2, temp;
				ss >> name1 >> temp >> name2;
				if (temp == ",")
				{
					bool found1, found2;
					int index1, index2, type1, type2;
					found1 = found2 = false;
					for (int i = 0; i < ints.size() && (!found1 || !found2); i++)
					{
						if (ints[i].name == name1 && !found1)
						{
							index1 = i;
							type1 = 1;
							found1 = true;
						}
						if (ints[i].name == name2 && !found2)
						{
							index2 = i;
							type2 = 1;
							found2 = true;
						}
					}
					for (int i = 0; i < decs.size() && (!found1 || !found2); i++)
					{
						if (decs[i].name == name1 && !found1)
						{
							index1 = i;
							type1 = 2;
							found1 = true;
						}
						if (decs[i].name == name2 && !found2)
						{
							index2 = i;
							type2 = 2;
							found2 = true;
						}
					}
					for (int i = 0; i < coms.size() && (!found1 || !found2); i++)
					{
						if (coms[i].name == name1 && !found1)
						{
							index1 = i;
							type1 = 3;
							found1 = true;
						}
						if (coms[i].name == name2 && !found2)
						{
							index2 = i;
							type2 = 3;
							found2 = true;
						}
					}
					if (!found1 || !found2)
						cout << "Not found." << endl;
					else
					{
						if (type1 == 1)
						{
							if (type2 == 1)
								out = Power(ints[index1], ints[index2]);
							else if (type2 == 2)
								out = Power(ints[index1] , decs[index2]);
							else if (type2 == 3)
								out = Power(ints[index1] , coms[index2]);
						}
						else if (type1 == 2)
						{
							if (type2 == 1)
								out = Power(decs[index1], ints[index2]);
							else if (type2 == 2)
								out = Power(decs[index1], decs[index2]);
							else if (type2 == 3)
								out = Power(decs[index1], coms[index2]);
						}
						else if (type1 == 3)
						{
							if (type2 == 1)
								out = Power(coms[index1], ints[index2]);
							else if (type2 == 2)
								out = Power(coms[index1], decs[index2]);
							else if (type2 == 3)
								out = Power(coms[index1], coms[index2]);
						}
						cout << endl << out << endl;
						cout << "=============================================================================" << endl;
					}
				}
				else if (temp == "^")
				{
					bool found = false;
					for (int i = 0; i < ints.size() && !found; i++)
					{
						if (ints[i].name == name1)
						{
							out = Power(ints[i], name2);
							found = true;
						}
					}
					for (int i = 0; i < decs.size() && !found; i++)
					{
						if (decs[i].name == name1)
						{
							out = Power(decs[i], name2);
							found = true;
						}
					}
					for (int i = 0; i < coms.size() && !found; i++)
					{
						if (coms[i].name == name1)
						{
							out = Power(coms[i], name2);
							found = true;
						}
					}
					if (!found)
						cout << "Not found." << endl;
					else
					{
						cout << endl << out << endl;
						cout << "=============================================================================" << endl;
					}
				}
			}
			else if (order == "Fac" || order == "fac")// Fac a  or  Fac << number
			{
				string name, temp;
				ss >> name;
				Integer integer;
				if (ss >> temp)
				{
					integer = Factorial(temp);
					cout << endl << integer << endl;
					cout << "=============================================================================" << endl;
				}
				else
				{
					bool found = false;
					for (int i = 0; i < ints.size() && !found; i++)
					{
						if (ints[i].name == name)
						{
							integer = Factorial(ints[i]);
							found = true;
						}
					}
					for (int i = 0; i < decs.size() && !found; i++)
					{
						if (decs[i].name == name)
						{
							integer = Factorial(decs[i]);
							found = true;
						}
					}
					for (int i = 0; i < coms.size() && !found; i++)
					{
						if (coms[i].name == name)
						{
							integer = Factorial(coms[i]);
							found = true;
						}
					}
					if (!found)
						cout << "Not found." << endl;
					else
					{
						cout << endl << integer << endl;
						cout << "=============================================================================" << endl;
					}
				}
			}
			else
			{
				Number k(order);
				cout << endl << k.printAns() << endl;
				cout << "=============================================================================" << endl;
			}
		}
		

		

		/*
		vector<Number*> nums;
		Complex c,c1;// ("3+2i");
		DEcimal b,b1;// ("5.5+0.4");
		Integer a,a1;// ("2*3");
		Number* ra = &a;
		Number *rb = &b;
		Number* rc = &c;
		cin >> a >> b >> c;
		a = b + c + a;
		cout << a << endl;
		cout << "===================\n";
		b = Power(a, b) + c;
		cout << *rb << endl;
		cout << "===================\n";
		c = Factorial(b);
		cout << *rc << endl;
		cout << "===================\n";
		a = Power(a, c);
		cout << *ra << endl;
		cout << "===================\n";
		a = Factorial(a);
		cout << *ra << endl;
		cout << "===================\n";
		c = Power(b, c);
		cout << *rc << endl;
		cout << "===================\n";
		c = Factorial(b);
		cout << *rc << endl;
		cout << "===================\n";*/

	}
	return 0;
}