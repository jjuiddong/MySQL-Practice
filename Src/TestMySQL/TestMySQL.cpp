//
// https://github.com/flurreh/mysqlquerypp
//

#include "pch.h"
#include <iostream>
#include "mysqlquery.h"
#include <time.h>

#pragma comment(lib, "libmysql.lib")

using namespace std;

int main()
{
	MySQLConnection mySqlCon;

	if (!mySqlCon.Connect("127.0.0.1", 3306, "root", "1111", "acs"))
	{
		cout << "Error db connection " << endl;
		return 0;
	}

	cout << "Connection Success " << endl;

	MySQLQuery query(&mySqlCon, "SELECT * FROM acs.robot;");
	if (query.ExecuteQuery())
	{
		unsigned int row = query.GetResultRowCount();
		unsigned int col = query.GetFieldCount();
		for (unsigned int r = 0; r < row; ++r)
		{
			cout << "id = " << query.getInt(r + 1, "id")
				<< ", name = " << query.getString(r + 1, "name")
				<< ", date = " << query.getString(r + 1, "date")
				<< endl;
		}
	}

	MySQLQuery logQuery(&mySqlCon, "INSERT INTO acs.log (name, date, message) VALUES ('Robot1', '2019-02-04 11:33:01', 'test message222');");
	if (logQuery.ExecuteInsert())
	{
		cout << "Success Query Insert" << endl;
	}

	MySQLQuery workQuery(&mySqlCon, "UPDATE acs.work SET state = '2' WHERE workname = 'work1';");
	if (workQuery.ExecuteUpdate())
	{
		cout << "Success Query Update" << endl;
	}
}