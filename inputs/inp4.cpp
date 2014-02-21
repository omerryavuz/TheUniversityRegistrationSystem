#include "hw1.h"
#include <iostream>
#include <fstream>
using namespace std;

int main(){
	try{

		Course* ceng213 = new Course(213);
		ceng213->addPreReqCourseCodes(100);
		ceng213->addPreReqCourseCodes(111);
		ceng213->addPreReqCourseCodes(140);

		Instructor* nkc = new Instructor(1234567, "Nihan Kesim Cicekli");

		Offering* section2 = new  Offering(ceng213, 2, nkc, 2, 3, 2) ;
		cout << *section2 << endl;
		cout << *nkc;
		
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

