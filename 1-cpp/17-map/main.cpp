#include <iostream>
#include <map>

using namespace std;

int main()
{
    map<string,int> m;
    //Add elements (two ways)
    m["hello"] = 1;
    m.emplace("world",2);
    //Iteration (both key and value)
    for(auto& e : m)
        cout<<e.first<<e.second<<"\n";
    //Random access (if sure exists)
    int x = m["world"];
    //Random access (if unsure)
    auto it = m.find("missing");
    if(it == m.end())
        cout << "Not found\n";
    else cout << it->second << "\n";
    //Remove by key
    m.erase("hello");
}
