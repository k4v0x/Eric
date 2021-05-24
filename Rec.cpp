#include <iostream>

using namespace std;

int power( int a, int mag ) {
  if( mag == 0 ) { return 1; }
  return a * power ( a, mag - 1 );
}

int main() {
  int k, j;
  cin>>k>>j;
  cout<<power( k, j );
}
