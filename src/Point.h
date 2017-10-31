#ifndef POINT_H
#define POINT_H

class Point{
private:
	
public:
	int x; //Alpha characters
	int y; //Numeric characters
    
	Point();
	Point(int X, int Y);
	bool Equals(Point tip);
	bool onBoard();
};

#endif