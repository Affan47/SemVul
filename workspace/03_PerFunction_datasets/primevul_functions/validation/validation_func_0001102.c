void Profiler::beginFrame(const char *symbol) {
  Frame *current = createFrame(symbol);


  int recursion_level = 0;
  if (m_func_hash_counters[current->m_hash_code] > 0) {

    for (Frame *p = current->m_parent; p; p = p->m_parent) {
      if (strcmp(current->m_name, p->m_name) == 0) {
        recursion_level = p->m_recursion + 1;
        break;
      }
    }
  }
  current->m_recursion = recursion_level;

  m_func_hash_counters[current->m_hash_code]++;
  beginFrameEx(symbol);
}
