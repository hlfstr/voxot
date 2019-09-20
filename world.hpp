#ifndef _WORLD_H_
#define _WORLD_H_

#include "chunk.hpp"
#include "voxot.hpp"

using namespace godot;

namespace Voxot {

class Chunk;
//class Block;

class World : public Spatial {
	GODOT_CLASS(World, Spatial);

public:
	String _name;

	static void _register_methods();
	void _init();
	void _process(float);

	virtual void Init();
	virtual void Generate();
	virtual void Update();

	void setChunkWidth(int);
	int getChunkWidth();

	void setChunkHeight(int);
	int getChunkHeight();

	void setChunkDepth(int);
	int getChunkDepth();

	void CreateChunk(String, int, int);

protected:
	int ChunkWidth;
	int ChunkHeight;
	int ChunkDepth;

	int WorldWidth;
	int WorldHeight;

	ResourceLoader *resources;

	bool isInit;
};
} // namespace Voxot

#endif