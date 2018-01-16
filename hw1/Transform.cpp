// Transform.cpp: implementation of the Transform class.


#include "Transform.h"
#include <iostream>
#include <glm/gtx/string_cast.hpp>

using namespace std;

//Please implement the following functions:

// Helper rotation function.  
mat3 Transform::rotate(const float degrees, const vec3& axis) {
	// YOUR CODE FOR HW1 HERE

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
    return m1 + m2 + m3;
}

// Transforms the camera left around the "crystal ball" interface
void Transform::left(float degrees, vec3& eye, vec3& up) {
	// YOUR CODE FOR HW1 HERE
    
    mat3 rotationMatrix = rotate(-degrees, up);
    eye = rotationMatrix * eye;
    up = rotationMatrix * up;

    printf("Coordinates: %.2f, %.2f, %.2f; distance: %.2f\n", eye.x, eye.y, eye.z, sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2)));
}

// Transforms the camera up around the "crystal ball" interface
void Transform::up(float degrees, vec3& eye, vec3& up) {
	// YOUR CODE FOR HW1 HERE 

    vec3 axis = glm::cross(up, eye);

    mat3 rotationMatrix = rotate(degrees, axis);
    eye = rotationMatrix * eye;
    up = rotationMatrix * up;

    printf("Coordinates: %.2f, %.2f, %.2f; distance: %.2f\n", eye.x, eye.y, eye.z, sqrt(pow(eye.x, 2) + pow(eye.y, 2) + pow(eye.z, 2)));
}

// Your implementation of the glm::lookAt matrix
mat4 Transform::lookAt(vec3 eye, vec3 up) {
	// YOUR CODE FOR HW1 HERE

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

Transform::Transform()
{

}

Transform::~Transform()
{

}
