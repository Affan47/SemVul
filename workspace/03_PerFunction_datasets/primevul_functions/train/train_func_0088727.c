Attribute ConvertSingleElementAttrToFloatAttr(Attribute attr) {
  const auto dense_fp_attr = attr.dyn_cast_or_null<DenseFPElementsAttr>();
  if (dense_fp_attr) {

    return dense_fp_attr;
  }

  OpBuilder builder(attr.getContext());

  const auto dense_int_attr = attr.dyn_cast<DenseIntElementsAttr>();
  const auto int_values = dense_int_attr.getIntValues();
  float float_val = 0.0f;
  if (!int_values.empty()) {
    const APInt apint_val = *int_values.begin();
    if (dense_int_attr.getType().getElementType().isSignedInteger()) {

      float_val = apint_val.getSExtValue();
    } else {

      float_val = apint_val.getZExtValue();
    }
  }
  return DenseFPElementsAttr::get(
      RankedTensorType::get({}, builder.getF32Type()),
      {llvm::APFloat(float_val)});
}
