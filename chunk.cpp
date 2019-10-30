#include "chunk.hpp"

namespace Voxot {

REGISTER_CLASS(Chunk);

MetaBlock Chunk::AirBlock = { "air", 0 };

Chunk::Chunk(){};
Chunk::~Chunk() {
	delete[] Blocks;
	MaterialList.clear();
}

String Chunk::toName(const int &x, const int &y, const int &z) {
	std::string out;
	if (std::abs(x) < 10)
		out = "0" + std::to_string(x);
	else
		out = std::to_string(x);

	if (std::abs(y) < 10)
		out = out + "0" + std::to_string(y);
	else
		out = out + std::to_string(y);

	if (std::abs(z) < 10)
		out = out + "0" + std::to_string(z);
	else
		out = out + std::to_string(z);

	return String(out.c_str());
}

Ref<SpatialMaterial> Chunk::GetMaterial(const String &name) {
	if (!MaterialList.has(name)) {
#ifdef DEBUG
		Godot::print("Unable to find material " + name);
#endif
		return nullptr;
	}
	return MaterialList[name];
}

void Chunk::_register_methods() {
	register_method("_ready", &Chunk::_ready);
	register_method("_process", &Chunk::_process);

	register_property<Chunk, Dictionary>("Material/Materials", &Chunk::MaterialList, Dictionary::make<String, Variant>("default", GODOT_VARIANT_TYPE_NIL));
}

void Chunk::_init() {
	MaterialList = Dictionary::make<String, Variant>("default", GODOT_VARIANT_TYPE_NIL);

	staticBody = StaticBody::_new();
	collisionShape = CollisionShape::_new();
	_collisionMesh = ConcavePolygonShape::_new();
	_meshArray = Array();
	_mesh = ArrayMesh::_new();

	add_child(staticBody);
	staticBody->add_child(collisionShape);
	isDirty = false;
	isGenerating = false;
	doneGenerating = false;
	Init();
}

void Chunk::_ready() {
	Ready();
}

void Chunk::setup(World *w, const int &posx, const int &posy, const int &posz) {

	_world = w;
	Width = _world->getChunkWidth();
	Height = _world->getChunkHeight();
	Depth = _world->getChunkDepth();

	X = posx;
	Y = posy;
	Z = posz;

	Vector3 pos = Vector3(X, Y, Z);
	Transform t = get_transform();
	t.origin = pos;
	set_transform(t);

	set_name(toName(X, Y, Z));
	staticBody->set_name(get_name());
	collisionShape->set_name(get_name());

	Blocks = new MetaBlock[Width * Height * Depth];

	Generate();
	dirty();
}

void Chunk::_process(double delta) {
	if (isDirty) {
		if (!isGenerating) {
			isGenerating = true;
			doneGenerating = false;
			std::thread th(&Chunk::GenMesh, this);
			th.detach();
		}
		if (doneGenerating) {
			Render();
			isGenerating = false;
			isDirty = false;
			doneGenerating = false;
		}
	}
	Update(delta);
}

void Chunk::Generate() {
	for (int x = 0; x < Width; x++) {
		for (int y = 0; y < Height; y++) {
			for (int z = 0; z < Depth; z++) {
				Blocks[x + y * Width + z * Width * Depth] = { "solid", 0 };
			}
		}
	}
}

void Chunk::GenMesh() {
	MeshData data = MeshData();
	_meshArray.clear();
	_collisionMesh = ConcavePolygonShape::_new();

	for (int x = 0; x < Width; x++) {
		for (int y = 0; y < Height; y++) {
			for (int z = 0; z < Depth; z++) {
				BlockBin::instance().Get(Blocks[x + y * Width + z * Width * Depth].name.c_str())->Draw(this, &data, x, y, z);
			}
		}
	}

	_meshArray.resize(ArrayMesh::ARRAY_MAX);
	_meshArray[ArrayMesh::ARRAY_VERTEX] = data.verts;
	_meshArray[ArrayMesh::ARRAY_TEX_UV] = data.uvs;
	_meshArray[ArrayMesh::ARRAY_NORMAL] = data.normals;
	_meshArray[ArrayMesh::ARRAY_TANGENT] = data.tangents;

	_collisionMesh->set_faces(data.verts);
	doneGenerating = true;
}

void Chunk::Render() {
	if (_mesh->get_surface_count() > 0)
		_mesh->surface_remove(0);
	_mesh->add_surface_from_arrays(Mesh::PRIMITIVE_TRIANGLES, _meshArray);
	set_mesh(_mesh);

	Ref<SpatialMaterial> mat = GetMaterial("default");
	if (!mat.is_valid()) {
		Godot::print("material not good");
	} else {
		set_surface_material(0, mat);
	}

	collisionShape->set_shape(_collisionMesh);
	_meshArray.clear();
}

Block *Chunk::GetBlock(const int &x, const int &y, const int &z) {
	if (inBounds(x, y, z))
		return BlockBin::instance().Get(Blocks[x + y * Width + z * Width * Depth].name.c_str());
	else
		return BlockBin::instance().Get("air");
}

bool Chunk::DeleteBlock(const int &x, const int &y, const int &z) {
	return SetBlock(AirBlock, x, y, z);
}

bool Chunk::SetBlock(const MetaBlock &block, const int &x, const int &y, const int &z) {
	if (isDirty)
		return false;

	if (inBounds(x, y, z)) {
		if (Blocks[x + y * Width + z * Width * Depth] == block)
			return false;

		Blocks[x + y * Width + z * Width * Depth] = block;
		dirty();
		return true;
	}
	return false;
}

bool Chunk::inBounds(const int &x, const int &y, const int &z) {
	if (x >= 0 && x < Width) {
		if (y >= 0 && y < Height) {
			if (z >= 0 && z < Depth) {
				return true;
			}
		}
	}
	return false;
}

} // namespace Voxot