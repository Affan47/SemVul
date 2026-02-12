TEST(HeaderMapImplTest, InlineAppend) {
  {
    TestRequestHeaderMapImpl headers;

    headers.setVia("");
    headers.appendVia("1.0 fred", ",");
    EXPECT_EQ(headers.getViaValue(), "1.0 fred");
    headers.appendVia("1.1 nowhere.com", ",");
    EXPECT_EQ(headers.getViaValue(), "1.0 fred,1.1 nowhere.com");
  }
  {

    TestRequestHeaderMapImpl headers;
    headers.appendVia("1.0 fred", ",");
    EXPECT_EQ(headers.getViaValue(), "1.0 fred");
    headers.appendVia("1.1 nowhere.com", ",");
    EXPECT_EQ(headers.getViaValue(), "1.0 fred,1.1 nowhere.com");
  }
  {

    TestRequestHeaderMapImpl headers;
    headers.setVia("");
    headers.appendVia("1.0 fred", ", ");
    EXPECT_EQ(headers.getViaValue(), "1.0 fred");
    headers.appendVia("1.1 nowhere.com", ", ");
    EXPECT_EQ(headers.getViaValue(), "1.0 fred, 1.1 nowhere.com");
  }
  {

    TestRequestHeaderMapImpl headers;
    headers.appendVia("1.0 fred", ",");
    headers.appendVia("1.1 nowhere.com", ",");
    EXPECT_EQ(headers.getViaValue(), "1.0 fred,1.1 nowhere.com");
    headers.setVia("2.0 override");
    EXPECT_EQ(headers.getViaValue(), "2.0 override");
  }
  {

    TestRequestHeaderMapImpl headers;
    headers.setGrpcTimeout(42);
    EXPECT_EQ(headers.getGrpcTimeoutValue(), "42");
    headers.appendGrpcTimeout("s", "");
    EXPECT_EQ(headers.getGrpcTimeoutValue(), "42s");
  }
}
