SetGlobalValue(
    const TemplateString variable,
    const TemplateString value) LOCKS_EXCLUDED(g_static_mutex) {


  char* value_copy = new char[value.length_ + 1];
  memcpy(value_copy, value.ptr_, value.length_);
  value_copy[value.length_] = '\0';

  GoogleOnceInit(&g_once, &SetupGlobalDict);

  MutexLock ml(&g_static_mutex);
  HashInsert(global_dict_,
             variable,
             TemplateString(value_copy, value.length_));
}
