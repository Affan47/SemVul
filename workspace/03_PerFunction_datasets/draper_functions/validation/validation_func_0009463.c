Init(uint32_t seed) {

  if (seed != 0) {
    rnd_ = seed;
  } else {
    rnd_ = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(this));
    if (rnd_ == 0) {
      rnd_ = 1;
    }
  }

  for (int i = 0; i < 20; i++) {
    rnd_ = NextRandom(rnd_);
  }

  bytes_until_sample_ = PickNextSamplingPoint();
}
