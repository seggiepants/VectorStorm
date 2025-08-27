#include "Level.h"
#include "Globals.h"

std::vector<Level*> levels;
int levelIdx;

void LevelInit()
{
	levels.clear();

	// Add the levels
	float width = SCREEN_WIDTH < SCREEN_HEIGHT ? SCREEN_WIDTH: SCREEN_HEIGHT;
	width = (4.0 * width) / 10.0; // 40% radius, 80% total
	float centerX = SCREEN_WIDTH / 2.0;
	float centerY = SCREEN_HEIGHT / 2.0;
	float totalRadians = 0.0f;
	float theta = M_PI / 2.0; 
	float delta = (M_PI / 8.0); // 2PI/16 or 16 segments per circle.

	// Level 1 = Circle
	Level* l = new Level();

	l->closedShape = true;
	while (totalRadians < (M_PI * 2.0))
	{
		l->points.push_back(Point2Df { centerX + (float)(width * cos(theta)), centerY + (float)(width * sin(theta)) });
		l->pointsInner.push_back(Point2Df{ centerX + (float)(0.2 * width * cos(theta)), centerY + (float)(width / 3.0) + (float)(0.2 * width * sin(theta))});
		totalRadians += delta;
		theta += delta;
		if (theta > (2.0 * M_PI))
		{
			theta -= (2.0 * M_PI);
		}
	}
	l->color = BLUE;
	levels.push_back(l);
	levelIdx = 0;
}

void LevelDestroy()
{
	for (Level* level : levels)
		delete level;
	levels.clear();
}