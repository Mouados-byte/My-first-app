#include "sql.h"
#include "fileio.h"

using namespace std;


int this_sql::data_sql(void)
{

        try {
        sql::Driver* driver2;
        sql::Connection* con2;
        sql::Statement* stmt2;
        sql::ResultSet* res2;

        /* Create a connection */
        driver2 = get_driver_instance();
        con2 = driver2->connect("localhost:3306", "root", "mouad123");
        /* Connect to the MySQL test database */
        con2->setSchema("test");

        vector<string> commands = reader("Resources\\car_rental.txt");
        stmt2 = con2->createStatement();
        res2 = stmt2->executeQuery("SELECT * FROM car");
        
        res = res2;
        /*for (const auto& command : commands) {
            stmt->execute(command);
            cout << "command" << i++ << "was executed succesfully";
        }*/
        
        

    }
    catch (sql::SQLException& e) {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }

    cout << endl;

    return 0;
}