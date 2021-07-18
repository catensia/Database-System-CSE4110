#pragma warning(disable:4996)
#include <iostream>
#include <string>
#include <mysql.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <limits>
#undef max
#pragma comment(lib, "libmySQL.lib")
using namespace std;

const char* host = "localhost";
const char* user = "root";
const char* pw = "mysql";
const char* db = "project";
MYSQL_RES* res;
MYSQL_ROW row;
MYSQL* connection = NULL;
MYSQL conn;

void execute_query(char query[]) {
	int state = 0;
	state = mysql_query(connection, query);
	if (state == 0) {
		res = mysql_store_result(connection);
		int fields = mysql_num_fields(res);
		while (row = mysql_fetch_row(res)) {
			for (int i = 0; i < fields; i++) {
				printf("%s\t", row[i]);
			}
			printf("\n");
		}
	}
	else {
		cout << "No Result" << endl;
	}
}

void type1(void) {
	int K;
	char brand[50];
	cout << "**Show the sales trends for a particular brand over the pask k years.**" << endl;
	cout << "Which brand? : ";
	cin >> brand;
	cout << "Which K? : ";
	cin >> K;
	char query[1000];
	sprintf(query,
		"select * from `project`.`sales` where vehicle_ID in("
		"select vehicle_ID from `project`.`asset` where options_option_ID in("
		"select option_ID from `project`.`options` where model_model_ID in("
		"select model_ID from `project`.`model` where brand_brand_ID in("
		"select brand_ID from `project`.`brand` where brand_name = '%s'))))"
		"and sell_date BETWEEN DATE_SUB(NOW(), INTERVAL %d YEAR) AND NOW();"
		, brand, K
	);
	cout << "Sales List with Date" << endl;
	cout << "vehicle_ID   |  dealer_ID    |  sell_date     | customer_ID" << endl;
	cout << "---------------------------------------------------------------" << endl;
	execute_query(query);
	cout << "---------------------------------------------------------------\n" << endl;
	int N;
	cout << "------------------------ Subtypes in TYPE 1 -------------------" << endl;
	cout << "                        1. TYPE 1-1" << endl;
	cout << "                        2. TYPE 1-1-1" << endl;
	cout << "Input query subtype: ";
	cin >> N;

	if (N == 1) {
		cout << "**Break out the data out by gender of the buyer**" << endl;
		cout << "Input 'M'(Male) or 'F'(Female)" << endl;
		char gender;
		cin >> gender;
		if (gender != 'M' && gender != 'F') {
			cout << "Invalid input" << endl;
			return;
		}

		sprintf(query,
			"select vehicle_ID, dealer_dealer_ID, sell_date, customer_customer_ID, gender from `project`.`sales` join `project`.`customer` where "
			"customer_customer_ID = customer_ID and gender = '%c' and vehicle_ID in("
			"select vehicle_ID from `project`.`asset` where options_option_ID in("
			"select option_ID from `project`.`options` where model_model_ID in("
			"select model_ID from `project`.`model` where brand_brand_ID in("
			"select brand_ID from `project`.`brand` where brand_name = '%s')))"
			"and sell_date BETWEEN DATE_SUB(NOW(), INTERVAL %d YEAR) AND NOW());", gender, brand, K
		);
		if (gender == 'M') cout << "Sales list of male customers" << endl;
		else cout << "Sales list of female customers" << endl;
		cout << "vehicle_ID   |  dealer_ID    |  sell_date     | customer_ID      | gender   " << endl;
		cout << "-----------------------------------------------------------------------------" << endl;
		execute_query(query);
		cout << "-----------------------------------------------------------------------------\n" << endl;

		return;

	}
	else {
		cout << "**Break out the data out by income range**" << endl;
		cout << "Input range of income [EX: 5000 10000]" << endl;
		int min, max;
		cin >> min >> max;
		if (min > max) {
			cout << "Invalid range" << endl;
			return;
		}
		sprintf(query,
			"select vehicle_ID, dealer_dealer_ID, sell_date, customer_customer_ID, annual_income from `project`.`sales` join `project`.`customer` where "
			"customer_customer_ID = customer_ID and annual_income between %d and %d and vehicle_ID in("
			"select vehicle_ID from `project`.`asset` where options_option_ID in("
			"select option_ID from `project`.`options` where model_model_ID in("
			"select model_ID from `project`.`model` where brand_brand_ID in("
			"select brand_ID from `project`.`brand` where brand_name = '%s')))"
			"and sell_date BETWEEN DATE_SUB(NOW(), INTERVAL %d YEAR) AND NOW());", min, max, brand, K
		);
		cout << "Sales list of customers with annual income range " << min << " - " << max << endl;
		cout << "vehicle_ID   |  dealer_ID    |  sell_date     | customer_ID   | annual_income" << endl;
		cout << "-----------------------------------------------------------------------------" << endl;
		execute_query(query);
		cout << "-----------------------------------------------------------------------------\n" << endl;

		return;
	}

}

