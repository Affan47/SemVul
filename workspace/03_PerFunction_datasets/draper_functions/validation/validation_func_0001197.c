analyzeFunction(Function *F, const TargetData *TD) {


  callsSetJmp = F->callsFunctionThatReturnsTwice();


  for (Function::const_iterator BB = F->begin(), E = F->end(); BB != E; ++BB)
    analyzeBasicBlock(&*BB, TD);
}
