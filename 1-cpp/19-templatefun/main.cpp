
template<typename T>
T max(T a, T b) {
    if(a >= b) return a;
    else return b;
}

int main() {
    int i1, i2;
    //Let compiler deduce template type
    int i3 = max(i1, i2);
    //Explicitly specify template type
    int i4 = max<int>(i1, i2);
 
    float f1, f2;
    float f3 = max(f1, f2);
}
