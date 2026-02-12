TEST(ExpressionFromAccumulators, StdDevPop) {
    assertExpectedResults("$stdDevPop",
                          {
                           {{Value("string"_sd), Value(BSONNULL), Value(), Value(3)}, Value(0.0)},

                           {{Value(1LL), Value(3LL)}, Value(1.0)},

                           {{}, Value(BSONNULL)}});
}
