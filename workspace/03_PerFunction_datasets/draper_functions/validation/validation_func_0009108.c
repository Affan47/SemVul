FindFiles() {
    std::vector<std::string> filenames;
    Status status = env_->GetChildren(dbname_, &filenames);
    if (!status.ok()) {
      return status;
    }
    if (filenames.empty()) {
      return Status::IOError(dbname_, "repair found no files");
    }

    uint64_t number;
    FileType type;
    for (size_t i = 0; i < filenames.size(); i++) {
      if (ParseFileName(filenames[i], &number, &type)) {
        if (type == kDescriptorFile) {
          manifests_.push_back(filenames[i]);
        } else {
          if (number + 1 > next_file_number_) {
            next_file_number_ = number + 1;
          }
          if (type == kLogFile) {
            logs_.push_back(number);
          } else if (type == kTableFile) {
            table_numbers_.push_back(number);
          } else {

          }
        }
      }
    }
    return status;
  }
