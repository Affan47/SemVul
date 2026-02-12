TEST(ExpressionFromAccumulators, Max) {
    assertExpectedResults("$max",
                          {
                           {{Value(1), Value(BSONNULL), Value(), Value("a"_sd)}, Value("a"_sd)},
                           {{Value("a"_sd), Value("b"_sd)}, Value("b"_sd)},

                           {{Value(10LL), Value(0.0), Value(5)}, Value(10LL)},

                           {{}, Value(BSONNULL)}});
}
