#include "hw1.h"

using namespace std;

Department::Department ( string name ) {
	this->name = name;
}

string Department::getDeptName () {
	return this->name;
}
vector<Instructor*> Department:: getInstructors (){
	return this->instructors;
}                    
vector<Student*>  Department::    getStudents    () {
	return this->students;
}
vector<Offering*>    Department:: getOfferings   () {
	return this->offeredCourses;

}
vector<Course*>       Department::getCurriculum  () {
	return this->curriculum ;
}
Instructor * Department::getInstructor  ( int id ) {
	int i;
	for(i=0; i< instructors.size();i++  ){
		if(id == instructors[i]->getID() )
			return instructors[i];
	}
	return NULL;
} 
Student             * Department::getStudent     ( int id )  {
	int i;
	for(i=0; i< students.size();i++  ){
		if(id == students[i]->getID() )
			return students[i];
	}
	return NULL;
}
Course              * Department::getCourse      ( int code ) {
	int i;
	for(i=0; i< curriculum.size() ; i++){
		if( code == curriculum[i]->getCourseCode() )
			return curriculum[i] ;
	
	}
	return NULL;

}        
Offering* Department::getOffering    ( int code , int section ) {
	int i;
	for(i=0;i< offeredCourses.size() ;i++){
		if((code == offeredCourses[i]->getCourse()->getCourseCode() )&& (section==offeredCourses[i]->getSection() )   )
			return offeredCourses[i];
	}
	throw(ERR_OFFERING_DOES_NOT_EXIST);
}

