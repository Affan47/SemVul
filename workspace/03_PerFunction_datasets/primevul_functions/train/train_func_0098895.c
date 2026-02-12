DEFINE_IDTENTRY_RAW(xenpv_exc_nmi)
{

	exc_nmi(regs);
}
