#ifndef FACE_H
#define FACE_H

#include "pca9685.h"
#include "pwmrgbled.h"
#include "rgb.h"

typedef enum {
	RIGHT_EYE = 1,
	LEFT_EYE = 2,
	EYES = 3,
	RIGHT_MOUTH = 4,
	CENTER_RIGHT_MOUTH = 8,
	CENTER_MOUTH = 16,
	CENTER_LEFT_MOUTH = 32,
	CENTER_RIGHT_MOUTH = 64,
	MOUTH = 124;
} FaceLED;

class Face {

private:
	shared_ptr<PCA9685> pwm1;
	shared_ptr<PCA9685> pwm2;

	shared_ptr<FaceLEDAddress> LEDs[7];

	Face();
	Face(Face const&);
	void operator=(Face const&);
	~Face();

public:
	
	static Face& getInstance() {
		static Face instance;
		return instance;
	}

};

#endif