dequeue(WorkerThread::id_t&ID, void*&data) {
    std::pair <id_t, void*> DATA;
    DATA.first=WorkerThread::INVALID;
    DATA.second=0;

    m_pimpl->m_done.lock();
    if(!m_pimpl->q_done.empty()) {
      DATA=m_pimpl->q_done.front();
      m_pimpl->q_done.POP();
    }
    m_pimpl->m_done.unlock();

    ID=DATA.first;
    data=DATA.second;


    return (WorkerThread::INVALID != ID);
  }
