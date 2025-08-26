#pragma once

#ifndef __UTILITY_H__
#define __UTILITY_H__

// Define MAX and MIN macros
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

// Define screen dimensions
#define SCREEN_WIDTH    800
#define SCREEN_HEIGHT   600

template <class T>
struct Point2D
{
public:
	T x;
	T y;
};

#define Point2Df Point2D<float>
#define Point2Di Point2D<int>

template <class T>
struct Point3D
{
public:
	T x;
	T y;
	T z;
};

#define Point3Df Point3D<float>
#define Point3Di Point3D<int>

enum Scenes
{
	SCENE_TITLE,
};



#endif
