ajFilewildnameExistsDir(const AjPStr wildname, const AjPStr path)
{
    DIR* dp;
#if defined(AJ_IRIXLF)
    struct dirent64 *de;
#else
    struct dirent* de;
#endif

#ifdef _POSIX_C_SOURCE
    char buf[sizeof(struct dirent)+MAXNAMLEN];
#endif

    if(ajStrGetLen(path))
        ajStrAssignS(&fileDirfixTmp, path);
    else
        ajStrAssignC(&fileDirfixTmp, CURRENT_DIR);

    if(ajStrGetCharLast(fileDirfixTmp) != SLASH_CHAR)
        ajStrAppendC(&fileDirfixTmp, SLASH_STRING);

    dp = fileOpenDir(&fileDirfixTmp);

    if(!dp)
        return ajFalse;

    while(
#if defined(AJ_IRIXLF)
#ifdef _POSIX_C_SOURCE
        !readdir64_r(dp,(struct dirent64 *)buf,&de)
#else
        (de=readdir64(dp))
#endif
#else
#ifdef _POSIX_C_SOURCE
        !readdir_r(dp,(struct dirent *)buf,&de)
#else
        (de=readdir(dp))
#endif
#endif
          )
    {
#ifdef _POSIX_C_SOURCE
        if(!de)
            break;
#endif

#ifndef __CYGWIN__
        if(!de->d_ino)
            continue;
#endif

        if(ajCharMatchC(de->d_name, "."))
            continue;

        if(ajCharMatchC(de->d_name, ".."))
            continue;

        if(!ajCharMatchWildS(de->d_name, wildname))
            continue;

        ajDebug("accept '%s'\n", de->d_name);
        closedir(dp);
        return ajTrue;
    }

    ajDebug("no files for '%S' '%S'\n", path, wildname);
    closedir(dp);

    return ajFalse;
}
