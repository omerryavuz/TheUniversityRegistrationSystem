#include "hw1.h"
#include <iostream>
#include <fstream>
using namespace std;

int main(){
	try{

		Department* ceng = new Department("CENG") ;

		Instructor* i1 = new Instructor(1234567, "AB CD ") ;
		Instructor* i2 = new Instructor(2345678, "EF GH") ;
		Instructor* i3 = new Instructor(3456789, "IJ KL") ;

		ceng->addInstructor(i1) ;
		ceng->addInstructor(i2) ;
		ceng->addInstructor(i3) ;

		cout << ceng->getDeptName() << "\n";// << dept.getInstructors() << "\n" <<dept.getStudents() << "\n" <<dept.getOfferings()<<endl;
		cout << "Instructors:" << "\n";
		for(unsigned int i = 0; i < ceng->getInstructors().size();i++){
			cout << *(ceng->getInstructors()[i]);
		}

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





