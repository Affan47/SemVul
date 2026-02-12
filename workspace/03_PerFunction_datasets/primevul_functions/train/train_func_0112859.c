inline float uint2float(const unsigned int u) {
      if (u<(1U<<19)) return (float)u;
      float f;
      const unsigned int v = u|(1U<<(8*sizeof(unsigned int)-1));

      std::memcpy(&f,&v,sizeof(float));
      return f;
}
