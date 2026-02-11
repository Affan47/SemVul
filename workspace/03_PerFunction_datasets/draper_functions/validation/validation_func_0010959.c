insertRegister(unsigned int address, Register *pReg)
{

  if(!cpu || !registers || nRegisters <= address ||!pReg)
    return false;

  Register *ptop = registers[address];
  pReg->setReplaced(ptop);
  registers[address] = pReg;

  return true;
}
