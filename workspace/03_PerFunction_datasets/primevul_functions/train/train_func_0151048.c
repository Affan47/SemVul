TEST(HeaderMapImplTest, RemoveHost) {
  TestRequestHeaderMapImpl headers;
  headers.setHost("foo");
  EXPECT_EQ("foo", headers.get_("host"));
  EXPECT_EQ("foo", headers.get_(":authority"));


  EXPECT_EQ(1UL, headers.remove("host"));
  EXPECT_EQ("", headers.get_("host"));
  EXPECT_EQ("", headers.get_(":authority"));
  EXPECT_EQ(nullptr, headers.Host());
}
