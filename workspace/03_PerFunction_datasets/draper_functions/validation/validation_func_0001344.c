SourceHash() {
  uint32_t hash = 0;
  Object* script = shared()->script();
  if (!script->IsUndefined()) {
    Object* source = Script::cast(script)->source();
    if (source->IsUndefined()) hash = String::cast(source)->Hash();
  }
  hash ^= ComputeIntegerHash(shared()->start_position_and_type());
  hash += ComputeIntegerHash(shared()->end_position());
  return hash;
}
