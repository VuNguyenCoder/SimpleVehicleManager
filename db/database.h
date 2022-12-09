#ifndef __DATABASE_H__
#define __DATABASE_H__

#include <string>
#include <unordered_map>
#include <vector>
#include <queue>
#include <fstream>

#define VEHICLE_DB "db/vehicles.txt"

class Database {
public:
	std::vector<std::vector<std::string>> read_db(const std::string& db_url) {
		std::vector<std::vector<std::string>> str_db;
		std::ifstream data(db_url);
		std::string str_info;
		std::string str_info_delimiter = ";";

		while (std::getline(data, str_info)) {
			std::vector<std::string> info;
			int pos_of_delimiter = 0;
			while ((pos_of_delimiter = str_info.find(str_info_delimiter)) != std::string::npos) {
				info.push_back(str_info.substr(0, pos_of_delimiter));
				str_info = str_info.substr(pos_of_delimiter + 1);
			}
			info.push_back(str_info.substr(pos_of_delimiter + 1));
			str_db.push_back(info);
		}
		return str_db;
	}

private:

};

#endif