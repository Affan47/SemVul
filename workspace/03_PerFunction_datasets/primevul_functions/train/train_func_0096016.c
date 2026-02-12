decompileSTOREREGISTER(int n, SWF_ACTION *actions, int maxn)
{
	struct SWF_ACTIONPUSHPARAM *data;
	OUT_BEGIN2(SWF_ACTIONSTOREREGISTER);
	data=peek();

	if (!regs[sact->Register] || sact->Register==0 )
	{
		regs[sact->Register] = data;
	}
	else
	{
		if ( regs[sact->Register]->Type == PUSH_VARIABLE)
		{
			if (data->Type==12)
				data->Type = PUSH_VARIABLE;
			else
			{
				char *l=getName(regs[sact->Register]);
				char *r=getName(data);
				if (strcmp(l,r))
				{
					INDENT
					if (data->Type==11)
					{
						println("%s;", r);
					}
					else
					{
						printf("%s = ",l);
						decompilePUSHPARAM(data,1);
						println(";");
					}
				}
			}
		}
	}
	return 0;
}
