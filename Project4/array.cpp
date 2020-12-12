#include <string>
#include <iostream>
#include <cassert>
using namespace std;

int appendToAll(string a[], int n, string value);
int lookup(const string a[], int n, string target);
int positionOfMax(const string a[], int n);
int rotateLeft(string a[], int n, int pos);
int countRuns(const string a[], int n);
int flip(string a[], int n);
int differ(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int lookupAny(const string a1[], int n1, const string a2[], int n2);
int separate(string a[], int n, string separator);

void printArray(string a[], int n) {
	cout << "[ ";
		for (int i = 0; i < n ; i++){		//Prints the array to help with testing
			cout << a[i] << " ";
		}
		cout << "]\n";
}

int main()
{
	const int N = 6;
	string a[N] = { "a", "b", "c", "", "b", "c" };

	//assert((All functions with negative n parameters) == -1);	//Check that each function catches for negative n

	assert(appendToAll(a, N, "!!!") == N);				//Ensure appendToAll() works
	printArray(a, N);
	assert(appendToAll(a, N, "") == N);				//Ensure appendToAll() works with blank strings
	printArray(a, N);
	assert(appendToAll(a, 0, "") == 0);				//Ensure no effect when n = 0
	printArray(a, N);

	assert(lookup(a, N, "b!!!") == 1);				//Ensure works and returns smallest position of matching string
	assert(lookup(a, N, "z") == -1);				//Ensure works for unfound string
	assert(lookup(a, 0, "a") == -1);				//Ensure works with n = 0

	assert(positionOfMax(a, N) == 2);				//Ensure works and returns smallest position of max string
	assert(positionOfMax(a, 0) == -1);				//Ensure works when n = 0;

	assert(rotateLeft(a, N, 3) == 3);				//Test rotateLeft()
	printArray(a, N);
	assert(rotateLeft(a, N, 0) == 0);				//Test left edge of rotateLeft()
	printArray(a, N);
	assert(rotateLeft(a, N, (N - 1)) == N - 1);			//Test right edge of rotateLeft()
	printArray(a, N);
	assert(rotateLeft(a, N, (N + 5)) == -1);			//Ensure returns -1 if position is larger than n
	assert(rotateLeft(a, 0, 0) == 0);				//Ensure works if n = 0

	string a2[N] = { "a", "a", "", "b", "b", "b" };

	assert((countRuns(a2, N) == 3));				//Ensure works
	string z[3] = { "a", "a", "a" };
	assert((countRuns(z, 3) == 1));					//Additional tests
	string z2[3] = { "", "A", "a" };
	assert((countRuns(z2, 3) == 3));				//Additional tests
	assert((countRuns(a2, 0) == 0));				//Ensure works if n = 0;

	assert(flip(a2, N) == N);					//Ensure works
	printArray(a2, N);
	assert(flip(a2, 0) == 0);					//Ensure works if n = 0;
	printArray(a2, N); 						//Make sure that didn't screw anything up

	const int N2 = 5;
	string b[N2] = { "b", "b", "b", "z", "a" };
	assert(differ(a2, N, b, N2) == 3);				//Ensure works
	assert(differ(b, N2, a2, N) == 3);				//Ensure works regardless of which array comes first
	assert(differ(a2, N, b, 2) == 2);				//Ensure works with an array running out before any difference
	assert(differ(a2, N, b, 0) == 0);				//Ensure works with n = 0;
	assert(differ(a2, N, a2, N) == N);				//Ensure works with both arrays running out simultaneously


	//a2 should be [ b b b "" a a ]
	assert(subsequence(a2, N, b, 2) == 0);				//Ensure works and returns first instance if multiple
	string z3[2] = { "a", "a" };
	assert(subsequence(a2, N, z3, 2) == 4);				//Ensure works past 0
	assert(subsequence(a2, N, b, 0) == 0);				//Ensure works according to spec if n2 = 0;
	assert(subsequence(a2, 0, b, 0) == 0);				//Ensure works according to spec if both values of n = 0;
	assert(subsequence(a2, N, b, N2) == -1);			//Ensure returns -1 if the subsequence isn't found

	string b2[N2] = { "z", "B", "", "a", "R" };
	assert(lookupAny(a2, N, b2, N2) == 3);				//Ensure works and works with empty strings
	assert(lookupAny(a2, N, b2, 2) == -1);				//Ensure works if not found
	assert(lookupAny(a2, N, b2, 0) == -1);				//Ensure works with n = 0

	string a3[] = { "q", "c", "e", "", "a", "x" };
	assert(separate(a3, N, "d") == 3);				//Ensure works
	printArray(a3, N);
	string a4[] = { "q", "c", "e", "", "a", "x" };
	assert(separate(a4, N, "c") == 2);				//Ensure works if seperator is in the array
	printArray(a4, N);
	string a5[] = { "q", "c", "e", "", "a", "c" };
	assert(separate(a5, N, "c") == 2);				//Ensure works if multiple seperators are in the array
	printArray(a5, N);
	string a6[] = { "q", "c", "e", "", "a", "x" };
	assert(separate(a6, N, "z") == N);				//Ensure works if all all values are less than seperator
	printArray(a6, N);
	string a7[] = { "c", "c", "c", "c", "c", "c" };
	assert(separate(a7, N, "c") == 0);				//Ensure works if all elements are the seperator 
	printArray(a7, N);
	string a8[] = { "b", "b", "e", "e", "x", "x" };
	assert(separate(a8, N, "a") == 0);				//Ensure works if all elements are more than the seperator 
	printArray(a8, N);
	assert(separate(a8, 0, "a") == 0);				//Ensure works for n = 0
	printArray(a8, N);						//Ensure that doesn't screw anything up

	//And all the spec given cases for redundancy
}

int appendToAll(string a[], int n, string value) {
	if (n < 0) {
		return -1;
	}
	for (int i = 0; i < n; i++) {
		a[i] += value;
	}
	return n;
}

int lookup(const string a[], int n, string target) {
	for (int i = 0; i < n; i++) {
		if (a[i] == target) {
			return i;
		}
	}
	return -1;
}

int positionOfMax(const string a[], int n) {
	int posMax = -1;
	string maxStr = "";
	for (int i = 0; i < n; i++) {
		if (a[i] > maxStr) {
			posMax = i;
			maxStr = a[i];
		}
	}
	return posMax;
}

int rotateLeft(string a[], int n, int pos) {
	if (n < 0 || pos > n) {
		return -1;
	}
	string hold = a[pos];
	for (int i = pos; i < n - 1; i++) {
		a[i] = a[i + 1];					
	}
	if (n > 0) {
		a[n - 1] = hold;
	}
	return pos;
}

int countRuns(const string a[], int n) {
	if (n < 0) {
		return -1;
	}
	else if (n == 0) {		//because our program starts by comparing the second string
		return 0;			//to the first, we have to cover if there isnt a first string
	}
	string currstr = a[0];
	int runs = 1;
	for (int i = 1; i < n; i++) {
		if (a[i] != currstr) {
			runs++;
			currstr = a[i];
		}
	}
	return runs;
}

int flip(string a[], int n) {
	if (n < 0) {
		return -1;
	}
	string hold = "";						//"holds" a string to allow us to swap places of strings
	for (int i = 0; i < n / 2; i++) {
		hold = a[i];
		a[i] = a[(n - 1) - i];
		a[(n - 1) - i] = hold;
	}
	return n;
}

int differ(const string a1[], int n1, const string a2[], int n2) {
	if (n1 < 0 || n2 < 0) {
		return -1;
	}
	int smaller;
	if (n1 <= n2) {
		smaller = n1;
	}
	else {
		smaller = n2;
	}
	for (int i = 0; i < smaller; i++) {
		if (a1[i] != a2[i]) {
			return i;
		}
	}
	return smaller;
}
int subsequence(const string a1[], int n1, const string a2[], int n2) {
	if (n1 < 0 || n2 < 0 || n2 > n1) {
		return -1;
	}
	if (n2 == 0) {
		return 0;
	}
	for (int i = 0; i < n1; i++) {
		int passes = 0;						//keeps track of how many items "pass" the subsequence "test". It resets to 0 to test each item in a1
		if (a1[i] == a2[0]) {					//Only starts the loop when an item in a1 matches the first item of a2
			for (; passes < n2; passes++) {
				if (a1[i+passes] != a2[passes]) { //overflow			//breaks the loop if the subsequence isnt found
					break;
				}
			}
			if (passes == n2) {			//if the loop successfully runs n2 times, then the subsequence in the array exists
				return i;
			}
		}
	}
	return -1;
}
int lookupAny(const string a1[], int n1, const string a2[], int n2) {
	for (int i = 0; i < n1; i++) {
			for (int b = 0; b < n2; b++) {
				if (a1[i] == a2[b]) {
					return i;
				}
			}
	}
	return -1;
}
int separate(string a[], int n, string separator) {
	if (n < 0) {
		return -1;
	}
	int frindex = 0;			//index of where in the array we are 
	string hold = "";
	for (int i = 0; i < n; i++) {		// move all the items < seperator to the front
		if (a[i] < separator) {
			hold = a[frindex];
			a[frindex] = a[i];
			a[i] = hold;			//swap items so we dont leave any out
			frindex++;
		}
	}
	int ret;
	if (frindex < n) {
		ret = frindex;		//assign the return value before dealing with items == seperator 
	}
	else {
		ret = n;
	}

	for (int i = frindex; i < n; i++) {		//move all the items == seperator to after the items < seperator
		if (a[i] == separator) {
			hold = a[frindex];
			a[frindex] = a[i];
			a[i] = hold;
			frindex++;
		}
	}
	return ret;
}