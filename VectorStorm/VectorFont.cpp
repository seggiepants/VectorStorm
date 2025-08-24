#include "VectorFont.h"
#include "Globals.h"

const int stepX = 11;
const int stepY = 19;

VectorFont::VectorFont()
{
	// Initialize the font data.
	this->characters = new std::map<char, std::vector<std::vector<Point2Df>>>();

	// Lets fill it up
	this->characters->insert(std::pair<char, std::vector<std::vector<Point2Df>>>('0', { {{0, 0}, {0, -16}, {8, -16}, {8, 0}, {0, 0}, {0, 0}, {8, -16}} }));
	this->characters->insert(std::pair<char, std::vector<std::vector<Point2Df>>>('1', { {{2, 0}, {6, 0}}, {{4, 0}, {4,-16}, {3, -16}} }));
	this->characters->insert(std::pair<char, std::vector<std::vector<Point2Df>>>('2', { {{0, -16}, {8, -16}, {8, -8}, {0, -8}, {0, 0}, {8, 0}} }));
	this->characters->insert(std::pair<char, std::vector<std::vector<Point2Df>>>('3', { {{0, -16}, {8, -16}, {8, 0}, {0, 0}}, {{2, -8}, {8, -8}} }));
	this->characters->insert(std::pair<char, std::vector<std::vector<Point2Df>>>('4', { {{0, -16}, {0, -8}, {8, -8}}, {{8, -16}, {8, 0}} }));
	this->characters->insert(std::pair<char, std::vector<std::vector<Point2Df>>>('5', { {{8, -16}, {0, -16}, {0, -8}, {8, -8}, {8, 0}, {0, 0}} }));
	this->characters->insert(std::pair<char, std::vector<std::vector<Point2Df>>>('6', { {{8, -16}, {0, -16}, {0, 0}, {8, 0}, {8, -8}, {0, -8}} }));
	this->characters->insert(std::pair<char, std::vector<std::vector<Point2Df>>>('7', { {{0, -16}, {8, -16}, {8, 0}} }));
	this->characters->insert(std::pair<char, std::vector<std::vector<Point2Df>>>('8', { {{0, 0}, {0, -16}, {8, -16}, {8, 0}, {0, 0}}, {{0, -8}, {8, -8}} }));
	this->characters->insert(std::pair<char, std::vector<std::vector<Point2Df>>>('9', { {{0, 0}, {8, 0}, {8, -16}, {0, -16}, {0, -8}, {8, -8}} }));
	this->characters->insert(std::pair<char, std::vector<std::vector<Point2Df>>>('A', { {{0, 0}, {4, -16}, {8, 0}}, {{2, -8}, {6,-8}} }));
	this->characters->insert(std::pair<char, std::vector<std::vector<Point2Df>>>('B', { {{0, 0}, {0, -16}, {8, -12}, {0, -8}, {8, -4}, {0, 0}} }));
	this->characters->insert(std::pair<char, std::vector<std::vector<Point2Df>>>('C', { {{8, 0}, {0, 0}, {0, -16}, {8, -16}} }));
	this->characters->insert(std::pair<char, std::vector<std::vector<Point2Df>>>('D', { {{0, 0}, {0, -16}, {8, -8}, {0, 0}} }));
	this->characters->insert(std::pair<char, std::vector<std::vector<Point2Df>>>('E', { {{8, 0}, {0, 0}, {0, -16}, {8, -16}}, {{0, -8}, {6, -8}} }));
	this->characters->insert(std::pair<char, std::vector<std::vector<Point2Df>>>('F', { {{0, 0}, {0, -16}, {8, -16}}, {{0, -8}, {6, -8}} }));
	this->characters->insert(std::pair<char, std::vector<std::vector<Point2Df>>>('G', { {{8, -16}, {0, -16}, {0, 0}, {8, 0}, {8, -8}, {4, -8}, {4, -6}} }));
	this->characters->insert(std::pair<char, std::vector<std::vector<Point2Df>>>('H', { {{0, 0}, {0, -16}}, {{0, -8}, {8, -8}}, {{8, 0}, {8, -16}} }));
	this->characters->insert(std::pair<char, std::vector<std::vector<Point2Df>>>('I', { {{3, 0}, {5, 0}}, {{3, -16}, {5, -16}}, {{4, 0}, {4, -16}} }));
	this->characters->insert(std::pair<char, std::vector<std::vector<Point2Df>>>('J', { {{8, -16}, {8, 0}, {0, 0}, {0, -4}} }));
	this->characters->insert(std::pair<char, std::vector<std::vector<Point2Df>>>('K', { {{0, 0}, {0, -16}}, {{8, -16}, {0, -8}, {8, 0}} }));
	this->characters->insert(std::pair<char, std::vector<std::vector<Point2Df>>>('L', { {{0, -16}, {0, 0}, {8, 0}} }));
	this->characters->insert(std::pair<char, std::vector<std::vector<Point2Df>>>('M', { {{0, 0}, {0, -16}, {4, -8}, {8, -16}, {8, 0}} }));
	this->characters->insert(std::pair<char, std::vector<std::vector<Point2Df>>>('N', { {{0, 0}, {0, -16}, {8, 0}, {8, -16}} }));
	this->characters->insert(std::pair<char, std::vector<std::vector<Point2Df>>>('O', { {{0, 0}, {0, -16}, {8, -16}, {8, 0}, {0, 0}} }));
	this->characters->insert(std::pair<char, std::vector<std::vector<Point2Df>>>('P', { {{0, 0}, {0, -16}, {8, -16}, {8, -8}, {0, -8}} }));
	this->characters->insert(std::pair<char, std::vector<std::vector<Point2Df>>>('Q', { {{0, 0}, {0, -16}, {8, -16}, {8, 0}, {0, 0}}, {{8, 0}, {4, -4}} }));
	this->characters->insert(std::pair<char, std::vector<std::vector<Point2Df>>>('R', { {{0, 0}, {0, -16}, {8, -16}, {8, -8}, {0, -8}}, {{4, -8}, {8, 0}} }));
	this->characters->insert(std::pair<char, std::vector<std::vector<Point2Df>>>('S', { {{8, -16}, {0, -16}, {0, -8}, {8, -8}, {8, 0}, {0, 0}} }));
	this->characters->insert(std::pair<char, std::vector<std::vector<Point2Df>>>('T', { {{0, -16}, {8, -16}}, {{4, 0}, {4, -16}} }));
	this->characters->insert(std::pair<char, std::vector<std::vector<Point2Df>>>('U', { {{0, -16}, {0, 0}, {8, 0}, {8, -16}} }));
	this->characters->insert(std::pair<char, std::vector<std::vector<Point2Df>>>('V', { {{0, -16}, {4, 0}, {8, -16}} }));
	this->characters->insert(std::pair<char, std::vector<std::vector<Point2Df>>>('W', { {{0, -16}, {2, 0}, {4, -8}, {6, 0}, {8, -16}} }));
	this->characters->insert(std::pair<char, std::vector<std::vector<Point2Df>>>('X', { {{0, -16}, {8, 0}}, {{8, -16}, {0, 0}} }));
	this->characters->insert(std::pair<char, std::vector<std::vector<Point2Df>>>('Y', { {{0, -16}, {4, -8}, {8, -16}}, {{4, -8}, {4, 0}} }));
	this->characters->insert(std::pair<char, std::vector<std::vector<Point2Df>>>('Z', { {{0, -16}, {8, -16}, {0, 0}, {8, 0}} }));
	this->characters->insert(std::pair<char, std::vector<std::vector<Point2Df>>>(' ', { {} }));
	this->characters->insert(std::pair<char, std::vector<std::vector<Point2Df>>>(',', { {{4, -3}, {5, -3}, {5, -2}, {4, -1}, {4.5, -2}, {4, -2}, {4, -3}} }));
	this->characters->insert(std::pair<char, std::vector<std::vector<Point2Df>>>(':', { {{4, -3}, {5, -3}, {5, -2}, {4, -2}, {4, -3}}, {{4, -14}, {5, -14}, {5, -13}, {4, -13}, {4, -14}} }));
	this->characters->insert(std::pair<char, std::vector<std::vector<Point2Df>>>(';', { {{4, -3}, {5, -3}, {5, -2}, {4, -1}, {4.5, -2}, {4, -2}, {4, -3}}, {{4, -14}, {5, -14}, {5, -13}, {4, -13}, {4, -14}} }));

	this->scaleX = this->scaleY = 1.0;
}

