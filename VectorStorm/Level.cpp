#include "Level.h"
#include "Globals.h"

std::vector<Level*> levels;
int levelIdx;

Level* GenerateCircle()
{
	float width = SCREEN_WIDTH < SCREEN_HEIGHT ? SCREEN_WIDTH : SCREEN_HEIGHT;
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
		l->points.push_back(Point2Df{ centerX + (float)(width * cos(theta)), centerY + (float)(width * sin(theta)) });
		l->pointsInner.push_back(Point2Df{ centerX + (float)(0.2 * width * cos(theta)), centerY + (float)(width / 3.0) + (float)(0.2 * width * sin(theta)) });
		totalRadians += delta;
		theta += delta;
		if (theta > (2.0 * M_PI))
		{
			theta -= (2.0 * M_PI);
		}
	}
	l->color = BLUE;

	return l;
}

Level* GenerateSquare()
{
	float width = SCREEN_WIDTH < SCREEN_HEIGHT ? SCREEN_WIDTH : SCREEN_HEIGHT;
	width = (4.0 * width) / 10.0; // 40% radius, 80% total

	float centerX = SCREEN_WIDTH / 2.0;
	float centerY = SCREEN_HEIGHT / 2.0;

	Level* l = new Level();
	l->closedShape = true;
	float offsetX = 0.0;
	float offsetY = (3.0 * width) / 7.0;
	float innerSize = (width / 6.0);
	float stepX = width / 2.0;
	float stepY = width / 2.0;
	float innerStepX = innerSize / 2.0;
	float innerStepY = innerSize / 2.0;
	// bottom center and two over left
	for (int i = 0; i >= -2; i--)
	{
		l->points.push_back(Point2Df{ centerX + (i * stepX), centerY + width });
		l->pointsInner.push_back(Point2Df{ centerX + offsetX + (i * innerStepX), centerY + offsetY + innerSize });
	}

	// four up.
	for (int i = 1; i >= -2; i--)
	{
		l->points.push_back(Point2Df{ centerX - width, centerY + (i * stepY) });
		l->pointsInner.push_back(Point2Df{ centerX + offsetX - innerSize, centerY + offsetY + (i * innerStepY) });
	}

	// four forward right
	for (int i = -1; i <= 2; i++)
	{
		l->points.push_back(Point2Df{ centerX + (i * stepX), centerY - width });
		l->pointsInner.push_back(Point2Df{ centerX + offsetX + (i * innerStepX), centerY + offsetY - innerSize });
	}

	// four down.
	for (int i = -1; i <= 2; i++)
	{
		l->points.push_back(Point2Df{ centerX + width, centerY + (i * stepY) });
		l->pointsInner.push_back(Point2Df{ centerX + offsetX + innerSize, centerY + offsetY + (i * innerStepY) });
	}

	// finish the loop
	l->points.push_back(Point2Df{ centerX + stepX, centerY + width });
	l->pointsInner.push_back(Point2Df{ centerX + offsetX + innerStepX, centerY + offsetY + innerSize });

	l->color = BLUE;

	return l;
}

