
//hostname: mymysql.senecacollege.ca:3306
//username : your MySQL username db_yhde_oliveira_falcao
//password : you MySQL password  3mR+8xcFv[

#include <mysql.h>
#include <iostream>

	using namespace std;
	int main(void) {

		MYSQL* conn;
		conn = mysql_init(0);
		conn = mysql_real_connect(conn, "mymysql.senecacollege.ca", "db_yhde-oliveira-falcao", "3mR+8xcFv[", "db_yhde-oliveira-falcao", 3306, nullptr, 0);
		/*
		if (conn) {
			cout << "successful connection to database" << endl;
		}
		else {
			cout << "Connection Failed" << mysql_error(conn) << endl;
		}
		*/ 
		//Test if the connection is successful
	
		string query = "select employees.employeeNumber, employees.firstName, employees.lastName, offices.phone, employees.extension from employees inner join offices on employees.officeCode = offices.officeCode where city = 'San Francisco';";
		const char* q = query.c_str();
		 //query to select the data required

		int exequery;
		exequery = mysql_query(conn, q);
		//save the query and connection to a variable
		MYSQL_RES* res;
		res = mysql_store_result(conn);
		//stores he result of the query on a variable
		
		if (mysql_affected_rows(conn) == 0) {
			cout << "The result is empty." << endl;
		}

		MYSQL_ROW row;
		cout << "**************** Employee Report ****************" << endl;
		cout << "Employee Report:" << endl;

		while (row = mysql_fetch_row(res)) {
			printf("ID: %s\t  Name: %s %s\t Phone: %s\t Extension: %s\n", row[0], row[1], row[2], row[3], row[4]);

		}//print all the data of the query

		
		string query2 = "select employees.employeeNumber, employees.firstName, employees.lastName, offices.phone,  employees.extension FROM employees inner join offices on  employees.officeCode=offices.officeCode where employeeNumber in (select reportsTo from employees) order by employeeNumber asc;";

		//string query2 = "select emp.employeeNumber, emp.firstName, emp.lastName, offices.phone,  emp.extension FROM offices, (employees as e inner join employees as emp on e.employeeNumber = emp.reportsTo);";
		const char* q2 = query2.c_str();

		
		int exequery2;
		exequery2 = mysql_query(conn, q2);

		MYSQL_RES* res2;
		res2 = mysql_store_result(conn);

		if (mysql_fetch_row(res2) < 0) {
			cout << "The result is empty." << endl;
		}

		MYSQL_ROW row2;
		cout << "Manager Report" << endl;


		while (row2 = mysql_fetch_row(res2)) {
			printf("ID: %s\t Name: %s %s\t Phone: %s\t Extension: %s\n", row2[0], row2[1], row2[2], row2[3], row2[4]);
		}
	}//print all the data of the query

		
		mysql_close(conn);
		
		return 0;
	}

