#if !defined Point
  #include ./Point.h
  #define Point
#end if

Point() {
  x = 0;
  y = 0;
}

Point(int X, int Y) {
  x = X;
  y = Y;
}

