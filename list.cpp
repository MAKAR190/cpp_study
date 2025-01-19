#include <iostream>
#include <list>

int main() {
  using namespace std;

  list <int> c1;
  list <int>::iterator c1_Iter;
  c1.push_back( 20 );
  c1.push_back( 10 );
  c1.push_back( 30 );
  cout << "Before sorting: c1 =";
  for ( c1_Iter = c1.begin( ); c1_Iter != c1.end( ); c1_Iter++ )
    cout << " " << *c1_Iter;
  cout << endl;
  c1.sort( );
  cout << "After sorting c1 =";
  for ( c1_Iter = c1.begin( ); c1_Iter != c1.end( ); c1_Iter++ )
    cout << " " << *c1_Iter;
  cout << endl;
  c1.sort( greater<int>( ) );
  cout << "After sorting with 'greater than' operation, c1 =";
  for ( c1_Iter = c1.begin( ); c1_Iter != c1.end( ); c1_Iter++ )
    cout << " " << *c1_Iter;
  cout << endl;
  return 0;
}