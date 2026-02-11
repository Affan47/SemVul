visitExtractElementInst(ExtractElementInst &I) {
    insertShadowCheck(I.getOperand(1), &I);
    IRBuilder<> IRB(&I);
    setShadow(&I, IRB.CreateExtractElement(getShadow(&I, 0), I.getOperand(1),
              "_msprop"));
    setOrigin(&I, getOrigin(&I, 0));
  }
