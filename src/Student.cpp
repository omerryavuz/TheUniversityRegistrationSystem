#include "hw1.h"

using namespace std;

Student::Student ( int id , string name ){
	this->id = id;
	this->name = name; 
	busyhours = new int*[DAYS_WORKING];
	int i,j;
  	for ( int i = 0 ; i < DAYS_WORKING ; i++ )
  	{
    	busyhours[i] = new int[HOURS_PER_DAY] ;
		for ( int j = 0 ; j < HOURS_PER_DAY ; j++ )
			busyhours[i][j] = 0 ;
  	}
}
Student::~Student (){
	for ( int i = 0 ; i < DAYS_WORKING ; i++ )
			delete [] busyhours[i] ;
		delete [] busyhours ;
	
}
string Student::getName() {
	return this->name;
}
int Student::getID () {
	return this->id;
}
vector<int> Student::getPrevCourses () {
	return this->prevTakenCourses ;
}
int** Student:: getBusyHours(){
	return this->busyhours ;
}
Schedule* Student::getSchedule(){
	return &(this->schedule) ;
}

void Student::addPrevCourse ( int prevCourseCode ){
	for(int i= 0; i< prevTakenCourses.size() ;i++){
		if(prevCourseCode == prevTakenCourses[i])
			throw(ERR_COURSE_ALREADY_EXISTS);
	}
	this->prevTakenCourses.push_back(prevCourseCode);
}

int Student::addCourse(Offering * newOffering){
	int i,j,ok=0;
	int CourseCode = newOffering->getCourse()->getCourseCode();
	Offering* current = new Offering;
	current = schedule.getCurrentOffering(CourseCode);
	
	if(current != NULL )throw(ERR_COURSE_ALREADY_EXISTS);
	
	vector<int> taken(10) ;
	taken =  this->getPrevCourses();
	vector<int> preReq(10) ;
	preReq =  newOffering->getCourse()->getPreReqCourseCodes();
	for(i=0;i<taken.size();i++){
		for(j=0;j<preReq.size();j++){
			if( taken[i] == preReq[j] )
				ok += 1; 
		}
	}
	if(ok!=preReq.size()){
		throw(ERR_PREREQISITE_IS_NOT_TAKEN_YET);
	}
	
	int newDay = newOffering->getDay();
	int newDur = newOffering->getDuration();
	int newHour = newOffering->getWhichHour();
	for(i=0;i<newDur ; i++ ){
		if( busyhours[newDay][i+newHour] == 1  ){
			throw(ERR_CONFLICT);
		}
	}
	
	
	for(i=0;i<newDur ; i++ ){
		 busyhours[newDay][i+newHour] = 1 ;
	}
	
	this->schedule.addOffering(newOffering);
	return 1;
}

void Student::dropCourse(Offering * newOffering){
	Offering* temp = new Offering;
	temp = schedule.getCurrentOffering(newOffering->getCourse()->getCourseCode());
	if(temp == NULL)  throw(ERR_OFFERING_IS_NOT_TAKEN) ;
	if(temp->getSection() != newOffering->getSection() )   throw(ERR_OFFERING_IS_NOT_TAKEN) ;

 	int newDay = newOffering->getDay();
	int newDur = newOffering->getDuration();
	int newHour = newOffering->getWhichHour();
	for(int i=0;i<newDur ; i++ ){
		 busyhours[newDay][i+newHour] = 0 ;
	}
	
	this->schedule.removeOffering(newOffering);
}
bool Student::changeSection ( 	int courseCode , 
					 			int newSection , 
				     			vector<Offering*> Offerings ){

	int i,j,ok=1;
	int day,hour,dur;
	Offering * old = new Offering ;
	old = schedule.getCurrentOffering(courseCode);
	if (old == NULL )
		return false;
	
	int old_day ,old_hour,old_dur;
	old_day = old->getDay();
	old_hour = old->getWhichHour();
	old_dur = old->getDuration();
	for(i=0;i<old_dur;i++){
		busyhours[old_day][i+old_hour] = 0;
	}
	for(i=0; i< Offerings.size() ; i++){
		
		if ( Offerings[i]->getCourse()->getCourseCode()==courseCode && Offerings[i]->getSection()==newSection ){
			ok = 1;
			day = Offerings[i]->getDay();
			hour = Offerings[i]->getWhichHour();
			dur = Offerings[i]->getDuration();	
			
			for(j=0;j<  dur; j++){
				if(busyhours[day][j+hour]==1 ){
					ok = 0;
					break;
				}
			
			}
			if(ok==1){
				for(j=0;j<  dur; j++){
					this->busyhours[day][j+hour]=1 ;
				}
				
				schedule.addOffering(Offerings[i]);
				schedule.removeOffering(old);
				return true;
			}
		}
	
	}
	for(i=0;i<old_dur;i++){
		busyhours[old_day][i+old_hour] = 1;
	}
	if(old->getSection() == newSection)
		throw(ERR_OFFERING_ALREADY_ADDED);
	return false;
}


ostream & operator<< ( ostream & out , Student & student ){
	int i=0,j;
	vector<int> prevCourse = student.getPrevCourses();
	out <<"ID:"<<student.getID()<<"\t"<<"NAME:"<<student.getName()<<"\t";
	out<< "PREV_COURSE_CODES:" ;
	if(prevCourse.size() != 0) {
		for(i=0;i<prevCourse.size()-1;i++){
			out<<prevCourse[i]<<"-";
		}
		out<<prevCourse[i];
	}
	out<< *(student.getSchedule());
	return out ;	
}
