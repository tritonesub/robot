#ifndef FACE_H
#define FACE_H

#include "pca9685.h"

class Face {

private:
	PCA9685 pwm1;
	PCA9685 pwm2;

public:
	Face();
	~Face();

};

#endif