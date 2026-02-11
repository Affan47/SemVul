print_control_flow_mt(FILE *fp,
			   Block *bpt)
{
    int npre, i;

    npre = bpt->ncfpre;
    fprintf(fp," %d",npre);

    for(i = 0; i < npre; i++){
	fprintf(fp," %d",bpt->cfpre[i]->no);
    }

}
