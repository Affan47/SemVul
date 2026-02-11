CreateDirectoriesRecursively() const {
  if (!this->IsDirectory()) {
    return false;
  }

  if (pathname_.length() == 0 || this->DirectoryExists()) {
    return true;
  }

  const FilePath parent(this->RemoveTrailingPathSeparator().RemoveFileName());
  return parent.CreateDirectoriesRecursively() && this->CreateFolder();
}
