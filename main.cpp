#include<iostream>
#include<iomanip>
#include<string>
#include<fstream>
using namespace std;

fstream file; // 1st file

class admin
{
public:
    int noOfCourses, creditHours, semNO;
    string courseName, courseCode, instructorName, phoneNoOfInstructor;
    admin* nptrAdmin = NULL;
    void offeringCourses();
    void DetailsAdmin();
    void DetailsFaculty();
};

int numMatch[50], num[50], courseNoGlobal;
admin* fptrAdmin = NULL;
int i = 0, totalStudentsFile = 0;

class faculty : public admin
{
    int quiz[50], quizabs[50], assessments[50], aAbs[50], projects[50], projectsAbs[50], sessionals[50], finals[50];
public:
    int indexfaculty[50];
    faculty* nptrFaculty;
    void SettingGrades();
};

faculty* fptrFaculty = NULL;

class student : public faculty
{
private:
    string login, password;
public:
    int indexCourseAccept[50], semesterNumber[50];
    int totalNoOfCoursesOptBySingleStudentForClass = 0;
    string courseNameAccept[50], courseCodeAccept[50], courseCodeMatch[50];
    int courseCreditHoursAccept[50], noOfCourses;
    int totalCreditHoursForSingleStudent = 0;
    string StudentName, departmentname, phoneNOStudent;
    student* nptrStudent;
    int quiz, quizAbsolute, assignments, assignmentsAbsolute, projects, projectsAbsolute, sessional1, sessional2, finalsAbsolute;
    string coursesOptbySingleStudent_courseName[50], coursesOptbySingleStudent_coursecode[50], coursesOptbySingleStudent_instructorName[50];
    int coursesOptbySingleStudent_CreditHoors[50];
    string courseCodeOptMatch[50];
    int courseCodeOptMatchCount = 0;

    void credentials(string login1, string password1);
    string gerCredentialLogin() { return login; }
    string gerCredentialpassword() { return password; }
    void settingLogin(string& logincopy) { login = logincopy; }
    void coursesAccepting(int icA[], string cdM[], int& totalNoOfCoursesOptBySingleStudent, string ccom[], int& ccoc, int ccossCH[], string ccossCC[], string ccossCN[], string ccossIN[]);
    void studentData(string courseNameAccept[], string courseCodeAccept[], int courseCreditHoursAccept[], int index[], int semesterNumber[], int& countSingleStudentSemester);
    void studentDataAfter(string& student, string& department, string& pho);
    void DetailsofStudents();
};

student* fptrStudent = NULL;
int studentsCount = 0;

void ExitFunctionOutputing();
void fileReadingFunction();
void showAdminSemeterCourse()
{
	int l = 0;
	cout << "!! All SEMESTER & COURSES Offered By Administrator are HEREUNDER !!\n\n\n";
	cout << "\t\t\t\t\t\t\t\t" << setw(20) << "SEMESTER #" << setw(20) << "NAME" << setw(20) << "COURSE NAME" << setw(20) << "COURSE CODE" << setw(20) << "CREDIT HOURS" << setw(20) << "PHONE #" << setw(20) << "EXTENSION";
	cout << endl;
	admin* currentptr = fptrAdmin;
	while (currentptr != NULL)
	{
		cout << "\t\t\t\t\t\t\t\t" << setw(20) << currentptr->semNO << setw(20) << currentptr->instructorName << setw(20) << currentptr->courseName << setw(20) << currentptr->courseCode << setw(20) << currentptr->creditHours << setw(20) << currentptr->phoneNoOfInstructor << endl;
		currentptr = currentptr->nptrAdmin;
		l++;
	}
}


