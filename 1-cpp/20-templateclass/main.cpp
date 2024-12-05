
template<typename T>
class Point {
public:
    Point(T x, T y) : x(x), y(y) {}

    //Other methods omitted for brevity
private:
    T x, y;
};

int main() {
    //With template classes must always
    //specify template type when making
    //objects
    Point<int> pi(1, 2);
    Point<float> pf(1.5, 3.3);
}
