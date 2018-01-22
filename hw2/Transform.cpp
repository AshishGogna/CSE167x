// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"
#include <iostream>

using namespace std;

// Helper rotation function.  Please implement this.  
mat3 Transform::rotate(const float degrees, const vec3& axis) 
{
  // YOUR CODE FOR HW2 HERE
  // Please implement this.  Likely the same as in HW 1.  

    //Rodrigues Rotation Formula !
      
    float rad = degrees * (pi / 180);
    vec3 normAxis = normalize(axis);
      
    float cosRad = cos(rad);
    float sinRad = sin(rad);
      
    mat3 m1(1, 0, 0,
            0, 1, 0,
            0, 0, 1);
    m1 = cosRad * m1;
      
    mat3 m2(normAxis.x * normAxis.x, normAxis.x * normAxis.y, normAxis.x * normAxis.z,
            normAxis.x * normAxis.y, normAxis.y * normAxis.y, normAxis.y * normAxis.z,
            normAxis.x * normAxis.z, normAxis.y * normAxis.z, normAxis.z * normAxis.z);
    m2 = (1-cosRad) * m2;
      
    mat3 m3(0,           -normAxis.z,  normAxis.y,
            normAxis.z,   0,          -normAxis.x,
            -normAxis.y,  normAxis.x,  0);
    m3 = sinRad * m3;
      
    // You will change this return call
    return transpose(m1 + m2 + m3);
    //return m1 + m2 + m3;
}

void Transform::left(float degrees, vec3& eye, vec3& up) 
{
  // YOUR CODE FOR HW2 HERE
  // Likely the same as in HW 1.  

    mat3 rotationMatrix = rotate(degrees, up);
    eye = rotationMatrix * eye;
    up = rotationMatrix * up;
}

void Transform::up(float degrees, vec3& eye, vec3& up) 
{
  // YOUR CODE FOR HW2 HERE 
  // Likely the same as in HW 1.  

    vec3 axis = cross(up, eye);

    mat3 rotationMatrix = rotate(-degrees, axis);
    eye = rotationMatrix * eye;
    up = rotationMatrix * up;
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up) 
{
  // YOUR CODE FOR HW2 HERE
  // Likely the same as in HW 1.  

    //The View Matrix!
    
    vec3 w = normalize(eye);
    vec3 u = normalize(cross(up, eye));
    vec3 v = normalize(cross(w, u));
    
    mat4 m1(u.x, u.y, u.z, dot(u, -eye),
            v.x, v.y, v.z, dot(v, -eye),
            w.x, w.y, w.z, dot(w, -eye),
            0,   0,   0,   1);
    
	// You will change this return call
	return transpose(m1);
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
  // YOUR CODE FOR HW2 HERE
  // New, to implement the perspective transform as well.  

    mat4 ret(0);

    float scl = 1 / tan(fovy * 0.5 * M_PI / 180);
    float zRange = zFar - zNear;
    
    ret[0][0] = scl/aspect;
    ret[1][1] = scl;
    ret[2][2] = -zFar / zRange;
    ret[3][2] = -zFar * zNear / zRange;
    ret[2][3] = -1;
    ret[3][3] = 0;
    
    return ret;
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz) 
{
  // YOUR CODE FOR HW2 HERE
  // Implement scaling 

  mat4 ret(sx, 0, 0, 0,
           0, sy, 0, 0,
           0, 0, sz, 0,
           0, 0, 0,  1);

  return transpose(ret);
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) 
{
  // YOUR CODE FOR HW2 HERE
  // Implement translation 

  mat4 ret(1, 0, 0, tx,
           0, 1, 0, ty,
           0, 0, 1, tz,
           0, 0, 0, 1);

  return transpose(ret);
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec) 
{
  vec3 x = glm::cross(up,zvec); 
  vec3 y = glm::cross(zvec,x); 
  vec3 ret = glm::normalize(y); 
  return ret; 
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