void type2(void) {
	int K;
	char query[1000];
	cout << "**Show sales trends for various brands over the past k months**" << endl;
	cout << "Which K?: ";
	cin >> K;
	cout << "vehicle_ID   |  dealer_ID    |  sell_date     | customer_ID        " << endl;
	cout << "-----------------------------------------------------------------------------" << endl;
	sprintf(query, "select * from `project`.`sales` where sell_date BETWEEN DATE_SUB(NOW(), INTERVAL %d MONTH) AND NOW();", K);
	execute_query(query);

	cout << "-----------------------------------------------------------------------------\n" << endl;
	int N;
	cout << "------------------------ Subtypes in TYPE 1 -------------------" << endl;
	cout << "                        1. TYPE 2-1" << endl;
	cout << "                        2. TYPE 2-1-1" << endl;
	cout << "Input query subtype: ";
	cin >> N;

	if (N == 1) {
		cout << "**Break out the data out by gender of the buyer**" << endl;
		cout << "Input 'M'(Male) or 'F'(Female)" << endl;
		char gender;
		cin >> gender;
		if (gender != 'M' && gender != 'F') {
			cout << "Invalid input" << endl;
			return;
		}

		sprintf(query,
			"select vehicle_ID, dealer_dealer_ID, sell_date, customer_customer_ID, gender from `project`.`sales` join "
			"`project`.`customer` where customer_customer_ID = customer_ID and gender = '%c' "
			"and sell_date BETWEEN DATE_SUB(NOW(), INTERVAL %d MONTH) AND NOW();", gender, K
		);


		if (gender == 'M') cout << "Sales list of male customers" << endl;
		else cout << "Sales list of female customers" << endl;
		cout << "vehicle_ID   |  dealer_ID    |  sell_date     | customer_ID      | gender   " << endl;
		cout << "-----------------------------------------------------------------------------" << endl;
		execute_query(query);
		cout << "-----------------------------------------------------------------------------\n" << endl;

		return;

	}
	else if (N == 2) {

		cout << "**Break out the data out by income range**" << endl;
		cout << "Input range of income [EX: 5000 10000]" << endl;
		int min, max;
		cin >> min >> max;
		if (min > max) {
			cout << "Invalid range" << endl;
			return;
		}
		sprintf(query,
			"select vehicle_ID, dealer_dealer_ID, sell_date, customer_customer_ID, annual_income from `project`.`sales` join "
			"`project`.`customer` where customer_customer_ID = customer_ID and annual_income between %d and %d "
			"and sell_date BETWEEN DATE_SUB(NOW(), INTERVAL %d MONTH) AND NOW();", min, max, K
		);
		cout << "Sales list of customers with annual income range " << min << " - " << max << endl;
		cout << "vehicle_ID   |  dealer_ID    |  sell_date     | customer_ID   | annual_income" << endl;
		cout << "-----------------------------------------------------------------------------" << endl;
		execute_query(query);
		cout << "-----------------------------------------------------------------------------\n" << endl;

		return;
	}


}

