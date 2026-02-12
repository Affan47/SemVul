TEST(ExpressionFromAccumulators, Min) {
    assertExpectedResults("$min",
                          {
                           {{Value("string"_sd)}, Value("string"_sd)},
                           {{Value(1), Value(BSONNULL), Value(), Value("a"_sd)}, Value(1)},
                           {{Value("a"_sd), Value("b"_sd)}, Value("a"_sd)},

                           {{Value(0LL), Value(20.0), Value(10)}, Value(0LL)},

                           {{}, Value(BSONNULL)}});
}
