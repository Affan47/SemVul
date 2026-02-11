file_exist(const char *filename)
{
  std::ifstream infile(filename, std::ios::binary);
  return infile.good();
}
