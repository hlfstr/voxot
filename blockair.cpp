#include "blockair.hpp"

namespace Voxot {
BlockAir::BlockAir() {}
BlockAir::~BlockAir() {}

bool BlockAir::isVisible() {
	return false;
}

bool BlockAir::isSolid() {
	return false;
}

void BlockAir::Draw(Chunk *chunk, PoolVector3Array *data, int x, int y, int z) {
}

} // namespace Voxot