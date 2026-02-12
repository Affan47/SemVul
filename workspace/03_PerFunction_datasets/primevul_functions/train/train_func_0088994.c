TEST(WriterTest, MoveCtor) {
  MemoryWriter w;
  w << "test";
  check_move_writer("test", w);

  std::string s;
  for (int i = 0; i < fmt::internal::INLINE_BUFFER_SIZE; ++i)
    s += '*';
  w.clear();
  w << s;
  check_move_writer(s, w);
  const char *inline_buffer_ptr = w.data();


  w << '*';
  MemoryWriter w2(std::move(w));

  EXPECT_EQ(inline_buffer_ptr, w.data());
  EXPECT_EQ(s + '*', w2.str());
}
