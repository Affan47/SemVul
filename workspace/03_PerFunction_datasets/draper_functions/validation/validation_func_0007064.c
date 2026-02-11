update_register_banks(void)
{
	UINT32 temp;
	int i, bank;


	bank = jaguar.FLAGS & RPAGEFLAG;
	if (jaguar.FLAGS & IFLAG) bank = 0;


	if ((!bank && jaguar.b0 != jaguar.r) || (bank && jaguar.b1 != jaguar.r))
	{

		bankswitch_icount = jaguar_icount - 1;


		for (i = 0; i < 32; i++)
			temp = jaguar.r[i], jaguar.r[i] = jaguar.a[i], jaguar.a[i] = temp;


		if (!bank)
		{
			jaguar.b0 = jaguar.r;
			jaguar.b1 = jaguar.a;
		}
		else
		{
			jaguar.b0 = jaguar.a;
			jaguar.b1 = jaguar.r;
		}
	}
}
