TEST(QuantizedInt8PoolingOpTest, MaxPool) {


  SymmetricQuantizedPoolingOpModel m(
      BuiltinOperator_MAX_POOL_2D,
      {TensorType_INT8, {1, 2, 4, 1}, 0, 15.9375},
      2, 2,
      {TensorType_INT8, {}, 0, 15.9375});
  m.SetInput({
      0, 6, 2, 4,
      3, 2, 10, 7,
  });
  m.Invoke();

  EXPECT_THAT(m.GetDequantizedOutput(),
              ElementsAreArray(ArrayFloatNear({6, 10})));
  EXPECT_THAT(m.GetOutput(), ElementsAreArray({96 - 128, 160 - 128}));
}