void admin::offeringCourses()
{
	cout << left << setw(20) << "Admin Offering Semesters Are Listed Below : \n";
	cout << "\n1.Fall 2023\t\t2.Spring 2024"
		<< "\n3.Fall 2023\t\t4.Spring 2024"
		<< "\n5.Fall 2023\t\t6.Spring 2024"
		<< "\n7.Fall 2023\t\t8.Spring 2024";
	cout << "\nChoose The Semester : "; tryAgain:
	cin >> num[i];
	numMatch[i] = num[i];
	if (num[i] <= 0 || num[i] > 8)
	{
		cout << setw(20) << "Wrong Input !\nPlease Try Again : ";
		goto tryAgain;
	}
	else
	{
		for (int j = 0; j < i; j++)
		{
			if (numMatch[j] == num[i])
			{
				cout << setw(20) << "\nAdmin has Already offered The Semester.\nTry Another : ";
				goto tryAgain;
			}
		}
	}
	cout << setw(20) << "\nEnter Number of Courses Offered for Semester - " << num[i] << " : ";
	cin.clear();
	cin.ignore();
	cin >> courseNoGlobal; cout << endl;
	cin.ignore();
	for (int k = 0; k < courseNoGlobal; k++)
	{
		admin* ptrAdmin = new admin;
		ptrAdmin->semNO = num[i];
		cout << "\n\t\t Details of Course - " << k + 1 << " : ";
		cout << "\n\nEnter the Name of Course : ";
		getline(cin, ptrAdmin->courseName);
		cout << "Enter the Course Code : "; EnterCourseCodeAgain:
		getline(cin, ptrAdmin->courseCode);

		admin* ptrCheckCourseCode = fptrAdmin;
		while (ptrCheckCourseCode != NULL)
		{
			if (ptrAdmin->courseCode == ptrCheckCourseCode->courseCode)
			{
				cout << "\n\t\tCourse Code has Already Assigned \n\t\tEnter Again : ";
				goto EnterCourseCodeAgain;
			}
			ptrCheckCourseCode = ptrCheckCourseCode->nptrAdmin;
		}
		cout << "Enter the Credit Hours : ";
		cin >> ptrAdmin->creditHours;
		cin.clear();
		cin.ignore();
		cout << "Enter the Name OF Instructor : ";
		getline(cin, ptrAdmin->instructorName);
		cout << "Enter the  Phone Number : ";
		getline(cin, ptrAdmin->phoneNoOfInstructor);
		cout << "\n";
		if (fptrAdmin == NULL)
		{
			fptrAdmin = ptrAdmin;
			fptrAdmin->nptrAdmin = NULL;
		}
		else
		{
			admin* cptr = fptrAdmin;
			while (cptr->nptrAdmin != NULL)
			{
				cptr = cptr->nptrAdmin;
			}
			cptr->nptrAdmin = ptrAdmin;
			ptrAdmin->nptrAdmin = NULL;
		}
	}
	i++;
}         //done

void admin::DetailsAdmin()
{
	cout << left << setw(30) << "----------------------------------------\n";
	cout << left << setw(30) << "|| ADMIN ASSIGNED SEMESTER & COURSES ||\n";
	cout << left << setw(30) << "----------------------------------------\n\n\n";
	admin* cptrdetails = fptrAdmin;
	cout << right << setw(30) << "Semister #" << setw(30) << "Course Name" << setw(30) << "Course Code" << setw(30) << "Credit Hours" << setw(30) << "Instructor Name\n";
	while (cptrdetails != NULL)
	{
		cout << right << setw(30) << cptrdetails->semNO << setw(30) << cptrdetails->courseName << setw(30) << cptrdetails->courseCode << setw(30) << cptrdetails->creditHours << setw(30) << cptrdetails->instructorName << endl;
		cptrdetails = cptrdetails->nptrAdmin;
	}
	cout << "\n\n";
}

void admin::DetailsFaculty()
{
	cout << "\n";
	cout << left << setw(15) << "-----------------------\n";
	cout << left << setw(15) << "|| FACULTY ASSIGNED ||\n";
	cout << left << setw(15) << "-----------------------\n\n\n";
	admin* cptrdetailsF = fptrAdmin;
	cout << right << setw(30) << "Semister #" << setw(30) << "Course Name" << setw(30) << setw(30) << "Credit Hours" << setw(30) << "Instructor Name" << setw(30) << "Phone #" << setw(30) << "Extension\n";
	while (cptrdetailsF != NULL)
	{
		cout << right << setw(30) << cptrdetailsF->semNO << setw(30) << cptrdetailsF->courseName << setw(30) << cptrdetailsF->creditHours << setw(30) << cptrdetailsF->instructorName << setw(30) << cptrdetailsF->phoneNoOfInstructor << endl;
		cptrdetailsF = cptrdetailsF->nptrAdmin;
	}
	cout << "\n\n";
}

