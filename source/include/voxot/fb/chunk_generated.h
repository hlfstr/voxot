// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_CHUNK_VOXOT_H_
#define FLATBUFFERS_GENERATED_CHUNK_VOXOT_H_

#include "flatbuffers/flatbuffers.h"

namespace voxot {

struct Vec3;

struct fbChunk;
struct fbChunkBuilder;

FLATBUFFERS_MANUALLY_ALIGNED_STRUCT(4) Vec3 FLATBUFFERS_FINAL_CLASS {
 private:
  float x_;
  float y_;
  float z_;

 public:
  Vec3()
      : x_(0),
        y_(0),
        z_(0) {
  }
  Vec3(float _x, float _y, float _z)
      : x_(flatbuffers::EndianScalar(_x)),
        y_(flatbuffers::EndianScalar(_y)),
        z_(flatbuffers::EndianScalar(_z)) {
  }
  float x() const {
    return flatbuffers::EndianScalar(x_);
  }
  float y() const {
    return flatbuffers::EndianScalar(y_);
  }
  float z() const {
    return flatbuffers::EndianScalar(z_);
  }
};
FLATBUFFERS_STRUCT_END(Vec3, 12);

struct fbChunk FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  typedef fbChunkBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_NAME = 4
  };
  const flatbuffers::String *name() const {
    return GetPointer<const flatbuffers::String *>(VT_NAME);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_NAME) &&
           verifier.VerifyString(name()) &&
           verifier.EndTable();
  }
};

struct fbChunkBuilder {
  typedef fbChunk Table;
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_name(flatbuffers::Offset<flatbuffers::String> name) {
    fbb_.AddOffset(fbChunk::VT_NAME, name);
  }
  explicit fbChunkBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  flatbuffers::Offset<fbChunk> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<fbChunk>(end);
    return o;
  }
};

inline flatbuffers::Offset<fbChunk> CreatefbChunk(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::String> name = 0) {
  fbChunkBuilder builder_(_fbb);
  builder_.add_name(name);
  return builder_.Finish();
}

inline flatbuffers::Offset<fbChunk> CreatefbChunkDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const char *name = nullptr) {
  auto name__ = name ? _fbb.CreateString(name) : 0;
  return voxot::CreatefbChunk(
      _fbb,
      name__);
}

inline const voxot::fbChunk *GetfbChunk(const void *buf) {
  return flatbuffers::GetRoot<voxot::fbChunk>(buf);
}

inline const voxot::fbChunk *GetSizePrefixedfbChunk(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<voxot::fbChunk>(buf);
}

inline bool VerifyfbChunkBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<voxot::fbChunk>(nullptr);
}

inline bool VerifySizePrefixedfbChunkBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<voxot::fbChunk>(nullptr);
}

inline void FinishfbChunkBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<voxot::fbChunk> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedfbChunkBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<voxot::fbChunk> root) {
  fbb.FinishSizePrefixed(root);
}

}  // namespace voxot

#endif  // FLATBUFFERS_GENERATED_CHUNK_VOXOT_H_
