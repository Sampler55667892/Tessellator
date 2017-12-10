#include <vector>
#include <list>
#include "tessellator.h"
#include "vertex.h"

using namespace std;
using namespace tesslib;

int main( int argc, char * argv[] )
{
	Tessellator tess;

	vector<Vertex> outerLoop;
	list<vector<Vertex> *> innerLoops;

	//xxxxx
	//GLdouble quad2[8][3] = { {-2,3,0}, {-2,0,0}, {2,0,0}, { 2,3,0},
    //                     {-1,2,0}, {-1,1,0}, {1,1,0}, { 1,2,0} };

	outerLoop.push_back( Vertex( -2.0, 3.0, .0 ) );
	outerLoop.push_back( Vertex( -2.0, .0, .0 ) );
	outerLoop.push_back( Vertex( 2.0, .0, .0 ) );
	outerLoop.push_back( Vertex( 2.0, 3.0, .0 ) );

	auto innerLoop = new vector<Vertex>();
	innerLoop->push_back( Vertex( -1.0, 2.0, .0 ) );
	innerLoop->push_back( Vertex( -1.0, 1.0, .0 ) );
	innerLoop->push_back( Vertex( 1.0, 1.0, .0 ) );
	innerLoop->push_back( Vertex( 1.0, 2.0, .0 ) );

	innerLoops.push_back( innerLoop );

	auto triangleVertices = tess.tessellate( outerLoop, innerLoops );

	delete innerLoop;

	int i;
	cin >> i;
	return 0;
}
