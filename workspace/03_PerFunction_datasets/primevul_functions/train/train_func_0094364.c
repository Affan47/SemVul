TEST(FloatPoolingOpTest, L2PoolPaddingSameSlide1) {
  FloatPoolingOpModel m(BuiltinOperator_L2_POOL_2D,
                        {TensorType_FLOAT32, {1, 2, 4, 1}},
                        2, 2,
                        {TensorType_FLOAT32, {}}, Padding_SAME, 1,
                        1);
  m.SetInput({
      0, 6, 2, 4,
      3, 2, 10, 7,
  });
  m.Invoke();
  EXPECT_THAT(m.GetOutput(),
              ElementsAreArray(ArrayFloatNear(
                  {3.5, 6.0, 6.5, 5.70088, 2.54951, 7.2111, 8.63134, 7.0},
                  1e-4)));
}
