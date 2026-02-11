operator[](const std::string &key)
    {
        auto ourKey = std::string(key[0] == '.' ? key : "." + key);
        std::transform(ourKey.begin(), ourKey.end(), ourKey.begin(), tolower);

        auto entry = mimeTypes_.find(ourKey);
        if (entry == mimeTypes_.end()) {
            return defaultMimeType_;
        }

        return entry->second;
    }
