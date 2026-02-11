LoadSymbol(DllHandle handle,
                       const char *symbol_name,
                       void **symbol) {
#ifdef LINUX
  *symbol = dlsym(handle, symbol_name);
  const char *err = dlerror();
  if (err) {
    LOG(LS_ERROR) << "Error loading symbol " << symbol_name << ": " << err;
    return false;
  } else if (!*symbol) {
    LOG(LS_ERROR) << "Symbol " << symbol_name << " is NULL";
    return false;
  }
  return true;
#else
#error Not implemented
#endif
}
