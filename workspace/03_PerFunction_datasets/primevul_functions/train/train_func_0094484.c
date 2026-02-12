TEST(Random, FixedSeed) {

  struct ConstantRNG {
    typedef uint32_t result_type;
    result_type operator()() {
      return 4;

    }
    static constexpr result_type min() {
      return std::numeric_limits<result_type>::min();
    }
    static constexpr result_type max() {
      return std::numeric_limits<result_type>::max();
    }
  };


  ConstantRNG gen;


  auto value = Random::rand32(10, gen);


  for (int i = 0; i < 1024; ++i) {
    auto result = Random::rand32(10, gen);
    EXPECT_EQ(value, result);
  }
}
