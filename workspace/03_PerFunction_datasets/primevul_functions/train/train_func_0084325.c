TEST(TensorSliceTest, UpdateToCover) {

  TensorSlice s({{2, 2}, {0, -1}, {3, 7}});

  TensorSlice other({{0, -1}, {1, 3}, {2, 2}});

  s.UpdateToCover(other);

  EXPECT_EQ("-:-:2,8", s.DebugString());
}
