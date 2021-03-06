#pragma once

#ifdef _WINDOWS
#include <GL/glew.h>
#endif
#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include "ShaderProgram.h"
#include "glm/gtc/matrix_transform.hpp"
#include "stb_image.h"
#include <iterator>
#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <cassert>
#include <SDL_mixer.h>
#ifdef _WINDOWS
#define RESOURCE_FOLDER ""
#else
#define RESOURCE_FOLDER "NYUCodebase.app/Contents/Resources/"
#endif

struct FlareMapEntity {
	std::string type;
	float x;
	float y;
};

class FlareMap {
public:
	FlareMap();
	~FlareMap();

	void Load(const std::string fileName);

	int mapWidth;
	int mapHeight;
	unsigned int **mapData;
	std::vector<FlareMapEntity> entities;
	std::vector<FlareMapEntity> ground;

private:

	bool ReadHeader(std::ifstream &stream);
	bool ReadLayerData(std::ifstream &stream);
	bool ReadEntityData(std::ifstream &stream);

};

class SheetSprite
{
public:
	SheetSprite();
	SheetSprite(unsigned int textureID, float u, float v, float width, float height, float size);
	void Draw(ShaderProgram &p);
	float size;
	unsigned int textureID;
	float u;
	float v;
	float x;
	float y;
	float width=0;
	float height = 0;
};


class Entity
{
public:
	void Draw(ShaderProgram &p);
	glm::vec3 position=glm::vec3(-1.0, 0.0, 0.0);
	float velocity=3.0;
	glm::vec3 size=glm::vec3(-1.0, 0.0, 0.0);
	bool faceLeft;

	float rotation=0.0;

	SheetSprite sprite;

	float health=0.0;
	float timeAlive=0.0f;
	bool isStatic=false;
};

class Game
{
public:
	float gravity = 4.0f;
	float tileSize = 0.1;
	int sprite_count_x = 16;
	int sprite_count_y = 10;
	std::vector<float> vertices;
	std::vector<float> texCoords;
	std::vector<Entity> enemies;
	FlareMap map;
	Entity ship;
	float lastFrameTicks;
	float speed;
	bool done;
	std::vector<Entity> entities;
	ShaderProgram program;
	GLuint fontTexture;
	bool start;
	std::vector<Entity> bullets;
	std::vector<int> ground;
	unsigned int platformSheetTexture;
	Mix_Chunk *shootSound;
	Mix_Chunk *hitSound;
	bool enemyKilled = false;
};

class MixerSound
{
public:
	Uint32 offset;
	Uint32 length;
	Uint8 *buffer;
	float volume;
	SDL_AudioFormat format;
	bool loaded;
	bool playing;
	bool loop;
	Mix_Chunk *shootSound;
	Mix_Chunk *hitSound;
};

class DemoApp
{
public:
	std::vector<MixerSound> mixSounds;
};

GLuint LoadTexture(const char *filepath);
void Setup(Game &g);
void Render(Game &g, float elapsed);
void Runner(Game &g);
void Update(Game &g);
void DrawText(ShaderProgram &p, int fontTexture, std::string text, float size, float spacing);
void shootBullet(Game &g);
void drawMap(Game &g);
void worldToTileCoordinates(Game &g, float worldX, float worldY, int *gridX, int *gridY);
bool collisionBottom(Game &g);
bool collisionBot(Game &g,Entity &e);