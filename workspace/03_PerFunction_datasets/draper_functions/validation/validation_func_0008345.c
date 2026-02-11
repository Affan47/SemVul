fileutils_move (const char *srcpath, const char *dstpath)

{
int  ii;

struct stat sb;


ER_TRACE(__func__)

if ((ii = fileutils_copy (srcpath, dstpath)) != 0)
   {
   if (ii == 99)
      return 99;
   else
      return (-2);
   }


if (stat (srcpath, &sb) == -1 || !(sb.st_mode & S_IWUSR))
   {
   (void) unlink (dstpath);
   return -1;
   }

   (void) unlink (srcpath);
return 0;

}