//Students Functions
void student::credentials(string login1, string password1)
{
	login = login1;
	password = password1;
	cout << "\n\t\t\t!!Student Credentials!!\n"
		<< "\t\t\t    1.Login ID : "; loginAgain:
	getline(cin, login); int flag = 0;
	student* checkloginPtr = fptrStudent; int count = 0;
	while (checkloginPtr != NULL)
	{
		if (login == checkloginPtr->login)
		{
			count++;
			if (count == 1)
			{
				flag = 1;
			}
		}
		checkloginPtr = checkloginPtr->nptrStudent;
	}
	if (flag == 1)
	{
		cout << "\nThis Id Already Exist \nPlease Enter Another ID : ";
		goto loginAgain;
	}
	cout << "\t\t\t    2.Password : ";
	getline(cin, password);
}
int totalStudents = 0;
void student::coursesAccepting(int icA[], string cdM[], int& totalNoOfCoursesOptBySingleStudent, string ccom[], int& ccoc, int ccossCH[], string ccossCC[], string ccossCN[], string ccossIN[])
{
	string courseCodeMatch;
	int opt = 0, count = 0; int countCourseAccepting = 0;
	cout << "\n\n!! All SEMESTER & COURSES Offered By Administrator are HEREUNDER !!\n\n";
	admin* cptrCoursesAccepting = fptrAdmin;
	while (cptrCoursesAccepting != NULL)
	{
		cout << "\n\n \t\t\t!!COURSE - " << countCourseAccepting + 1 << " of Semester - " << cptrCoursesAccepting->semNO << " !!\n";
		cout << countCourseAccepting + 1 << ".Course Name : " << cptrCoursesAccepting->courseName << "\t\tCourse Code : " << cptrCoursesAccepting->courseCode << "\t\tInstuctor Name : " << cptrCoursesAccepting->instructorName << "\t\tCredit Hours : " << cptrCoursesAccepting->creditHours << endl;

		cptrCoursesAccepting = cptrCoursesAccepting->nptrAdmin;
		countCourseAccepting++;
		count++;
	}
	totalNoOfCoursesOptBySingleStudent = countCourseAccepting;
againOpt:
	cout << "\n\nPlease Enter  Course Code to Opt the Course : "; int cdmCount = 0; reEnter:againChoose:
	cin >> cdM[cdmCount];
	for (int j = 0; j < cdmCount && j != cdmCount; j++)
	{
		if (cdM[cdmCount] == cdM[j])
		{
			cout << "\n\t\t This Course has Already Opt \n\t\tChoose another : ";
			goto againChoose;
		}
	}
	admin* cptrCheck = fptrAdmin; int flag = 0; int check = 0, p = 0;
	while (cptrCheck != NULL)
	{
		if (cdM[cdmCount] == cptrCheck->courseCode)
		{
			icA[p] = check;
			p++;
			flag = 1;
			ccom[ccoc] = cptrCheck->courseCode;
			ccossCH[ccoc] = cptrCheck->creditHours;
			ccossCC[ccoc] = cptrCheck->courseCode;
			ccossCN[ccoc] = cptrCheck->courseName;
			ccossIN[ccoc] = cptrCheck->instructorName;
			ccoc++;
		}
		cptrCheck = cptrCheck->nptrAdmin;
		check++;
	}
	if (flag != 1)
	{
		cout << "\nThis Course is Not offered Re Enter Again : ";
		goto reEnter;
	}
	cdmCount++;
	cout << "\nDo you Wany to Opt Another Course(y/n)\nPress 1 for YES 0 for NO : ";
	cin >> opt;
	if (opt == 1){
		goto againOpt;
	}
	totalNoOfCoursesOptBySingleStudent = p;
	totalStudents++;
}
void student::studentData(string courseNameAccept[], string courseCodeAccept[], int courseCreditHoursAccept[], int index[], int semisterNumber[], int& countSingleStudentSemester)
{
	int indexData, check = 0, j = 0;
	admin* ptrAddData = fptrAdmin;
	for (int i = 0; i < countSingleStudentSemester; i++)
	{
		indexData = index[i];
		while (ptrAddData != NULL)
		{
			if (indexData == check)
			{
				courseNameAccept[j] = ptrAddData->courseName;
				courseCodeAccept[j] = ptrAddData->courseCode;
				courseCreditHoursAccept[j] = ptrAddData->creditHours;
				semisterNumber[j] = ptrAddData->semNO;
				j++;
			}
			ptrAddData = ptrAddData->nptrAdmin;
			check++;
		}
	}
}
void student::studentDataAfter(string& student, string& department, string& pho)
{
	cout << "\nEnter Name of Student : ";
	getline(cin, student);

	cout << "\nEnter Department Name : ";
	getline(cin, department);

	cout << "\nEnter Phone Number of Student : ";
	getline(cin, pho);
}
void student::DetailsofStudents()
{
	// 2nd file
	cout << "\n";
	cout << left << setw(15) << "---------------------\n";
	cout << left << setw(15) << "|| STUDENT DETAILS ||\n";
	cout << left << setw(15) << "---------------------\n\n\n";
	cout << "Total Number of Students : " << totalStudents << endl << endl;
	student* cptrStudentDetilsShow = fptrStudent;
	while (cptrStudentDetilsShow != NULL)
	{
		cout << "\n----------------------------------------------------------------------------------------------------------------------\n";
		cout << right << setw(30) << "Student Name" << setw(30) << "Department Name" << setw(30) << "Phone #" << setw(30) << "ID \n";
		int ccocCheck = 0;
		cout << right << setw(30) << cptrStudentDetilsShow->StudentName << setw(30) << cptrStudentDetilsShow->departmentname << setw(30) << cptrStudentDetilsShow->phoneNOStudent << setw(30) << cptrStudentDetilsShow->gerCredentialLogin() << endl;
		cout << "\n\n!!Courses Opt By the Student are Here under !!\n\n";
		file << "Courses Opt By the Student" << endl;
		if (cptrStudentDetilsShow != NULL)
		{
			for (int i = 0; i < cptrStudentDetilsShow->courseCodeOptMatchCount; i++)
			{
				cout << right << setw(30) << "Course Code : " << cptrStudentDetilsShow->coursesOptbySingleStudent_coursecode[ccocCheck] << right << setw(30) << "Course Name : " << cptrStudentDetilsShow->coursesOptbySingleStudent_courseName[ccocCheck] << right << setw(30) << "Instructor Name : " << cptrStudentDetilsShow->coursesOptbySingleStudent_instructorName[ccocCheck] << right << setw(30) << "Credit Hours : " << cptrStudentDetilsShow->coursesOptbySingleStudent_CreditHoors[ccocCheck] << endl << endl;
				ccocCheck++;
			}
		}
		cptrStudentDetilsShow = cptrStudentDetilsShow->nptrStudent;
	}
	cout << "\n\n";
}

