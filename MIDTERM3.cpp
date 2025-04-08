#include <iostream>
#include <stack>
using namespace std;

int main() {
    stack<long int> A;
    A.push(10245);
    A.push(20255);
    A.push(30356);
    A.push(12347);
    A.push(77878);
    A.push(10255);
    A.push(12032);
    A.push(11234);

    cout << "Stack of A: " << A.size() << endl;
    cout << "Contents of A: " << endl;
    while (!A.empty()) {
        cout << A.top() << endl;
       A.pop();
    }
    cout << endl;
    return 0;
}
