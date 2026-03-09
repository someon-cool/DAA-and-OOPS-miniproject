#include <vector>
using namespace std;

class Product {
public:
    int getID();
    double getPrice();
};

/* ---------- QUICK SORT FOR PRODUCTS (BY PRICE) ---------- */

int partition(vector<Product>& products, int low, int high) {

    double pivot = products[high].getPrice();
    int i = low - 1;

    for(int j = low; j < high; j++) {

        if(products[j].getPrice() < pivot) {
            i++;

            Product temp = products[i];
            products[i] = products[j];
            products[j] = temp;
        }
    }

    Product temp = products[i+1];
    products[i+1] = products[high];
    products[high] = temp;

    return i + 1;
}

void quickSort(vector<Product>& products, int low, int high) {

    if(low < high) {

        int pi = partition(products, low, high);

        quickSort(products, low, pi - 1);
        quickSort(products, pi + 1, high);
    }
}

/* ---------- BINARY SEARCH (BY PRODUCT ID) ---------- */

int binarySearch(vector<Product>& products, int targetID) {

    int left = 0;
    int right = products.size() - 1;

    while(left <= right) {

        int mid = (left + right) / 2;

        if(products[mid].getID() == targetID)
            return mid;

        if(products[mid].getID() < targetID)
            left = mid + 1;

        else
            right = mid - 1;
    }

    return -1;
}