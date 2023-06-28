#include "coord.h"

Coordinate::Coordinate(int f1, int f2, int s1, int s2, int d){
	if( f1 > f2 ){
		fi = f2;
		fe = f1;
		si = s2;
		se = s1;
		this->d = d;
	}else{
		fi = f1;
		fe = f2;
		si = s1;
		se = s2;
		this->d = d;
	}
}


bool compareCoordinates(const Coordinate& c1, const Coordinate& c2) {
    // Compare based on the x coordinate
    if (c1.fi != c2.fi)
        return c1.fi < c2.fi;

    // If x coordinates are equal, compare based on the y coordinate
    if (c1.fe != c2.fe)
        return c1.fe < c2.fe;

    // If y coordinates are equal, compare based on the z coordinate
    if (c1.si != c2.si)
        return c1.si < c2.si;

    // If z coordinates are equal, compare based on the w coordinate
    return c1.se < c2.se;
}

std::ostream& operator<<(std::ostream& os, const Coordinate& coordinate) {
    os <<  coordinate.fi << ", " << coordinate.fe << ", " << coordinate.si << ", " << coordinate.se;
    return os;
}

bool operator==(const Coordinate& c1, const Coordinate& c2) {
    return (c1.fi == c2.fi) && (c1.fe == c2.fe) && (c1.si == c2.si) && (c1.se == c2.se);
}

bool operator!=(const Coordinate& c1, const Coordinate& c2) {
    return  ! (c1 == c2);
}
