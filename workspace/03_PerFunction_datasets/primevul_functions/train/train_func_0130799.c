TEST(ExpressionPowTest, LargeExponentValuesWithBaseOfZero) {
    assertExpectedResults(
        "$pow",
        {
            {{Value(0), Value(0)}, Value(1)},
            {{Value(0LL), Value(0LL)}, Value(1LL)},

            {{Value(0), Value(10)}, Value(0)},
            {{Value(0), Value(10000)}, Value(0)},

            {{Value(0LL), Value(10)}, Value(0LL)},


            {{Value(0LL), Value(std::numeric_limits<long long>::max())}, Value(0LL)},
        });
}
