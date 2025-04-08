#include <iostream>
#include <string>
using namespace std;

class SariSariStoreProduct {
public:
    string id;
    string name;
    double price;
    int shelfLife;
    int pieces;

    void setData(string i, string n, double p, int sl, int pcs) {
        id = i;
        name = n;
        price = p;
        shelfLife = sl;
        pieces = pcs;
    }

    void displayInfo() {
        cout << "Product ID: " << id << endl;
        cout << "Product Name: " << name << endl;
        cout << "Price:  " << price << endl;
        cout << "Shelf Life: " << shelfLife << " days" << endl;
        cout << "Pieces: " << pieces << endl;
    }
};

void selectionSort(SariSariStoreProduct arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j].shelfLife < arr[minIndex].shelfLife) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            SariSariStoreProduct temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
}

int main() 
{
    SariSariStoreProduct Product[8];
    Product[0].setData("10245", "mangoes", 20, 60, 100);
    Product[1].setData("20255", "apple", 15, 38, 50);
    Product[2].setData("30356", "C2_red", 30, 360, 200);
    Product[3].setData("12347", "bukopie", 40, 120, 150);
    Product[4].setData("77878", "magic_sarap", 10, 520, 1000);
    Product[5].setData("10255", "C2_green", 25, 360, 300);
    Product[6].setData("12032", "boy_bawang", 18, 400, 140);
    Product[7].setData("11234", "banana", 7, 24, 30);

    selectionSort(Product, 8);

    cout << "Products sorted by shelf life in ascending order." << endl;
    for (int i = 0; i < 8; i++) {
        cout << Product[i].name << endl;
    }
    
    return 0;
}
