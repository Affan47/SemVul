nlforw(void)
{
    register int  i = 0;
    register LINE *lp = curwp->w_linep;

    while(lp != curwp->w_dotp){
	lp = lforw(lp);
	i++;
    }
    return(i);
}
