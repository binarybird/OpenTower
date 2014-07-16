#include "OTOffice.h"

USING_NS_STRUCTURE

OTOffice::OTOffice(void)
{
	this->classType = OTOFFICE;
	this->eval = 0;
	this->rent = 1000;
	this->occupancy = 10;
	this->customOfficeName = "Generic Co.";
}


OTOffice::~OTOffice(void)
{
}

void OTOffice::save(OT::OTObjectBlob *state)
{
	char* name = (char *)customOfficeName.c_str();
	char buffer[33];
	
	state->addData("classtype", &classType, D_INT, 1);
	state->addData("eval", &eval, D_FLOAT, 1);
	state->addData("rent", &rent, D_DOUBLE, 1);
	state->addData("occupancy", &occupancy, D_INT, 1);
	state->addData("name", name, D_CHAR, strlen(name)+1);
	state->addData("positionx", &x, D_FLOAT, 1);
	state->addData("positiony", &y, D_FLOAT, 1);
	state->addData("width", &width, D_FLOAT, 1);
	state->addData("height", &height, D_FLOAT, 1);
	state->addData("hash", &hash, D_INT, 1);
	
}
void OTOffice::load(OT::OTObjectBlob *state)
{

	//#include <sstream>
	//#include <iostream>
	//unsigned int x;   
 //   std::stringstream ss;
 //   ss << std::hex << "fffefffe";
 //   ss >> x;
 //   // output it as a signed type
 //   std::cout << static_cast<int>(x) << std::endl;
}

