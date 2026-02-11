usage(const char *arg0, bool brief)
{
	printf("Usage: sechecker [OPTIONS] -p profile [POLICY ...]\n");
	printf("       sechecker [OPTIONS] -m module [POLICY ...]\n");
	printf("       sechecker [OPTIONS] -p profile -m module [POLICY ...]\n");
	printf("\n");
	if (brief) {
		printf("\tTry %s --help for more help.\n\n", arg0);
	} else {
		printf("Perform modular checks on a SELinux policy.\n");
		printf("\n");
		printf("   -p PROF, --profile=PROF      name or path of profile to load\n");
		printf("                                if used without -m, run all modules in profile\n");
		printf("   -m MODULE, --module=MODULE   MODULE to run\n");
		printf("   --fcfile=FILE                file_contexts file to load\n");
		printf("\n");
		printf("   -q, --quiet                  suppress output\n");
		printf("   -s, --short                  print short output\n");
		printf("   -v, --verbose                print verbose output\n");
		printf("   --min-sev={low|med|high}     set the minimum severity to report\n");
		printf("\n");
		printf("   -l, --list                   print a list of profiles and modules and exit\n");
		printf("   -h[MODULE], --help[=MODULE]  print this help text or help for MODULE\n");
		printf("   -V, --version                print version information and exit\n");
		printf("\n");
	}
}
