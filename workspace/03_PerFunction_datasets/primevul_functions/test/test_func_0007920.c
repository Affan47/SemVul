void Curl_conncache_remove_conn(struct Curl_easy *data,
                                struct connectdata *conn, bool lock)
{
  struct connectbundle *bundle = conn->bundle;
  struct conncache *connc = data->state.conn_cache;


  if(bundle) {
    if(lock) {
      CONNCACHE_LOCK(data);
    }
    bundle_remove_conn(bundle, conn);
    if(bundle->num_connections == 0)
      conncache_remove_bundle(connc, bundle);
    conn->bundle = NULL;
    if(connc) {
      connc->num_conn--;
      DEBUGF(infof(data, "The cache now contains %zu members",
                   connc->num_conn));
    }
    if(lock) {
      CONNCACHE_UNLOCK(data);
    }
  }
}
