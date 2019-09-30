#pragma once

#include "pgr.h"


struct frame_buffer_info {

	unsigned int flags;
	bool msaa; // to enable or disable it when wee need it

	frame_buffer_info() {
		//default
		flags = GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH;
		msaa = false;
	}

	frame_buffer_info(bool color, bool depth, bool stencil, bool msaa) {
		flags = GLUT_DOUBLE; // this is a must
		if (color)
			flags |= GLUT_RGBA | GLUT_ALPHA;
		if (depth)
			flags |= GLUT_DEPTH;
		if (stencil)
			flags |= GLUT_STENCIL;
		if (msaa)
			flags |= GLUT_MULTISAMPLE;
		this->msaa = msaa;
	}
};