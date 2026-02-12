TEST_F(QueryPlannerTest, SkipEvaluatesAfterFetchWithPredicate) {
    addIndex(fromjson("{a: 1}"));

    runQuerySkipNToReturn(fromjson("{a: 5, b: 7}"), 8, 0);

    ASSERT_EQUALS(getNumSolutions(), 2U);
    assertSolutionExists("{skip: {n: 8, node: {cscan: {dir: 1, filter: {a: 5, b: 7}}}}}");


    assertSolutionExists(
        "{skip: {n: 8, node: {fetch: {filter: {b: 7}, node: "
        "{ixscan: {filter: null, pattern: {a: 1}}}}}}}");
}
