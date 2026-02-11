getPairPtrInfo(Instruction *I, Instruction *J,
        Value *&IPtr, Value *&JPtr, unsigned &IAlignment, unsigned &JAlignment,
        unsigned &IAddressSpace, unsigned &JAddressSpace,
        int64_t &OffsetInElmts, bool ComputeOffset = true) {
      OffsetInElmts = 0;
      if (LoadInst *LI = dyn_cast<LoadInst>(I)) {
        LoadInst *LJ = cast<LoadInst>(J);
        IPtr = LI->getPointerOperand();
        JPtr = LJ->getPointerOperand();
        IAlignment = LI->getAlignment();
        JAlignment = LJ->getAlignment();
        IAddressSpace = LI->getPointerAddressSpace();
        JAddressSpace = LJ->getPointerAddressSpace();
      } else {
        StoreInst *SI = cast<StoreInst>(I), *SJ = cast<StoreInst>(J);
        IPtr = SI->getPointerOperand();
        JPtr = SJ->getPointerOperand();
        IAlignment = SI->getAlignment();
        JAlignment = SJ->getAlignment();
        IAddressSpace = SI->getPointerAddressSpace();
        JAddressSpace = SJ->getPointerAddressSpace();
      }

      if (!ComputeOffset)
        return true;

      const SCEV *IPtrSCEV = SE->getSCEV(IPtr);
      const SCEV *JPtrSCEV = SE->getSCEV(JPtr);


      const SCEV *OffsetSCEV = SE->getMinusSCEV(JPtrSCEV, IPtrSCEV);
      if (const SCEVConstant *ConstOffSCEV =
            dyn_cast<SCEVConstant>(OffsetSCEV)) {
        ConstantInt *IntOff = ConstOffSCEV->getValue();
        int64_t Offset = IntOff->getSExtValue();
        const DataLayout &DL = I->getModule()->getDataLayout();
        Type *VTy = IPtr->getType()->getPointerElementType();
        int64_t VTyTSS = (int64_t)DL.getTypeStoreSize(VTy);

        Type *VTy2 = JPtr->getType()->getPointerElementType();
        if (VTy != VTy2 && Offset < 0) {
          int64_t VTy2TSS = (int64_t)DL.getTypeStoreSize(VTy2);
          OffsetInElmts = Offset/VTy2TSS;
          return (std::abs(Offset) % VTy2TSS) == 0;
        }

        OffsetInElmts = Offset/VTyTSS;
        return (std::abs(Offset) % VTyTSS) == 0;
      }

      return false;
    }
