#include "hw1.h"
#include <iostream>
#include <fstream>
using namespace std;

int main(){
	try{

		Instructor* i1 = new Instructor(1234567, "AB CD") ;
		Instructor* i3 = new Instructor(3456789, "Jeremy KL") ;

		Course* c1 = new Course(140)  ;
		c1->addPreReqCourseCodes(100) ;
		//c1->addPreReqCourseCodes(111) ;

		Course* c2 = new Course(213)   ;
		//c2->addPreReqCourseCodes(140)  ;

		Course* c3 = new Course(223) ;

		vector<Offering*>   offerings ;
		Offering* o1_1 = new  Offering(c2, 1, i1, 3, 3, 1) ;
		Offering* o1_2 = new  Offering(c1, 2, i1, 3, 5, 2) ;
		Offering* o3_1 = new  Offering(c3, 1, i3, 3, 1, 2) ;
		offerings.push_back(o1_1);
		offerings.push_back(o1_2);
		offerings.push_back(o3_1);

		Student* s1 = new Student(100000, "Veli") ;
		s1->addPrevCourse(100) ;
		s1->addPrevCourse(111) ;

		int added1 = s1->addCourse(o3_1) ;
		int added2 = s1->addCourse(o1_2) ;
		int added3 = s1->addCourse(o1_1) ;
		Schedule* schedule = s1->getSchedule() ;

		cout<<*schedule;
		cout<< *s1;
	}
	catch(SystemError e){
		switch(e){
		case 1:
			cout << "ERR_STUDENT_ALREADY_EXISTS:"<<e << endl;
			break;
		case 2:
			cout << "ERR_INSTRUCTOR_ALREADY_EXISTS:"<<e << endl;
			break;
		case 3:
			cout << "ERR_COURSE_ALREADY_EXISTS:"<<e << endl;
			break;
		case 4:
			cout << "ERR_OFFERING_ALREADY_EXISTS:"<<e << endl;
			break;
		case 5:
			cout << "ERR_OFFERING_ALREADY_ADDED:"<<e << endl;
			break;
		case 6:
			cout << "ERR_OFFERING_IS_NOT_TAKEN:"<<e << endl;
			break;
		case 7:
			cout << "ERR_OFFERING_DOES_NOT_EXIST:"<<e << endl;
			break;
		case 8:
			cout << "ERR_PREREQISITE_IS_NOT_TAKEN_YET:"<<e << endl;
			break;
		case 9:
			cout << "ERR_PREREQISITE_ALREADY_EXISTS:"<<e << endl;
			break;
		case 10:
			cout << "ERR_CONFLICT:"<<e << endl;
			break;
		default:
			cout << "exception:"<<e << endl;
			break;
		}

	}
	return 0;
}





