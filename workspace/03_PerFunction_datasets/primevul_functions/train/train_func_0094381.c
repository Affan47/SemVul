TEST(FloatPoolingOpTest, L2PoolActivationRelu) {
  FloatPoolingOpModel m(BuiltinOperator_L2_POOL_2D,
                        {TensorType_FLOAT32, {1, 2, 4, 1}},
                        2, 2,
                        {TensorType_FLOAT32, {}}, Padding_VALID, 2,
                        2, ActivationFunctionType_RELU);
  m.SetInput({
      -1, -6, 2, 4,
      -3, -2, 10, 7,
  });
  m.Invoke();
  EXPECT_THAT(m.GetOutput(), ElementsAreArray(ArrayFloatNear({3.53553, 6.5})));
}
