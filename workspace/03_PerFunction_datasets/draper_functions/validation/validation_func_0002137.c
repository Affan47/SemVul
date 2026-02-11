local_build_list(copyinfo **filelist,
                            const char *lpath, const char *rpath)
{
    DIR *d;
    struct dirent *de;
    struct stat st;
    copyinfo *dirlist = 0;
    copyinfo *ci, *next;


    d = opendir(lpath);
    if(d == 0) {
        fprintf(stderr,"cannot open '%s': %s\n", lpath, strerror(errno));
        return -1;
    }

    while((de = readdir(d))) {
        char stat_path[PATH_MAX];
        char *name = de->d_name;

        if(name[0] == '.') {
            if(name[1] == 0) continue;
            if((name[1] == '.') && (name[2] == 0)) continue;
        }


        if (strlen(lpath) + strlen(de->d_name) + 1 > sizeof(stat_path))
            continue;
        strcpy(stat_path, lpath);
        strcat(stat_path, de->d_name);
        stat(stat_path, &st);

        if (S_ISDIR(st.st_mode)) {
            ci = mkcopyinfo(lpath, rpath, name, 1);
            ci->next = dirlist;
            dirlist = ci;
        } else {
            ci = mkcopyinfo(lpath, rpath, name, 0);
            if(lstat(ci->src, &st)) {
                fprintf(stderr,"cannot stat '%s': %s\n", ci->src, strerror(errno));
                closedir(d);

                return -1;
            }
            if(!S_ISREG(st.st_mode) && !S_ISLNK(st.st_mode)) {
                fprintf(stderr, "skipping special file '%s'\n", ci->src);
                free(ci);
            } else {
                ci->time = st.st_mtime;
                ci->mode = st.st_mode;
                ci->size = st.st_size;
                ci->next = *filelist;
                *filelist = ci;
            }
        }
    }

    closedir(d);

    for(ci = dirlist; ci != 0; ci = next) {
        next = ci->next;
        local_build_list(filelist, ci->src, ci->dst);
        free(ci);
    }

    return 0;
}
