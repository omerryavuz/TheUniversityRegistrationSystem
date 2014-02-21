#include "hw1.h"
#include <iostream>
#include <fstream>
using namespace std;

int main(){
	try{

		Department* ceng = new Department("CENG") ;

		Instructor* i1 = new Instructor(1234567, "AB CD ") ;
		Instructor* i2 = new Instructor(2345678, "EF GH") ;
		Instructor* i3 = new Instructor(3456789, "IJ KL YZ") ;

		ceng->addInstructor(i1) ;
		ceng->addInstructor(i2) ;
		ceng->addInstructor(i3) ;

		Course* c1 = new Course(140)  ;
		c1->addPreReqCourseCodes(100) ;
		c1->addPreReqCourseCodes(111) ;

		ceng->addCourseToCurriculum(c1) ;

		Course* c2 = new Course(213)   ;
		c2->addPreReqCourseCodes(140)  ;
		c2->addPreReqCourseCodes(1099) ;
		c2->addPreReqCourseCodes(1070) ;

		ceng->addCourseToCurriculum(c2) ;

		Course* c3 = new Course(223) ;
		Course* c4 = new Course(280) ;
		Course* c5 = new Course(260) ;
		ceng->addCourseToCurriculum(c3) ;
		ceng->addCourseToCurriculum(c4) ;
		ceng->addCourseToCurriculum(c5) ;

		Offering* o1_1 = new  Offering(c1, 1, i1, 2, 3, 2) ;
		Offering* o1_2 = new  Offering(c1, 2, i1, 3, 3, 2) ;
		Offering* o1_3 = new  Offering(c1, 3, i2, 2, 4, 2) ;
		Offering* o2_1 = new  Offering(c2, 1, i3, 2, 1, 3) ;
		Offering* o3_1 = new  Offering(c3, 1, i3, 3, 1, 2) ;
		Offering* o3_2 = new  Offering(c3, 2, i3, 2, 5, 3) ;
		Offering* o4_1 = new  Offering(c4, 1, i2, 3, 5, 1) ;
		Offering* o5_1 = new  Offering(c5, 1, i2, 3, 6, 3) ;

		ceng->offerNewCourse(o1_1) ;
		ceng->offerNewCourse(o1_2) ;
		ceng->offerNewCourse(o1_3) ;
		ceng->offerNewCourse(o2_1) ;
		ceng->offerNewCourse(o3_1) ;
		ceng->offerNewCourse(o3_2) ;
		ceng->offerNewCourse(o4_1) ;
		ceng->offerNewCourse(o5_1) ;

		Student* s1 = new Student(100000, "Veli") ;
		s1->addPrevCourse(100) ;
		s1->addPrevCourse(111) ;

		int added1 = s1->addCourse(ceng->getOffering(140,1)) ;
		Schedule* s1_sched = s1->getSchedule() ;

		s1->changeSection(140,2,ceng->getOfferings()) ;

		int added4 = s1->addCourse(ceng->getOffering(223,1)) ;

		s1->dropCourse(ceng->getOffering(140,2)) ;

		int added6 = s1->addCourse(ceng->getOffering(140,2)) ;
		int added7 = s1->addCourse(ceng->getOffering(260,1)) ;
		int added8 = s1->addCourse(ceng->getOffering(280,1)) ;

		cout << added1 << "\t" <<added4 << "\t"  << added6 << "\t" <<added7 <<"\t" <<added8<<endl ;

		ceng->addStudent(s1);
		ceng->cancelOffering(ceng->getOffering(140,2));

		cout << ceng->getDeptName() << "\n";// << dept.getInstructors() << "\n" <<dept.getStudents() << "\n" <<dept.getOfferings()<<endl;
		cout << "Instructors:" << "\n";
		for(unsigned int i = 0; i < ceng->getInstructors().size();i++){
			cout << *(ceng->getInstructors()[i]);
		}
		cout << "All courses:" << "\n";
		for(unsigned int i = 0; i < ceng->getCurriculum().size();i++){
			cout << *(ceng->getCurriculum()[i]);
		}
		cout << "Offerings:" << "\n";
		for(unsigned int i = 0; i < ceng->getOfferings().size();i++){
			cout << *(ceng->getOfferings()[i]) << "\n";
		}
		cout << "Students:" << "\n";
		for(unsigned int i = 0; i < ceng->getStudents().size();i++){
			cout << *(ceng->getStudents()[i]) << "\n";
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





