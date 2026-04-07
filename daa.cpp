#include <vector>
#include <algorithm>
using namespace std;


int partition(vector<Product>& products, int low, int high) {

    double pivot = products[high].getPrice();
    int i = low - 1;

    for(int j = low; j < high; j++) {

        if(products[j].getPrice() < pivot) {

            i++;
            swap(products[i], products[j]);
        }
    }
    swap(products[i+1], products[high]);

    return i + 1;
}

void quickSort(vector<Product>& products, int low, int high) {

    if(low < high) {

        int pi = partition(products, low, high);

        quickSort(products, low, pi - 1);
        quickSort(products, pi + 1, high);
    }
}
//binary search

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

//greedy algo


vector<Product> greedySelectProducts(vector<Product>& products, double budget) {
    vector<Product> sorted = products;

    sort(sorted.begin(), sorted.end(), [](Product& a, Product& b) {
        return a.getPrice() < b.getPrice();
    });

    vector<Product> selected;
    double spent = 0;

    for(Product& p : sorted) {

        if(spent + p.getPrice() <= budget) {

            selected.push_back(p);
            spent += p.getPrice();
        }
    }

    return selected;
}