VectorFont::~VectorFont()
{
	std::map<char, std::vector<std::vector<Point2Df>>>::iterator iterChar = this->characters->begin();
	while (iterChar != this->characters->end())
	{
		// char rune = iterChar->first;
		std::vector<std::vector<Point2Df>> lines = iterChar->second;
		for (std::vector<Point2Df> line : lines)
		{
			line.clear();
		}
		lines.clear();
		iterChar++;
	}
	this->characters->clear();
	delete this->characters;
	this->characters = nullptr;
}

void VectorFont::Construct(float scaleX, float scaleY)
{
	this->scaleX = scaleX;
	this->scaleY = scaleY;
}

void VectorFont::DrawText(std::string message, int x, int y, SDL_Color color)
{
	int px = x, py = y;
	int x1 = 0, y1 = 0, x2 = 0, y2 = 0;

	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
	for (char rune : message)
	{
		std::map<char, std::vector<std::vector<Point2Df>>>::iterator match = this->characters->find(rune);
		if (match != this->characters->end())
		{
			for (std::vector<Point2Df> points : match->second)
			{
				bool firstPoint = true;
				for (Point2Df point : points)
				{
					x1 = x2;
					y1 = y2;
					x2 = (int)(point.x * this->scaleX);
					y2 = (int)(point.y * this->scaleY);
					if (firstPoint)
					{
						firstPoint = false;
					}
					else
					{
						SDL_RenderDrawLine(renderer, px + x1, py + y1, px + x2, py + y2);
						
					}
				}
			}
			px += (int)(stepX * this->scaleX);
			if ((px + stepX) >= SCREEN_WIDTH)
			{
				px = x;
				py += (int)(stepY * this->scaleY);
			}
		}
	}
}

void VectorFont::MeasureText(std::string message, int* width, int* height)
{
	*height = stepY * this->scaleY;
	*width = message.length() * stepX * this->scaleX;
}
