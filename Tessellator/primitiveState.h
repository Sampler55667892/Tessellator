#ifndef _primitiveState_h_
#define _primitiveState_h_

#include <FGL/freeglut.h>
#include <vector>
#include "vertex.h"

using namespace std;

namespace tesslib
{
	struct PrimitiveState
	{
		GLenum type;
		vector<Vertex> points;

		void clear()
		{
			type = -1;
			points.clear();
		}
	};
}

#endif // _primitiveState_h_
