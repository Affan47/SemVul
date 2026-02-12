TEST(ExpressionFromAccumulators, Sum) {
    assertExpectedResults(
        "$sum",
        {
         {{Value("string"_sd), Value(BSONNULL), Value(), Value(3)}, Value(3)},

         {{Value(10LL), Value(10.0)}, Value(20.0)},

         {{Value(10LL), Value(10)}, Value(20LL)},

         {{}, Value(0)}});
}
