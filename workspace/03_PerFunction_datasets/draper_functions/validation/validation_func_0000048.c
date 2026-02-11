add_insn(int insn, int arg, int arg2, const String &arg3)
{


    if (_insns.size() == 0 && insn != INSN_INITIAL && insn != INSN_WAIT_STEP
	&& insn != INSN_WAIT_TIME)
	add_insn(INSN_INITIAL, 0);
    _insns.push_back(insn);
    _args.push_back(arg);
    _args2.push_back(arg2);
    _args3.push_back(arg3);
}
