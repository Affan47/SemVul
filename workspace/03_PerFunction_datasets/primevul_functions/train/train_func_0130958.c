TEST(ExpressionFromAccumulators, StdDevSamp) {
    assertExpectedResults(
        "$stdDevSamp",
        {
         {{Value("string"_sd), Value(BSONNULL), Value(), Value(3)}, Value(BSONNULL)},

         {{Value(1LL), Value(2LL), Value(3LL)}, Value(1.0)},

         {{}, Value(BSONNULL)}});
}
