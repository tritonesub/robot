#ifndef ENVCANADA_H
#define ENVCANADA_H 

#include <string>
#include <vector>
#include <memory>


typedef struct {
	
	std::string& summary;
 	std::string& condition;
	float temperature;
	float visibility;
	int hummidity;
	float dewpoint;
	std::string& windDirection;
	float windSpeed;

} Weather; 

class EnvCanada {

public:
	
	//constructors
	EnvCanada(){};
	EnvCanada(const std::string& location);
	~EnvCanada();
	std::shared_ptr<const Weather> operator [] (const int i);

	const std::string& location();
	void location(const std::string& l);
	void load();


private:
	static const std::string URL;
	std::string _location;
	std::vector<std::shared_ptr<const Weather>> forecast;

};

#endif //envcanada.h
