TEST(HeaderMapImplTest, SetCopyNewBehavior) {
  TestRequestHeaderMapImpl headers;
  LowerCaseString foo("hello");
  headers.setCopy(foo, "world");
  EXPECT_EQ("world", headers.get(foo)->value().getStringView());


  headers.setCopy(foo, "monde");
  EXPECT_EQ("monde", headers.get(foo)->value().getStringView());


  headers.addCopy(foo, "monde2");
  EXPECT_EQ(headers.size(), 2);


  headers.setCopy(foo, "override-monde");
  EXPECT_EQ(headers.size(), 1);

  HeaderAndValueCb cb;

  InSequence seq;
  EXPECT_CALL(cb, Call("hello", "override-monde"));
  headers.iterate(cb.asIterateCb());


  EXPECT_EQ(1UL, headers.remove(foo));
  EXPECT_EQ(headers.size(), 0);
  const std::string empty;
  headers.setCopy(foo, empty);
  EXPECT_EQ(headers.size(), 1);
  headers.setCopy(foo, "not-empty");
  EXPECT_EQ(headers.get(foo)->value().getStringView(), "not-empty");


  headers.clear();
  EXPECT_EQ(headers.size(), 0);
  headers.setCopy(Headers::get().Path, "/");
  EXPECT_EQ(headers.size(), 1);
  EXPECT_EQ(headers.getPathValue(), "/");
  headers.setPath("/foo");
  EXPECT_EQ(headers.size(), 1);
  EXPECT_EQ(headers.getPathValue(), "/foo");
}
