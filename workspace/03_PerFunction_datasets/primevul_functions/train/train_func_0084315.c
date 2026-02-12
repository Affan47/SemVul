TEST(TensorSliceTest, Deserialization) {


  const char pb2[] =
      "\x0A\x02\x10\x05\x0A\x04\x08\x00"
      "\x10\x0A\x0A\x04\x08\x0E\x10\x01\x0A\x02\x08\x01\x0A\x00";
  const char pb3[] =
      "\x0A\x02\x10\x05\x0A\x02"
      "\x10\x0A\x0A\x04\x08\x0E\x10\x01\x0A\x02\x08\x01\x0A\x00";


  TensorSliceProto proto2;
  ASSERT_TRUE(proto2.ParseFromArray(pb2, sizeof(pb2) - 1));
  TensorSlice ts2(proto2);

  TensorSliceProto proto3;
  ASSERT_TRUE(proto3.ParseFromArray(pb3, sizeof(pb3) - 1));
  TensorSlice ts3(proto3);


  EXPECT_EQ("0,5:0,10:14,1:1,-1:-", ts2.DebugString());
  EXPECT_EQ("0,5:0,10:14,1:1,-1:-", ts3.DebugString());
}
