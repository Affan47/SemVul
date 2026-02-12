int find(const ByteVectorMirror &pattern, uint offset = 0, int byteAlign = 1) const
    {
      ByteVectorMirror v(*this);

      if(offset > 0) {
        offset = size() - offset - pattern.size();
        if(offset >= size())
          offset = 0;
      }

      const int pos = vectorFind<ByteVectorMirror>(v, pattern, offset, byteAlign);


      if(pos == -1)
        return -1;

      return size() - pos - pattern.size();
    }
