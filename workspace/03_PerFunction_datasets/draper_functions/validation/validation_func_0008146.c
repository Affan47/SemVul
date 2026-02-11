decode(const char * in, int size, FilterCharVector & out) const {
      if (size == -1) {
        for (;*in; ++in)
          out.append(lookup[*in]);
      } else {
        const char * stop = in + size;
        for (;in != stop; ++in)
          out.append(lookup[*in]);
      }
    }
