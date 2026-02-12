TEST(ExprMatchTest, IdenticalPostOptimizedExpressionsAreEquivalent) {
    BSONObj expression = BSON("$expr" << BSON("$multiply" << BSON_ARRAY(2 << 2)));
    BSONObj expressionEquiv = BSON("$expr" << BSON("$const" << 4));
    BSONObj expressionNotEquiv = BSON("$expr" << BSON("$const" << 10));


    const boost::intrusive_ptr<ExpressionContextForTest> expCtx(new ExpressionContextForTest());
    std::unique_ptr<MatchExpression> matchExpr =
        stdx::make_unique<ExprMatchExpression>(expression.firstElement(), expCtx);
    matchExpr = MatchExpression::optimize(std::move(matchExpr));


    std::unique_ptr<ExprMatchExpression> pipelineExpr(
        dynamic_cast<ExprMatchExpression*>(matchExpr.release()));
    ASSERT_TRUE(pipelineExpr);

    ASSERT_TRUE(pipelineExpr->equivalent(pipelineExpr.get()));

    ExprMatchExpression pipelineExprEquiv(expressionEquiv.firstElement(), expCtx);
    ASSERT_TRUE(pipelineExpr->equivalent(&pipelineExprEquiv));

    ExprMatchExpression pipelineExprNotEquiv(expressionNotEquiv.firstElement(), expCtx);
    ASSERT_FALSE(pipelineExpr->equivalent(&pipelineExprNotEquiv));
}
