banz(void)
{
		if (R.AR[ARP]) R.PC = M_RDOP_ARG(R.PC);
		else R.PC++ ;
		MODIFY_AR_ARP();
}
