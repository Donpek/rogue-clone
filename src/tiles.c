#include "rogue.h"

void initColors(){
  init_pair(WHITE, COLOR_WHITE, COLOR_BLACK);
  init_pair(RED, COLOR_RED, COLOR_BLACK);
  init_pair(GREEN, COLOR_GREEN, COLOR_BLACK);
  init_pair(BLUE, COLOR_BLUE, COLOR_BLACK);
  init_pair(YELLOW, COLOR_YELLOW, COLOR_BLACK);
  init_pair(MAGENTA, COLOR_MAGENTA, COLOR_BLACK);
}

Tile* initTiles(){
  Tile* tiles = malloc(sizeof(Tile) * NUM_OF_TILES);

  tiles[PLAYER_ID].gfx = PLAYER_GFX;
  tiles[PLAYER_ID].color = PLAYER_COLOR;
  tiles[PLAYER_ID].visible = PLAYER_VISIBLE;
  tiles[PLAYER_ID].category = PLAYER_CATEGORY;

  tiles[GRASS_ID].gfx = GRASS_GFX;
  tiles[GRASS_ID].color = GRASS_COLOR;
  tiles[GRASS_ID].visible = GRASS_VISIBLE;
  tiles[GRASS_ID].category = GRASS_CATEGORY;

  tiles[VERTICAL_DOOR_ID].gfx = VERTICAL_DOOR_GFX;
  tiles[VERTICAL_DOOR_ID].color = VERTICAL_DOOR_COLOR;
  tiles[VERTICAL_DOOR_ID].visible = VERTICAL_DOOR_VISIBLE;
  tiles[VERTICAL_DOOR_ID].category = VERTICAL_DOOR_CATEGORY;

  tiles[HORIZONTAL_DOOR_ID].gfx = HORIZONTAL_DOOR_GFX;
  tiles[HORIZONTAL_DOOR_ID].color = HORIZONTAL_DOOR_COLOR;
  tiles[HORIZONTAL_DOOR_ID].visible = HORIZONTAL_DOOR_VISIBLE;
  tiles[HORIZONTAL_DOOR_ID].category = HORIZONTAL_DOOR_CATEGORY;

  tiles[CORNER_ID].gfx = CORNER_GFX;
  tiles[CORNER_ID].color = CORNER_COLOR;
  tiles[CORNER_ID].visible = CORNER_VISIBLE;
  tiles[CORNER_ID].category = CORNER_CATEGORY;

  tiles[WALL_ID].gfx = WALL_GFX;
  tiles[WALL_ID].color = WALL_COLOR;
  tiles[WALL_ID].visible = WALL_VISIBLE;
  tiles[WALL_ID].category = WALL_CATEGORY;

  tiles[FLOOR_ID].gfx = FLOOR_GFX;
  tiles[FLOOR_ID].color = FLOOR_COLOR;
  tiles[FLOOR_ID].visible = FLOOR_VISIBLE;
  tiles[FLOOR_ID].category = FLOOR_CATEGORY;

  return tiles;
}