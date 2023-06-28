#include <iostream>

class Coordinate {
public:
    int fi;
    int fe;
    int si;
    int se;
    int d;

    Coordinate(int f1, int f2, int s1, int s2, int d);

    friend std::ostream& operator<<(std::ostream& os, const Coordinate& coordinate);
    friend bool operator==(const Coordinate& c1, const Coordinate& c2);
};

bool compareCoordinates(const Coordinate& c1, const Coordinate& c2);
