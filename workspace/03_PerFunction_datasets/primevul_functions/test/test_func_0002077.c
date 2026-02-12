DisjointSet<Handle>::GetMergedValue(Handle value) {
  Rep* rep = Find(value);
  if (!rep) {

    return HandleToObject<Handle>::Unknown();
  }
  return rep->value;
}
