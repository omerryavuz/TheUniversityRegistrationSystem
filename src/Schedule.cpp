#include "hw1.h"

using namespace std ;

Schedule::Schedule () {
	weeklySchedule = new OfferingPair[5];
	for(int i=0;i<5;i++){
		weeklySchedule[i].off = NULL;
		weeklySchedule[i].nextOff = NULL;
	}
	
}
OfferingPair* Schedule::getSchedule () {

	return weeklySchedule ;
}
Offering* Schedule::getCurrentOffering ( int courseCode ){
	int i;
	Course* tmp = new Course(0);
	OfferingPair * week = new OfferingPair[5];
	OfferingPair * point = new OfferingPair;
	week = this->getSchedule();
	int n = 0;
	for(i=0;i<5;i++){
			if(weeklySchedule[i].off == NULL)
				n++;
	}
	if(n==5)return NULL;

	for(i=0;i<5 ;i++){
		point = &week[i];
		while(1){
			if(point->off==NULL)break;
			tmp = point->off->getCourse();
			if( (point->nextOff == NULL ) && ( courseCode == tmp->getCourseCode() )) return point->off;
			if( (point->nextOff == NULL ) && ( courseCode != tmp->getCourseCode() ) ) break;
			if (courseCode == tmp->getCourseCode() ) return point->off;
			else{
				point = point->nextOff;
			}
		}
	}	
	return NULL;
}

void Schedule::addOffering ( Offering * o ){
	OfferingPair *q,*t,*s;
	q = new OfferingPair;
	int day = o->getDay();
	q = &weeklySchedule[day];
	int added = 0;
	if(q->off == NULL ){
		q->off = new Offering;
		q->off = o;
		q->nextOff = NULL;
		return ;
	}

//---------------------------------------------------------------------------------------------------------------------------	
	q = &weeklySchedule[day];
	for(; q->nextOff != NULL  ;q = q->nextOff ){
		if(q->off->getCourse()->getCourseCode()==o->getCourse()->getCourseCode() &&  q->off->getSection()==o->getSection() ){
			throw(ERR_OFFERING_ALREADY_ADDED);
		}
	}
	if(q->off->getCourse()->getCourseCode()==o->getCourse()->getCourseCode() &&  q->off->getSection()==o->getSection() ){
			throw(ERR_OFFERING_ALREADY_ADDED);
	}
//----------------------------------------------------------------------------------------------------------------------------	

	
	else{
		q = &weeklySchedule[day];
		t = new OfferingPair;
		t->off = o;							
		t->nextOff = q->nextOff;
		q->nextOff = t;
		Offering* temp = new Offering;
		temp = q->off;
		q->off = q->nextOff->off;
		q->nextOff->off = temp;
		s = &weeklySchedule[day];
		Offering* tmp = new Offering;
		while(s->nextOff!=NULL ){
			if ( s->off->getWhichHour() > s->nextOff->off->getWhichHour() ){
				tmp = s->off;
				s->off = s->nextOff->off;
				s->nextOff->off = tmp; 
			}
			else
				break;
			s = s->nextOff;
		}
	}
}
void Schedule::removeOffering ( Offering * o ){
	bool exists=false;
	OfferingPair *q,*r;
	int day = o->getDay();
	q =  &(weeklySchedule[day]) ;
	Offering* tmp = new Offering;
	if(q->off == NULL)throw(ERR_OFFERING_IS_NOT_TAKEN);
	if(q->off->getCourse()->getCourseCode() == o->getCourse()->getCourseCode() && q->off->getSection()==o->getSection() ){
//	if(q->off == o ){
		if(q->nextOff==NULL){
			weeklySchedule[day].off = NULL;
			return ;
		}
		tmp = q->off;
 		q->off = q->nextOff->off;
 		q->nextOff->off = tmp;
	}
	q =  &weeklySchedule[day] ;
	r = q;
	while( q != NULL){
//		if(q->off == o){
		if(q->off->getCourse()->getCourseCode() == o->getCourse()->getCourseCode() && q->off->getSection()==o->getSection() ){
			r->nextOff  = q->nextOff;
			delete q;

			return;
		} 
		r = q;
		q = q->nextOff;
	}
	if(exists == false)
		throw(ERR_OFFERING_IS_NOT_TAKEN);
	
}
ostream & operator<< ( ostream & out , Schedule & schedule ) {
	OfferingPair *p = new OfferingPair[5];
	OfferingPair *q = new OfferingPair;
	p = schedule.getSchedule();
	int n=0;
	for(int i=0;i< 5 ; i++){
		if(p[i].off==NULL) 
			n++;
	}
//	if(n==5 )return out;
	int i=0;
	vector<string> days(7);days[0]="Mon";days[1]="Tue";days[2]="Wed";days[3]="Thu";days[4]="Fri";days[5]="Sat";days[6]="Sun";  
	out << endl;
	while(i<5){
		if(p[i].off != NULL){
			q = &p[i];
			out << days[i] << ":";
			while(1){
				out << q->off->getWhichHour() << "-" << q->off->getDuration() + q->off->getWhichHour()-1<< ":";
				out << *(q->off) << "\t"; 
				q = q->nextOff;
				if(q == NULL)
					break;
			}
			out << endl;	
		}
		i++;
	}
	return out;
}

