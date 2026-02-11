mlinew (header *hd)
{	header *st=hd,*res;
	int h,old=linewidth;
	hd=getvalue(hd); if (error) return;
	if (hd->type!=s_real)
	{	output("Argument for linewidth must be a real!");
		error=90; return;
	}
	if ((h=(int)*realof(hd))!=0) linewidth=h;
	res=new_real(old,"");
	moveresult(st,res);
}
