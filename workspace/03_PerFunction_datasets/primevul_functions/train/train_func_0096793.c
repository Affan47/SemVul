Status GetMatchingPaths(FileSystem* fs, Env* env, const string& pattern,
                        std::vector<string>* results) {

  if (fs == nullptr || env == nullptr || results == nullptr) {
    return Status(tensorflow::error::INVALID_ARGUMENT,
                  "Filesystem calls GetMatchingPaths with nullptr arguments");
  }


  results->clear();
  if (pattern.empty()) {
    return Status::OK();
  }


  std::vector<std::string> dirs = AllDirectoryPrefixes(pattern);


  int matching_index = GetFirstGlobbingEntry(dirs);


  if (matching_index == dirs.size()) {
    if (fs->FileExists(pattern).ok()) {
      results->emplace_back(pattern);
    }
    return Status::OK();
  }


  std::deque<std::pair<string, int>> expand_queue;
  std::deque<std::pair<string, int>> next_expand_queue;
  expand_queue.emplace_back(dirs[matching_index - 1], matching_index - 1);


  mutex result_mutex;
  mutex queue_mutex;

  while (!expand_queue.empty()) {
    next_expand_queue.clear();


    auto handle_level = [&fs, &results, &dirs, &expand_queue,
                         &next_expand_queue, &result_mutex,
                         &queue_mutex](int i) {

      const auto& queue_item = expand_queue.at(i);
      const std::string& parent = queue_item.first;
      const int index = queue_item.second + 1;
      const std::string& match_pattern = dirs[index];


      std::vector<std::string> children;
      Status s = fs->GetChildren(parent, &children);
      if (s.code() == tensorflow::error::PERMISSION_DENIED) {
        return;
      }


      if (children.empty()) {
        return;
      }


      std::vector<Status> children_status(children.size());
      auto handle_children = [&fs, &match_pattern, &parent, &children,
                              &children_status](int j) {
        const std::string path = io::JoinPath(parent, children[j]);
        if (!fs->Match(path, match_pattern)) {
          children_status[j] =
              Status(tensorflow::error::CANCELLED, "Operation not needed");
        } else {
          children_status[j] = fs->IsDirectory(path);
        }
      };
      ForEach(0, children.size(), handle_children);


      for (size_t j = 0; j < children.size(); j++) {
        if (children_status[j].code() == tensorflow::error::CANCELLED) {
          continue;
        }

        const std::string path = io::JoinPath(parent, children[j]);
        if (index == dirs.size() - 1) {
          mutex_lock l(result_mutex);
          results->emplace_back(path);
        } else if (children_status[j].ok()) {
          mutex_lock l(queue_mutex);
          next_expand_queue.emplace_back(path, index);
        }
      }
    };
    ForEach(0, expand_queue.size(), handle_level);


    std::swap(expand_queue, next_expand_queue);
  }

  return Status::OK();
}
