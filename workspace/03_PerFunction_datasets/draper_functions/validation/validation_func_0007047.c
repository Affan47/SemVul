mfracformat (header *hd)
{	header *st=hd,*result;
	int oldl=outputlength,l;
	double oldeps=fraceps,eps;
	hd=getvalue(hd); if (error) return;
	if (hd->type!=s_matrix || dimsof(hd)->r!=1 || dimsof(hd)->c!=2)
		wrong_arg_in("fracformat");
	l=(int)*matrixof(hd);
	eps=*(matrixof(hd)+1);
	if (l<2 || l>80 || eps<=0 || eps>1)
		wrong_arg_in("fracformat");
	outputlength=l;
	fieldw=l+1;
	linew=linelength/fieldw;
	if (linew<=0) linew=1;
	result=new_matrix(1,2,""); if (error) return;
	*matrixof(result)=oldl;
	*(matrixof(result)+1)=oldeps;
	moveresult(st,result);
    fraceps=eps;
}
