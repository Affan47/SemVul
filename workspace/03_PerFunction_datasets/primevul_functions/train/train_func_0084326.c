TEST(TensorSliceTest, BuildTensorSlice) {
  TensorSliceProto proto;
  TensorSlice({{0, -1}, {0, 10}, {14, 1}}).AsProto(&proto);
  TensorSlice s;


  {
    TF_ASSERT_OK(TensorSlice::BuildTensorSlice(proto, &s));
    EXPECT_EQ("-:0,10:14,1", s.DebugString());
  }


  {
    TensorSliceProto invalid_proto = proto;
    invalid_proto.mutable_extent(0)->set_start(-1);
    EXPECT_FALSE(TensorSlice::BuildTensorSlice(invalid_proto, &s).ok());
  }


  {
    TensorSliceProto invalid_proto = proto;
    invalid_proto.mutable_extent(2)->set_length(-1);
    EXPECT_FALSE(TensorSlice::BuildTensorSlice(invalid_proto, &s).ok());
  }


  {
    TensorSliceProto invalid_proto = proto;
    invalid_proto.mutable_extent(2)->clear_length();
    EXPECT_FALSE(TensorSlice::BuildTensorSlice(invalid_proto, &s).ok());
  }


  {
    TensorSliceProto invalid_proto = proto;
    invalid_proto.mutable_extent(2)->set_length(
        std::numeric_limits<int64_t>::max());
    EXPECT_FALSE(TensorSlice::BuildTensorSlice(invalid_proto, &s).ok());
  }
}
