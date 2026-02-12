TEST(TensorSliceTest, Intersection) {

  {
    TensorSlice a = TensorSlice::ParseOrDie("-:-");
    TensorSlice b = TensorSlice::ParseOrDie("1,2:3,4");
    TensorSlice c;
    EXPECT_TRUE(a.Intersect(b, &c));
    EXPECT_EQ("1,2:3,4", c.DebugString());
  }

  {
    TensorSlice a = TensorSlice::ParseOrDie("-:-");
    TensorSlice b = TensorSlice::ParseOrDie("1,2:3,4");
    TensorSlice c;
    EXPECT_TRUE(b.Intersect(a, &c));
    EXPECT_EQ("1,2:3,4", c.DebugString());
  }


  {
    TensorSlice a = TensorSlice::ParseOrDie("1,5:2,6:3,7:5,10");
    TensorSlice b = TensorSlice::ParseOrDie("1,2:3,4:9,10:12,1");
    TensorSlice c;
    EXPECT_TRUE(a.Intersect(b, &c));
    EXPECT_EQ("1,2:3,4:9,1:12,1", c.DebugString());
  }


  {
    TensorSlice a = TensorSlice::ParseOrDie("-:1,1");
    TensorSlice b = TensorSlice::ParseOrDie("-:0,2");
    TensorSlice c;
    EXPECT_TRUE(a.Intersect(b, &c));
    EXPECT_EQ("-:1,1", c.DebugString());
  }


  {
    TensorSlice a = TensorSlice::ParseOrDie("1,2:3,1:5,6");
    TensorSlice b = TensorSlice::ParseOrDie("1,3:4,5:1,6");
    TensorSlice c;
    EXPECT_FALSE(a.Intersect(b, &c));
    EXPECT_EQ("", c.DebugString());
  }

  {
    TensorSlice a = TensorSlice::ParseOrDie("1,2:3,1:-");
    TensorSlice b = TensorSlice::ParseOrDie("-:-");
    TensorSlice c;
    EXPECT_FALSE(a.Intersect(b, &c));
    EXPECT_EQ("", c.DebugString());
  }
}
