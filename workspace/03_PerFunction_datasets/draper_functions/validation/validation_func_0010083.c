mputlongword (header *hd)
{	header *st=hd,*result;
	int n,i;
	long *p,*start=(long *)newram;
	double *m;
	hd=getvalue(hd); if (error) return;
	if (hd->type!=s_real && hd->type!=s_matrix)
		wrong_arg_in("putchar(v)");
	getmatrix(hd,&i,&n,&m);
	if (i!=1 || n<1) wrong_arg_in("putchar(v)");
	if (fa)
	{	if (!freeramfrom(start,n*sizeof(long)))
		{	output("Stack overflow in getchar(n).");
			error=1; return;
		}
		for (p=start,i=0; i<n; i++) *p++=(long)*m++;
		fwrite(start,sizeof(long),n,fa);
	}
	result=new_real(ferror(fa),""); if (error) return;
	moveresult(st,result);
}