//Faculty Functions
int studentC = 0;
void faculty::SettingGrades()
{
	cout << "Total Number of Students : " << totalStudents << endl;
	student* cptrStudentDetilsShow = fptrStudent;
	while (cptrStudentDetilsShow != NULL)
	{
		cout << right << setw(30) << "Student Name" << setw(30) << "Department Name" << setw(30) << "Phone #" << setw(30) << "ID \n";
		int ccocCheck = 0;
		cout << right << setw(30) << cptrStudentDetilsShow->StudentName << setw(30) << cptrStudentDetilsShow->departmentname << setw(30) << cptrStudentDetilsShow->phoneNOStudent << setw(30) << cptrStudentDetilsShow->gerCredentialLogin() << endl;
		cout << "\t\t\t!!Courses Opt By the Student are Here under !!\n";
		if (cptrStudentDetilsShow != NULL)
		{
			for (int i = 0; i < cptrStudentDetilsShow->courseCodeOptMatchCount; i++)
			{
				cout << right << setw(30) << "Course Code : " << cptrStudentDetilsShow->coursesOptbySingleStudent_coursecode[ccocCheck] << right << setw(30) << "Course Name : " << cptrStudentDetilsShow->coursesOptbySingleStudent_courseName[ccocCheck] << right << setw(30) << "Instructor Name : " << cptrStudentDetilsShow->coursesOptbySingleStudent_instructorName[ccocCheck] << right << setw(30) << "Credit Hours : " << cptrStudentDetilsShow->coursesOptbySingleStudent_CreditHoors[ccocCheck] << endl << endl;
				cout << "\nEntering marks of Student " << cptrStudentDetilsShow->StudentName << " for Course : " << cptrStudentDetilsShow->coursesOptbySingleStudent_courseName[ccocCheck] << " \n ";
				cout << "\t\tEnter Number Of Quizes in Whole Course : ";
				cin >> cptrStudentDetilsShow->quiz;
				cout << "\t\tEnter Absolute marks Of each Quiz : ";
				cin >> cptrStudentDetilsShow->quizAbsolute;
				cout << "\t\tEnter Number Of Assignments in Whole Course : ";
				cin >> cptrStudentDetilsShow->assignments;
				cout << "\t\tEnter Absolute marks Of each Assignment in Whole Course : ";
				cin >> cptrStudentDetilsShow->assignmentsAbsolute;
				cout << "\t\tEnter Number Of Projects in Whole Course : ";
				cin >> cptrStudentDetilsShow->projects;
				cout << "\t\tEnter Absolute marks Of each Project in Whole Course : ";
				cin >> cptrStudentDetilsShow->projectsAbsolute;
				cout << "\t\tEnter Absolute marks Of 1st Sessional : ";
				cin >> cptrStudentDetilsShow->sessional1;
				cout << "\t\tEnter Absolute marks Of 2nd Sessional : ";
				cin >> cptrStudentDetilsShow->sessional2;
				cout << "\t\tEnter Absolute marks Of Finals : ";
				cin >> cptrStudentDetilsShow->finalsAbsolute;
				cout << "\n\n";
				ccocCheck++;
			}
		}
		cptrStudentDetilsShow = cptrStudentDetilsShow->nptrStudent;
	}
}

