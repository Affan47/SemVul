_e_fm2_path_parent_set(Evas_Object *obj, const char *path)
{
   char buf[PATH_MAX], *p;
   int idx;

   p = strrchr(path, '/');
   if (!p || (p == path))
     e_fm2_path_set(obj, "/", "/");
   else
     {
        idx = p - path;
        if (idx < PATH_MAX)
          {
             strncpy(buf, path, idx);
             buf[idx] = '\0';
             e_fm2_path_set(obj, "/", buf);
          }
        else
          e_fm2_path_set(obj, "/", "/");
     }
}
