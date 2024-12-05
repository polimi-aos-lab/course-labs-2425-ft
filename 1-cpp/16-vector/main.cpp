#include <iostream>
#include <vector>

using namespace std;

int main()
{
    //Sequence initialization
    vector<int> v={1,2,3};
    //Add element to back
    v.push_back(4);
    //Iteration
    for(auto& i : v) cout<<i<<"\n";
    //Random access
    int x = v.at(2);
    //Remove element from back
    v.pop_back();
}
