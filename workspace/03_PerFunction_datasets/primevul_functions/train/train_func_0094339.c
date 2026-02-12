TEST(QuantizedPoolingOpTest, AveragePoolLargeDepth) {


  constexpr int depth = 1999;
  QuantizedPoolingOpModel m(
      BuiltinOperator_AVERAGE_POOL_2D,
      {TensorType_UINT8, {1, 2, 4, depth}, 0, 15.9375},
      2, 2,
      {TensorType_UINT8, {}, 0, 15.9375});

  std::vector<float> input_image_plane({
      0.f, 6.f, 2.f, 4.f,
      3.f, 2.f, 10.f, 7.f,
  });
  std::vector<float> output_image_plane({2.75f, 5.75f});

  m.SetInput(ReplicateDepthRamp(input_image_plane, depth, 1.f / 512.f));
  m.Invoke();

  EXPECT_THAT(m.GetDequantizedOutput(),
              ElementsAreArray(ArrayFloatNear(
                  ReplicateDepthRamp(output_image_plane, depth, 1.f / 512.f),
                  1. / 32.f)));
}
