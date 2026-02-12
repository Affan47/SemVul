TEST_F(QueryPlannerTest, MaxMinReverseIndexDir) {
    addIndex(BSON("a" << -1));


    runQueryFull(BSONObj(),
                 fromjson("{a: -1}"),
                 BSONObj(),
                 0,
                 0,
                 BSONObj(),
                 fromjson("{a: 8}"),
                 fromjson("{a: 2}"),
                 false);

    assertNumSolutions(1);
    assertSolutionExists("{fetch: {node: {ixscan: {filter: null, dir: 1, pattern: {a: -1}}}}}");
}
