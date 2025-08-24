#pragma once

#ifndef __UTILITY_H__
#define __UTILITY_H__

// Define MAX and MIN macros
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

// Define screen dimensions
#define SCREEN_WIDTH    800
#define SCREEN_HEIGHT   600

enum Scenes
{
	SCENE_TITLE,
};

#endif
