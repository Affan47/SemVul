CalculateRetainingPaths() {
  List<HeapGraphPath*>* retaining_paths = new List<HeapGraphPath*>(4);
  CachedHeapGraphPath path;
  FindRetainingPaths(&path, retaining_paths);
  return retaining_paths;
}
