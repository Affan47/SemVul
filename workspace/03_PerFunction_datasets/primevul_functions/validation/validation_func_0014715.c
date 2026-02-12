TEST_F(QueryPlannerTest, CannotSnapshotWithGeoNear) {

    addIndex(BSON("a"
                  << "2d"));
    runQuerySnapshot(fromjson("{a: {$near: [0,0]}}"));

    ASSERT_EQUALS(getNumSolutions(), 1U);
    assertSolutionExists("{geoNear2d: {a: '2d'}}");
}
