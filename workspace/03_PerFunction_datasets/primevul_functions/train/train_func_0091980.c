bool IsSupported(const NodeDef* node) const override {


    return IsAnyDiv(*node) && !IsDivNoNan(*node) && !IsFloorDiv(*node);
  }
