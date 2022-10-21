#include <cmath>
#include <iostream>
#include <math.h>
#include <string>

using namespace std;

string Decrypt(int *, int, int, int);
void FactorOfN(int *, int *, int);
string DecryptHelper(int *, int m);
char DecryptHelperHelper(int value);
// int InverseE(int, int, int*, int*);
int InverseE(int, int);
int GCD(int, int);
bool SquareFree(int);
int IntMessageHelper(int, int, int);

int main() {
  // take in the inputs
  int e, n, m;
  cin >> e;
  cin >> n;
  // if (InverseE(e, n) != 1){
  if (!SquareFree(n)) {
    cout << "Public key is not valid!" << endl;
    return 0;
  }
  cin.ignore(); // ignore \n
  cin >> m;
  cin.ignore();
  // create an area of size m full of integers
  int arr[m];
  for (int i = 0; i < m; i++) {
    cin >> arr[i];
  }
  cout << Decrypt(arr, m, n, e) << endl;
}

string Decrypt(int *arr, int m, int n, int e) {
  string message = "";
  int int_message[m];
  int p, q, d;
  // int long long c;
  // find p and q
  FactorOfN(&p, &q, n);
  // one last check if p and q are the same
  if (p == q) {
    cout << "Public key is not valid!" << endl;
    return message;
  }
  int x, y;
	if (GCD(e, (p-1)*(q-1)) != 1){
		cout << "Public key is not valid!" << endl;
		return message;
	}
  d = InverseE(e, ((p - 1) * (q - 1)));
  // d = InverseE(e, ((p-1)*(q-1)), &x, &y);
  cout << p << ' ' << q << ' ' << (p - 1) * (q - 1) << ' ' << d << endl;
  for (int i = 0; i < m; i++) {
    // cout << arr[i];
    // c = (static_cast<unsigned int long long>(pow(arr[i], e))) % n;
    // cout << c;
    // cout << pow(arr[i],d) << endl;
    int_message[i] = IntMessageHelper(arr[i], d, n);
    cout << int_message[i];
    if ((i + 1) < m) {
      cout << ' ';
    } else {
      cout << endl;
    }
  }
  message = DecryptHelper(int_message, m);
  return message;
}

void FactorOfN(int *factor_n1, int *factor_n2, int n) {
  // remember this copy of n is a COPY
  int factor_test = floor(sqrt(n));
  if (factor_test % 2 ==
      0) { // make sure it's odd (no even prime numbers except for 2)
    factor_test--;
  }
  bool found = false;
  while (!found) {
    if (n % factor_test == 0) {
      found = true;
    } else {
      factor_test -= 2;
    }
  }
  *factor_n1 = factor_test;
  *factor_n2 = n / factor_test;
}

string DecryptHelper(int *int_message, int m) {
  string temp_message = "";
  for (int i = 0; i < m; i++) {
    (temp_message).push_back(DecryptHelperHelper(int_message[i]));
  }
  return temp_message;
}

char DecryptHelperHelper(int value) {
  char return_char = 'A';
  int x = 5;
  int temp = (value - x) % 31;
  if ((temp) <= 25) {
    return_char = 'A' + (value - 5);
  } else {
    switch ((temp)) {
    case 26:
      return_char = ' ';
      break;
    case 27:
      return_char = '"';
      break;
    case 28:
      return_char = ',';
      break;
    case 29:
      return_char = '.';
      break;
    case 30:
      return_char = '\'';
    }
  }
  return return_char;
}

int InverseE(int e, int mod) {
  for (int i = 1; i < mod; i++) {
    if (((e % mod) * (i % mod)) % mod == 1) {
      return i;
    }
  }
  return -1;
}

int GCD(int a, int b) {
  int result = min(a, b);
  while (result > 0) {
    if (a % result == 0 && b % result == 0) {
      break;
    }
    result--;
  }
  return result;
}

bool SquareFree(int n) {
  if (n % 2 == 0) { // is even?
    n = n / 2;
  }
  if (n % 2 == 0) { //if odd
    return false;
  }
  for (int i = 3; i <= sqrt(n); i += 2) {
    if (n % i == 0) {
      n = n / i;
      if (n % i == 0) {
        return false;
      }
    }
  }
  return true;
}

int IntMessageHelper(int value, int d, int n) {
  int return_value = 1;
  while (d > 0) {
    return_value *= value;
    return_value = return_value % n;
    d--;
  }
  return return_value;
}

/*
int IntMessageHelper(int value, int d, int n){
        int return_value = 1;
        value = value % n;
        while (d > 1){
                if (d % 2 == 1){
                        return_value *= value;
                        d--;
                        return_value = return_value % n;
                }
                value = pow(value, 2);
                d -= 2;
                value = value % n;
        }
        return_value *= pow(value, d);
        return_value = return_value % n;
        return return_value;
}
*/
/*
int InverseE(int e, int mod, int* x, int* y){
        if (e == 0){
                *x = 0;
                *y = 1;
                return mod;
        }
        int x1, y1;
        int inverse_e = InverseE(mod%e, e, &x1, &y1);

        *x = y1 - ((mod/e) * x1);
        *y = x1;

        return inverse_e;
}
*/