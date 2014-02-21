#include "hw1.h"

using namespace std ;

Course::Course(int code){
	this->code = code;
}

vector<int> Course::getPreReqCourseCodes () {

	return this->preReqCourseCodes;
}

void Course::addPreReqCourseCodes ( int preCode ) {
	
	for(int i= 0;i< preReqCourseCodes.size() ; i++){
		if (preReqCourseCodes[i] == preCode)
			throw(ERR_PREREQISITE_ALREADY_EXISTS);
	}	
	this->preReqCourseCodes.push_back(preCode);
}

int  Course::getCourseCode () {

	return this->code;
}

ostream & operator<< ( ostream & out ,  Course & course ) {
	out << course.code << ":" ;
	int i=0;
	if(course.getPreReqCourseCodes().size() != 0 ){
		for( ;i< course.getPreReqCourseCodes().size()-1 ; i++){
			out << course.getPreReqCourseCodes()[i] << "-";
		}
		out << course.getPreReqCourseCodes ()[ i ] ;
	}
	return out << endl;
}

