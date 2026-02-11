Finish(HControlInstruction* end) {
  ASSERT(!IsFinished());
  AddInstruction(end);
  end_ = end;
  for (HSuccessorIterator it(end); !it.Done(); it.Advance()) {
    it.Current()->RegisterPredecessor(this);
  }
}
