afd_open(AFFILE *af)
{
    if(af->fname==0 || strlen(af->fname)==0) return -1;


    char *lastc = af->fname + strlen(af->fname) - 1;
    if(*lastc=='/') *lastc = '\000';


    struct stat sb;
    af->exists = 1;
    if(stat(af->fname,&sb)!=0){
	if((af->openflags & O_CREAT) == 0){
	    errno = ENOTDIR;
	    return -1;
	}
	mode_t cmask = umask(0);
	umask(cmask & 077);
	mkdir(af->fname,af->openmode|0111);
	umask(cmask);
	af->exists = 0;
	if(stat(af->fname,&sb)) return -1;
    }

    if(!S_ISDIR(sb.st_mode)){
	errno = ENOTDIR;
	return -1;
    }


    af->maxsize = AFD_DEFAULT_MAXSIZE;
    af->vnodeprivate = (void *)calloc(1,sizeof(struct afd_private));
    struct afd_private *ap = AFD_PRIVATE(af);
    ap->afs = (AFFILE **)malloc(sizeof(AFFILE *));


    DIR *dirp = opendir(af->fname);
    if(!dirp){
	return -1;
    }
    struct dirent *dp;
    while ((dp = readdir(dirp)) != NULL){
	if (af_ext_is(dp->d_name,"aff")){
	    char path[MAXPATHLEN+1];
	    strlcpy(path,af->fname,sizeof(path));
	    strlcat(path,"/",sizeof(path));
	    strlcat(path,dp->d_name,sizeof(path));
	    if(afd_add_file(af,path)){
		return -1;
	    }
	}
    }
    closedir(dirp);
    if(ap->num_afs==0 && af->exists){
	snprintf(af->error_str,sizeof(af->error_str),".afd directory contains no .aff files!");
	return -1;
    }
    return 0;
}
