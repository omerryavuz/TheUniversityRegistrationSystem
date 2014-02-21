#include "hw1.h"

using namespace std ;


Offering::Offering (Course     * course   ,
               		int          section    ,
               		Instructor * lec      ,
               		int          day        ,
               		int          hour       ,
               		int          dur      ) { 	
	this->course = course;
	this->section = section;
	this->lecturer = lec;
	this->day = day;
	this->whichHour = hour;
	this->duration = dur;
	if(lec != NULL)
		lec->offerNewCourse(this);
}
	
	
int  Offering::getSection    () {
	return this->section;

}
int  Offering::getDay        () {
	return this->day;

}
int  Offering::getWhichHour  () {
	
	return this->whichHour;
}
int  Offering::getDuration   () {
	return this->duration;

}
void Offering::setDay        ( int  d   ) {
	this->day = d;

}
void Offering::setWhichHour  ( int wh  ) {
	this->whichHour = wh;

}
void Offering::setDuration   ( int   dur ) {
	this->duration = dur;
}

Course* Offering::getCourse() {
	return this->course;
}

Instructor* Offering::getInstructor () {
	return this->lecturer;

}
void Offering::setInstructor ( Instructor * ins ) {
	lecturer->cancelOffering(this);
	this->lecturer = ins;
	lecturer->offerNewCourse(this);
	
	
}


ostream & operator<< ( ostream & out , Offering & offering ) {
	out <<  (offering.getCourse() )->getCourseCode()<<"-"<< offering.getSection()<< "-";
	int i;
	string name = (offering.getInstructor())->getName();
	if(name[0] != ' ')
		out << name[0];
	for(i=1;i< name.length(); i++){
		if(name[i-1]==' ' && name[i] != ' ')
			out<<name[i];
	}
	return out;
}
