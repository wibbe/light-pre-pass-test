
#ifndef MATH_HPP
#define MATH_HPP

namespace math
{
   
   class Vector3
   {
      public:
         Vector3()
           : x(0.0f),
             y(0.0f),
             z(0.0f)
         { }

         Vector3(float _x, float _y, float _z)
           : x(_x),
             y(_y),
             z(_z)
         { }

         Vector3(Vector3 const& v)
           : x(v.x),
             y(v.y),
             z(v.z)
         { }

         float x, y, z;
   };

   inline float dot(Vector3 const& a, Vector3 const& b)
   {
     return a.x * b.x + a.y * b.y + a.z * b.z;
   }
   
}

#endif

