str2top(char *p)
{
	Re2 oldtop;

	oldtop = topre;
	input = p;
	topre.beg = 0;
	topre.end = 0;
	yyparse();
	gen++;
	if(topre.beg == 0)
		yyerror("syntax");
	if(oldtop.beg)
		topre = re2or(oldtop, topre);
}
