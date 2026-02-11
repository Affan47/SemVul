CanReadFile(const std::string& filename)
  {
    bool isReadable = true;
    NativeBinaryFileStream ifs(filename, BinaryFileStream::In);
    if ((ifs.ReadI8() <= 0) || (ifs.ReadI8() != 80))
      isReadable = false;
    ifs.Close();
    return isReadable;
  }
