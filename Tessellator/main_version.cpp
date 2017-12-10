//
#include <iostream>
#include "version.h"

using namespace std;

int main( int argc, char *argv[] )
{
	Version v;
	v.init( argc, argv );
	v.showVersion();

	int i; cin >> i;

	return 0;
}
//
