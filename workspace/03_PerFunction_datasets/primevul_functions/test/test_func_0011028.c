line_capability(const char *name)
{
    bool result = FALSE;
    static const char *table[] =
    {
	"csr",
	"clear",
	"ed",
	"cwin",
	"cup",
	"cud1",
	"home",
	"mrcup",
	"ll",
	"cuu1",
	"dl1",
	"hd",
	"flash",
	"ff",
	"il1",
	"nel",
	"dl",
	"cud",
	"indn",
	"il",
	"rin",
	"cuu",
	"mc0",
	"vpa",
	"ind",
	"ri",
	"hu",
    };
    size_t n;
    for (n = 0; n < SIZEOF(table); ++n) {
	if (!strcmp(name, table[n])) {
	    result = TRUE;
	    break;
	}
    }
    return result;
}
