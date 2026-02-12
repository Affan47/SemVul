static std::vector<std::string> AllDirectoryPrefixes(const std::string& d) {
  std::vector<std::string> dirs;
  const std::string patched = PatchPattern(d);
  StringPiece dir(patched);


  bool is_directory = d[d.size() - 1] == '/';
#ifdef PLATFORM_WINDOWS
  is_directory = is_directory || (d[d.size() - 1] == '\\');
#endif
  if (is_directory) {
    dir = io::Dirname(dir);
  }

  while (!dir.empty()) {
    dirs.emplace_back(dir);
    StringPiece new_dir(io::Dirname(dir));


    if (dir == new_dir) break;
    dir = new_dir;
  }


  std::reverse(dirs.begin(), dirs.end());

  return dirs;
}
