sendnodecmdoptimize(int clsock, REQUEST *req, NODE *node){
  CBDATUM *datum;
  if(est_mtdb_optimize(node->db, ESTOPTNOPURGE)){
    node->mtime = req->now;
    datum = cbdatumopen(NULL, -1);
    cbdatumprintf(datum, "HTTP/1.0 200 OK\r\n");
    addservinfo(datum, req->now, 0);
    cbdatumprintf(datum, "Content-Type: text/plain; charset=UTF-8\r\n");
    cbdatumprintf(datum, "\r\n");
    cbdatumprintf(datum, "OK\n");
    est_sock_send_all(clsock, cbdatumptr(datum), cbdatumsize(datum));
    cbdatumclose(datum);
    log_print(LL_DEBUG, "[%s:%d]: 200 OK (optimize)", req->claddr, req->clport);
  } else {
    if(est_mtdb_fatal(node->db))
      log_print(LL_ERROR, "DB-ERROR: %s", est_err_msg(est_mtdb_error(node->db)));
    senderror(clsock, req, 400, "Bad Request (maybe, the database has a fatal error)");
  }
}