void type3(void) {
	//Find that transmissions made by supplier(company name) between two given dates are defective
	char query[2000];
	char company_name[30];
	char date_from[30], date_to[30];
	int N = 0;
	cout << "**Find the transmissions made by supplier between two given dates are defective**" << endl;
	cout << "Which Company? : ";
	cin >> company_name;

	cout << "From when? [EX:2010-01-12]   :";
	cin >> date_from;
	cout << "To when? [EX:2020-07-31]   :";
	cin >> date_to;
	sprintf(query,
		"with my_model(my_ID) as( "
			"select parts_parts_ID from `project`.`manufactured` where parts_parts_ID in( "
				"select parts_parts_ID from `project`.`supplied` where model_model_ID in( "
					"select model_ID from `project`.`model` where brand_brand_ID in( "
						"select brand_ID from `project`.`brand` where company_company_name in( "
							 "select company_name from `project`.`company` where company_name = '%s')))) "
			"and manufactured_date between '%s' and '%s'), "
		"company_model(company_model_ID) as( "
			"select model_model_ID from my_model join `project`.`supplied` on my_ID = parts_parts_ID) "
		"select distinct transmission from company_model join `project`.`options` on model_model_ID = company_model_ID "
		,company_name, date_from, date_to
	);
	cout << "Transmissions made by" << company_name << " between " << date_from << " - " << date_to << endl;
	cout << "transmissions" << endl;
	cout << "-------------" << endl;
	execute_query(query);
	cout << "-------------\n" << endl;
	
	//subquery 1: Find the VIN of each car containing such a transmission and the customer to which it was sold
	//subquery 2: Find the dealer who sold the VIN and transmission for each vehicle containing these transmssion


	cout << "------------------------ Subtypes in TYPE 1 -------------------" << endl;
	cout << "                        1. TYPE 3-1" << endl;
	cout << "                        2. TYPE 3-1-1" << endl;
	cout << "Input query subtype: ";
	int subquery;
	cin >> subquery;
	cin.clear();

	if (subquery == 1) {
		cout << "**Find the VIN of each car containing such a transmission and the customer to which it was sold.**" << endl;
		sprintf(query,
			"with my_model(my_ID) as( "
			"	select parts_parts_ID from `project`.`manufactured` where parts_parts_ID in( "
			"		select parts_parts_ID from `project`.`supplied` where model_model_ID in( "
			"			select model_ID from `project`.`model` where brand_brand_ID in( "
			"				select brand_ID from `project`.`brand` where company_company_name in( "
			"					select company_name from `project`.`company` where company_name = '%s')))) "
			"	and manufactured_date between '%s' and '%s'), "
			"company_model(company_model_ID) as( "
			"	select model_model_ID from my_model join `project`.`supplied` on my_ID = parts_parts_ID), "
			"bad_option(opt) as( "
			"	select distinct option_ID from company_model join `project`.`options` on model_model_ID = company_model_ID) "
			"select vehicle_ID, customer_customer_ID from `project`.`sales` where vehicle_ID in( "
			"	select vehicle_ID from `project`.`asset` join bad_option on options_option_ID = opt);"
			,company_name, date_from, date_to
		);
		cout << "vehicle_ID   |  customer_ID" << endl;
		cout << "-------------------------------" << endl;
		execute_query(query);
		cout << "-------------------------------\n" << endl;
	}
	else {
		cout << "**Find the dealer who sold the VIN and transmission for each vehicle containing these transmssion.**" << endl;
		sprintf(query,
			"with my_model(my_ID) as( select parts_parts_ID from `project`.`manufactured` where parts_parts_ID in( "
			"select parts_parts_ID from `project`.`supplied` where model_model_ID in( select model_ID from `project`.`model` where brand_brand_ID in( "
			"select brand_ID from `project`.`brand` where company_company_name in( select company_name from `project`.`company` where company_name = '%s')))) "
			"and manufactured_date between '%s' and '%s'), "
			"company_model(company_model_ID) as( select model_model_ID from my_model join `project`.`supplied` on my_ID = parts_parts_ID), "
			"bad_option(opt) as( select distinct option_ID from company_model join `project`.`options` on model_model_ID = company_model_ID), "
			"VID_deal_trans_opt(vehicle_ID, dealer_ID, transmission, option_ID) as( "
			"select vehicle_ID, dealer_dealer_ID, transmission, option_ID from `project`.`options` join `project`.`asset` on options_option_ID = option_ID), "
			"bad_VID(vehicle_ID, transmission, dealer_ID) as( "
			"select vehicle_ID, transmission, dealer_ID from VID_deal_trans_opt join bad_option on option_ID = opt) "
			"select dealer_name, transmission from bad_VID as adeal join `project`.`dealer` as deal on adeal.dealer_ID = deal.dealer_ID;"
			,company_name, date_from, date_to
		);
		cout << "dealer_name   |    transmission" << endl;
		cout << "-----------------------------" << endl;
		execute_query(query);
		cout << "-----------------------------\n" << endl;
	}


}

