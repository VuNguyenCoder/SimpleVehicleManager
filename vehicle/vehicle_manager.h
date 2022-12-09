#ifndef __VEHICLE_MANAGER_H__
#define __VEHICLE_MANAGER_H__ 

#include "../db/database.h"

struct VehicleInfo {
    std::string brand;
    std::string license;
    bool is_approved = false;
};

class VehicleManager {
public:
    static VehicleManager* get_instance() {
        if (manager == NULL) {
            manager = new VehicleManager();
        }
        return manager;
    }

	std::vector<VehicleInfo> get_vehicle_info(const std::string& user_id = "") {
		std::vector<VehicleInfo> vehicle_info;
		auto str_info = db_.read_db(VEHICLE_DB);
		for(auto str_info : str_info) {
			if(str_info[0] == user_id || user_id == "") {
				VehicleInfo info;
				info.brand = str_info[1];
				info.license = str_info[2];
				info.is_approved = std::stoi(str_info[3]);
				vehicle_info.push_back(info);
			}
		}
		return vehicle_info;
	}

	bool submit_vehicle_registration(const std::string& user_id, 
						const std::string& brand, 
						const std::string& license) 
	{
		for(auto& info : get_vehicle_info(user_id))
			if(info.license == license) return false;
		
		std::ofstream data(VEHICLE_DB, std::ios::app);
		data << "\n" << user_id << ";" << brand << ";" << license << ";0"; 
		return true;
	}

	bool store_vehicle(std::vector<VehicleInfo>& vehicle_info) {
		std::ofstream data(VEHICLE_DB);
		for(int i = 0; i < vehicle_info.size(); i++) {
			const auto& vehicle = vehicle_info[i];
			data << vehicle.brand << ";" 
				<< vehicle.license << ";"
				<< (vehicle.is_approved ? "1" : "0")
				<< (i != vehicle_info.size()-1 ? "\n" : "");
		}
		return true;
	}

private:
    Database db_;

    static VehicleManager* manager;

    VehicleManager()
    {

    }
};

VehicleManager* VehicleManager::manager = NULL;

#endif