void ExitFunctionOutputing()
{
	file.open("All Semster & Courses.txt", ios::out);
	admin* currentptr = fptrAdmin; int l = 0;
	while (currentptr != NULL)
	{
		file << currentptr->semNO << endl;                                           // file outputing
		file << currentptr->instructorName << endl;
		file << currentptr->courseName << endl;
		file << currentptr->courseCode << endl;
		file << currentptr->creditHours << endl;
		file << currentptr->phoneNoOfInstructor << endl;
		currentptr = currentptr->nptrAdmin;
		l++;
	}
	file << "~";
	file.close();
	file.open("Student Details.txt", ios::out);                                                 // 2nd file
	file << totalStudents << endl;
	student* cptrStudentDetilsShow = fptrStudent;
	while (cptrStudentDetilsShow != NULL)
	{
		file << cptrStudentDetilsShow->StudentName << endl;
		file << cptrStudentDetilsShow->departmentname << endl;
		file << cptrStudentDetilsShow->phoneNOStudent << endl;
		file << cptrStudentDetilsShow->gerCredentialLogin() << endl;
		if (cptrStudentDetilsShow != NULL)
		{
			file << cptrStudentDetilsShow->courseCodeOptMatchCount << endl;
			int ccocCheck = 0;
			for (int i = 0; i < cptrStudentDetilsShow->courseCodeOptMatchCount; i++)
			{
				file << cptrStudentDetilsShow->coursesOptbySingleStudent_coursecode[ccocCheck] << endl;
				file << cptrStudentDetilsShow->coursesOptbySingleStudent_courseName[ccocCheck] << endl;

				file << cptrStudentDetilsShow->coursesOptbySingleStudent_instructorName[ccocCheck] << endl;

				file << cptrStudentDetilsShow->coursesOptbySingleStudent_CreditHoors[ccocCheck] << endl;

				ccocCheck++;
			}
		}
		cptrStudentDetilsShow = cptrStudentDetilsShow->nptrStudent;
	}
	file << "~";
	file.close();
	file.open("Grading Show.txt", ios::out);
	student* cptrStudentDetilsShow2 = fptrStudent;
	while (cptrStudentDetilsShow2 != NULL)
	{
		int ccocCheck = 0;
		if (cptrStudentDetilsShow2 != NULL)
		{
			for (int i = 0; i < cptrStudentDetilsShow2->courseCodeOptMatchCount; i++)
			{
				file << cptrStudentDetilsShow2->quiz << endl;
				file << cptrStudentDetilsShow2->quizAbsolute << endl;
				file << cptrStudentDetilsShow2->assignments << endl;
				file << cptrStudentDetilsShow2->assignmentsAbsolute << endl;
				file << cptrStudentDetilsShow2->projects << endl;
				file << cptrStudentDetilsShow2->projectsAbsolute << endl;
				file << cptrStudentDetilsShow2->sessional1 << endl;
				file << cptrStudentDetilsShow2->sessional2 << endl;
				file << cptrStudentDetilsShow2->finalsAbsolute << endl;
				ccocCheck++;
			}
		}
		cptrStudentDetilsShow2 = cptrStudentDetilsShow2->nptrStudent;
	}
	file.close();
}
void fileReadingFunction()
{
	file.open("All Semster & Courses.txt", ios::in);
	if (file)
	{
		char temp = '0';
		do
		{
			string taking;
			admin* fileAdmin = new admin;
			getline(file, taking);    int changing = 0;
			fileAdmin->semNO = stoi(taking);
			getline(file, taking);
			fileAdmin->instructorName = taking;
			getline(file, taking);
			fileAdmin->courseName = taking;
			getline(file, taking);
			fileAdmin->courseCode = taking;
			getline(file, taking);
			fileAdmin->creditHours = stoi(taking);
			getline(file, taking);
			fileAdmin->phoneNoOfInstructor = taking;
			if (fptrAdmin == NULL)
			{
				fptrAdmin = fileAdmin;
				fileAdmin->nptrAdmin = NULL;
			}
			else
			{
				admin* cptrFileAdmin = fptrAdmin;
				while (cptrFileAdmin->nptrAdmin != NULL)
				{
					cptrFileAdmin = cptrFileAdmin->nptrAdmin;
				}
				cptrFileAdmin->nptrAdmin = fileAdmin;
				fileAdmin->nptrAdmin = NULL;
			}
			temp = file.peek();
		} while (temp != '~');
	}
	file.close();

	file.open("Student Details.txt", ios::in);
	if (file)
	{
		string take;
		getline(file, take);
		totalStudents = stoi(take);
		char temp = '0';
		do
		{
			string taking;
			student* ptrStudent = new student;
			getline(file, taking);
			ptrStudent->StudentName = taking;
			getline(file, taking);
			ptrStudent->departmentname = taking;
			getline(file, taking);
			ptrStudent->phoneNOStudent = taking;
			getline(file, taking);
			ptrStudent->settingLogin(taking);       // while loop ends
			getline(file, taking);
			ptrStudent->courseCodeOptMatchCount = stoi(taking);
			int i = 0; int countforEnd = 0;
			do
			{
				getline(file, taking);
				ptrStudent->coursesOptbySingleStudent_coursecode[i] = taking;
				getline(file, taking);
				ptrStudent->coursesOptbySingleStudent_courseName[i] = taking;
				getline(file, taking);
				ptrStudent->coursesOptbySingleStudent_instructorName[i] = taking;
				getline(file, taking);
				ptrStudent->coursesOptbySingleStudent_CreditHoors[i] = stoi(taking);
				i++;
			} while (ptrStudent->courseCodeOptMatchCount != i);
			if (fptrStudent == NULL)
			{
				fptrStudent = ptrStudent;
				ptrStudent->nptrStudent = NULL;
			}
			else
			{
				student* cptrFileStudent = fptrStudent;
				while (cptrFileStudent->nptrStudent != NULL)
				{
					cptrFileStudent = cptrFileStudent->nptrStudent;
				}
				cptrFileStudent->nptrStudent = ptrStudent;
				ptrStudent->nptrStudent = NULL;
			}
			temp = file.peek();
		} while (temp != '~');
	}
	file.close();
	file.open("Grading Show.txt", ios::in);
	student* cptrStudentDetilsShow2 = fptrStudent;
	while (cptrStudentDetilsShow2 != NULL)
	{
		int ccocCheck = 0;
		string taking;
		if (cptrStudentDetilsShow2 != NULL)
		{
			for (int i = 0; i < cptrStudentDetilsShow2->courseCodeOptMatchCount; i++)
			{
				getline(file, taking);
				cptrStudentDetilsShow2->quiz = stoi(taking);
				getline(file, taking);
				cptrStudentDetilsShow2->quizAbsolute = stoi(taking);
				getline(file, taking);
				cptrStudentDetilsShow2->assignments = stoi(taking);
				getline(file, taking);
				cptrStudentDetilsShow2->assignmentsAbsolute = stoi(taking);
				getline(file, taking);
				cptrStudentDetilsShow2->projects = stoi(taking);
				getline(file, taking);
				cptrStudentDetilsShow2->projectsAbsolute = stoi(taking);
				getline(file, taking);
				cptrStudentDetilsShow2->sessional1 = stoi(taking);
				getline(file, taking);
				cptrStudentDetilsShow2->sessional2 = stoi(taking);
				getline(file, taking);
				cptrStudentDetilsShow2->finalsAbsolute = stoi(taking);
				ccocCheck++;
			}
		}
		cptrStudentDetilsShow2 = cptrStudentDetilsShow2->nptrStudent;
	}
	file.close();
}

