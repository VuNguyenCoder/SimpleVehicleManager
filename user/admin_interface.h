#ifndef __ADMIN_INTERFACE_H__
#define __ADMIN_INTERFACE_H__

#include "user_interface.h"
#include "../vehicle/vehicle_manager.h"
#include "../common.h"

class AdminInterface {
public:

    void show_admin_menu(const std::string& user_id) {
        std::cout << TITLE << "Tai khoan: " << user_id << "\n"
            "Mode: Quan tri vien (Admin)\n";
        std::cout << "Chon chuc nang:\n"
                    << "[1] Xem danh sach user\n" 
                    << "[2] Tao user\n"
                    << "[3] Xoa user\n"
                    << "----\n"
                    << "[4] Xem danh sach phuong tien\n"
                    << "[5] Phe duyet phuong tien\n"
                    << "[6] Them phuong tien\n"
                    << "[7] Xoa phuong tien\n"
                    << "----\n"
                    << "[0] Dang xuat\n";
        
        int command;
        
        std::cout << "> Chon: ";
        std::cin >> command;
        switch(command) {
            case 1:
                user_interface.show_user_list();
                break;
            case 2:
                user_interface.show_create_user();
                break;
            case 3: 
                user_interface.show_remove_user();
                break;
            case 4: 
                show_vehicle_list();
                break;
            case 5:
                show_approve_vehicle(); 
                break;
            case 6: 
                show_add_vehicle();
                break;
            case 7: 
                show_remove_vehicle();
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

    void show_vehicle_list() {
        for(auto info : VehicleManager::get_instance()->get_vehicle_info()) {
            if(info.is_approved)
                std::cout << "\t* " << info.brand << " - " << info.license << "\n";
        }
    }

    void show_approve_vehicle() {
        std::vector<VehicleInfo> vehicle_info = VehicleManager::get_instance()->get_vehicle_info();
        int index = 1;
        for(auto info : vehicle_info) {
            if(!info.is_approved) {
                std::cout << "[" << index++ << "] " 
                    << info.brand << " - " << info.license << "\n";
            }
        }

        int selection = 1;
        std::cout << "> Chon vehicle: ";
        std::cin >> selection;
        if(selection < 1 || selection > index) {
            std::cout << "Invalid\n";
        }

        vehicle_info[selection].is_approved = true;
        VehicleManager::get_instance()->store_vehicle(vehicle_info);
    }

    void show_add_vehicle() {

    }

    void show_remove_vehicle() {

    }

private:
    UserInterface user_interface;
};

#endif