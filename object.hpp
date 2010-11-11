#ifndef OBJECT_HPP
#define OBJECT_HPP


class Object
{

public:
   Object();
   void setPosition(int x, int y);
   const int* getPosition();
   double distance(Object* o);
   ~Object();

protected:
   int position[2];
};

#endif // OBJECT_HPP
