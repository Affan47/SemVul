TEST_F(QueryPlannerTest, InSparseIndex) {
    addIndex(fromjson("{a: 1}"),
             false,
             true);
    runQuery(fromjson("{a: {$in: [null]}}"));

    assertNumSolutions(1U);
    assertSolutionExists("{cscan: {dir: 1, filter: {a: {$eq: null}}}}");
}
