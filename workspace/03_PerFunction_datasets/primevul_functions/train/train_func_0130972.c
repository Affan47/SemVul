TEST(FieldPath, NoOptimizationForRootFieldPathWithDottedPath) {
    intrusive_ptr<ExpressionContextForTest> expCtx(new ExpressionContextForTest());
    intrusive_ptr<ExpressionFieldPath> expression =
        ExpressionFieldPath::parse(expCtx, "$$ROOT.x.y", expCtx->variablesParseState);


    ASSERT_EQUALS(expression, expression->optimize());
}
