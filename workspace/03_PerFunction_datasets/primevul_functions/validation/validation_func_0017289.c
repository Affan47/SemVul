TEST_F(QueryPlannerTest, MaxMinSortEqualityFirstSortSecond) {
    addIndex(BSON("a" << 1 << "b" << 1));


    runQueryFull(BSONObj(),
                 fromjson("{b: 1}"),
                 BSONObj(),
                 0,
                 0,
                 BSONObj(),
                 fromjson("{a: 1, b: 1}"),
                 fromjson("{a: 1, b: 2}"));

    assertNumSolutions(1);
    assertSolutionExists("{fetch: {node: {ixscan: {filter: null, pattern: {a: 1, b: 1}}}}}");
}
