TEST(FloatPoolingOpTest, L2PoolActivationRelu6) {
  FloatPoolingOpModel m(BuiltinOperator_L2_POOL_2D,
                        {TensorType_FLOAT32, {1, 2, 4, 1}},
                        2, 2,
                        {TensorType_FLOAT32, {}}, Padding_VALID, 2,
                        2, ActivationFunctionType_RELU6);
  m.SetInput({
      -0.1, -0.6, 2, 4,
      -0.3, -0.2, 10, 7,
  });
  m.Invoke();
  EXPECT_THAT(m.GetOutput(), ElementsAreArray(ArrayFloatNear({0.353553, 6.0})));
}
