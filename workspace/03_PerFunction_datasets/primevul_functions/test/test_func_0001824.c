Literal *hermes::evalBinaryOperator(
    BinaryOperatorInst::OpKind kind,
    IRBuilder &builder,
    Literal *lhs,
    Literal *rhs) {
  Type leftTy = lhs->getType();
  Type rightTy = rhs->getType();

  auto *leftLiteralNum = llvh::dyn_cast<LiteralNumber>(lhs);
  auto *rightLiteralNum = llvh::dyn_cast<LiteralNumber>(rhs);

  auto *leftNull = llvh::dyn_cast<LiteralNull>(lhs);
  auto *rightNull = llvh::dyn_cast<LiteralNull>(rhs);

  auto *leftUndef = llvh::dyn_cast<LiteralUndefined>(lhs);
  auto *rightUndef = llvh::dyn_cast<LiteralUndefined>(rhs);

  auto *leftStr = llvh::dyn_cast<LiteralString>(lhs);
  auto *rightStr = llvh::dyn_cast<LiteralString>(rhs);

  auto leftNaN = isNaN(lhs);
  auto rightNaN = isNaN(rhs);

  auto &ctx = builder.getModule()->getContext();

  using OpKind = BinaryOperatorInst::OpKind;

  if (leftNaN || rightNaN) {
    switch (kind) {
      case OpKind::EqualKind:
      case OpKind::StrictlyEqualKind:
      case OpKind::LessThanKind:
      case OpKind::LessThanOrEqualKind:
      case OpKind::GreaterThanKind:
      case OpKind::GreaterThanOrEqualKind:


        return builder.getLiteralBool(false);
      case OpKind::NotEqualKind:
      case OpKind::StrictlyNotEqualKind:


        return builder.getLiteralBool(true);
      case OpKind::LeftShiftKind:
      case OpKind::RightShiftKind:
      case OpKind::UnsignedRightShiftKind:


        break;
      case OpKind::AddKind:


        if (leftStr) {
          SmallString<256> result =
              buildString(ctx.toString(leftStr->getValue()), "NaN");
          return builder.getLiteralString(result.str());
        }

        if (rightStr) {
          SmallString<256> result =
              buildString("NaN", ctx.toString(rightStr->getValue()));
          return builder.getLiteralString(result.str());
        }


        return builder.getLiteralNaN();
      case OpKind::SubtractKind:
      case OpKind::MultiplyKind:
      case OpKind::DivideKind:
      case OpKind::ModuloKind:

        return builder.getLiteralNaN();
      case OpKind::OrKind:
      case OpKind::XorKind:
      case OpKind::AndKind:


        break;
      default:


        return nullptr;
    }
  }

  auto numericOrder = getNumericOrder(lhs, rhs);

  switch (kind) {
    case OpKind::EqualKind:

      if (lhs == rhs) {
        return builder.getLiteralBool(true);
      }


      if (numericOrder.hasValue()) {
        switch (numericOrder.getValue()) {
          case NumericOrder::LessThan:
            return builder.getLiteralBool(false);
          case NumericOrder::Equal:
            return builder.getLiteralBool(true);
          case NumericOrder::GreaterThan:
            return builder.getLiteralBool(false);
          case NumericOrder::Unordered:
            break;
        }
      }


      if (leftStr && rightStr) {
        return builder.getLiteralBool(
            leftStr->getValue() == rightStr->getValue());
      }

      break;
    case OpKind::NotEqualKind:

      if (lhs == rhs) {
        return builder.getLiteralBool(false);
      }


      if (numericOrder.hasValue()) {
        switch (numericOrder.getValue()) {
          case NumericOrder::LessThan:
            return builder.getLiteralBool(true);
          case NumericOrder::Equal:
            return builder.getLiteralBool(false);
          case NumericOrder::GreaterThan:
            return builder.getLiteralBool(true);
          case NumericOrder::Unordered:
            break;
        }
      }

      if (leftStr && rightStr) {
        return builder.getLiteralBool(
            leftStr->getValue() != rightStr->getValue());
      }

      break;
    case OpKind::StrictlyEqualKind:

      if (lhs == rhs) {
        return builder.getLiteralBool(true);
      }


      if (disjointComparisonTypes(leftTy, rightTy))
        return builder.getLiteralBool(false);


      if (numericOrder.hasValue()) {
        switch (numericOrder.getValue()) {
          case NumericOrder::LessThan:
            return builder.getLiteralBool(false);
          case NumericOrder::Equal:
            return builder.getLiteralBool(true);
          case NumericOrder::GreaterThan:
            return builder.getLiteralBool(false);
          case NumericOrder::Unordered:
            break;
        }
      }


      if (leftStr && rightStr) {
        return builder.getLiteralBool(
            leftStr->getValue() == rightStr->getValue());
      }

      break;
    case OpKind::StrictlyNotEqualKind:

      if (lhs == rhs) {
        return builder.getLiteralBool(false);
      }


      if (numericOrder.hasValue()) {
        switch (numericOrder.getValue()) {
          case NumericOrder::LessThan:
            return builder.getLiteralBool(true);
          case NumericOrder::Equal:
            return builder.getLiteralBool(false);
          case NumericOrder::GreaterThan:
            return builder.getLiteralBool(true);
          case NumericOrder::Unordered:
            break;
        }
      }


      if (leftStr && rightStr) {
        return builder.getLiteralBool(
            leftStr->getValue() != rightStr->getValue());
      }

      break;
    case OpKind::LessThanKind:

      if (!leftTy.isUndefinedType() && lhs == rhs)
        return builder.getLiteralBool(false);


      if (numericOrder.hasValue()) {
        switch (numericOrder.getValue()) {
          case NumericOrder::LessThan:
            return builder.getLiteralBool(true);
          case NumericOrder::Equal:
            return builder.getLiteralBool(false);
          case NumericOrder::GreaterThan:
            return builder.getLiteralBool(false);
          case NumericOrder::Unordered:
            break;
        }
      }
      break;
    case OpKind::LessThanOrEqualKind:

      if (!leftTy.isUndefinedType() && lhs == rhs)
        return builder.getLiteralBool(true);


      if (numericOrder.hasValue()) {
        switch (numericOrder.getValue()) {
          case NumericOrder::LessThan:
            return builder.getLiteralBool(true);
          case NumericOrder::Equal:
            return builder.getLiteralBool(true);
          case NumericOrder::GreaterThan:
            return builder.getLiteralBool(false);
          case NumericOrder::Unordered:
            break;
        }
      }

      break;
    case OpKind::GreaterThanKind:

      if (!leftTy.isUndefinedType() && lhs == rhs)
        return builder.getLiteralBool(false);


      if (numericOrder.hasValue()) {
        switch (numericOrder.getValue()) {
          case NumericOrder::LessThan:
            return builder.getLiteralBool(false);
          case NumericOrder::Equal:
            return builder.getLiteralBool(false);
          case NumericOrder::GreaterThan:
            return builder.getLiteralBool(true);
          case NumericOrder::Unordered:
            break;
        }
      }

      break;
    case OpKind::GreaterThanOrEqualKind:

      if (!leftTy.isUndefinedType() && lhs == rhs)
        return builder.getLiteralBool(true);


      if (numericOrder.hasValue()) {
        switch (numericOrder.getValue()) {
          case NumericOrder::LessThan:
            return builder.getLiteralBool(false);
          case NumericOrder::Equal:
            return builder.getLiteralBool(true);
          case NumericOrder::GreaterThan:
            return builder.getLiteralBool(true);
          case NumericOrder::Unordered:
            break;
        }
      }

      break;
    case OpKind::LeftShiftKind:
    case OpKind::RightShiftKind:
    case OpKind::UnsignedRightShiftKind: {

      auto *lnum = evalToNumber(builder, lhs);
      auto *rnum = evalToNumber(builder, rhs);
      if (!lnum || !rnum) {

        break;
      }
      uint32_t shiftCount = rnum->truncateToUInt32() & 0x1f;

      int64_t result = 0;
      if (kind == OpKind::LeftShiftKind) {


        result = static_cast<int32_t>(lnum->truncateToUInt32() << shiftCount);
      } else if (kind == OpKind::RightShiftKind) {
        result = static_cast<int64_t>(lnum->truncateToInt32() >> shiftCount);
      } else {
        result = static_cast<int64_t>(lnum->truncateToUInt32() >> shiftCount);
      }
      return builder.getLiteralNumber(result);
    }
    case OpKind::AddKind: {

      if (leftLiteralNum && rightLiteralNum) {
        return builder.getLiteralNumber(
            leftLiteralNum->getValue() + rightLiteralNum->getValue());
      }


      if (leftStr && rightStr) {
        SmallString<256> result = buildString(
            ctx.toString(leftStr->getValue()),
            ctx.toString(rightStr->getValue()));
        return builder.getLiteralString(result.str());
      }

      if (leftNull && rightNull) {
        return builder.getLiteralPositiveZero();
      }

      if (leftUndef && rightUndef) {
        return builder.getLiteralNaN();
      }

      if (leftNull) {
        if (rightLiteralNum) {
          return rhs;
        } else if (rightStr) {
          SmallString<256> result =
              buildString("null", ctx.toString(rightStr->getValue()));
          return builder.getLiteralString(result.str());
        }
      }

      if (rightNull) {
        if (leftLiteralNum) {
          return lhs;
        } else if (leftStr) {
          SmallString<256> result =
              buildString(ctx.toString(leftStr->getValue()), "null");
          return builder.getLiteralString(result.str());
        }
      }

      if (leftUndef) {
        if (rightLiteralNum) {
          return builder.getLiteralNaN();
        } else if (rightStr) {
          SmallString<256> result =
              buildString("undefined", ctx.toString(rightStr->getValue()));
          return builder.getLiteralString(result.str());
        }
      }

      if (rightUndef) {
        if (leftLiteralNum) {
          return builder.getLiteralNaN();
        } else if (leftStr) {
          SmallString<256> result =
              buildString(ctx.toString(leftStr->getValue()), "undefined");
          return builder.getLiteralString(result.str());
        }
      }

      break;
    }
    case OpKind::SubtractKind:

      if (leftLiteralNum && rightLiteralNum) {
        return builder.getLiteralNumber(
            leftLiteralNum->getValue() - rightLiteralNum->getValue());
      }

      break;

    case OpKind::MultiplyKind:

      if (leftLiteralNum && rightLiteralNum) {
        return builder.getLiteralNumber(
            leftLiteralNum->getValue() * rightLiteralNum->getValue());
      }

      if ((leftNull && rightLiteralNum) || (rightNull && leftLiteralNum) ||
          (leftNull && rightNull)) {
        if ((leftLiteralNum && std::signbit(leftLiteralNum->getValue())) ||
            (rightLiteralNum && std::signbit(rightLiteralNum->getValue()))) {
          return builder.getLiteralNegativeZero();
        }
        return builder.getLiteralPositiveZero();
      }

      break;
    case OpKind::DivideKind:
      if (leftLiteralNum && rightLiteralNum) {


        return builder.getLiteralNumber(
            leftLiteralNum->getValue() / rightLiteralNum->getValue());
      }
      break;
    case OpKind::ModuloKind:


      if (leftLiteralNum && rightLiteralNum) {
        return builder.getLiteralNumber(
            std::fmod(leftLiteralNum->getValue(), rightLiteralNum->getValue()));
      }

      break;
    case OpKind::ExponentiationKind:
      if (leftLiteralNum && rightLiteralNum) {
        return builder.getLiteralNumber(hermes::expOp(
            leftLiteralNum->getValue(), rightLiteralNum->getValue()));
      }
      break;
    case OpKind::OrKind:
      if (leftLiteralNum && rightLiteralNum) {
        return builder.getLiteralNumber(
            leftLiteralNum->truncateToInt32() |
            rightLiteralNum->truncateToInt32());
      }

      break;
    case OpKind::XorKind:
      if (leftLiteralNum && rightLiteralNum) {
        return builder.getLiteralNumber(
            leftLiteralNum->truncateToInt32() ^
            rightLiteralNum->truncateToInt32());
      }

      break;
    case OpKind::AndKind:
      if (leftLiteralNum && rightLiteralNum) {
        return builder.getLiteralNumber(
            leftLiteralNum->truncateToInt32() &
            rightLiteralNum->truncateToInt32());
      }

      break;
    default:
      break;
  }

  return nullptr;
}
