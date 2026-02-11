ccpu_set_context(void *src)
{
	if( src )
	{
		CONTEXTCCPU context;
		ccpuRegs *Regs = src;
		context.accVal = Regs->accVal;
		context.cmpVal = Regs->cmpVal;
		context.pa0 = Regs->pa0;
		context.cFlag = Regs->cFlag;
		context.eRegPC = Regs->eRegPC;
		context.eRegA = Regs->eRegA;
		context.eRegB = Regs->eRegB;
		context.eRegI = Regs->eRegI;
		context.eRegJ = Regs->eRegJ;
		context.eRegP = Regs->eRegP;
		context.eCState = (CINESTATE)Regs->eCState;
		cSetContext (&context);
	}
}
