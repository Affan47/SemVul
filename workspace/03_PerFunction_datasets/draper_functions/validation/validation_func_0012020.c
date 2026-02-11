encode(const FilterChar * in, const FilterChar * stop,
                CharVector & out) const {
      for (; in != stop; ++in) {
        out.append(lookup(*in));
      }
    }
