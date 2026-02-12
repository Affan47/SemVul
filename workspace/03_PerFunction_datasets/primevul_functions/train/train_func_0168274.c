int wget_main(int argc UNUSED_PARAM, char **argv)
{
#if ENABLE_FEATURE_WGET_LONG_OPTIONS
	static const char wget_longopts[] ALIGN1 =

		"continue\0"         No_argument       "c"
		"quiet\0"            No_argument       "q"
		"server-response\0"  No_argument       "S"
		"output-document\0"  Required_argument "O"
		"output-file\0"      Required_argument "o"
		"directory-prefix\0" Required_argument "P"
		"proxy\0"            Required_argument "Y"
		"user-agent\0"       Required_argument "U"
IF_FEATURE_WGET_TIMEOUT(
		"timeout\0"          Required_argument "T")

IF_DESKTOP(	"tries\0"            Required_argument "t")
		"header\0"           Required_argument "\xff"
		"post-data\0"        Required_argument "\xfe"
		"spider\0"           No_argument       "\xfd"
		"no-check-certificate\0" No_argument   "\xfc"

IF_DESKTOP(	"passive-ftp\0"      No_argument       "\xf0")

IF_DESKTOP(	"no-cache\0"         No_argument       "\xf0")
IF_DESKTOP(	"no-verbose\0"       No_argument       "\xf0")
IF_DESKTOP(	"no-clobber\0"       No_argument       "\xf0")
IF_DESKTOP(	"no-host-directories\0" No_argument    "\xf0")
IF_DESKTOP(	"no-parent\0"        No_argument       "\xf0")
		;
# define GETOPT32 getopt32long
# define LONGOPTS ,wget_longopts
#else
# define GETOPT32 getopt32
# define LONGOPTS
#endif

#if ENABLE_FEATURE_WGET_LONG_OPTIONS
	llist_t *headers_llist = NULL;
#endif

	INIT_G();

#if ENABLE_FEATURE_WGET_TIMEOUT
	G.timeout_seconds = 900;
	signal(SIGALRM, alarm_handler);
#endif
	G.proxy_flag = "on";
	G.user_agent = "Wget";

	GETOPT32(argv, "^"
		"cqSO:o:P:Y:U:T:+"
		 "t:"
		 "n::"


		"\0"
		"-1"
		IF_FEATURE_WGET_LONG_OPTIONS(":\xff::")
		LONGOPTS
		, &G.fname_out, &G.fname_log, &G.dir_prefix,
		&G.proxy_flag, &G.user_agent,
		IF_FEATURE_WGET_TIMEOUT(&G.timeout_seconds) IF_NOT_FEATURE_WGET_TIMEOUT(NULL),
		NULL,
		NULL
		IF_FEATURE_WGET_LONG_OPTIONS(, &headers_llist)
		IF_FEATURE_WGET_LONG_OPTIONS(, &G.post_data)
	);
#if 0
	if (option_mask32 & WGET_OPT_RETRIES) bb_error_msg("-t NUM");
	if (option_mask32 & WGET_OPT_nsomething) bb_error_msg("-nsomething");
	if (option_mask32 & WGET_OPT_HEADER) bb_error_msg("--header");
	if (option_mask32 & WGET_OPT_POST_DATA) bb_error_msg("--post-data");
	if (option_mask32 & WGET_OPT_SPIDER) bb_error_msg("--spider");
	if (option_mask32 & WGET_OPT_NO_CHECK_CERT) bb_error_msg("--no-check-certificate");
	exit(0);
#endif
	argv += optind;

#if ENABLE_FEATURE_WGET_LONG_OPTIONS
	if (headers_llist) {
		int size = 0;
		char *hdr;
		llist_t *ll = headers_llist;
		while (ll) {
			size += strlen(ll->data) + 2;
			ll = ll->link;
		}
		G.extra_headers = hdr = xmalloc(size + 1);
		while (headers_llist) {
			int bit;
			const char *words;

			size = sprintf(hdr, "%s\r\n",
					(char*)llist_pop(&headers_llist));

			bit = 1;
			words = wget_user_headers;
			while (*words) {
				if (strstr(hdr, words) == hdr) {
					G.user_headers |= bit;
					break;
				}
				bit <<= 1;
				words += strlen(words) + 1;
			}
			hdr += size;
		}
	}
#endif

	G.output_fd = -1;
	G.o_flags = O_WRONLY | O_CREAT | O_TRUNC | O_EXCL;
	if (G.fname_out) {
		if (LONE_DASH(G.fname_out)) {
			G.output_fd = 1;
			option_mask32 &= ~WGET_OPT_CONTINUE;
		}

		G.o_flags = O_WRONLY | O_CREAT | O_TRUNC;
	}

	G.log_fd = -1;
	if (G.fname_log) {
		if (!LONE_DASH(G.fname_log)) {

			G.log_fd = xopen(G.fname_log, O_WRONLY | O_CREAT | O_TRUNC);

			xdup2(G.log_fd, STDERR_FILENO);
		}
	}

	while (*argv)
		download_one_url(*argv++);

	if (G.output_fd >= 0)
		xclose(G.output_fd);

	if (G.log_fd >= 0)
		xclose(G.log_fd);

#if ENABLE_FEATURE_CLEAN_UP && ENABLE_FEATURE_WGET_LONG_OPTIONS
	free(G.extra_headers);
#endif
	FINI_G();

	return EXIT_SUCCESS;
}
