collect()
{

  m_comm->broadcast(m_id);

  if((m_write_type==WRITE_TYPE_SUM)||(m_write_type==WRITE_TYPE_MAX)) {
    collectSum();
  } else {
    collectFull();
  }

}