void type4(void) {
	char query[1000];
	cout << "**Find the top K brands by dollar-amount sold by the year**" << endl;
	int year,K;
	cout << "Which year? : ";
	cin >> year;
	cout << "Which K? : ";
	cin >> K;
	sprintf(query,
		"with sales_ID(VID, sell_date) as( "
		"	select sales.vehicle_ID, sales.sell_date from `project`.`sales` as sales join `project`.`asset` as asset "
		"on sales.vehicle_ID = asset.vehicle_ID where YEAR(sales.sell_date) = '%d'), "
		"asset_option(MID, vehicle_ID) as( select model_model_ID, vehicle_ID from `project`.`asset` join `project`.`options` on option_ID = options_option_ID), "
		"model_brand(model_ID, brand_name, price) as( select model_ID, brand_name, model_price from `project`.`model` join `project`.`brand` on brand_ID = brand_brand_ID), "
		"model_brand_option(vehicle_ID, brand, price) as( select vehicle_ID, brand_name, price from asset_option join model_brand on MID = model_ID) "
		"select sum(price) as total_sales, brand, sell_date from model_brand_option join sales_ID on VID = vehicle_ID "
		"group by brand order by total_sales DESC limit %d "
		, year, K
	);
	//185950  Maybach 2016-04-18
	cout << "total_sales($)  |  brand  | sell_date" << endl;
	cout << "-------------------------------------" << endl;
	execute_query(query);
	cout << "-------------------------------------\n" << endl;
}

void type5(void) {
	char query[1000];
	cout << "**Find the top K brands by unit-sales sold by the year**" << endl;
	int year, K;
	cout << "Which year? : ";
	cin >> year;
	cout << "Which K? : ";
	cin >> K;
	sprintf(query,
		"with sales_ID(VID, sell_date) as( select sales.vehicle_ID, sales.sell_date from `project`.`sales` as sales join `project`.`asset` as asset "
		"on sales.vehicle_ID = asset.vehicle_ID where YEAR(sales.sell_date) = '%d'), "
		"asset_option(MID, vehicle_ID) as( select model_model_ID, vehicle_ID from `project`.`asset` join `project`.`options` on option_ID = options_option_ID), "
		"model_brand(model_ID, brand_name, price) as( select model_ID, brand_name, model_price from `project`.`model` join `project`.`brand` on brand_ID = brand_brand_ID), "
		"model_brand_option(vehicle_ID, brand, price) as( select vehicle_ID, brand_name, price from asset_option join model_brand on MID = model_ID) "
		"select count(vehicle_ID) as sell_count, brand, sell_date from model_brand_option join sales_ID on VID = vehicle_ID "
		"group by brand order by sell_count DESC limit %d "
		, year, K
	);
	cout << "unit_sales  |  brand  | sell_date" << endl;
	cout << "-------------------------------------" << endl;
	execute_query(query);
	cout << "-------------------------------------\n" << endl;
}

void type6(void) {
	char query[1000];
	cout << "**In what months do convertibles sell best?**" << endl;
	sprintf(query,
		"with sales_ID(VID, sell_date) as( select sales.vehicle_ID, sales.sell_date from `project`.`sales` as sales join `project`.`asset` as asset "
		"on sales.vehicle_ID = asset.vehicle_ID), "
		"asset_option(MID, vehicle_ID) as( select model_model_ID, vehicle_ID from `project`.`asset` join `project`.`options` "
		"on option_ID = options_option_ID), "
		"model_brand(model_ID, brand_name, price) as( select model_ID, brand_name, model_price from `project`.`model` "
		"join `project`.`brand` on brand_ID = brand_brand_ID), "
		"model_brand_option(vehicle_ID, brand, price) as( select vehicle_ID, brand_name, price from asset_option join model_brand on MID = model_ID) "
		"select count(vehicle_ID) as sell_count, MONTH(sell_date) from model_brand_option join sales_ID on VID = vehicle_ID "
		"group by MONTH(sell_date) order by sell_count desc limit 12 "
	);
	cout << "units|  month" << endl;
	cout << "---------------" << endl;
	execute_query(query);
	cout << "---------------\n" << endl;

}

