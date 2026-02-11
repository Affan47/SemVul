rpc_reason_string_translated(int reason) {
    switch (reason) {
    case RPC_REASON_USER_REQ: return _("Requested by user");
    case RPC_REASON_NEED_WORK: return _("To fetch work");
    case RPC_REASON_RESULTS_DUE: return _("To report completed tasks");
    case RPC_REASON_TRICKLE_UP: return _("To send trickle-up message");
    case RPC_REASON_ACCT_MGR_REQ: return _("Requested by account manager");
    case RPC_REASON_INIT: return _("Project initialization");
    case RPC_REASON_PROJECT_REQ: return _("Requested by project");
    default: return _("Unknown reason");
    }
}
