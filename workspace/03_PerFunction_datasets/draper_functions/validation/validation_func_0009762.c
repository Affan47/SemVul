rpc_failed(const char* msg) {
    project_rpc_backoff(cur_proj, msg);
    switch (cur_proj->sched_rpc_pending) {
    case RPC_REASON_INIT:
    case RPC_REASON_ACCT_MGR_REQ:
        break;
    default:
        cur_proj->sched_rpc_pending = 0;
    }
    cur_proj = 0;
}
