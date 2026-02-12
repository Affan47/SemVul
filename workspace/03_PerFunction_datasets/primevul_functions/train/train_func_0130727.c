TEST(ParseObject, ShouldRecognizeKnownExpression) {
    auto resultExpression = parseObject(BSON("$and" << BSONArray()));


    auto resultAnd = dynamic_cast<ExpressionAnd*>(resultExpression.get());
    ASSERT_TRUE(resultAnd);
}
