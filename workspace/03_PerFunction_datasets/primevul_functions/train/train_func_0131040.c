TEST(ExpressionFromAccumulators, Avg) {
    assertExpectedResults("$avg",
                          {
                           {{Value("string"_sd), Value(BSONNULL), Value(), Value(3)}, Value(3.0)},

                           {{Value(10LL), Value(20LL)}, Value(15.0)},

                           {{}, Value(BSONNULL)}});
}
