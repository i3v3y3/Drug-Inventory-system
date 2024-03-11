
#pragma once
#include <iostream>
#include <string>
#include <windows.h>


#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>

using namespace std;
using namespace sql;

int newnodrug;

void checkpoint()
{
    system("cls");
    Sleep(1000);

    cout << "\t\t\t\t\t\t\n\n\n\n Welcome Procument!!";
    cout << "\t\t\n\nThe system will now load the drugs from the database. Please be patient...";
    system("cls");

    Driver* driver;
    Connection* con;

    driver = get_driver_instance();
    // here change your username and password as intended
    con = driver->connect("tcp://127.0.0.1:3306", "root", "MatoborIvy33");

    con->setSchema("druginventory");

    Statement* stmt;
    stmt = con->createStatement();

    ResultSet* res;
    res = stmt->executeQuery("SELECT * FROM drugsavailable");

    while (res->next()) {
        int NO_ = res->getInt(1);
        int quantity = res->getInt(2);
        string drugname = res->getString(3);
        string drugbrand = res->getString(4);
        cout << "\t\t " << NO_ << "\t\t" << quantity << " \t\t" << drugname << " \t\t " << drugbrand << endl;

    }
    cout << "What would you like to perform?\n\n\t 1.Restock on drugs\n\n\t 2. Remove specific drug\n\n\t\t";

    int procchoice;
    cin >> procchoice;
    switch (procchoice)
    {
    case 1:
    {
        system("cls");
        Sleep(1000);


        sql::ResultSet* res = stmt->executeQuery("SELECT * FROM drugsavailable WHERE NO_ = " + std::to_string(newnodrug));
        if (!res->next()) {
            cout << "Drug not found." << endl;
            delete res;
            break;
        }

        cout << "\t\t\n\n How many are you adding?: ";
        int newnumber;
        cin >> newnumber;

        // Prepare a statement to update the quantity column in the table
        sql::PreparedStatement* pstmt;
        pstmt = con->prepareStatement("UPDATE drugsavailable SET quantity = quantity + ? WHERE NO_ = ?");
        pstmt->setInt(1, newnumber);
        pstmt->setInt(2, newnodrug);

        // Execute the statement and update the table
        int rowsAffected = pstmt->executeUpdate();
        cout << rowsAffected << " row(s) updated." << endl;

        // Close the prepared statement
        delete pstmt;

        Sleep(1000);

        break;
    }
    case 2:
    { // you can write here something else you want to be performed
        cout << " hello";
        break;
    }
    }
}

