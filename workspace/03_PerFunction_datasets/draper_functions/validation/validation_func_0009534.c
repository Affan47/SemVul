get()
  {
    RegisterValue rv = m_cpu->registers[m_addr]->getRV();
    return rv.init ? m_unknown : m_cpu->registers[rv.data]->getRV();
  }
