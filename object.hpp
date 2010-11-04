#ifndef OBJECT_HPP
#define OBJECT_HPP


class Object
{

public:
   Object();
   void setPosition(int x, int y);
   const int* getPosition();
   ~Object();

private:
   int position[2];
};

#endif // OBJECT_HPP
