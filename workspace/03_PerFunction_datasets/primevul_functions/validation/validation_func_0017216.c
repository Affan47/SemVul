TEST_F(QueryPlannerTest, MaxMinSelectCorrectlyOrderedIndex) {

    addIndex(BSON("a" << 1));
    addIndex(BSON("a" << -1));


    runQueryFull(
        BSONObj(), BSONObj(), BSONObj(), 0, 0, BSONObj(), fromjson("{a: 8}"), fromjson("{a: 2}"));

    assertNumSolutions(1);
    assertSolutionExists("{fetch: {node: {ixscan: {filter: null, dir: 1, pattern: {a: -1}}}}}");


    runQueryFull(
        BSONObj(), BSONObj(), BSONObj(), 0, 0, BSONObj(), fromjson("{a: 2}"), fromjson("{a: 8}"));

    assertNumSolutions(1);
    assertSolutionExists("{fetch: {node: {ixscan: {filter: null, dir: 1, pattern: {a: 1}}}}}");
}
