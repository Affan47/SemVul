TEST(HeaderMapImplTest, PseudoHeaderOrder) {
  HeaderAndValueCb cb;

  {
    LowerCaseString foo("hello");
    Http::TestRequestHeaderMapImpl headers{};
    EXPECT_EQ(0UL, headers.size());
    EXPECT_TRUE(headers.empty());

    headers.addReferenceKey(foo, "world");
    EXPECT_EQ(1UL, headers.size());
    EXPECT_FALSE(headers.empty());

    headers.setReferenceKey(Headers::get().ContentType, "text/html");
    EXPECT_EQ(2UL, headers.size());
    EXPECT_FALSE(headers.empty());


    headers.setReferenceKey(Headers::get().Method, "PUT");
    EXPECT_EQ(3UL, headers.size());
    EXPECT_FALSE(headers.empty());

    InSequence seq;
    EXPECT_CALL(cb, Call(":method", "PUT"));
    EXPECT_CALL(cb, Call("hello", "world"));
    EXPECT_CALL(cb, Call("content-type", "text/html"));

    headers.iterate(cb.asIterateCb());


    EXPECT_EQ(1UL, headers.remove(foo));
    EXPECT_EQ(2UL, headers.size());
    EXPECT_FALSE(headers.empty());

    EXPECT_CALL(cb, Call(":method", "PUT"));
    EXPECT_CALL(cb, Call("content-type", "text/html"));

    headers.iterate(cb.asIterateCb());


    headers.setReferenceKey(Headers::get().Path, "/test");
    EXPECT_EQ(3UL, headers.size());
    EXPECT_FALSE(headers.empty());

    EXPECT_CALL(cb, Call(":method", "PUT"));
    EXPECT_CALL(cb, Call(":path", "/test"));
    EXPECT_CALL(cb, Call("content-type", "text/html"));

    headers.iterate(cb.asIterateCb());


    EXPECT_EQ(1UL, headers.remove(Headers::get().ContentType));
    EXPECT_EQ(2UL, headers.size());
    EXPECT_FALSE(headers.empty());

    EXPECT_CALL(cb, Call(":method", "PUT"));
    EXPECT_CALL(cb, Call(":path", "/test"));

    headers.iterate(cb.asIterateCb());


    headers.setReferenceKey(Headers::get().Host, "host");
    EXPECT_EQ(3UL, headers.size());
    EXPECT_FALSE(headers.empty());

    EXPECT_CALL(cb, Call(":method", "PUT"));
    EXPECT_CALL(cb, Call(":path", "/test"));
    EXPECT_CALL(cb, Call(":authority", "host"));

    headers.iterate(cb.asIterateCb());


    headers.setReferenceKey(Headers::get().ContentType, "text/html");
    EXPECT_EQ(4UL, headers.size());
    EXPECT_FALSE(headers.empty());

    EXPECT_CALL(cb, Call(":method", "PUT"));
    EXPECT_CALL(cb, Call(":path", "/test"));
    EXPECT_CALL(cb, Call(":authority", "host"));
    EXPECT_CALL(cb, Call("content-type", "text/html"));

    headers.iterate(cb.asIterateCb());


    EXPECT_EQ(1UL, headers.remove(Headers::get().Path));
    EXPECT_EQ(1UL, headers.remove(Headers::get().Method));
    EXPECT_EQ(1UL, headers.remove(Headers::get().Host));
    EXPECT_EQ(1UL, headers.size());
    EXPECT_FALSE(headers.empty());

    EXPECT_CALL(cb, Call("content-type", "text/html"));

    headers.iterate(cb.asIterateCb());


    EXPECT_EQ(1UL, headers.remove(Headers::get().ContentType));
    EXPECT_EQ(0UL, headers.size());
    EXPECT_TRUE(headers.empty());


    headers.setReferenceKey(Headers::get().Status, "200");
    EXPECT_EQ(1UL, headers.size());
    EXPECT_FALSE(headers.empty());

    EXPECT_CALL(cb, Call(":status", "200"));

    headers.iterate(cb.asIterateCb());
  }


  {
    auto headers = TestRequestHeaderMapImpl({{Headers::get().ContentType.get(), "text/plain"},
                                             {Headers::get().Method.get(), "GET"},
                                             {Headers::get().Path.get(), "/"},
                                             {"hello", "world"},
                                             {Headers::get().Host.get(), "host"}});

    InSequence seq;
    EXPECT_CALL(cb, Call(":method", "GET"));
    EXPECT_CALL(cb, Call(":path", "/"));
    EXPECT_CALL(cb, Call(":authority", "host"));
    EXPECT_CALL(cb, Call("content-type", "text/plain"));
    EXPECT_CALL(cb, Call("hello", "world"));

    headers.iterate(cb.asIterateCb());
  }


  {
    auto headers = TestRequestHeaderMapImpl({{Headers::get().Path.get(), "/"},
                                             {Headers::get().ContentType.get(), "text/plain"},
                                             {Headers::get().Method.get(), "GET"},
                                             {"hello", "world"},
                                             {Headers::get().Host.get(), "host"}});

    InSequence seq;
    EXPECT_CALL(cb, Call(":path", "/"));
    EXPECT_CALL(cb, Call(":method", "GET"));
    EXPECT_CALL(cb, Call(":authority", "host"));
    EXPECT_CALL(cb, Call("content-type", "text/plain"));
    EXPECT_CALL(cb, Call("hello", "world"));

    headers.iterate(cb.asIterateCb());
  }
}
