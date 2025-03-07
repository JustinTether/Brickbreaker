#include "main.h"






int main()
{
	Engine demo;
	if (demo.Construct(demo.MapWidth * demo.TileSize.x, demo.MapHeight * demo.TileSize.y, 2, 2))
		demo.Start();
	return 0;
}
