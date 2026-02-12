
    CImg<T>& load_analyze(std::FILE *const file, float *const voxel_size=0) {
      return _load_analyze(file,0,voxel_size);
}
