TEST_F(QueryPlannerTest, IndexBoundsAndWithNestedOr) {
    addIndex(BSON("a" << 1));
    runQuery(fromjson("{$and: [{a: 1, $or: [{a: 2}, {a: 3}]}]}"));


    size_t matches = 0;
    matches += numSolutionMatches(
        "{cscan: {dir: 1, filter: "
        "{$or: [{a: 2, a:1}, {a: 3, a:1}]}}}");
    matches += numSolutionMatches(
        "{cscan: {dir: 1, filter: "
        "{$and: [{$or: [{a: 2}, {a: 3}]}, {a: 1}]}}}");
    ASSERT_GREATER_THAN_OR_EQUALS(matches, 1U);
}
