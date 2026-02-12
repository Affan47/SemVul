static std::string make_relative_path(const std::string& path) {
  if (path.empty()) {
    return path;
  }


  std::string canonical(FileUtil::canonicalize(path));


  if (FileUtil::isDirSeparator(canonical[0])) {
    return canonical.substr(1);
  }


  std::string relative(canonical);
  int idx = canonical.length() - 1;
  while (1) {
    while (idx > 0 && !(FileUtil::isDirSeparator(canonical[idx]))) {
      idx--;
    }

    if (idx == 0) {
      return canonical;
    }
    if (idx >= 1 && (canonical[idx - 1] == '.' || canonical[idx - 1] == ':')) {
      relative = canonical.substr(idx + 1);
      break;
    }
    idx--;
  }
  return relative;
}
