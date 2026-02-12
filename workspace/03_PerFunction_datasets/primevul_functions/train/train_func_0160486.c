TEST(ExprMatchTest, OptimizingAnAlreadyOptimizedCloneIsANoop) {
    const boost::intrusive_ptr<ExpressionContextForTest> expCtx(new ExpressionContextForTest());
    BSONObj expression = fromjson("{$expr: {$eq: ['$a', 4]}}");


    std::unique_ptr<MatchExpression> singlyOptimized =
        stdx::make_unique<ExprMatchExpression>(expression.firstElement(), expCtx);
    singlyOptimized = MatchExpression::optimize(std::move(singlyOptimized));


    ASSERT(dynamic_cast<const AndMatchExpression*>(singlyOptimized.get()));


    std::unique_ptr<MatchExpression> doublyOptimized = singlyOptimized->shallowClone();
    doublyOptimized = MatchExpression::optimize(std::move(doublyOptimized));
    ASSERT_TRUE(doublyOptimized->equivalent(singlyOptimized.get()));
}
