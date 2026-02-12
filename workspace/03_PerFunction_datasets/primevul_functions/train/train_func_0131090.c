TEST_F(DateExpressionTest, DoesRespectTimeZone) {

    auto expCtx = getExpCtx();
    for (auto&& expName : dateExpressions) {
        auto spec = BSON(expName << BSON("date" << Date_t{} << "timezone"
                                                << "America/New_York"));
        auto dateExp = Expression::parseExpression(expCtx, spec, expCtx->variablesParseState);
        auto contextDoc = Document{{"_id", 0}};
        dateExp->evaluate(contextDoc);
    }


    auto date = Date_t::fromMillisSinceEpoch(1496777923000LL);
    auto specWithoutTimezone = BSON("$hour" << BSON("date" << date));
    auto hourWithoutTimezone =
        Expression::parseExpression(expCtx, specWithoutTimezone, expCtx->variablesParseState)
            ->evaluate({});
    ASSERT_VALUE_EQ(hourWithoutTimezone, Value(19));

    auto specWithTimezone = BSON("$hour" << BSON("date" << date << "timezone"
                                                        << "America/New_York"));
    auto hourWithTimezone =
        Expression::parseExpression(expCtx, specWithTimezone, expCtx->variablesParseState)
            ->evaluate({});
    ASSERT_VALUE_EQ(hourWithTimezone, Value(15));
}
