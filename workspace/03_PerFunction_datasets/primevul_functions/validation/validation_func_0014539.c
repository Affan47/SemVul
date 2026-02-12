TEST_F(QueryPlannerTest, NaturalSortAndHint) {
    addIndex(BSON("x" << 1));


    runQuerySortHint(fromjson("{x: {$exists: true}}"), BSON("$natural" << -1), BSONObj());
    assertNumSolutions(1U);
    assertSolutionExists("{cscan: {dir: -1}}");


    runQuerySortHint(fromjson("{x: {$exists: true}}"), BSON("$natural" << 1), BSONObj());
    assertNumSolutions(1U);
    assertSolutionExists("{cscan: {dir: 1}}");


    runQuerySortHint(
        fromjson("{x: {$exists: true}}"), BSON("$natural" << -1), BSON("$natural" << -1));
    assertNumSolutions(1U);
    assertSolutionExists("{cscan: {dir: -1}}");


    runQuerySortHint(
        fromjson("{x: {$exists: true}}"), BSON("$natural" << 1), BSON("$natural" << 1));
    assertNumSolutions(1U);
    assertSolutionExists("{cscan: {dir: 1}}");


    runQuerySortHint(BSONObj(), BSON("$natural" << -1), BSONObj());
    assertNumSolutions(1U);
    assertSolutionExists("{cscan: {dir: -1}}");


    runQuerySortHint(BSONObj(), BSON("$natural" << 1), BSONObj());
    assertNumSolutions(1U);
    assertSolutionExists("{cscan: {dir: 1}}");


    runQuerySortHint(BSONObj(), BSON("$natural" << -1), BSON("$natural" << -1));
    assertNumSolutions(1U);
    assertSolutionExists("{cscan: {dir: -1}}");


    runQuerySortHint(BSONObj(), BSON("$natural" << 1), BSON("$natural" << 1));
    assertNumSolutions(1U);
    assertSolutionExists("{cscan: {dir: 1}}");
}
