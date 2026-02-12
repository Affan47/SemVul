TEST_F(QueryPlannerTest, OrEnumerationLimit2) {
    params.options = QueryPlannerParams::NO_TABLE_SCAN;
    addIndex(BSON("a" << 1));
    addIndex(BSON("b" << 1));
    addIndex(BSON("c" << 1));
    addIndex(BSON("d" << 1));


    runQuery(
        fromjson("{$or: [{a: 1, b: 1, c: 1, d: 1},"
                 "{a: 2, b: 2, c: 2, d: 2},"
                 "{a: 3, b: 3, c: 3, d: 3}]}"));

    assertNumSolutions(internalQueryEnumerationMaxOrSolutions.load());
}
