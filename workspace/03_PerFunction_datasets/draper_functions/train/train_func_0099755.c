clear_all_register(Processor *c,unsigned int address)
{

  if(!c || address<0 || address > c->register_memory_size())
    return;


  while(c->registers[address]->isa()==Register::BP_REGISTER) {

    BreakpointRegister *nr = dynamic_cast<BreakpointRegister *>(c->registers[address]);

    if(!nr)
      return;

    bp.clear(nr->bpn & ~Breakpoints::BREAK_MASK);
  }
}
