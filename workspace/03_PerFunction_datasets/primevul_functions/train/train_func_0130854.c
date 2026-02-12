void run() {
        OptimizeBase::run();
        BSONObj specObject = BSON("" << spec());
        BSONElement specElement = specObject.firstElement();
        intrusive_ptr<ExpressionContextForTest> expCtx(new ExpressionContextForTest());
        VariablesParseState vps = expCtx->variablesParseState;
        intrusive_ptr<Expression> expression = Expression::parseOperand(expCtx, specElement, vps);

        ASSERT_BSONOBJ_EQ(constify(spec()), expressionToBson(expression));

        ASSERT_BSONOBJ_EQ(expectedResult(), toBson(expression->evaluate(Document())));

        intrusive_ptr<Expression> optimized = expression->optimize();
        ASSERT_BSONOBJ_EQ(expectedResult(), toBson(optimized->evaluate(Document())));
    }
