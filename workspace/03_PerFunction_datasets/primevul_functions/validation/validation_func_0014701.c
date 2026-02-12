TEST_F(QueryPlannerTest, UniqueIndexLookup) {
    params.options = QueryPlannerParams::INDEX_INTERSECTION;
    params.options |= QueryPlannerParams::NO_TABLE_SCAN;

    addIndex(BSON("a" << 1));
    addIndex(BSON("b" << 1),
             false,
             false,
             true);

    runQuery(fromjson("{a: 1, b: 1}"));

    assertNumSolutions(1U);
    assertSolutionExists(
        "{fetch: {filter: {a: 1}, node: "
        "{ixscan: {filter: null, pattern: {b: 1}}}}}");
}
