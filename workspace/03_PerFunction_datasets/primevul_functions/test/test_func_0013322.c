Name deduplicate(Name base) {
    Name name = base;

    for (int i = 1; !usedNames.insert(name).second; ++i) {
      name = std::string(base.str) + std::string(".") + std::to_string(i);
    }
    return name;
  }
