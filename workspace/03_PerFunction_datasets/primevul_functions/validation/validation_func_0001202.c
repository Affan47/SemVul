bool operator()(const StringData* s1, const StringData* s2) {

      return int64_t(s1) > 0 && (s1 == s2 || s1->same(s2));
    }
