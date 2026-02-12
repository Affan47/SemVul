TEST_F(AsStringGraphTest, NoShortestForNonFloat) {
  Status s = Init(DT_INT32, "", -1, -1,
                  false, true);
  ASSERT_EQ(error::INVALID_ARGUMENT, s.code());
  ASSERT_TRUE(absl::StrContains(
      s.error_message(),
      "scientific and shortest format not supported for datatype"));
}
