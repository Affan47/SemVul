TEST(ExprMatchTest, OptimizingIsANoopWhenAlreadyOptimized) {
    const boost::intrusive_ptr<ExpressionContextForTest> expCtx(new ExpressionContextForTest());
    BSONObj expression = fromjson("{$expr: {$eq: ['$a', 4]}}");


    std::unique_ptr<MatchExpression> singlyOptimized =
        stdx::make_unique<ExprMatchExpression>(expression.firstElement(), expCtx);
    singlyOptimized = MatchExpression::optimize(std::move(singlyOptimized));


    ASSERT(dynamic_cast<const AndMatchExpression*>(singlyOptimized.get()));


    std::unique_ptr<MatchExpression> doublyOptimized =
        stdx::make_unique<ExprMatchExpression>(expression.firstElement(), expCtx);
    for (size_t i = 0; i < 2u; ++i) {
        doublyOptimized = MatchExpression::optimize(std::move(doublyOptimized));
    }
    ASSERT_TRUE(doublyOptimized->equivalent(singlyOptimized.get()));
}
