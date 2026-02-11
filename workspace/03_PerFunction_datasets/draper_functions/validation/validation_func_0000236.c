prflags(u_int32_t flags, const FN *fnp)
{
	const char *sep;

	sep = "\t";
	printf("Flags:");
	for (; fnp->mask != 0; ++fnp)
		if (fnp->mask & flags) {
			printf("%s%s", sep, fnp->name);
			sep = ", ";
		}
	printf("\n");
}