Level* GenerateCross()
{
	float width = SCREEN_WIDTH < SCREEN_HEIGHT ? SCREEN_WIDTH : SCREEN_HEIGHT;
	width = (4.0 * width) / 10.0; // 40% radius, 80% total

	float centerX = SCREEN_WIDTH / 2.0;
	float centerY = SCREEN_HEIGHT / 2.0;

	Level* l = new Level();
	l->closedShape = true;
	float offsetX = 0.0;
	float offsetY = ((3.0 * width) / 7.0) - 32.0;
	float innerSize = (width / 6.0);
	float stepX = width / 2.0;
	float stepY = width / 2.0;
	float innerStepX = innerSize / 2.0;
	float innerStepY = innerSize / 2.0;

	// bottom center and two over left
	l->points.push_back(Point2Df{ centerX, centerY + width });
	l->pointsInner.push_back(Point2Df{ centerX + offsetX, centerY + offsetY + innerSize });

	l->points.push_back(Point2Df{ centerX - stepX, centerY + width });
	l->pointsInner.push_back(Point2Df{ centerX + offsetX - innerStepX, centerY + offsetY + innerSize });

	l->points.push_back(Point2Df{ centerX + -stepX, centerY + stepY });
	l->pointsInner.push_back(Point2Df{ centerX + offsetX - innerStepX, centerY + offsetY + innerStepY });

	// four up.
	l->points.push_back(Point2Df{ centerX - width, centerY + stepY });
	l->pointsInner.push_back(Point2Df{ centerX + offsetX - innerSize, centerY + offsetY + innerStepY });

	l->points.push_back(Point2Df{ centerX - width, centerY });
	l->pointsInner.push_back(Point2Df{ centerX + offsetX - innerSize, centerY + offsetY });

	l->points.push_back(Point2Df{ centerX - width, centerY - stepY });
	l->pointsInner.push_back(Point2Df{ centerX + offsetX - innerSize, centerY + offsetY - innerStepY });

	l->points.push_back(Point2Df{ centerX - stepX, centerY - stepY });
	l->pointsInner.push_back(Point2Df{ centerX + offsetX - innerStepX, centerY + offsetY - innerStepY });

	// four forward right	
	l->points.push_back(Point2Df{ centerX - stepX, centerY - width });
	l->pointsInner.push_back(Point2Df{ centerX + offsetX - innerStepX, centerY + offsetY - innerSize });

	l->points.push_back(Point2Df{ centerX, centerY - width });
	l->pointsInner.push_back(Point2Df{ centerX + offsetX, centerY + offsetY - innerSize });

	l->points.push_back(Point2Df{ centerX + stepX, centerY - width });
	l->pointsInner.push_back(Point2Df{ centerX + offsetX + innerStepX, centerY + offsetY - innerSize });

	l->points.push_back(Point2Df{ centerX + stepX, centerY - stepY });
	l->pointsInner.push_back(Point2Df{ centerX + offsetX + innerStepX, centerY + offsetY - innerStepY });

	// four down.
	l->points.push_back(Point2Df{ centerX + width, centerY - stepY });
	l->pointsInner.push_back(Point2Df{ centerX + offsetX + innerSize, centerY + offsetY - innerStepY });

	l->points.push_back(Point2Df{ centerX + width, centerY });
	l->pointsInner.push_back(Point2Df{ centerX + offsetX + innerSize, centerY + offsetY  });

	l->points.push_back(Point2Df{ centerX + width, centerY + stepY });
	l->pointsInner.push_back(Point2Df{ centerX + offsetX + innerSize, centerY + offsetY + innerStepY });

	l->points.push_back(Point2Df{ centerX + stepX, centerY + stepY });
	l->pointsInner.push_back(Point2Df{ centerX + offsetX + innerStepX, centerY + offsetY + innerStepY });

	// finish the loop
	l->points.push_back(Point2Df{ centerX + stepX, centerY + width });
	l->pointsInner.push_back(Point2Df{ centerX + offsetX + innerStepX, centerY + offsetY + innerSize });

	l->color = BLUE;

	return l;
}

