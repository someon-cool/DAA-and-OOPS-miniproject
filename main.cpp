#include <iostream>

using namespace std;

#include "oops.cpp"
#include "daa.cpp"

int main() {

    Admin admin(1,"Admin");
    Customer customer(101,"Customer");

    int choice;

    while(true) {

        cout << "\n===== QUICKMART SYSTEM =====\n";
        cout << "1 Admin Panel\n";
        cout << "2 Customer Panel\n";
        cout << "3 Exit\n";

        cin >> choice;

        if(choice == 1) {

            int c;

            cout << "\n1 Add Product\n";
            cout << "2 View Products\n";
            cout << "3 Sort Products\n";

            cin >> c;

            if(c == 1) admin.addProduct();
            else if(c == 2) admin.viewProducts();
            else if(c == 3) admin.sortProducts();
        }

        else if(choice == 2) {

            int c;

            cout << "\n1 View Products\n";
            cout << "2 Search Product\n";
            cout << "3 Add To Cart\n";
            cout << "4 View Cart\n";
            cout << "5 Place Order\n";

            cin >> c;

            if(c == 1) customer.viewProducts();
            else if(c == 2) customer.searchProduct();
            else if(c == 3) customer.addToCart();
            else if(c == 4) customer.viewCart();
            else if(c == 5) customer.placeOrder();
        }

        else break;
    }

    return 0;
}
