inline SegmentBuilder::SegmentBuilder(
    BuilderArena* arena, SegmentId id, const word* ptr, SegmentWordCount size,
    ReadLimiter* readLimiter)
    : SegmentReader(arena, id, ptr, size, readLimiter),


      pos(const_cast<word*>(ptr + size)), readOnly(true) {}
