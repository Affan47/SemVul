AdvanceCurrentPositionInTrace(int by, RegExpCompiler* compiler) {
  ASSERT(by > 0);


  characters_preloaded_ = 0;


  quick_check_performed_.Advance(by, compiler->ascii());
  cp_offset_ += by;
  if (cp_offset_ > RegExpMacroAssembler::kMaxCPOffset) {
    compiler->SetRegExpTooBig();
    cp_offset_ = 0;
  }
  bound_checked_up_to_ = Max(0, bound_checked_up_to_ - by);
}
