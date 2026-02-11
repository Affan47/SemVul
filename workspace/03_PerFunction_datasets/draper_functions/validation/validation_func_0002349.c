MergeUnderN( f, b, t, n )
    ColorA *f, *b, *t;
    int n;
{
    float a;

    while( n-- ) {
	a = 1.0 - b->a;
	t->r = a * f->r + b->r;
	t->g = a * f->g + b->g;
	t->b = a * f->b + b->b;
	t->a = a * f->a + b->a;
	f++;
	b++;
	t++;
    }
}
