CreateImm(const MCExpr *Val, SMLoc StartLoc, SMLoc EndLoc){
    X86Operand *Res = new X86Operand(Immediate, StartLoc, EndLoc);
    Res->Imm.Val = Val;
    return Res;
  }
