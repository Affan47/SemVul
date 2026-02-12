bool CanOptimizeIdentitySliceOp(Value input, Attribute begin, Attribute size) {

  auto begin_attr = begin.dyn_cast<DenseIntElementsAttr>();
  auto size_attr = size.dyn_cast<DenseIntElementsAttr>();
  if (!begin_attr || !size_attr) {
    return false;
  }

  auto begin_elem_ty = begin_attr.getType().getElementType();
  if (!begin_elem_ty.isInteger(32) && !begin_elem_ty.isInteger(64)) {
    return false;
  }
  auto size_elem_ty = size_attr.getType().getElementType();
  if (!size_elem_ty.isInteger(32) && !size_elem_ty.isInteger(64)) {
    return false;
  }


  auto input_ty = input.getType().cast<ShapedType>();
  if (!input_ty.hasRank()) {
    return false;
  }

  int64_t rank = input_ty.getRank();
  if (rank != begin_attr.getNumElements() ||
      rank != size_attr.getNumElements()) {
    return false;
  }


  for (uint64_t i = 0; i < rank; ++i) {
    if (begin_attr.getValue<APInt>({i}).getSExtValue() != 0) return false;
    int64_t si = size_attr.getValue<APInt>({i}).getSExtValue();
    if (si != -1 && si != input_ty.getDimSize(i)) return false;
  }

  return true;
}
