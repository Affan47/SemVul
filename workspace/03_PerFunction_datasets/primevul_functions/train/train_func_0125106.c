TEST(BSONValidateFast, StringHasSomething) {
        BufBuilder bb;
        BSONObjBuilder ob(bb);
        bb.appendChar(String);
        bb.appendStr("x", true);
        bb.appendNum(0);
        const BSONObj x = ob.done();
        ASSERT_EQUALS(5
                      + 1
                      + 2
                      + 4
                      , x.objsize());
        ASSERT_NOT_OK(validateBSON(x.objdata(), x.objsize()));
    }
