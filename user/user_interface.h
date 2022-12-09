#ifndef __USER_INTERFACE_H__
#define __USER_INTERFACE_H__

#include "user_manager.h"
#include "../vehicle/vehicle_manager.h"

class UserInterface {
    public:

    void show_user_menu(const std::string& user_id) {
        std::cout << TITLE << "Tai khoan: " << user_id << "\n"
            "Mode: Nguoi dung (User)\n"
            "Danh sach xe dang ky:\n";
        auto vehicle_info = VehicleManager::get_instance()->get_vehicle_info(user_id);
        for(auto& vehicle : vehicle_info) {
            std::cout << "\t* " << vehicle.brand << " | " 
                                << vehicle.license 
                                << (vehicle.is_approved ? "" : " (cho phe duyet)")
                                << "\n";
        }
        std::cout << "Chon chuc nang:\n"
                    << "[1] Dang ky xe\n" 
                    << "[2] Huy dang ky xe\n"
                    << "[0] Dang xuat\n";
        
        int command;
        
        std::cout << "> Chon: ";
        std::cin >> command;
        switch(command) {
            case 1:
                show_register_vehicle(user_id);
                break;
            case 2:
                show_unregister_vehicle(user_id);
                break;
            case 0: 
                return;
            default:
                std::cout << "Invalid\n";
        }
        getchar(); 
        std::cout << "\n=======================================\n"
                    "Press Enter to continue!";
        getchar();
        system("clear");
    }
    void show_user_list() {
        std::vector<std::string> users = UserManager::get_instance()->get_user_list();
        for(auto& user : users) {
            std::cout << "\t* " << user << "\n";
        }
    }

    void show_create_user() {
        std::cin.ignore();
        std::string user, password;
        std::cout << "Tai khoan: ";
        std::getline(std::cin, user);
        std::cout << "Mat khau: ";
        std::getline(std::cin, password);

        if(UserManager::get_instance()->create_user(user, password)) {
            std::cout << "Registered successfully \n";
        }
        else {
            std::cout << "Failed\n";
        }
        getchar();
    }

    void show_remove_user() { 
        std::cin.ignore();
        std::string user, confirm;
        std::cout << "Tai khoan: ";
        std::getline(std::cin, user);
        std::cout << "Dong y xoa tai khoan nay (y/n): ";
        std::getline(std::cin, confirm);
        if(confirm == "y") {
            if(UserManager::get_instance()->remove_user(user)) {
                std::cout << "Xoa thanh cong\n";
            }
            else {
                std::cout << "Xoa that bai\n";
            }
            
        }
    }
    void show_register_vehicle(const std::string& user_id) {
        std::cin.ignore();
        std::string brand, license;
        std::cout << "Ten xe: ";
        std::getline(std::cin, brand);
        std::cout << "BKS: ";
        std::getline(std::cin, license);

        if(VehicleManager::get_instance()->submit_vehicle_registration(user_id, brand, license)) {
            std::cout << "Da yeu cau dang ky xe\n";
        }
        else {
            std::cout << "Dang ky xe that bai\n";
        }
        
    }
    void show_unregister_vehicle(const std::string& user_id) {
        std::cin.ignore();
        std::string license;
        std::cout << "BKS: ";
        std::getline(std::cin, license);
        /*
        if(db.delete_vehicle(user, brand, license)) {
            std::cout << "Huy dang ky xe thanh cong\n";
        }
        else {
            std::cout << "Huy dang ky xe that bai\n";
        }*/
        
    }


};

#endif