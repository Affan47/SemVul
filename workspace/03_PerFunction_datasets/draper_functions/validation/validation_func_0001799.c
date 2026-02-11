BuildInitialMoveList(LParallelMove* parallel_move) {


  const ZoneList<LMoveOperands>* moves = parallel_move->move_operands();
  for (int i = 0; i < moves->length(); ++i) {
    LMoveOperands move = moves->at(i);
    if (!move.IsRedundant()) moves_.Add(move);
  }
  Verify();
}
