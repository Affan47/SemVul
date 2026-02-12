TEST_F(QueryPlannerTest, NoFetchNoKeep) {
    params.options = QueryPlannerParams::KEEP_MUTATIONS;
    addIndex(BSON("x" << 1));

    runQuerySortProj(fromjson("{ x : {$gt: 1}}"), BSONObj(), fromjson("{_id: 0, x: 1}"));


    ASSERT_EQUALS(getNumSolutions(), 1U);
    assertSolutionExists(
        "{proj: {spec: {_id: 0, x: 1}, node: {ixscan: "
        "{filter: null, pattern: {x: 1}}}}}");
}
