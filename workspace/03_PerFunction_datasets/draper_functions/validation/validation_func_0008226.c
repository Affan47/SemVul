printC(fcomplex c)
{	if (c.r!=0 && c.i !=0) {
		if (c.i>0) printf("(%g+%g*I)",c.r,c.i);
		else  printf("(%g-%g*I)",c.r,fabs(c.i));
	}
	else if (c.r!=0) printf("%g",c.r);
	else if (c.i!=0) printf("(%g*I)",c.i);
        else printf("0.0");
}
