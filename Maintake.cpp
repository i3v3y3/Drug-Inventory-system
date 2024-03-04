#include <iostream>
#include <string>
#include <windows.h>
#include "Procu.h"

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>

using namespace sql;
using namespace std;


string drugname, drugbrand;

int quantity, availableno, buyingno, newnum, availabledrug, NO_;



int main()

{

    // here I initialize connection with mySQL
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* con;

    system("cls");
    //Here I will introduce the page and let the user selt their option
    system("color 03");

    cout << "\n\n\nHello\t\t\n\nKaribu Daktari\t\t\n\nKindly select your user" << endl;

    Sleep(5000);
    system("cls");

    string usersname;
    cout << "Insert here your name:";
    cin >> usersname;

    //I will now perform a username check after I get data on who is the user
    if (usersname == "Doc" || usersname == "Pharmacy" || usersname == "Front Desk" || usersname == "Daktari") // You can now include whoever is in charge of selling or checking
    {


        system("cls");
        cout << "Welcome," << usersname << "!";
        cout << "\t\n\n You are now being redricted to the drugs database. \t\t\n\n Please be patient";
        Sleep(2000);
        system("cls");

        // this part of the code is dedicated to connecting to the mySQL table and displaying the table contents
        try
        {
            sql::Driver* driver;
            sql::Connection* con;
            driver = get_driver_instance();
            // here change your username and password as intended
            con = driver->connect("tcp://127.0.0.1:3306", "root", "MatoborIvy33");

            con->setSchema("druginventory");

            sql::Statement* stmt;
            stmt = con->createStatement();

            sql::ResultSet* res;
            res = stmt->executeQuery("SELECT * FROM drugsavailable");

            while (res->next()) {
                int NO_ = res->getInt(1);
                int quantity = res->getInt(2);
                string drugname = res->getString(3);
                string drugbrand = res->getString(4);
                cout << "\t\t "<<NO_<<"\t\t" << quantity << " \t\t" << drugname << " \t\t " << drugbrand << endl;
            }
            //Here is the selection prompt which can be made easier by just selection but we use input prompt
            cout << "\t\t\n\n Do you want to sell a specific drug?\n\n\t\t Enter the number of the drug:";

            int availabledrug;
            cin >> availabledrug;

            // Get the current quantity of the selected drug
            res = stmt->executeQuery("SELECT quantity FROM drugsavailable WHERE NO_ = " + std::to_string(availabledrug));
            int currentQuantity = 0;
            if (res->next()) {
                currentQuantity = res->getInt(1);
            }
            else {
                cout << "Drug not found." << endl;
                delete res;
                delete stmt;
                delete con;
                return 1;
            }

            cout << "\t\t\n\nEnter the number available : ";

            
            cin >> availableno;

            cout << "\n\n\t\t How many does the client want\t\t\n\n Enter here:";

           
            cin >> buyingno;

            if (buyingno <= 0 || buyingno > availableno) {
                cout << "Invalid input." << endl;
            }
            else if (currentQuantity >= buyingno) {
                // Subtract the buyingno from the currentQuantity
                currentQuantity -= buyingno;

                // Update the quantity column in the database
                sql::PreparedStatement* pstmt;
                pstmt = con->prepareStatement("UPDATE drugsavailable SET quantity = ? WHERE NO_ = ?");
                pstmt->setInt(1, currentQuantity);
                pstmt->setInt(2, availabledrug);
                pstmt->executeUpdate();
                Sleep(1000);
                cout << "\n Successfully bought." << endl;

                system("cls");
                Sleep(5000);

                // Display updated table
                res = stmt->executeQuery("SELECT * FROM drugsavailable");
                cout << "\n\n Updated Table:\n\n";
                cout << "\t\t NO_\t\t Quantity\t\t Drug Name\t\t Drug Brand\n";
                while (res->next()) {
                    int NO_ = res->getInt(1);
                    int quantity = res->getInt(2);
                    string drugname = res->getString(3);
                    string drugbrand = res->getString(4);
                    cout << "\t\t " << NO_ << "\t\t" << quantity << " \t\t" << drugname << " \t\t " << drugbrand << endl;
                }
            }
            else {
                cout << "Not enough quantity available." << endl;
            }

            delete res;
            delete stmt;
            delete con;
         
        }
        catch (sql::SQLException& e) {
            cout << "# ERR: SQLException in " << __FILE__;
            cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
            cout << "# ERR: " << e.what();
            cout << " (MySQL error code: " << e.getErrorCode();
            cout << ", SQLState: " << e.getSQLState() << " )" << endl;
        }
        return 0;
    }
    else {
      cout<<"\n\n\t\t Are you in procument? ";
      string procpage;
      cin>> procpage;
      if (procpage == "yes" || procpage == "Y" || procpage == "YES"|| procpage=="Yes") {
        checkpoint();
      }
      else {
          cout << "Invalid choice!! Kindly reload the page";
      }
    }
    return (1);
}
