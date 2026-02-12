void print_szfun(FILE* outfile, LibRaw& MyCoolRawProcessor, std::string& fn)
{
	id2hr_t *Aspect;
	fprintf(outfile, "%s\t%s\t%s\t%d\t%d\n", fn.c_str(), P1.make, P1.model, S.width,
		S.height);


}
