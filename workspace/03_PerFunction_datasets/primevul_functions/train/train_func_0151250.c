TEST(HeaderMapImplTest, InlineHeaderByteSize) {
  {
    TestRequestHeaderMapImpl headers;
    std::string foo = "foo";
    headers.setHost(foo);
    EXPECT_EQ(headers.byteSize(), 13);
  }
  {

    TestRequestHeaderMapImpl headers;
    std::string foo = "foo";
    headers.setHost(foo);
    std::string big_foo = "big_foo";
    headers.setHost(big_foo);
    EXPECT_EQ(headers.byteSize(), 17);
  }
  {

    TestRequestHeaderMapImpl headers;
    std::string foo = "foo";
    headers.setHost(foo);
    EXPECT_EQ(headers.byteSize(), 13);
    std::string big_foo = "big_foo";
    headers.setReferenceHost(big_foo);
    EXPECT_EQ(headers.byteSize(), 17);
    EXPECT_EQ(1UL, headers.removeHost());
    EXPECT_EQ(headers.byteSize(), 0);
  }
  {

    TestResponseHeaderMapImpl headers;
    uint64_t status = 200;
    headers.setStatus(status);
    EXPECT_EQ(headers.byteSize(), 10);
    uint64_t newStatus = 500;
    headers.setStatus(newStatus);
    EXPECT_EQ(headers.byteSize(), 10);
    EXPECT_EQ(1UL, headers.removeStatus());
    EXPECT_EQ(headers.byteSize(), 0);
  }
  {

    TestResponseHeaderMapImpl headers;
    uint64_t status = 200;
    headers.setStatus(status);
    EXPECT_EQ(headers.byteSize(), 10);
    EXPECT_EQ(1UL, headers.removeStatus());
    EXPECT_EQ(headers.byteSize(), 0);
    uint64_t newStatus = 500;
    headers.setStatus(newStatus);
    EXPECT_EQ(headers.byteSize(), 10);
  }
}
