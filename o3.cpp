#include <iostream>
#include <stack>
using namespace std;

int main() {
    stack<long int> ID;
    ID.push(20221130923);
    ID.push(20221113019);
    ID.push(20241120910);
    ID.push(20241100947);
    ID.push(20241100023475);

    cout << "Stack of ID: " << endl;
    while (!ID.empty()) {
        cout << ID.top() << endl;
        ID.pop();
    }
    cout << endl;
    return 0;
}
    