void Department::addInstructor  ( Instructor * newIns        ) {
	int i;
	for (i=0; i <instructors.size() ; i++ ){
		if(instructors[i]->getID() == newIns->getID()  ){
			throw(ERR_INSTRUCTOR_ALREADY_EXISTS);
		}
	
	}

//	instructors.push_back(newIns);
	instructors.insert(instructors.begin(),newIns);
	

	int n = instructors.size();
	if(n==1 || n==0)return;
	for(i=0;i<n-1;i++){
		
		if(instructors[i]->getID() > instructors[i+1]->getID()  ){
			
			swap(instructors[i],instructors[i+1]);
		}
		else{
			break;
		}
		
	}
		
	
	
}
void Department::removeInstructor      ( int          oldInsID      ) {

	int j;
	int n,k;
	Offering *ins = new Offering;
	Offering *dep = new Offering;
	int Csize ;
	
	for ( unsigned int i = 0 ; i < instructors.size() ; i++ )
	{
		if (  instructors[i]->getID() == oldInsID  )
		{
			vector<Offering *> a  = getOfferings();
			Csize = a.size();
			for(k = 0; k< Csize ; k++){
				n = 	(instructors[i]->getOfferedCourses()).size();
				if (n==0)break;
				dep = a[k];
				for( j = 0; j< n  ; j++){
					ins = instructors[i]->getOfferedCourses()[j];
					if ( ins->getCourse()->getCourseCode()== dep->getCourse()->getCourseCode() && ins->getSection() == dep->getSection()  ){
							cancelOffering( (instructors[i]->getOfferedCourses() )[j] );
							break;
						
					}
					 
				}
			}

			instructors.erase( instructors.begin()+i ) ;
			break;
		}
	}
}
void Department::addStudent            ( Student    * newStds       ) {
	int i;
	for(i=0;i<students.size();i++){
		if(students[i]->getID() == newStds->getID())
			throw(ERR_STUDENT_ALREADY_EXISTS );
	
	}
//	students.push_back(newStds);
	students.insert(students.begin(),newStds);
	int n = students.size();
	if(n==1 || n==0)return;
	for(i=0;i<n-1;i++){
		
		if(students[i]->getID() > students[i+1]->getID()  ){
			
			swap(students[i],students[i+1]);
		}
		else{
			break;
		}
		
	}
}
void Department::removeStudent         ( int          gradutedStdID ) {
	for ( unsigned int i = 0 ; i < students.size() ; i++ )
	{
		if (  students[i]->getID() == gradutedStdID  )
		{   
			Offering* tmp = new Offering;
			for(int j = 0; j< offeredCourses.size() ; j++){
					tmp = students[i]->getSchedule()->getCurrentOffering( offeredCourses[j]->getCourse()->getCourseCode()  );
					if (tmp != NULL && tmp->getSection() == offeredCourses[j]->getSection() )
						students[i]->dropCourse(offeredCourses[j]  );
				
			}
			
			
			students.erase( students.begin()+i ) ;
		}
	}
}
void Department::offerNewCourse  ( Offering   * no            )  {
	int i = 0;
	for(i=0;i<curriculum.size() ; i++){
		if ( curriculum[i]->getCourseCode() == no->getCourse()->getCourseCode() )
			break;
	}
	if (i== curriculum.size()) {
			this->addCourseToCurriculum( no->getCourse());
	}
		
	
	
	for(i=0;i< offeredCourses.size() ; i++){
		if((offeredCourses[i]->getCourse()->getCourseCode()==no->getCourse()->getCourseCode()) && (offeredCourses[i]->getSection()==no->getSection() )&&
		offeredCourses[i]->getInstructor() == no->getInstructor() ){
			throw(ERR_OFFERING_ALREADY_EXISTS);
		}
	}

	offeredCourses.push_back(no);


}
void Department::cancelOffering     ( Offering   * co            )  {

	for(int i=0;i<instructors.size();i++){
		if(instructors[i]->getID() == co->getInstructor()->getID()){
			instructors[i]->cancelOffering(co);
			break;
		}
	}
	Offering* temp = new Offering;
	int code = co->getCourse()->getCourseCode();
	int section = co->getSection();
	for(int i=0;i<students.size();i++ ){
		  temp = students[i]->getSchedule()->getCurrentOffering( code  ); 
		  if(temp != NULL){
				if(section == temp->getSection())
					students[i]->dropCourse(co);
		  	
		  	
		  }
	}
	for ( unsigned int i = 0 ; i < offeredCourses.size() ; i++ )
	{
		if((offeredCourses[i]->getCourse()->getCourseCode()==co->getCourse()->getCourseCode()) && (offeredCourses[i]->getSection()==co->getSection()) 
		 	&& offeredCourses[i]->getInstructor() == co->getInstructor() )
		{
			offeredCourses.erase( offeredCourses.begin()+i ) ;
		}
	}
}
void Department::addCourseToCurriculum ( Course     * curr          ) {
	int i,j;
	for(i=0; i < curriculum.size() ; i++){
		if(curriculum[i]->getCourseCode() == curr->getCourseCode())
			throw(ERR_COURSE_ALREADY_EXISTS );
	}

	vector<int> preReq;
	int n = curriculum.size();

	int code = curr->getCourseCode();
	
	for(i=0; i < n ; i++ ){
		preReq = curriculum[i]->getPreReqCourseCodes();
		for(j=0; j < preReq.size() ; j++){
			if( code == preReq[j] ){
				curriculum.insert(curriculum.begin() + i, curr);
				return ;
			}
		} 
	}
	curriculum.push_back(curr);
	
	
}
ostream & operator<< ( ostream & out , Department & dept ) {
	int i;
	out << dept.getDeptName()<<endl;
	out << "Instructors:"<<endl;
	for(i=0;i< (dept.getInstructors()).size() ; i++   ){
		out << *( dept.getInstructors()[i]) ;
	}
	out<< "All courses:"<<endl;
	for(i=0;i< (dept.getCurriculum()).size() ; i++   ){
		out <<  *(dept.getCurriculum()[i] );
	}
	out << "Offerings:"<<endl;
	for(i=0;i< (dept.getOfferings()).size() ; i++   ){
		out <<  *(dept.getOfferings()[i]) <<endl;
	}
	out<< "Students:"<<endl;
	for(i=0;i< (dept.getStudents()).size() ; i++   ){
		out <<  *(dept.getStudents()[i] );
	}

	return out<<endl;
}
