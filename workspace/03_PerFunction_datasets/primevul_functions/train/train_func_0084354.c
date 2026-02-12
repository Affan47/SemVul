TEST(TensorSliceTest, SliceTensorShape) {

  {
    TensorSlice a = TensorSlice::ParseOrDie("1,1:-:4,1:2,6");
    TensorShape x({2, 4, 5, 8});
    TensorShape y;
    TF_EXPECT_OK(a.SliceTensorShape(x, &y));
    EXPECT_EQ("[1,4,1,6]", y.DebugString());
  }


  {
    TensorSlice a = TensorSlice::ParseOrDie("1,1:1,4:-:-");
    TensorShape x({2, 4, 5, 8});
    TensorShape y;
    Status s = a.SliceTensorShape(x, &y);
    EXPECT_EQ(s.code(), error::INTERNAL);
    EXPECT_TRUE(absl::StrContains(s.error_message(),
                                  "Extent in dimension 1 out of bounds: "
                                  "shape = [2,4,5,8], slice = 1,1:1,4:-:-"));
    EXPECT_EQ("[]", y.DebugString());
  }
}
