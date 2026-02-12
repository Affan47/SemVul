int realMain(int argc, char **argv)
{
	DEFiRet;

	register uchar *p;
	int ch;
	struct hostent *hent;
	extern int optind;
	extern char *optarg;
	int bEOptionWasGiven = 0;
	int bImUxSockLoaded = 0;
	int iHelperUOpt;
	int bChDirRoot = 1;
	char *arg;
	uchar legacyConfLine[80];
	uchar *LocalHostName;
	uchar *LocalDomain;
	uchar *LocalFQDNName;


	while((ch = getopt(argc, argv, "46a:Ac:def:g:hi:l:m:M:nN:op:qQr::s:t:T:u:vwx")) != EOF) {
		switch((char)ch) {
                case '4':
                case '6':
                case 'A':
                case 'a':
		case 'f':
		case 'h':
		case 'i':
		case 'l':
		case 'm':
		case 'n':
		case 'N':
                case 'o':
                case 'p':
		case 'q':
		case 'Q':
		case 's':
		case 'T':
		case 'u':
		case 'w':
		case 'x':
			CHKiRet(bufOptAdd(ch, optarg));
			break;
		case 'c':
			iCompatibilityMode = atoi(optarg);
			break;
		case 'd':
			debugging_on = 1;
			Debug = 1;
			break;
		case 'e':
			fprintf(stderr, "note: -e option is no longer supported, every message is now logged by default\n");
			bEOptionWasGiven = 1;
			break;
		case 'g':
#if defined(SYSLOG_INET) && defined(USE_GSSAPI)
			CHKiRet(bufOptAdd('g', optarg));
#else
			fprintf(stderr, "rsyslogd: -g not valid - not compiled with gssapi support");
#endif
			break;
		case 'M':
			glblModPath = (uchar*) optarg;
			break;
		case 'r':
#ifdef SYSLOG_INET
			CHKiRet(bufOptAdd(ch, optarg));
#else
			fprintf(stderr, "rsyslogd: -r not valid - not compiled with network support\n");
#endif
			break;
		case 't':
#ifdef SYSLOG_INET
			CHKiRet(bufOptAdd(ch, optarg));
#else
			fprintf(stderr, "rsyslogd: -t not valid - not compiled with network support\n");
#endif
			break;
		case 'v':
			printVersion();
			exit(0);
		case '?':
		default:
			usage();
		}
	}

	if ((argc -= optind))
		usage();

	DBGPRINTF("rsyslogd %s startup, compatibility mode %d, module path '%s'\n",
		  VERSION, iCompatibilityMode, glblModPath == NULL ? "" : (char*)glblModPath);


	ppid = getpid();

	CHKiRet_Hdlr(InitGlobalClasses()) {
		fprintf(stderr, "rsyslogd initializiation failed - global classes could not be initialized.\n"
				"Did you do a \"make install\"?\n"
				"Suggested action: run rsyslogd with -d -n options to see what exactly "
				"fails.\n");
		FINALIZE;
	}


	CHKiRet(prop.Construct(&pInternalInputName));
	CHKiRet(prop.SetString(pInternalInputName, UCHAR_CONSTANT("rsyslogd"), sizeof("rsyslgod") - 1));
	CHKiRet(prop.ConstructFinalize(pInternalInputName));

	CHKiRet(prop.Construct(&pLocalHostIP));
	CHKiRet(prop.SetString(pLocalHostIP, UCHAR_CONSTANT("127.0.0.1"), sizeof("127.0.0.1") - 1));
	CHKiRet(prop.ConstructFinalize(pLocalHostIP));


	net.getLocalHostname(&LocalFQDNName);
	CHKmalloc(LocalHostName = (uchar*) strdup((char*)LocalFQDNName));
	glbl.SetLocalFQDNName(LocalFQDNName);
	if((p = (uchar*)strchr((char*)LocalHostName, '.'))) {
		*p++ = '\0';
		LocalDomain = p;
	} else {
		LocalDomain = (uchar*)"";


		hent = gethostbyname((char*)LocalHostName);
		if(hent) {
			free(LocalHostName);
			CHKmalloc(LocalHostName = (uchar*)strdup(hent->h_name));

			if((p = (uchar*)strchr((char*)LocalHostName, '.')))
			{
				*p++ = '\0';
				LocalDomain = p;
			}
		}
	}


	for(p = LocalDomain ; *p ; p++)
		*p = (char)tolower((int)*p);


	glbl.SetLocalHostName(LocalHostName);
	glbl.SetLocalDomain(LocalDomain);
	glbl.GenerateLocalHostNameProperty();


	if((iRet = modInitIminternal()) != RS_RET_OK) {
		fprintf(stderr, "fatal error: could not initialize errbuf object (error code %d).\n",
			iRet);
		exit(1);
	}

	if((iRet = loadBuildInModules()) != RS_RET_OK) {
		fprintf(stderr, "fatal error: could not activate built-in modules. Error code %d.\n",
			iRet);
		exit(1);
	}


	while((iRet = bufOptRemove(&ch, &arg)) == RS_RET_OK) {
		DBGPRINTF("deque option %c, optarg '%s'\n", ch, (arg == NULL) ? "" : arg);
		switch((char)ch) {
                case '4':
	                glbl.SetDefPFFamily(PF_INET);
                        break;
                case '6':
                        glbl.SetDefPFFamily(PF_INET6);
                        break;
                case 'A':
                        send_to_all++;
                        break;
                case 'a':
			if(iCompatibilityMode < 3) {
				if(!bImUxSockLoaded) {
					legacyOptsEnq((uchar *) "ModLoad imuxsock");
					bImUxSockLoaded = 1;
				}
				snprintf((char *) legacyConfLine, sizeof(legacyConfLine), "addunixlistensocket %s", arg);
				legacyOptsEnq(legacyConfLine);
			} else {
				fprintf(stderr, "error -a is no longer supported, use module imuxsock instead");
			}
                        break;
		case 'f':
			ConfFile = (uchar*) arg;
			break;
		case 'g':
			if(iCompatibilityMode < 3) {
				legacyOptsParseTCP(ch, arg);
			} else
				fprintf(stderr,	"-g option only supported in compatibility modes 0 to 2 - ignored\n");
			break;
		case 'h':
			if(iCompatibilityMode < 3) {
				errmsg.LogError(0, NO_ERRCODE, "WARNING: -h option is no longer supported - ignored");
			} else {
				usage();
			}
			break;
		case 'i':
			PidFile = arg;
			break;
		case 'l':
			if(glbl.GetLocalHosts() != NULL) {
				fprintf (stderr, "rsyslogd: Only one -l argument allowed, the first one is taken.\n");
			} else {
				glbl.SetLocalHosts(crunch_list(arg));
			}
			break;
		case 'm':
			if(iCompatibilityMode < 3) {
				MarkInterval = atoi(arg) * 60;
			} else
				fprintf(stderr,
					"-m option only supported in compatibility modes 0 to 2 - ignored\n");
			break;
		case 'n':
			NoFork = 1;
			break;
		case 'N':
			iConfigVerify = atoi(arg);
			break;
                case 'o':
			if(iCompatibilityMode < 3) {
				if(!bImUxSockLoaded) {
					legacyOptsEnq((uchar *) "ModLoad imuxsock");
					bImUxSockLoaded = 1;
				}
				legacyOptsEnq((uchar *) "OmitLocalLogging");
			} else {
				fprintf(stderr, "error -o is no longer supported, use module imuxsock instead");
			}
                        break;
                case 'p':
			if(iCompatibilityMode < 3) {
				if(!bImUxSockLoaded) {
					legacyOptsEnq((uchar *) "ModLoad imuxsock");
					bImUxSockLoaded = 1;
				}
				snprintf((char *) legacyConfLine, sizeof(legacyConfLine), "SystemLogSocketName %s", arg);
				legacyOptsEnq(legacyConfLine);
			} else {
				fprintf(stderr, "error -p is no longer supported, use module imuxsock instead");
			}
			break;
		case 'q':
		        *(net.pACLAddHostnameOnFail) = 1;
		        break;
		case 'Q':
		        *(net.pACLDontResolve) = 1;
		        break;
		case 'r':
			if(iCompatibilityMode < 3) {
				legacyOptsEnq((uchar *) "ModLoad imudp");
				snprintf((char *) legacyConfLine, sizeof(legacyConfLine), "UDPServerRun %s", arg);
				legacyOptsEnq(legacyConfLine);
			} else
				fprintf(stderr, "-r option only supported in compatibility modes 0 to 2 - ignored\n");
			break;
		case 's':
			if(glbl.GetStripDomains() != NULL) {
				fprintf (stderr, "rsyslogd: Only one -s argument allowed, the first one is taken.\n");
			} else {
				glbl.SetStripDomains(crunch_list(arg));
			}
			break;
		case 't':
			if(iCompatibilityMode < 3) {
				legacyOptsParseTCP(ch, arg);
			} else
				fprintf(stderr,	"-t option only supported in compatibility modes 0 to 2 - ignored\n");
			break;
		case 'T':
			if(chroot(arg) != 0) {
				perror("chroot");
				exit(1);
			}
			break;
		case 'u':
			iHelperUOpt = atoi(arg);
			if(iHelperUOpt & 0x01)
				bParseHOSTNAMEandTAG = 0;
			if(iHelperUOpt & 0x02)
				bChDirRoot = 0;
			break;
		case 'w':
			glbl.SetOption_DisallowWarning(0);
			break;
		case 'x':
			glbl.SetDisableDNS(1);
			break;
		case '?':
		default:
			usage();
		}
	}

	if(iRet != RS_RET_END_OF_LINKEDLIST)
		FINALIZE;

	if(iConfigVerify) {
		fprintf(stderr, "rsyslogd: version %s, config validation run (level %d), master config %s\n",
			VERSION, iConfigVerify, ConfFile);
	}

	if(bChDirRoot) {
		if(chdir("/") != 0)
			fprintf(stderr, "Can not do 'cd /' - still trying to run\n");
	}


	if(iCompatibilityMode < 4) {
		errmsg.LogError(0, NO_ERRCODE, "WARNING: rsyslogd is running in compatibility mode. Automatically "
		                            "generated config directives may interfer with your rsyslog.conf settings. "
					    "We suggest upgrading your config and adding -c4 as the first "
					    "rsyslogd option.");
	}

	if(iCompatibilityMode < 3) {
		if(MarkInterval > 0) {
			legacyOptsEnq((uchar *) "ModLoad immark");
			snprintf((char *) legacyConfLine, sizeof(legacyConfLine), "MarkMessagePeriod %d", MarkInterval);
			legacyOptsEnq(legacyConfLine);
		}
		if(!bImUxSockLoaded) {
			legacyOptsEnq((uchar *) "ModLoad imuxsock");
		}
	}

	if(bEOptionWasGiven && iCompatibilityMode < 3) {
		errmsg.LogError(0, NO_ERRCODE, "WARNING: \"message repeated n times\" feature MUST be turned on in "
					    "rsyslog.conf - CURRENTLY EVERY MESSAGE WILL BE LOGGED. Visit "
					    "http://www.rsyslog.com/rptdmsgreduction to learn "
					    "more and cast your vote if you want us to keep this feature.");
	}

	if(!iConfigVerify)
		CHKiRet(doGlblProcessInit());


	glbl.GenerateLocalHostNameProperty();

	CHKiRet(mainThread());


	die(bFinished);

	thrdExit();

finalize_it:
	if(iRet == RS_RET_VALIDATION_RUN) {
		fprintf(stderr, "rsyslogd: End of config validation run. Bye.\n");
	} else if(iRet != RS_RET_OK) {
		fprintf(stderr, "rsyslogd run failed with error %d (see rsyslog.h "
				"or try http://www.rsyslog.com/e/%d to learn what that number means)\n", iRet, iRet*-1);
	}

	ENDfunc
	return 0;
}
