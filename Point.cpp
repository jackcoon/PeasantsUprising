#include "./Point.h"

Point::Point() {
  x = 0;
  y = 0;
}

Point::Point(int X, int Y) {
  x = X;
  y = Y;
}

bool Point::equals(Point tip) {
	if (x != tip.x)
		return false;
	return y == tip.y;
}

bool Point::onBoard() {//checks if a point is on the board
	return !(x < 0 || x > 7 || y < 0 || y > 7);
}


