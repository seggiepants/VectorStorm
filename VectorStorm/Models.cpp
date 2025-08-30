#include "Models.h"

Model player;
Model tanker;
Model playerShot;
Model enemyShot;

Model::Model()
{
	color = WHITE;
	x = (SCREEN_WIDTH / 2);
	y = (SCREEN_HEIGHT / 2);
	scaleX = 1.0;
	scaleY = 1.0;
	angle = 0.0;
}

void Model::Draw()
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	std::vector<SDL_Vertex> verts;
	for (Point3Di triangle : triangles)
	{
		/*
		verts.push_back(SDL_Vertex{SDL_FPoint{x + (scaleX * points[triangle.x].x), y + (scaleY * points[triangle.x].y)}, color});
		verts.push_back(SDL_Vertex{SDL_FPoint{x + (scaleX * points[triangle.y].x), y + (scaleY * points[triangle.y].y)}, color});
		verts.push_back(SDL_Vertex{SDL_FPoint{x + (scaleX * points[triangle.z].x), y + (scaleY * points[triangle.z].y)}, color});		
		*/
		verts.push_back(ProjectPoint(points[triangle.x]));
		verts.push_back(ProjectPoint(points[triangle.y]));
		verts.push_back(ProjectPoint(points[triangle.z]));
	}
	SDL_RenderGeometry(renderer, nullptr, verts.data(), verts.size(), nullptr, 0);

}

SDL_Vertex Model::ProjectPoint(Point2Df point)
{
	float x = point.x;
	float y = point.y;

	// rotate
	x = point.x * cos(angle) - point.y * sin(angle);
	y = point.x * sin(angle) + point.y * cos(angle);

	// scale
	x *= scaleX;
	y *= scaleY;

	// translate
	x += this->x;
	y += this->y;

	return SDL_Vertex{ SDL_FPoint{x, y}, color };
}

float Model::GetRadius()
{
	float radius = 0.001f;
	for(Point2Df point : player.points)
	{
		if (abs(point.x) > radius)
			radius = abs(point.x);
		if (abs(point.y) > radius)
			radius = abs(point.y);
	}
	return radius * (scaleX > scaleY ? scaleX : scaleY);
}

void ModelInit()
{
	player.points = {
		{-2.5, -4.5},
		{-7.5, 0.5},
		{-0.5, 4.5},
		{0.5, 4.5},
		{7.5, 0.5},
		{2.5, -4.5},
		{3.5, -0.5},
		{0.5, 1.5},
		{-0.5, 1.5},
		{-3.5, -0.5},
	};

	player.triangles = {
		{ 0, 1, 9 },
		{9, 1, 2},
		{9, 2, 8},
		{7, 8, 2},
		{7, 2, 3},
		{7, 3, 4},
		{4, 5, 6},
		{4, 6, 7},
	};

	player.color = YELLOW;
	player.scaleX = 10.0;
	player.scaleY = 10.0;
	player.y = 5 * (SCREEN_HEIGHT / 6);

	tanker.points = {
		{0, -8},
		{-8, 0},
		{0, 8},
		{8, 0},
		{0, -2},
		{-2, 0},
		{0, 2},
		{2, 0}
	};

	tanker.triangles = {
		{0, 4, 3},
		{7, 2, 3},
		{1, 2, 6},
		{0, 1, 5}
	};

	tanker.color = MAGENTA;
	tanker.scaleX = 2.0;
	tanker.scaleY = 2.0;
	tanker.x = (SCREEN_WIDTH / 2);
	tanker.y = (SCREEN_HEIGHT / 2);

	playerShot.points = {
		{0, -1.5},
		{-1.4, -1.4},
		{-1.4, 1.4},
		{0, 1.5},
		{1.4, 1.4},
		{1.4, -1.4}
	};

	playerShot.triangles = {
		{0, 1, 4},
		{1, 4, 5},
		{1, 2, 4},
		{2, 3, 4}
	};

	playerShot.color = YELLOW;
	playerShot.scaleX = 2.0;
	playerShot.scaleY = 2.0;
	playerShot.x = (SCREEN_WIDTH / 2);
	playerShot.y = (SCREEN_HEIGHT / 2);

	enemyShot.points = {
		{0, -1},
		{-1, 0},
		{0, 1},
		{1, 0},
		{-2, -2},
		{-2, -1},
		{-1, -1},
		{-1, -2},
		{-2, 1},
		{-2, 2},
		{-1, 2},
		{-1, 1},
		{1, 1},
		{1, 2},
		{2, 2},
		{2, 1},
		{1, -2},
		{1, -1},
		{2, -1},
		{2, -2}
	};

	enemyShot.triangles = {
		{0, 1, 2},
		{0, 2, 3},
		{4, 5, 6},
		{4, 6, 7},
		{8, 9, 10},
		{8, 10, 11},
		{12, 13, 14},
		{12, 14, 15},
		{16, 17, 18},
		{16, 18, 19}
	};
	enemyShot.color = WHITE;
	enemyShot.scaleX = 2.0;
	enemyShot.scaleY = 2.0;
	enemyShot.x = (SCREEN_WIDTH / 2);
	enemyShot.y = (SCREEN_HEIGHT / 2);


}