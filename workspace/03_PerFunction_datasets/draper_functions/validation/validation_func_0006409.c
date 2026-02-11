idr(int b, int d) {
	int e;
	e=ifree(N(Rb.i), Rb.i, 0);
	if(e<0) {
		wr(b, "No room on the floor."R);
		RET 0;
	}
	pr(b, "You drop %s."R, INM(B.i, d));
	STA(b, B.r, " drops %s."R, INM(B.i, d));
	if(id[B.i[d].v].wl==d&&d<=body) {
		s_rem(b, id[B.i[d].v].s);
	}
	imv(Rb.i+e, B.i+d);
	RET 1;
}
