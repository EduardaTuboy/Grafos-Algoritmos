#include <iostream>
using namespace std;

class Node {
  string a;
  public:
    string b() {
      return a;
    };
};

int main() {
  Node cell;
  cout << cell.b();
  return 0;
}
