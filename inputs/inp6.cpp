#include "hw1.h"
#include <iostream>
#include <fstream>
using namespace std;

int main(){
	try{

		Student* s1 = new Student(100000, "Veli") ;
		s1->addPrevCourse(100) ;
		s1->addPrevCourse(111) ;
		s1->addPrevCourse(140) ;

		vector<int> prevs = s1->getPrevCourses();
		cout << "ID:"<<s1->getID() << "\t NAME:" << s1->getName() <<"\t PREV_COURSE_CODES:";
		for(unsigned int i = 0; i < prevs.size();i++){
			cout << prevs[i];
			if(i != prevs.size()-1){
				cout << "-";
			}
		}
		Schedule* schedule = s1->getSchedule();

		cout << *schedule << endl;
		
		/*
		cout << "\n";
		string day;
		for(int i = 0; i < DAYS_WORKING; i++){
			switch(i){
			case 0:
				day = "Mon:";
				break;
			case 1:
				day ="Tue:";
				break;
			case 2:
				day="Wed:";
				break;
			case 3:
				day="Thu:";
				break;
			case 4:
				day="Fri:";
				break;
			default:
				cout<<"Unexpected day:" <<i<<"\n";
				break;
			}

			OfferingPair* curr = &((schedule->getSchedule())[i]);
			if(curr != NULL && curr->off != NULL){
				cout << day << curr->off->getWhichHour()<<"-"<<curr->off->getWhichHour()+curr->off->getDuration()-1<<":"<<*(curr->off) <<"\t";
				while(curr->nextOff != NULL){
					curr = curr->nextOff;
					cout<< curr->off->getWhichHour()<<"-"<<curr->off->getWhichHour()+curr->off->getDuration()-1<<":"<<*(curr->off) <<"\t";
				}
				cout << "\n";
			}

		}
		*/

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

