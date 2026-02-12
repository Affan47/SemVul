static inline JsonNode* json_mkstream(const std::stringstream& stream)
  {

    std::string str(stream.str());
    return json_mkstring(str.c_str());
  }
