LowerOperation(SDValue Op, SelectionDAG &DAG) const
{
  unsigned Opc = (unsigned) Op.getOpcode();
  EVT VT = Op.getValueType();

  switch (Opc) {
  default: {
#ifndef NDEBUG
    errs() << "SPUTargetLowering::LowerOperation(): need to lower this!\n";
    errs() << "Op.getOpcode() = " << Opc << "\n";
    errs() << "*Op.getNode():\n";
    Op.getNode()->dump();
#endif
    llvm_unreachable(0);
  }
  case ISD::LOAD:
  case ISD::EXTLOAD:
  case ISD::SEXTLOAD:
  case ISD::ZEXTLOAD:
    return LowerLOAD(Op, DAG, SPUTM.getSubtargetImpl());
  case ISD::STORE:
    return LowerSTORE(Op, DAG, SPUTM.getSubtargetImpl());
  case ISD::ConstantPool:
    return LowerConstantPool(Op, DAG, SPUTM.getSubtargetImpl());
  case ISD::GlobalAddress:
    return LowerGlobalAddress(Op, DAG, SPUTM.getSubtargetImpl());
  case ISD::JumpTable:
    return LowerJumpTable(Op, DAG, SPUTM.getSubtargetImpl());
  case ISD::ConstantFP:
    return LowerConstantFP(Op, DAG);


  case ISD::ADD:
  case ISD::SUB:
  case ISD::ROTR:
  case ISD::ROTL:
  case ISD::SRL:
  case ISD::SHL:
  case ISD::SRA: {
    if (VT == MVT::i8)
      return LowerI8Math(Op, DAG, Opc, *this);
    break;
  }

  case ISD::FP_TO_SINT:
  case ISD::FP_TO_UINT:
    return LowerFP_TO_INT(Op, DAG, *this);

  case ISD::SINT_TO_FP:
  case ISD::UINT_TO_FP:
    return LowerINT_TO_FP(Op, DAG, *this);


  case ISD::BUILD_VECTOR:
    return LowerBUILD_VECTOR(Op, DAG);
  case ISD::SCALAR_TO_VECTOR:
    return LowerSCALAR_TO_VECTOR(Op, DAG);
  case ISD::VECTOR_SHUFFLE:
    return LowerVECTOR_SHUFFLE(Op, DAG);
  case ISD::EXTRACT_VECTOR_ELT:
    return LowerEXTRACT_VECTOR_ELT(Op, DAG);
  case ISD::INSERT_VECTOR_ELT:
    return LowerINSERT_VECTOR_ELT(Op, DAG);


  case ISD::AND:
  case ISD::OR:
  case ISD::XOR:
    return LowerByteImmed(Op, DAG);


  case ISD::MUL:
    if (VT == MVT::i8)
      return LowerI8Math(Op, DAG, Opc, *this);

  case ISD::CTPOP:
    return LowerCTPOP(Op, DAG);

  case ISD::SELECT_CC:
    return LowerSELECT_CC(Op, DAG, *this);

  case ISD::SETCC:
    return LowerSETCC(Op, DAG, *this);

  case ISD::TRUNCATE:
    return LowerTRUNCATE(Op, DAG);

  case ISD::SIGN_EXTEND:
    return LowerSIGN_EXTEND(Op, DAG);
  }

  return SDValue();
}
