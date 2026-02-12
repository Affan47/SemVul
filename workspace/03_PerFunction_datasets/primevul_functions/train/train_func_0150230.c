void MonClient::_finish_auth(int auth_err)
{
  ldout(cct,10) << __func__ << " " << auth_err << dendl;
  authenticate_err = auth_err;


  if (!auth_err && active_con) {
    ceph_assert(auth);
    _check_auth_tickets();
  }
  auth_cond.SignalAll();

  if (!auth_err) {
    Context *cb = nullptr;
    if (session_established_context) {
      cb = session_established_context.release();
    }
    if (cb) {
      monc_lock.Unlock();
      cb->complete(0);
      monc_lock.Lock();
    }
  }
}
