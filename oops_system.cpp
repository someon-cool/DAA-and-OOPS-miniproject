#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <fstream>

using namespace std;

// PRODUCT CLASS 
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

// ALGORITHM DECLARATIONS 

extern void quickSort(vector<Product>& products, int low, int high);
extern int binarySearch(vector<Product>& products, int targetID);
extern vector<Product> greedySelectProducts(vector<Product>& products, double budget); // NEW

// PAYMENT CLASSES (Abstraction + Polymorphism) 

// Abstract base class — defines the contract for all payment methods
class Payment {
public:
    virtual void processPayment(double amount) = 0;  // Pure virtual
    virtual ~Payment() {}                             // Virtual destructor (good practice)
};

// Derived class 1 — UPI payment
class UPI : public Payment {
public:
    void processPayment(double amount) override {
        cout << "Processing UPI Payment of Rs." << amount << "...\n";
        cout << "Payment Successful via UPI\n";
    }
};

// Derived class 2 — Card payment
class Card : public Payment {
public:
    void processPayment(double amount) override {
        cout << "Processing Card Payment of Rs." << amount << "...\n";
        cout << "Payment Successful via Card\n";
    }
};

// Derived class 3 — Cash payment
class Cash : public Payment {
public:
    void processPayment(double amount) override {
        cout << "Processing Cash Payment of Rs." << amount << "...\n";
        cout << "Payment Successful via Cash\n";
    }
};

//USER BASE CLASS 

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

// Cart class

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

// ORDER CLASS 

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

vector<Product> products;
queue<Order> orderQueue;

void loadProducts() {

    ifstream fin("products.txt");  

    if(!fin.is_open()) {
        cout << "No saved products found. Starting fresh.\n";
        return;
    }

    int id, quantity;
    string name;
    double price;

    // Read one product per line until EOF
    while(fin >> id >> name >> price >> quantity) {

        Product p(id, name, price, quantity);
        products.push_back(p);
    }

    fin.close();  
    cout << "Products loaded from file. Total: " << products.size() << "\n";
}

void saveProducts() {

    ofstream fout("products.txt");  

    if(!fout.is_open()) {
        cout << "Error: Could not open file for saving.\n";
        return;
    }

    // Write each product as: id name price quantity
    for(Product &p : products) {
        fout << p.getID()       << " "
             << p.getName()     << " "
             << p.getPrice()    << " "
             << p.getQuantity() << "\n";
    }

    fout.close();  // Always close the file after writing

    cout << "Products saved to file.\n";
}

//admin class

class Admin : public User {

public:

    Admin(int id, string name) : User(id, name) {}

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

        Product p(id, name, price, quantity);

        products.push_back(p);

        saveProducts();  

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

        quickSort(products, 0, products.size() - 1);

        cout << "Products sorted by price\n";
    }
};
// Customer class

class Customer : public User {

private:
    Cart cart;

public:

    Customer(int id, string name) : User(id, name) {}

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

        int index = binarySearch(products, id);

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

        cout << "\nTotal Amount: " << total << "\n";

        // --- Runtime Polymorphism: choose payment method at runtime ---
        cout << "\nSelect Payment Method:\n";
        cout << "1 UPI\n";
        cout << "2 Card\n";
        cout << "3 Cash\n";

        int payChoice;
        cin >> payChoice;

        Payment* payment;                          // Base class pointer

        if(payChoice == 1)      payment = new UPI();   
        else if(payChoice == 2) payment = new Card();  
        else                    payment = new Cash();  

        payment->processPayment(total);           

        delete payment;                           

        int orderID = orderQueue.size() + 1;

        Order newOrder(orderID, items, total);

        orderQueue.push(newOrder);

        cout << "Order Placed Successfully\n";
    }

    // Greedy: suggest max products within a given budget
    void suggestProductsUnderBudget() {

        if(products.empty()) {
            cout << "No products available\n";
            return;
        }
        double budget;
        cout << "Enter Budget: ";
        cin >> budget;
        vector<Product> suggested = greedySelectProducts(products, budget);

        if(suggested.empty()) {
            cout << "No products fit within your budget\n";
            return;
        }

        cout << "\nSuggested Products:\n";

        double total = 0;

        for(Product &p : suggested) {
            cout << p.getName() << " - " << p.getPrice() << "\n";
            total += p.getPrice();
        }

        cout << "\nTotal: " << total << "\n";
        cout << "Products selected: " << suggested.size() << "\n";
    }
};
