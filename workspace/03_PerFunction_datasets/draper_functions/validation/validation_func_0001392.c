run()
{
  rados_t cl;
  RETURN1_IF_NONZERO(rados_create(&cl, NULL));
  rados_conf_parse_argv(cl, m_argc, m_argv);
  RETURN1_IF_NONZERO(rados_conf_read_file(cl, NULL));
  rados_conf_parse_env(cl, NULL);

  if (m_setup_sem) {
    m_setup_sem->wait();
    m_setup_sem->post();
  }

  rados_ioctx_t io_ctx;
  RETURN1_IF_NONZERO(rados_connect(cl));
  RETURN1_IF_NONZERO(rados_ioctx_create(cl, m_pool_name.c_str(), &io_ctx));

  if (m_notify_sem) {
    m_notify_sem->wait();
    m_notify_sem->post();
  }

  printf("%s: notifying object %s\n", get_id_str(), m_obj_name.c_str());
  RETURN1_IF_NOT_VAL(m_notify_retcode,
		     rados_notify(io_ctx, m_obj_name.c_str(), 0, NULL, 0));
  if (m_notified_sem) {
    m_notified_sem->post();
  }

  rados_ioctx_destroy(io_ctx);
  rados_shutdown(cl);

  return 0;
}
