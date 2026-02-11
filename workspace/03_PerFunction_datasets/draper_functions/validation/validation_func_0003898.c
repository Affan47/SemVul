Process() {


  for (int i = 0; i < graph_->blocks()->length(); i++) {
    HBasicBlock* block = graph_->blocks()->at(i);
    if (block->IsLoopHeader()) {
      HBasicBlock* back_edge = block->loop_information()->GetLastBackEdge();
      HBasicBlock* dominator = back_edge;
      while (true) {
        HInstruction* instr = dominator->first();
        while (instr != NULL) {
          if (instr->IsCall()) {
            block->loop_information()->stack_check()->Eliminate();
            break;
          }
          instr = instr->next();
        }


        if (dominator == block) break;


        dominator = dominator->dominator();
      }
    }
  }
}
