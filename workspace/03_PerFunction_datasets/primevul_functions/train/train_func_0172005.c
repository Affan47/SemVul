isPathSecure(const char *path)
{
    struct stat sb;


    if (path == NULL) return -1;


    if (lstat(path, &sb) != 0) return 0;


    if ( S_ISLNK(sb.st_mode ) ) return -1;
    if ( S_ISDIR(sb.st_mode ) ) return -1;
    if ( S_ISCHR(sb.st_mode ) ) return -1;
    if ( S_ISBLK(sb.st_mode ) ) return -1;
    if ( S_ISFIFO(sb.st_mode ) ) return -1;
    if ( S_ISSOCK(sb.st_mode ) ) return -1;

    return 0;
}
