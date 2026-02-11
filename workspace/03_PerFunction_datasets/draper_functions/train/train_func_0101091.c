runOnModule(Module &M) {
  CallGraph &CG = getAnalysis<CallGraph>();
  bool Changed = doInitialization(CG);


  scc_iterator<CallGraph*> CGI = scc_begin(&CG);

  CallGraphSCC CurSCC(&CGI);
  while (!CGI.isAtEnd()) {


    std::vector<CallGraphNode*> &NodeVec = *CGI;
    CurSCC.initialize(&NodeVec[0], &NodeVec[0]+NodeVec.size());
    ++CGI;


    unsigned Iteration = 0;
    bool DevirtualizedCall = false;
    do {
      DEBUG(if (Iteration)
              dbgs() << "  SCCPASSMGR: Re-visiting SCC, iteration #"
                     << Iteration << '\n');
      DevirtualizedCall = false;
      Changed |= RunAllPassesOnSCC(CurSCC, CG, DevirtualizedCall);
    } while (Iteration++ < MaxIterations && DevirtualizedCall);

    if (DevirtualizedCall)
      DEBUG(dbgs() << "  CGSCCPASSMGR: Stopped iteration after " << Iteration
                   << " times, due to -max-cg-scc-iterations\n");

    if (Iteration > MaxSCCIterations)
      MaxSCCIterations = Iteration;

  }
  Changed |= doFinalization(CG);
  return Changed;
}
