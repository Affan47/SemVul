bool IsScalarizableSplatConstant(mlir::Value value,
                                   DenseElementsAttr *elements_attr) const {
    if (!matchPattern(value, m_Constant(elements_attr))) {
      return false;
    }
    auto element_type = value.getType().cast<ShapedType>().getElementType();


    if (element_type.isa<quant::UniformQuantizedPerAxisType>()) {
      return false;
    }
    if (IsScalar(value)) {
      return false;
    }
    return elements_attr->isSplat();
  }
