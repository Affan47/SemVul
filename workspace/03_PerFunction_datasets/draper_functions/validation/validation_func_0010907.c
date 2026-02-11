sge_stracasecmp(const char *cp, char **cpp)
{
   while (*cpp) {
      if (!strcasecmp(*cpp, cp))
         return cpp;
      cpp++;
   }
   return NULL;
}
