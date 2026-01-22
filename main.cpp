// NOTE: This file was written for testing purposes only.
// It is intended solely to catch linkage runtime DLL errors.

#include <iostream>
#include <Poco/Data/Session.h>
#include <Poco/Data/PostgreSQL/Connector.h>
#include <Poco/Data/RecordSet.h>
#include <Poco/Data/Statement.h>

using namespace Poco::Data;
using namespace Poco::Data::Keywords;

int main()
{
    try
    {
        std::cout << "Poco PostgreSQL Sample Program" << std::endl;
        std::cout << "==============================" << std::endl;

        PostgreSQL::Connector::registerConnector();

        std::string connectionString = 
            "host=localhost "
            "port=5432 "
            "dbname=postgres "
            "user=postgres "
            "password=postgres";

        std::cout << "\nConnecting to PostgreSQL..." << std::endl;

        Session session(PostgreSQL::Connector::KEY, connectionString);

        std::cout << "Connection successful!" << std::endl;

        std::cout << "\nQuerying PostgreSQL version..." << std::endl;
        
        std::string version;
        Statement select(session);
        select << "SELECT version()",
            into(version),
            now;

        std::cout << "PostgreSQL Version: " << version << std::endl;

        std::cout << "\nCreating test table..." << std::endl;
        
        session << "DROP TABLE IF EXISTS test_table", now;
        session << "CREATE TABLE test_table (id SERIAL PRIMARY KEY, name VARCHAR(100), value INTEGER)", now;
        
        std::cout << "Table created!" << std::endl;

        std::cout << "\nInserting data..." << std::endl;
        
        std::string name1 = "Test Item 1";
        int value1 = 100;
        session << "INSERT INTO test_table (name, value) VALUES ($1, $2)",
            use(name1),
            use(value1),
            now;

        std::string name2 = "Test Item 2";
        int value2 = 200;
        session << "INSERT INTO test_table (name, value) VALUES ($1, $2)",
            use(name2),
            use(value2),
            now;

        std::cout << "Data inserted!" << std::endl;

        std::cout << "\nReading data..." << std::endl;
        
        Statement selectData(session);
        selectData << "SELECT id, name, value FROM test_table";
        selectData.execute();

        RecordSet rs(selectData);
        
        std::cout << "\nData read from table:" << std::endl;
        std::cout << "---------------------" << std::endl;
        
        bool more = rs.moveFirst();
        while (more)
        {
            std::cout << "ID: " << rs["id"].convert<int>()
                      << ", Name: " << rs["name"].convert<std::string>()
                      << ", Value: " << rs["value"].convert<int>()
                      << std::endl;
            more = rs.moveNext();
        }

        std::cout << "\nDropping test table..." << std::endl;
        session << "DROP TABLE test_table", now;

        PostgreSQL::Connector::unregisterConnector();

        std::cout << "\nProgram completed successfully!" << std::endl;
        return 0;
    }
    catch (Poco::Exception& ex)
    {
        std::cerr << "\nPoco Error: " << ex.displayText() << std::endl;
        return 1;
    }
    catch (std::exception& ex)
    {
        std::cerr << "\nStandard Error: " << ex.what() << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cerr << "\nAn unknown error occurred!" << std::endl;
        return 1;
    }
}
