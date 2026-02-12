inline int32_t GetReciprocal(int32_t x, int x_integer_digits,
                             int* num_bits_over_unit) {
  int headroom_plus_one = CountLeadingZeros(static_cast<uint32_t>(x));


  *num_bits_over_unit = x_integer_digits - headroom_plus_one;
  const int32_t shifted_sum_minus_one =
      static_cast<int32_t>((static_cast<uint32_t>(x) << headroom_plus_one) -
                           (static_cast<uint32_t>(1) << 31));

  gemmlowp::FixedPoint<int32_t, 0> shifted_scale =
      gemmlowp::one_over_one_plus_x_for_x_in_0_1(
          gemmlowp::FixedPoint<int32_t, 0>::FromRaw(shifted_sum_minus_one));
  return shifted_scale.raw();
}
