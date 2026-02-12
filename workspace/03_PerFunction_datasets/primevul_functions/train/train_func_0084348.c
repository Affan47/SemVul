void SimpleIntXHelper(
    const TensorSliceWriter::CreateBuilderFunction& create_function,
    TensorSliceReader::OpenTableFunction open_function,
    const string& checkpoint_file) {
  const string fname_base = io::JoinPath(testing::TmpDir(), checkpoint_file);

  TensorShape shape({4, 5});


  {
    const string fname = strings::StrCat(fname_base, "_0");
    TensorSliceWriter writer(fname, create_function);
    const T data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    TensorSlice slice = TensorSlice::ParseOrDie("0,2:-");
    TF_CHECK_OK(writer.Add("test", shape, slice, data));
    TF_CHECK_OK(writer.Finish());
  }


  {
    const string fname = strings::StrCat(fname_base, "_1");
    TensorSliceWriter writer(fname, create_function);

    {
      const T data[] = {10, 11, 12, 15, 16, 17};
      TensorSlice slice = TensorSlice::ParseOrDie("2,2:0,3");
      TF_CHECK_OK(writer.Add("test", shape, slice, data));
    }

    {
      const T data[] = {18, 19};
      TensorSlice slice = TensorSlice::ParseOrDie("3,1:3,2");
      TF_CHECK_OK(writer.Add("test", shape, slice, data));
    }
    TF_CHECK_OK(writer.Finish());
  }


  const string filepattern = strings::StrCat(fname_base, "_*");
  TensorSliceReader reader(filepattern, std::move(open_function));
  TF_EXPECT_OK(reader.status());
  EXPECT_EQ(2, reader.num_files());


  {
    TensorShape shape;
    DataType type;
    EXPECT_TRUE(reader.HasTensor("test", &shape, &type));
    EXPECT_EQ("[4,5]", shape.DebugString());
    EXPECT_EQ(DataTypeToEnum<T>::v(), type);
    EXPECT_FALSE(reader.HasTensor("don't exist", nullptr, nullptr));
  }


  {
    TensorSlice s = TensorSlice::ParseOrDie("0,2:-");
    T expected[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    U results[10];
    EXPECT_TRUE(reader.CopySliceData("test", s, results));
    for (int i = 0; i < 10; ++i) {
      EXPECT_EQ(expected[i], results[i]);
    }
  }


  {
    TensorSlice s = TensorSlice::ParseOrDie("1,1:-");
    T expected[] = {5, 6, 7, 8, 9};
    U results[5];
    EXPECT_TRUE(reader.CopySliceData("test", s, results));
    for (int i = 0; i < 5; ++i) {
      EXPECT_EQ(expected[i], results[i]);
    }
  }


  {
    TensorSlice s = TensorSlice::ParseOrDie("1,2:2,3");
    U results[6];
    EXPECT_FALSE(reader.CopySliceData("test", s, results));
  }
}