void type7(void) {
	char query[1000];
	cout << "**Find the dealers who keep a vehicle in inventory for the longest average time**" << endl;
	sprintf(query,
		"with stock_dealer(vehicle_ID, stock_date, dealer_ID, dealer_name) as( "
		"	select vehicle_ID, stock_date, dealer_ID, dealer_name from `project`.`asset` join `project`.`dealer` "
		"where dealer_dealer_ID = dealer_ID), "
		"date_diff(days, dealer_name) as( select datediff(sales.sell_date, sd.stock_date) as days, sd.dealer_name "
		"from stock_dealer as sd join `project`.`sales` as sales where sd.vehicle_ID = sales.vehicle_ID), "
		"dealer_avg(avg_days, dealer_name) as(select round(avg(days)) as avg_days, dealer_name from date_diff "
		"group by dealer_name order by avg_days desc) "
		"select avg_days, dealer_name from dealer_avg where avg_days in(select MAX(avg_days) from dealer_avg) "
	);
	cout << "days|  dealer_name" << endl;
	cout << "------------------" << endl;
	execute_query(query);
	cout << "------------------\n" << endl;
}

int main(void) {

	if (mysql_init(&conn) == NULL)
		printf("mysql_init() error!");
	else {
		printf("mysql_init() success.\n");
	}
	connection = mysql_real_connect(&conn, host, user, pw, db, 3306, (const char*)NULL, 0);
	if (connection == NULL)
	{
		printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
		return 1;
	}
	else {
		printf("Connection Succeed\n");
		char buffer[2000];
		FILE* fp = fopen("20161634.txt", "r");
		if (!fp) {
			cout << "No file! Exit." << endl;
			exit(0);
		}
		if (mysql_select_db(&conn, db))
		{
			printf("%d ERROR : %s\n", mysql_errno(&conn), mysql_error(&conn));
			return 1;
		}
		
		printf("Initiating Tables....\n");
		for (int i = 1; i <= 21; i++) {
			fgets(buffer, sizeof(buffer), fp);
			mysql_query(&conn, buffer);
		}
		printf("Tables OK\n");
		printf("Inserting Tuples....\n");
		for (int i = 22; i <= 688; i++) {
			fgets(buffer, sizeof(buffer), fp);
			mysql_query(&conn, buffer);
		}
		printf("Insertion OK");
		

		int A = -1;
		bool Loop = true;
		while (Loop) {

			cout << "---------- SELECT QUERY TYPES ----------" << endl;
			cout << "          1. TYPE 1" << endl;
			cout << "          2. TYPE 2" << endl;
			cout << "          3. TYPE 3" << endl;
			cout << "          4. TYPE 4" << endl;
			cout << "          5. TYPE 5" << endl;
			cout << "          6. TYPE 6" << endl;
			cout << "          7. TYPE 7" << endl;
			cout << "          0. QUIT" << endl;
			cout << "Input query TYPE: ";
			cin >> A;
			cout << "INPUT: " << A << endl;

			if (cin.fail()) {
				cout << "Invalid input" << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				continue;
			}
			switch (A) {
			case 0: Loop = false; break;
			case 1: type1(); break;
			case 2: type2(); break;
			case 3: type3(); break;
			case 4: type4(); break;
			case 5: type5(); break;
			case 6: type6(); break;
			case 7: type7(); break;
			default:
				cout << "Invalid input" << endl;
				break;
			}
		}


		printf("Deleting tuples....\n");
		for (int i = 689; i <= 1343; i++) {
			fgets(buffer, sizeof(buffer), fp);
			mysql_query(&conn, buffer);
		}
		printf("Deletion OK\n");
		printf("Dropping tables....\n");
		for (int i = 1344; i <= 1358; i++) {
			fgets(buffer, sizeof(buffer), fp);
			mysql_query(&conn, buffer);
		}
		printf("Drop OK\n");


		printf("Exit Program");

	}
	
	mysql_close(&conn);


	return 0;
}