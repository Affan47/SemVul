getExternalFunctionStub(void *FnAddr) {

  void *&Stub = ExternalFnToStubMap[FnAddr];
  if (Stub) return Stub;

  TargetJITInfo::StubLayout SL = TheJIT->getJITInfo().getStubLayout();
  JE.startGVStub(0, SL.Size, SL.Alignment);
  Stub = TheJIT->getJITInfo().emitFunctionStub(0, FnAddr, JE);
  JE.finishGVStub();

  DEBUG(dbgs() << "JIT: Stub emitted at [" << Stub
               << "] for external function at '" << FnAddr << "'\n");
  return Stub;
}
