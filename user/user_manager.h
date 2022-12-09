
#ifndef __USER_MANAGER_H__
#define __USER_MANAGER_H__

#include "../db/database.h"
#include <unordered_map>

#define USER_DB "db/users.txt"

typedef std::string UserID;

enum UserRole { ADMIN = 0, USER = 1 };

struct UserInfo {
    std::string password;
    UserRole role;
};

class UserManager {
public:
    static UserManager* get_instance() {
        if (manager == NULL) {
            manager = new UserManager();
        }
        return manager;
    }
    
	bool load_user_data() {
		user_data_.clear();

		auto str_info = db_.read_db(USER_DB);
		for(auto str_info : str_info) {
			user_data_[str_info[0]].password = str_info[1];
			user_data_[str_info[0]].role = UserRole(std::stoi(str_info[2]));
		}

        return true;
	}

	std::vector<std::string> get_user_list() {
		std::vector<std::string> users;
		for(auto& user : user_data_) {
			users.push_back(user.first);
		}
		return users;
	}
    
    bool login(const std::string& user_id, const std::string& password, UserRole& role) {     
		load_user_data();
		for(auto& item : user_data_) {
			//std::cout << item.first << "\n";
		}
		if(user_id_existed(user_id) && password == user_data_[user_id].password) {
			role = UserRole(user_data_[user_id].role);
			return true;
		}
        return false;
    }

	bool user_id_existed(const UserID& user_id) {
		return !(user_data_.find(user_id) == user_data_.end());
	}

	bool create_user(const std::string& user_id, const std::string& password) {
		if(user_id_existed(user_id)) return false; 
		std::ofstream data(USER_DB, std::ios::app);
		data << "\n" << user_id << ";" << password << ";" << UserRole::USER;
		return true;
	}

	bool remove_user(const std::string& user_id) {
		if(!user_id_existed(user_id)) return false; 
		
		user_data_.erase(user_id);

		std::string str_data;
		for(auto& user : user_data_) {
			UserID user_id = user.first;
			const std::string password = user.second.password;
			const std::string role = std::to_string(user.second.role);
			str_data += user_id + ";" + password + ";" + role + "\n"; 
		}
		if(str_data.length() > 1) {
			str_data.replace(str_data.length()-1, 1, "");
		}

		std::ofstream data(USER_DB);
		data << str_data;
		return true;
	}
private:
	std::unordered_map<UserID, UserInfo> user_data_;
    Database db_;

    static UserManager* manager;

    UserManager()
    {

    }
};

UserManager* UserManager::manager = NULL;



#endif