bool IsAllowListedOpTypeForEvaluateNode(const string& op_type) {
  static const gtl::FlatSet<string>* const kOpTpeAllowlist =
      CHECK_NOTNULL((new gtl::FlatSet<string>{

          "Floor",
          "Round",
          "Sqrt",
          "Square",
          "Sign",

          "Add",
          "AddV2",
          "Div",
          "FloorDiv",
          "FloorMod",
          "Greater",
          "GreaterEqual",
          "Less",
          "LessEqual",
          "LogicalAnd",
          "LogicalNot",
          "LogicalOr",
          "Maximum",
          "Minimum",
          "Mod",
          "Mul",
          "NotEqual",
          "QuantizedAdd",
          "QuantizedMul",
          "SquareDifference",
          "Sub",
          "TruncateDiv",
          "TruncateMod",
          "RealDiv",

          "AddN",

          "StridedSlice",
          "OnesLike",
          "ZerosLike",
          "Concat",
          "ConcatV2",
          "Split",
          "Range",
          "Fill",
          "Cast",
          "Prod",
          "Unpack",
          "GatherV2",
          "Pack",

          "ExpandDims",
      }));
  return kOpTpeAllowlist->find(op_type) != kOpTpeAllowlist->end();
}
