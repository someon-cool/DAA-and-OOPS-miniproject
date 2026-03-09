#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

/* -------------------- PRODUCT CLASS -------------------- */

class Product {
private:
    int productID;
    string name;
    double price;
    int quantity;

public:
    Product(int id, string n, double p, int q) {
        productID = id;
        name = n;
        price = p;
        quantity = q;
    }

    int getID() {
        return productID;
    }

    string getName() {
        return name;
    }

    double getPrice() {
        return price;
    }

    int getQuantity() {
        return quantity;
    }

    void reduceQuantity(int q) {
        quantity -= q;
    }

    void display() {
        cout << "ID: " << productID
             << " | Name: " << name
             << " | Price: " << price
             << " | Quantity: " << quantity << endl;
    }
};

/* -------------------- ALGORITHM DECLARATIONS -------------------- */

extern void quickSort(vector<Product>& products, int low, int high);
extern int binarySearch(vector<Product>& products, int targetID);

/* -------------------- USER BASE CLASS -------------------- */

class User {
protected:
    int userID;
    string name;

public:
    User(int id, string n) {
        userID = id;
        name = n;
    }
};

/* -------------------- CART CLASS -------------------- */

class Cart {
private:
    vector<Product> items;

public:
    void addProduct(Product p) {
        items.push_back(p);
        cout << "Product added to cart\n";
    }

    void viewCart() {

        if(items.empty()) {
            cout << "Cart is empty\n";
            return;
        }

        cout << "\nCart Items\n";

        for(Product &p : items)
            p.display();
    }

    double calculateTotal() {

        double total = 0;

        for(Product &p : items)
            total += p.getPrice();

        return total;
    }

    vector<Product> getItems() {
        return items;
    }
};

/* -------------------- ORDER CLASS -------------------- */

class Order {
private:
    int orderID;
    vector<Product> items;
    double totalAmount;
    string status;

public:
    Order(int id, vector<Product> cartItems, double total) {

        orderID = id;
        items = cartItems;
        totalAmount = total;
        status = "Placed";
    }

    void displayOrder() {

        cout << "\nOrder ID: " << orderID << endl;

        for(Product &p : items)
            p.display();

        cout << "Total Amount: " << totalAmount << endl;
        cout << "Status: " << status << endl;
    }
};

/* -------------------- GLOBAL STORAGE -------------------- */

vector<Product> products;
queue<Order> orderQueue;

/* -------------------- ADMIN CLASS -------------------- */

class Admin : public User {

public:

    Admin(int id, string name) : User(id,name) {}

    void addProduct() {

        int id, quantity;
        string name;
        double price;

        cout << "\nEnter Product ID: ";
        cin >> id;

        cout << "Enter Product Name: ";
        cin >> name;

        cout << "Enter Price: ";
        cin >> price;

        cout << "Enter Quantity: ";
        cin >> quantity;

        Product p(id,name,price,quantity);

        products.push_back(p);

        cout << "Product added successfully\n";
    }

    void viewProducts() {

        if(products.empty()) {
            cout << "No products available\n";
            return;
        }

        cout << "\nProduct List\n";

        for(Product &p : products)
            p.display();
    }

    void sortProducts() {

        if(products.empty()) {
            cout << "No products available\n";
            return;
        }

        quickSort(products,0,products.size()-1);

        cout << "Products sorted by price\n";
    }
};

/* -------------------- CUSTOMER CLASS -------------------- */

class Customer : public User {

private:
    Cart cart;

public:

    Customer(int id, string name) : User(id,name) {}

    void viewProducts() {

        if(products.empty()) {
            cout << "No products available\n";
            return;
        }

        cout << "\nProducts\n";

        for(Product &p : products)
            p.display();
    }

    void searchProduct() {

        int id;

        cout << "Enter Product ID: ";
        cin >> id;

        int index = binarySearch(products,id);

        if(index == -1)
            cout << "Product not found\n";

        else
            products[index].display();
    }

    void addToCart() {

        int id;

        cout << "Enter Product ID: ";
        cin >> id;

        for(Product &p : products) {

            if(p.getID() == id) {

                cart.addProduct(p);
                return;
            }
        }

        cout << "Product not found\n";
    }

    void viewCart() {
        cart.viewCart();
    }

    void placeOrder() {

        vector<Product> items = cart.getItems();

        if(items.empty()) {
            cout << "Cart empty\n";
            return;
        }

        double total = cart.calculateTotal();

        int orderID = orderQueue.size() + 1;

        Order newOrder(orderID,items,total);

        orderQueue.push(newOrder);

        cout << "Order placed successfully\n";
    }
};
