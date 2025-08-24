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
	/*
	Point2D<T>();
	Point2D<T>(const Point2D<T>& source);
	Point2D<T>(T x, T y);
	*/
	// T& operator=(const T& other);
	T x;
	T y;
};

#define Point2Df Point2D<float>
#define Point2Di Point2D<int>

enum Scenes
{
	SCENE_TITLE,
};



#endif
