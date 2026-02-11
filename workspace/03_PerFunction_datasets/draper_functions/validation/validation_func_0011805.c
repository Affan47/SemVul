modperl_cmd_log_handlers(cmd_parms *parms, void *dummy, const char *arg)
{
    MP_dSCFG(parms->server);
    modperl_config_dir_t *dcfg = (modperl_config_dir_t *)dummy;
    if (!MpSrvENABLE(scfg)) {
        return apr_pstrcat(parms->pool,
                           "Perl is disabled for server ",
                           parms->server->server_hostname, NULL);
    }
    if (!MpSrvLOG(scfg)) {
        return apr_pstrcat(parms->pool,
                           "PerlLogHandler is disabled for server ",
                           parms->server->server_hostname, NULL);
    }
    MP_TRACE_d(MP_FUNC, "push @%s, %s", parms->cmd->name, arg);
    return modperl_cmd_push_handlers(&(dcfg->handlers_per_dir [MP_LOG_HANDLER]), arg, parms->pool);
}
