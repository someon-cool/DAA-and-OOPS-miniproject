#include <iostream>
using namespace std;

#include "quickmart_oops.cpp"
#include "quickmart_daa.cpp"

int main() {

    Admin admin(1,"Admin");
    Customer customer(101,"Customer");

    int choice;

    while(true) {

        cout << "\n===== QuickMart System =====\n";
        cout << "1 Admin Panel\n";
        cout << "2 Customer Panel\n";
        cout << "3 Exit\n";

        cin >> choice;

        if(choice == 1) {

            int adminChoice;

            cout << "\n--- Admin Menu ---\n";
            cout << "1 Add Product\n";
            cout << "2 View Products\n";
            cout << "3 Sort Products\n";

            cin >> adminChoice;

            if(adminChoice == 1)
                admin.addProduct();

            else if(adminChoice == 2)
                admin.viewProducts();

            else if(adminChoice == 3)
                admin.sortProducts();
        }

        else if(choice == 2) {

            int customerChoice;

            cout << "\n--- Customer Menu ---\n";
            cout << "1 View Products\n";
            cout << "2 Search Product\n";
            cout << "3 Add To Cart\n";
            cout << "4 View Cart\n";
            cout << "5 Place Order\n";

            cin >> customerChoice;

            if(customerChoice == 1)
                customer.viewProducts();

            else if(customerChoice == 2)
                customer.searchProduct();

            else if(customerChoice == 3)
                customer.addToCart();

            else if(customerChoice == 4)
                customer.viewCart();

            else if(customerChoice == 5)
                customer.placeOrder();
        }

        else
            break;
    }

    return 0;
}