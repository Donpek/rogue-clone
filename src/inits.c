#include "rogue.h"

void initColors(){
  init_pair(WHITE, COLOR_WHITE, COLOR_BLACK);
  init_pair(RED, COLOR_RED, COLOR_BLACK);
  init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
  init_pair(BLUE, COLOR_BLUE, COLOR_BLACK);
  init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);
  init_pair(MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
  init_pair(SOLID_WHITE, COLOR_WHITE, COLOR_WHITE);
}

Tile* initTiles(){
  Tile* tiles = malloc(sizeof(Tile) * NUM_OF_TILES);

  int i;
  for(i=0; i<NUM_OF_TILES; i++){
    tiles[i].known = 0;
    tiles[i].foggy = 1;
  }

  tiles[PLAYER_ID].gfx = PLAYER_GFX;
  tiles[PLAYER_ID].color = PLAYER_COLOR;
  tiles[PLAYER_ID].category = PLAYER_CATEGORY;

  tiles[GRASS_ID].gfx = GRASS_GFX;
  tiles[GRASS_ID].color = GRASS_COLOR;
  tiles[GRASS_ID].category = GRASS_CATEGORY;

  tiles[VERTICAL_DOOR_ID].gfx = VERTICAL_DOOR_GFX;
  tiles[VERTICAL_DOOR_ID].color = VERTICAL_DOOR_COLOR;
  tiles[VERTICAL_DOOR_ID].category = VERTICAL_DOOR_CATEGORY;

  tiles[HORIZONTAL_DOOR_ID].gfx = HORIZONTAL_DOOR_GFX;
  tiles[HORIZONTAL_DOOR_ID].color = HORIZONTAL_DOOR_COLOR;
  tiles[HORIZONTAL_DOOR_ID].category = HORIZONTAL_DOOR_CATEGORY;

  tiles[CORNER_ID].gfx = CORNER_GFX;
  tiles[CORNER_ID].color = CORNER_COLOR;
  tiles[CORNER_ID].category = CORNER_CATEGORY;

  tiles[WALL_ID].gfx = WALL_GFX;
  tiles[WALL_ID].color = WALL_COLOR;
  tiles[WALL_ID].category = WALL_CATEGORY;

  tiles[FLOOR_ID].gfx = FLOOR_GFX;
  tiles[FLOOR_ID].color = FLOOR_COLOR;
  tiles[FLOOR_ID].category = FLOOR_CATEGORY;

  tiles[SLIME_ID].gfx = SLIME_GFX;
  tiles[SLIME_ID].color = SLIME_COLOR;
  tiles[SLIME_ID].category = SLIME_CATEGORY;

  tiles[GRASS2_ID].gfx = GRASS2_GFX;
  tiles[GRASS2_ID].color = GRASS2_COLOR;
  tiles[GRASS2_ID].category = GRASS2_CATEGORY;

  return tiles;
}
