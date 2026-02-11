printAndVerify(PassManagerBase &PM,
                           const char *Banner) {
  if (PrintMachineCode)
    PM.add(createMachineFunctionPrinterPass(dbgs(), Banner));

  if (VerifyMachineCode)
    PM.add(createMachineVerifierPass());
}
