//hostname: mymysql.senecacollege.ca:3306
//username : your MySQL username 
//password : you MySQL password  

#define _CRT_SECURE_NO_WARNINGS
#include <mysql.h>
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <sstream>
//#include <stdlib.h>
#include <string>
#include <ctype.h>
using namespace std;

struct Employee {
	int employeeNumber;
	char lastName[50];
	char firstName[50];
	char email[100];
	char phone[50];
	char extension[10];
	char reportsTo[100];
	char jobTitle[50];
	char city[50];
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////===========QUERY SENDING FUNCTION==============///////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


MYSQL_RES* executeQuery(string QRY, MYSQL* connection) { 
	MYSQL_RES* returned = nullptr;
	int exQ;
	const char* qry = QRY.c_str(); //assign a char pointer to the returned value of the function QRY
	exQ = mysql_query(connection, qry); //Test if the returned value of query inside the function returns true or false
	if (!exQ) {
		returned = mysql_store_result(connection);
	}	else {
		// If the returned value is true 
		cout << "error message: " << mysql_error(connection) << ": " << mysql_errno(connection) << endl;
	}
	return returned;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////===========EACH MENU FUNCTION==============///////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int findEmployee(MYSQL* conn, int employeeNumber, struct Employee* employee_) {
	MYSQL_RES* returned = nullptr;
	MYSQL_ROW row;
	int test = 0;
	string query = "SELECT E.employeeNumber E, E.lastName, E.firstName, E.email, O.phone, E.extension, "
		"ifnull(concat(M.firstName, ' ', M.lastName),'') 'ReportTo', E.jobTitle, O.city "
		"FROM employees E "
		"LEFT JOIN employees M ON E.reportsTo = M.employeeNumber "
		"JOIN offices O ON E.officeCode = O.officeCode "
		"WHERE E.employeeNumber = " + to_string(employeeNumber);
	returned = executeQuery(query, conn); 
	if (returned == nullptr) {
		test = 2;
	}	else if (row = mysql_fetch_row(returned)) {
		test = 1;
		employee_->employeeNumber = stoi(row[0]); 
		strcpy(employee_->lastName, row[1]);
		strcpy(employee_->firstName, row[2]);
		strcpy(employee_->email, row[3]);
		strcpy(employee_->phone, row[4]);
		strcpy(employee_->extension, row[5]);
		strcpy(employee_->reportsTo, row[6]);
		strcpy(employee_->jobTitle, row[7]);
		strcpy(employee_->city, row[8]);
	}
	return test;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void displayEmployee(MYSQL* conn, struct Employee employee_) { //Function to display the left part of the Selected Employees Table
	cout << "***************************************************" << endl;
	cout << "Employee Information:" << endl;
	cout << "EmployeeNumber: " << employee_.employeeNumber << endl;
	cout << "LastName: " << employee_.lastName << endl;
	cout << "FirstName: " << employee_.firstName << endl;
	cout << "Email: " << employee_.email << endl;
	cout << "Phone: " << employee_.phone << endl;
	cout << "Extension: " << employee_.extension << endl;
	cout << "ReportsTo: " << employee_.reportsTo << endl;
	cout << "JobTitle: " << employee_.jobTitle << endl;
	cout << "City: " << employee_.city << endl;
	cout << "***************************************************" << endl;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void displayAllEmployees(MYSQL* conn) { //Function to perform a query to return all the employees display
	MYSQL_ROW row;
	MYSQL_RES* returned = nullptr;
	string query = "SELECT E.employeeNumber E, concat(E.firstName, ' ', E.lastName) 'Employee Name', "
		"E.email 'Email', O.phone 'Phone', E.extension 'Ext', "
		"ifnull(concat(M.firstName, ' ', M.lastName),'') 'Manager' "
		"FROM employees E "
		"LEFT JOIN employees M ON E.reportsTo = M.employeeNumber "
		"JOIN offices O ON E.officeCode = O.officeCode;";
	returned = executeQuery(query, conn);
	if (returned == nullptr) {
		//If the execution of the query above results in nothing (nullptr) then do nothing.
	}	else if (returned->row_count > 0) {
		cout << setw(10) << left << "E";
		cout << setw(29) << left << "Employee Name";
		cout << setw(39) << left << "Email";
		cout << setw(20) << left << "Phone";
		cout << setw(10) << left << "Ext";
		cout << "Manager" << endl;
		cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
		while (row = mysql_fetch_row(returned)) { //Printing the rows of the table
			cout << setw(10) << left << row[0];
			cout << setw(29) << left << row[1];
			cout << setw(39) << left << row[2];
			cout << setw(20) << left << row[3];
			cout << setw(10) << left << row[4];
			cout << row[5] << endl;
		}
	}	else
	{
		cout << "There is no employees' information to be displayed." << endl;
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int getIntInRange(int minimun, int maximum)
{ //Funtion that asks for input and tests if it is between the range of options of the menu. 
	int opt = 0;
	cin >> opt;
	do {
		if (opt < minimun || opt > maximum) {
			cout << "OUT OF RANGE! Please, enter a number between " << minimun << " and " << maximum << ": ";
			cin >> opt;
		}
	} while (opt < minimun || opt > maximum);
	return opt;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void insertEmployee(MYSQL* conn, struct Employee emp) {
	int test, id;
	printf("Enter Employee Number: ");
	scanf("%d", &id);

	test = findEmployee(conn, id, &emp);

	if (test == 1) {
		printf("An employee with the same employee number exists.\n");

	}
	else if (test == 0) {

		string query2 = "insert  into `employees` (`employeeNumber`,`lastName`,`firstName`,`email`,`extension`,`jobTitle`,`officeCode`,`reportsTo`) values( ";

		printf("\n");
		printf("Employee Number: ");
		scanf("%d", &(emp.employeeNumber));
		query2 += to_string(emp.employeeNumber);
		query2 += ',';

		printf("Last Name: ");
		scanf("%s", emp.lastName);
		query2 += "\'";
		query2 += (emp.lastName);
		query2 += "\',";
		printf("First Name:");
		scanf("%s", emp.firstName);
		query2 += "\'";
		query2 += (emp.firstName);
		query2 += "\',";
		printf("Email : ");
		scanf("%s", emp.email);
		query2 += "\'";
		query2 += (emp.email);
		query2 += "\',";
		printf("extension : ");
		scanf("%s", emp.extension);
		query2 += "\'";
		query2 += (emp.extension);

		query2 += "\',";
		cin.ignore(2000, '\n');
		printf("Job Title :");

		cin.getline(emp.jobTitle, 50, '\n');
		query2 += "\'";
		query2 += (emp.jobTitle);
		query2 += "\',";
		query2 += "\'";
		query2 += to_string(1);
		query2 += "\',";
		query2 += "\'";
		query2 += to_string(1002);
		query2 += "\'";
		query2 += ")";

		printf("\n");
		const char* q2 = query2.c_str();
		int exequery2 = mysql_query(conn, q2);

		if (!exequery2) {

			MYSQL_RES* res2;
			res2 = mysql_store_result(conn);
			printf("The new employee is added successfully.\n");
		}
		else {

			cout << "Query failed.\n" << mysql_errno(conn) << " " << mysql_error(conn) << endl;
		}
	}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void updateEmployee(MYSQL* conn, int employeeNumber) {

	char next[10];
	cout << "New Extension :";
	cin >> next;

	string query3 = "UPDATE employees  SET extension = '";
	query3 += next;
	query3 += "\'";
	query3 += " WHERE employeeNumber = ";
	query3 += to_string(employeeNumber);
	query3 += "\;";

	const char* q3 = query3.c_str();
	int exequery3 = mysql_query(conn, q3);
	if (!exequery3) {
		MYSQL_RES* res3;
		res3 = mysql_store_result(conn);
		cout << " Employee " + to_string(employeeNumber) + " updated." << endl;
	}
	else {

		cout << "Query failed." << mysql_errno(conn) << " " << mysql_error(conn) << endl;
	}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void deleteEmployee(MYSQL* conn, int employeeNumber)
{
	MYSQL_RES* res = nullptr;
	string queryT = "SELECT *\nFROM employees\nWHERE employeeNumber=" + to_string(employeeNumber) + ";";
	string query = "DELETE FROM employees\nWHERE employeeNumber=" + to_string(employeeNumber) + ";";
	res = executeQueryT(queryT, conn);
	if (res != nullptr)
	{
		executeQuery(query, conn);
		cout << "\nEmployee Number: " << employeeNumber << " deleted successfully\n" << endl;
	}

	else
		cout << "\nInvalid Employee Number.\n" << endl;
	
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////===========MENU FUNCTION==============///////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int menu(void) { //Function to display the menu choices 
	int opt; //Declare an integer to store the value of the option
	cout << "1) Find Employee" << endl;
	cout << "2) Employees Report" << endl;
	cout << "3) Add Employee" << endl;
	cout << "4) Update Employee" << endl;
	cout << "5) Remove Employee" << endl;
	cout << "0. Exit" << endl;
	cout << "Please, select an option: ";
	opt = getIntInRange(0, 5); //Calling the getIntInRange to ask for input and assign opt to this value
	return opt; //Returns the value of the chosen menu 
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////===========MAIN FUNCTION==============///////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int main() {
	MYSQL* conn; //Declaration of pointer variable to store the connection info
	Employee* ArgEmplo = nullptr; 
	conn = mysql_init(0); //declare the pointer variable to the initialier function for MYSQL
	conn = mysql_real_connect(conn, "mymysql.senecacollege.ca", "", "", "", 3306, nullptr, 0);
	// Establish a connection of the application with my database in MYSQL hosted by Seneca College
	if (conn) // Test if the connection is successful
	{ 
		cout << "********************* HR Menu *********************" << endl;
		int option;
		while (option = menu()) { 
			switch (option) //Start a switch case menu with the entered input, compared with the menu options.
			{
			case 1:
			{
				cout << "Enter the employee number: ";
				int eNum;
				cin >> eNum;
				ArgEmplo = new Employee[1];
				int returned = findEmployee(conn, eNum, ArgEmplo); //Assign the returned value to an integer to test it
				if (returned == 0)
				{
					cout << "Employee " << eNum << " does not exist." << endl;
					cout << "***************************************************" << endl;
				}
				else if (returned == 2) {
					cout << "***************************************************" << endl;
				}
				else
				{
					displayEmployee(conn, *ArgEmplo); //Calling the display function with the the connection argument (it will send the query of the function to MYSQL and return the results)
				}
				break;
			}
			case 2:
				cout << "***************************************************" << endl;
				displayAllEmployees(conn); //Calling the display function with the the connection argument (it will return the results)
				cout << "***************************************************" << endl;
				break;
			case 3:
			{
				ArgEmplo = new Employee[1];
				//*ArgEmplo = { 0,"","","","","","","","" };
				insertEmployee(conn, *ArgEmplo);
				break;
			}
			case  4:
			{
				cout << "Enter Employee Number: ";
				int eNum;
				cin >> eNum;
				ArgEmplo = new Employee[1];
				int returned = findEmployee(conn, eNum, ArgEmplo);

				if (returned == 1) {
					updateEmployee(conn, eNum);
				}
				break;
			}
			case 5:
			
				int empNoFv;
				cout << "\nEnter the Employee Number: ";
				cin >> empNoFv;
				deleteEmployee(conn, empNoFv);
				break;
				
			
			case 0:
				break;
			default:
				break;
			}
		}
	}	else	{
		cout << "Connection Failed" << mysql_error(conn) << endl; //If the connection faills 
	}
	mysql_close(conn);
	conn = nullptr;
	delete conn;

	if (ArgEmplo != nullptr) {
		delete[] ArgEmplo;
		ArgEmplo = nullptr;
	}
	return 0;
}



