TEST_F(AsStringGraphTest, OnlyOneOfScientificAndShortest) {
  Status s = Init(DT_FLOAT, "", -1, -1,
                  true, true);
  ASSERT_EQ(error::INVALID_ARGUMENT, s.code());
  ASSERT_TRUE(
      absl::StrContains(s.error_message(),
                        "Cannot select both scientific and shortest notation"));
}