int main()
{
	string login1, password1;  string tempp;
	string choose;
	fileReadingFunction();
	cout << right << setw(130) << "-------------------------------\n";
	cout << setw(130) << "  || STUDENT MANAGEMENT SYSTEM ||\n";
	cout << setw(130) << "-------------------------------\n";
	file.open("All Semster & Courses.txt", ios::in);
	if (file)
	{
		cout << "\n!!Please Choose one !!"
			<< "\n\t\t\t1. Admin Login"
			<< "\n\t\t\t2. Faculty Login"
			<< "\n\t\t\t3. Student Login " << "\t\tChoose Option : "; char optionany = '!'; againone2:
		cin >> optionany;
		switch (optionany)
		{
		case '1':
		{
			goto oneAdminLogin;
			break;
		}
		case '2':
		{
			goto facultylogin;
			break;
		}
		case '3':
		{
			cout << "\n\t\t\t\t\t1. Enrolling Student";
			cout << "\n\t\t\t\t\t2. Student Portal" << "\t\tChoose Option : "; char ooo = '!'; againone:
			cin >> ooo;
			switch (ooo)
			{
			case '1':
			{
				goto EnrollingStudentsss;
				break;
			}
			case '2':
			{
				goto studentPortallll;
				break;
			}
			default:
			{
				cout << "\nINVALID INPUT\nPlease Try Again : ";
				goto againone;
			}
			}
		}
		default:
		{
			cout << "\nINVALID INPUT\nPlease Try Again : ";
			goto againone2;
		}
		}
	}
	else
	{
	oneAdminLogin:
		while (1)
		{
			cout << left << setw(30) << "----------------------------------------\n";
			cout << left << setw(30) << "|| ADMIN ASSIGNING SEMESTER & COURSES ||\n";
			cout << left << setw(30) << "----------------------------------------\n";
			cout << "\n\n";
		reoffer:
			cout << "\n\n";
			admin obj;
			obj.offeringCourses();
			cout << "\nDo you Want to Offer Other Semesters(y/n)\nPress 1 for Yes & any key for No : "; string option;
			cin >> option;
			if (option == "1")
				goto reoffer;
			else
				break;
		}
		getline(cin, tempp);
		cout << "\n\n";
		showAdminSemeterCourse();
		cout << "\n\n";
		system("pause");
		system("CLS");
		file.open("Student Details.txt", ios::in);
		if (!file)
		{
		EnteringMoreStudents:
		EnrollingStudentsss:
			while (1)
			{
				static int studentsCount = 0;
				cout << left << setw(20) << "------------------------\n";
				cout << left << setw(20) << "|| STUDENT ENROLLMENT ||\n";
				cout << left << setw(20) << "------------------------\n";
				student* ptrStudent = new student;
				studentsCount++;
				cin.clear();
				cin.ignore();
				ptrStudent->credentials(login1, password1);
				ptrStudent->studentDataAfter(ptrStudent->StudentName, ptrStudent->departmentname, ptrStudent->phoneNOStudent);//done
				ptrStudent->coursesAccepting(ptrStudent->indexCourseAccept, ptrStudent->courseCodeMatch, ptrStudent->totalNoOfCoursesOptBySingleStudentForClass, ptrStudent->courseCodeOptMatch, ptrStudent->courseCodeOptMatchCount, ptrStudent->coursesOptbySingleStudent_CreditHoors, ptrStudent->coursesOptbySingleStudent_coursecode, ptrStudent->coursesOptbySingleStudent_courseName, ptrStudent->coursesOptbySingleStudent_instructorName);
				if (fptrStudent == NULL)
				{
					fptrStudent = ptrStudent;
					fptrStudent->nptrStudent = NULL;
				}
				else
				{
					student* currentPtr = fptrStudent;
					while (currentPtr->nptrStudent != NULL)
					{
						currentPtr = currentPtr->nptrStudent;
					}
					currentPtr->nptrStudent = ptrStudent;
					ptrStudent->nptrStudent = NULL;
				}
				cout << "\nDo you Want to Enroll other Students(y/n)\nPress 1 for Yes & 0 for No : "; string option1;
				cin >> option1;
				if (option1 == "1")
					continue;
				else
					break;
			}
			cout << "\n\n";
			system("pause");
			system("CLS");
		}
		file.close();
		file.open("Student Details.txt", ios::in);
		if (!file)
		{
		facultylogin:
			while (1)
			{
			facultyRole:
			backFacultyRoleFille1:
				cout << left << setw(15) << "------------------\n";
				cout << left << setw(15) << "|| FACULTY ROLE ||\n";
				cout << left << setw(15) << "------------------\n\n\n";
				cout << "press 1 for Setting Grades \n"
					<< "press 2 to Main Menu\n"
					<< "Choose Option : ";
				char option3; PAgain:
				cin >> option3;
				switch (option3)
				{
				case '1':
				{
					faculty obj2;
					obj2.SettingGrades();
					break;
				}
				case '2':
				{
					goto outside;
				}
				default:
				{
					cout << "\nINVALID INPUT\nPlease Try Again : ";
					goto PAgain;
				}
				}
			}
			system("pause");
			system("CLS");
		}
	outside:
		file.close();
		while (1)
		{
		MENU:
			cout << left << setw(15) << "---------------\n";
			cout << left << setw(15) << "|| MAIN MENU ||\n";
			cout << left << setw(15) << "---------------\n\n";
			cout << "\n1. View Semester And Courses Offered By Admin"
				<< "\n2. View Faculty Offering Courses "
				<< "\n3. View Student Details"
				<< "\n4. Back to Faculty Role"
				<< "\n5. Enterig More Students"
				<< "\n6. Back to Faculty Role"
				<< "\n7. Exit"
				<< "\nChoose Option : ";  cAgain:
			cin >> choose;
			if (choose == "1")
			{
				admin details;
				details.DetailsAdmin();
			}
			else if (choose == "2")
			{
				admin FacultyDetails;
				FacultyDetails.DetailsFaculty();
			}
			else if (choose == "3")
			{
			studentPortallll:
				student detailsShow;
				detailsShow.DetailsofStudents();
			studentPortal:
				cout << "\nPress 1 for Checking Marks"
					<< "\nPress 2 for Returning to Menu"
					<< "\nPress 3 to Exit : "; char lastChoose; ptA:
				cin >> lastChoose;
				switch (lastChoose)
				{
				case '1':
				{
					faculty setGrades;
					setGrades.SettingGrades();
					break;
				}
				case '2':
				{
					goto exitFinallll;
				}
				case '3':
				{
					goto MENU;
				}
				default:
				{
					cout << "\nINVALID\nPlease Try Again : ";
					goto ptA;
				}
				}
				goto studentPortal;
			}
			else if (choose == "7")
				goto exitthis;
			else if (choose == "4")
				goto facultyRole;
			else if (choose == "5")
			{
				goto EnteringMoreStudents;
			}
			else if (choose == "6")
			{
				goto backFacultyRoleFille1;
			}
			else
			{
				cout << "\nINVALID INPUT\nPlease Try Again : ";
				goto cAgain;
			}
		}
	}
exitFinallll:
exitthis:
	file.close();
	ExitFunctionOutputing();
	return 0;
}
