#include <iostream>
#include <string>
using namespace std;

int main() {
	//initialize variables needed for whole program
	string def = "";
	double amt;
	string yn = "";

	//ask for inputs
	cout << "Defendant: ";
	getline(cin, def);
	cout << "Amount paid (in thousands): ";
	cin >> amt;
	cout << "Fake athlete? (y/n): ";
	cin.ignore(10000, '\n');
	getline(cin, yn);

	cout << "---" << endl;

	//check for bad inputs
	if (def == "") {
		cout << "You must enter a defendant name." << endl;
		return 1;
	}
	else if (amt < 0) {
		cout << "The amount paid must not be negative." << endl;
		return 1;
	}
	else if (yn != "y" && yn != "n") {
		cout << "You must enter y or n." << endl;
		return 1;
	}
	else {
		//initialize variables needed for calculation
		double fine = 20.0;
		double add = .10; //(fine % for $40k-$250)
		if (yn == "y") {
			add = .22; //increases % if fake athlete
		}

		//Calculate fine for each possible bribe range according to spec
		if (amt <= 40.0) {
			fine += (.66 * amt);
		}
		else if (amt <= 250.0) {
			fine += ((.66 * 40.0) + ((amt - 40.0) * add));
		}
		else {
			fine += ((.66 * 40.0) + (210.0 * add) + .14 * (amt - 250.0));
		}

		//set the output to state only one decimal place
		cout.setf(ios::fixed);
		cout.precision(1);

		//output the suggested fine
		cout << "The suggested fine for " << def << " is $" << fine << " thousand." << endl;
	}
	
}