TEST_F(QueryPlannerTest, MaxMinBadHintSelectsReverseIndex) {

    addIndex(BSON("a" << 1));
    addIndex(BSON("a" << -1));


    runInvalidQueryFull(BSONObj(),
                        BSONObj(),
                        BSONObj(),
                        0,
                        0,
                        fromjson("{a: 1}"),
                        fromjson("{a: 8}"),
                        fromjson("{a: 2}"),
                        false);
}
