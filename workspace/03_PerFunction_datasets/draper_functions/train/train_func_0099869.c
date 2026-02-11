nlm_unset_rpc_clnt (rpc_clnt_t *rpc)
{
        nlm_client_t *nlmclnt = NULL;
        rpc_clnt_t *rpc_clnt = NULL;

        LOCK (&nlm_client_list_lk);
        list_for_each_entry (nlmclnt, &nlm_client_list, nlm_clients) {
                if (rpc == nlmclnt->rpc_clnt) {
                        rpc_clnt = nlmclnt->rpc_clnt;
                        nlmclnt->rpc_clnt = NULL;
                        break;
                }
        }
        UNLOCK (&nlm_client_list_lk);
        if (rpc_clnt == NULL) {
                return -1;
        }
        if (rpc_clnt) {

                rpc_clnt_connection_cleanup (&rpc_clnt->conn);

                rpc_clnt_unref (rpc_clnt);
        }
        return 0;
}
