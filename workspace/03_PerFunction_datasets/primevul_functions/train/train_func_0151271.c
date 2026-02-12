TEST(HeaderIsValidTest, InvalidHeaderValuesAreRejected) {


  for (int i = 0; i < 32; i++) {
    if (i == 9) {
      continue;
    }

    EXPECT_FALSE(HeaderUtility::headerValueIsValid(std::string(1, i)));
  }
}
