#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <string>

#include "common.h"
#include "user/admin_interface.h"
#include "user/user_interface.h"
#include "vehicle/vehicle_manager.h"

class App {
public:
    void run() {
        while(true) {
            show_home_menu(); 
        }    
    }
    
    void show_home_menu() {
        std::cout << TITLE 
                    << "Chon chuc nang:\n"
                    << "[1] Dang nhap\n" 
                    << "[2] Dang ky\n"
                    << "[0] Thoat\n";
        int command; 
        std::cout << "> Chon: ";
        std::cin >> command;
        switch(command) {
            case 1:
                show_login();
                break;
            case 2:
                show_register();
                break;
            default:
                return;
        }
        system("clear");
    }

    void show_login() {
        std::cin.ignore();
        std::string user, password;
        UserRole role;
        std::cout << "Tai khoan: ";
        std::getline(std::cin, user);
        std::cout << "Mat khau: ";
        std::getline(std::cin, password);

        if(UserManager::get_instance()->login(user, password, role)) {
            std::cout << "> Dang nhap thanh cong\n> Loading...\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            system("clear");
            switch(role) {
                case UserRole::USER :
                    switch_user_mode(user); break;
                case UserRole::ADMIN :
                    switch_admin_mode(user);break;
            }
        }
        else {
            std::cout << "Dang nhap that bai\n";
        }
    }
    
    void switch_user_mode(const std::string& user_id) {
        while(true) {
            user_interface.show_user_menu(user_id); 
        }
    }

    void switch_admin_mode(const std::string& user_id) {
        while(true) {
            admin_interface.show_admin_menu(user_id); 
        }
    }

    void show_register() {
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
    
private:
    UserInterface user_interface;
    AdminInterface admin_interface;
};

int main()
{
    App app;
    app.run();
    return 0;
}

