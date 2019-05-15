#include <iostream>
#include "binHeap.h"
#include <vector>

using namespace std;

int main()
{
  vector<int> v{3,4,8,9,7,1,2,5,0,11,16,17,14,15,6};
  int el = 12;
  MaxHeap<int> M(v.begin(), v.end());
  M.push(el);
  cout << M.size() << endl;

  vector<int> V;

/*
  while (!M.empty()) {
    cout << M.top() << endl;
    M.pop();
  }
  */
  M.sort(V);
  for (auto it = V.begin(); it != V.end(); ++it)
    cout << *it << endl;

  return 0;
}
