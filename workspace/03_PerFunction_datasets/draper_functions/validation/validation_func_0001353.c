handle_blacklist_host_env(CS * c, Msg * _m)
{
  BlacklistHostEnvMsg *m = dynamic_cast<BlacklistHostEnvMsg *>(_m);
  if (!m)
    return false;
  for (list<CS*>::const_iterator it = css.begin(); it != css.end(); ++it)
    if ( (*it)->name == m->hostname )
      {
        trace() << "Blacklisting host " << m->hostname << " for environment " << m->environment
             << " (" << m->target << ")" << endl;
        c->blacklist[ *it ].push_back( make_pair( m->target, m->environment ));
      }
  return true;
}