Level* GenerateBowTie()
{
	float width = SCREEN_WIDTH < SCREEN_HEIGHT ? SCREEN_WIDTH : SCREEN_HEIGHT;
	width = (5 * width) / 10.0; // 40% radius, 80% total

	float centerX = SCREEN_WIDTH / 2.0;
	float centerY = (3 * SCREEN_HEIGHT) / 5.0;

	float xStep = (2 * width) / 11.0;
	float xStepHalf = xStep / 2.0;

	float yStep = (1.25 * width) / 7.0;
	float yStepHalf = yStep / 2.0;

	float innerSize = (width / 12.0);
	float innerStepX = innerSize / 2.0;
	float innerStepY = innerSize / 2.0;
	float innerStepHalfX = innerStepX / 2.0;
	float innerStepHalfY = innerStepY / 2.0;

	float offsetX = 0.0;
	float offsetY = ((0.5 * width) / 7.0);

	Level* l = new Level();
	l->closedShape = true;

	float currentX = centerX + xStepHalf;
	float currentY = centerY + yStepHalf + yStep;

	float innerCurrentX = centerX + offsetX + innerStepHalfX;
	float innerCurrentY = centerY + offsetY + innerStepHalfY + innerStepY;


	// bottom of bow tie
	l->points.push_back(Point2Df{ currentX, currentY });
	l->pointsInner.push_back(Point2Df{ innerCurrentX, innerCurrentY });

	currentX -= xStep;
	innerCurrentX -= innerStepX;	
	l->points.push_back(Point2Df{ currentX, currentY });
	l->pointsInner.push_back(Point2Df{ innerCurrentX, innerCurrentY });

	// left bow
	currentX -= (xStep * 2);
	innerCurrentX -= (innerStepX * 2);
	currentY += yStep;
	innerCurrentY += innerStepY;
	l->points.push_back(Point2Df{ currentX, currentY });
	l->pointsInner.push_back(Point2Df{ innerCurrentX, innerCurrentY });

	currentX -= (xStep * 2);
	innerCurrentX -= (innerStepX * 2);
	currentY -= yStep;
	innerCurrentY -= innerStepY;
	l->points.push_back(Point2Df{ currentX, currentY });
	l->pointsInner.push_back(Point2Df{ innerCurrentX, innerCurrentY });

	currentX -= xStep;
	innerCurrentX -= innerStepX;
	currentY -= (yStep * 2);
	innerCurrentY -= (innerStepY * 2);
	l->points.push_back(Point2Df{ currentX, currentY });
	l->pointsInner.push_back(Point2Df{ innerCurrentX, innerCurrentY });

	currentY -= yStep;
	innerCurrentY -= innerStepY;
	l->points.push_back(Point2Df{ currentX, currentY });
	l->pointsInner.push_back(Point2Df{ innerCurrentX, innerCurrentY });

	currentX += xStep;
	innerCurrentX += innerStepX;
	currentY -= (yStep * 2);
	innerCurrentY -= (innerStepY * 2);
	l->points.push_back(Point2Df{ currentX, currentY });
	l->pointsInner.push_back(Point2Df{ innerCurrentX, innerCurrentY });

	currentX += (xStep * 2);
	innerCurrentX += (innerStepX * 2);
	currentY -= yStep;
	innerCurrentY -= innerStepY;
	l->points.push_back(Point2Df{ currentX, currentY });
	l->pointsInner.push_back(Point2Df{ innerCurrentX, innerCurrentY });

	currentX += (xStep * 2);
	innerCurrentX += (innerStepX * 2);
	currentY += (yStep * 2);
	innerCurrentY += (innerStepY * 2);
	l->points.push_back(Point2Df{ currentX, currentY });
	l->pointsInner.push_back(Point2Df{ innerCurrentX, innerCurrentY });

	// Top of bow tie
	currentX += xStep;
	innerCurrentX += innerStepX;
	l->points.push_back(Point2Df{ currentX, currentY });
	l->pointsInner.push_back(Point2Df{ innerCurrentX, innerCurrentY });

	// Right bow
	currentX += (xStep * 2);
	innerCurrentX += (innerStepX * 2);
	currentY -= (yStep * 2);
	innerCurrentY -= (innerStepY * 2);
	l->points.push_back(Point2Df{ currentX, currentY });
	l->pointsInner.push_back(Point2Df{ innerCurrentX, innerCurrentY });

	currentX += (xStep * 2);
	innerCurrentX += (innerStepX * 2);
	currentY += yStep;
	innerCurrentY += innerStepY;
	l->points.push_back(Point2Df{ currentX, currentY });
	l->pointsInner.push_back(Point2Df{ innerCurrentX, innerCurrentY });

	currentX += xStep;
	innerCurrentX += innerStepX;
	currentY += (yStep * 2);
	innerCurrentY += (innerStepY * 2);
	l->points.push_back(Point2Df{ currentX, currentY });
	l->pointsInner.push_back(Point2Df{ innerCurrentX, innerCurrentY });

	currentY += yStep;
	innerCurrentY += innerStepY;
	l->points.push_back(Point2Df{ currentX, currentY });
	l->pointsInner.push_back(Point2Df{ innerCurrentX, innerCurrentY });

	currentX -= xStep;
	innerCurrentX -= innerStepX;
	currentY += (yStep * 2);
	innerCurrentY += (innerStepY * 2);
	l->points.push_back(Point2Df{ currentX, currentY });
	l->pointsInner.push_back(Point2Df{ innerCurrentX, innerCurrentY });

	currentX -= (xStep * 2);
	innerCurrentX -= (innerStepX * 2);
	currentY += yStep;
	innerCurrentY += innerStepY;
	l->points.push_back(Point2Df{ currentX, currentY });
	l->pointsInner.push_back(Point2Df{ innerCurrentX, innerCurrentY });

	l->color = BLUE;

	return l;
}

void LevelInit()
{
	levels.clear();

	// Add the levels	
	levels.push_back(GenerateCircle());

	levels.push_back(GenerateSquare());

	levels.push_back(GenerateCross());

	levels.push_back(GenerateBowTie());
	
}

void LevelDestroy()
{
	for (Level* level : levels)
		delete level;
	levels.clear();
}