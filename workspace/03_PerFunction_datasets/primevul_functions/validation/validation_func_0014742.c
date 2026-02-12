TEST_F(QueryPlannerTest, InvalidUtf8CodePointDoesNotLeadToInvalidIndexBoundsInvariantFailure) {
    params.options &= ~QueryPlannerParams::INCLUDE_COLLSCAN;
    addIndex(BSON("a" << 1));


    auto invalidCodePoint = std::string{"\xf4\x90\x80\x80"};
    auto findCommandWithInvalidCodepoint = BSON("find"
                                                << "testns"
                                                << "filter"
                                                << BSON("a" << BSON("$regex" << invalidCodePoint)));
    runQueryAsCommand(findCommandWithInvalidCodepoint);
}
