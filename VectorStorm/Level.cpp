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
	for (int i = 0; i < 20; i++)
	{
		l->enemyList.push_back(std::tuple<float, char>(1.5 * (float)i, 'T'));
	}

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
	for (int i = 0; i < 20; i++)
	{
		l->enemyList.push_back(std::tuple<float, char>(0.75 * i, 'T'));
	}

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
	for (int i = 0; i < 20; i++)
	{
		l->enemyList.push_back(std::tuple<float, char>(0.75 * i, 'T'));
	}

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
	for (int i = 0; i < 20; i++)
	{
		l->enemyList.push_back(std::tuple<float, char>(0.75 * i, 'T'));
	}

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

Level::Level()
{
}

Level::~Level()
{
	enemyList.clear();
}

void Level::Update(float dt)
{
	levelTime += dt;
}

void Level::Draw()
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	SDL_RenderDrawLine(renderer, pointsInner[0].x, pointsInner[0].y, points[0].x, points[0].y);
	if (closedShape)
	{
		SDL_RenderDrawLine(renderer, pointsInner[pointsInner.size() - 1].x, pointsInner[pointsInner.size() - 1].y, pointsInner[0].x, pointsInner[0].y);
		SDL_RenderDrawLine(renderer, points[points.size() - 1].x, points[points.size() - 1].y, points[0].x, points[0].y);
	}
	for (int i = 1; i < points.size(); i++)
	{
		SDL_RenderDrawLine(renderer, pointsInner[i - 1].x, pointsInner[i - 1].y, pointsInner[i].x, pointsInner[i].y);
		SDL_RenderDrawLine(renderer, pointsInner[i].x, pointsInner[i].y, points[i].x, points[i].y);
		SDL_RenderDrawLine(renderer, points[i - 1].x, points[i - 1].y, points[i].x, points[i].y);
	}
}

Enemy* Level::SpawnEnemy()
{
	if (enemyList.size() == 0)
		return nullptr;
	std::tuple<float, char> top = enemyList.front();
	if (std::get<0>(top) <= levelTime)
	{
		enemyList.pop_front();
		char c = std::get<1>(top);
		int idxA = rand() % levels[levelIdx]->points.size();
		int idxB = (idxA + 1) % levels[levelIdx]->points.size();
		Point2Df aBegin, aEnd, bBegin, bEnd;
		aBegin = levels[levelIdx]->pointsInner[idxA];
		bBegin = levels[levelIdx]->pointsInner[idxB];
		aEnd = levels[levelIdx]->points[idxA];
		bEnd = levels[levelIdx]->points[idxB];
		Point2Df begin, end;
		begin.x = aBegin.x + ((bBegin.x - aBegin.x) / 2.0);
		begin.y = aBegin.y + ((bBegin.y - aBegin.y) / 2.0);
		end.x = aEnd.x + ((bEnd.x - aEnd.x) / 2.0);
		end.y = aEnd.y + ((bEnd.y - aEnd.y) / 2.0);
		switch (c)
		{
		case 'T':
		{
			Tanker* t = new Tanker();
			

			t->Init(begin, end);
			return t;
		}
		default:
			return nullptr;
		}
	}
	return nullptr;
}

bool Level::AllEnemiesSpawned()
{ 
	return enemyList.size() <= 0;
}