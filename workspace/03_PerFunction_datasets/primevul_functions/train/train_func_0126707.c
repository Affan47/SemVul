set_readline(char * (**fn_readline_ptr)(const char *),
             void   (**fn_addhist_ptr)(const char *))
{
void *dlhandle;
void *dlhandle_curses = dlopen("libcurses." DYNLIB_FN_EXT, RTLD_GLOBAL|RTLD_LAZY);

dlhandle = dlopen("libreadline." DYNLIB_FN_EXT, RTLD_GLOBAL|RTLD_NOW);
if (dlhandle_curses != NULL) dlclose(dlhandle_curses);

if (dlhandle != NULL)
  {


  *fn_readline_ptr = (char *(*)(const char*))dlsym(dlhandle, "readline");
  *fn_addhist_ptr = (void(*)(const char*))dlsym(dlhandle, "add_history");
  }
else
  {
  DEBUG(D_any) debug_printf("failed to load readline: %s\n", dlerror());
  }

return dlhandle;
}
