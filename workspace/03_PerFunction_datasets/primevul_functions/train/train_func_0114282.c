
    inline unsigned int float2uint(const float f) {
      int tmp = 0;
      std::memcpy(&tmp,&f,sizeof(float));
      if (tmp>=0) return (unsigned int)f;
      unsigned int u;

      std::memcpy(&u,&f,sizeof(float));
      return ((u)<<1)>>1;
}
