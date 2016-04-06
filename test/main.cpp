#include <iostream>
#include "net.h"

using std::cin;

using namespace jaffe;

int main() {
    JNet<int> net;
    net.Init("/home/bluuuuer/forward-caffe/deploy.prototxt");
    //cout << "Hello, World!" << endl;
    cin.get();
    return 0;
}