glusterd_pending_node_get_rpc (glusterd_pending_node_t *pending_node)
{
        struct rpc_clnt *rpc = NULL;
        glusterd_brickinfo_t    *brickinfo = NULL;
        nodesrv_t               *shd       = NULL;
        glusterd_volinfo_t      *volinfo   = NULL;
        nodesrv_t               *nfs       = NULL;

        GF_VALIDATE_OR_GOTO (THIS->name, pending_node, out);
        GF_VALIDATE_OR_GOTO (THIS->name, pending_node->node, out);

        if (pending_node->type == GD_NODE_BRICK) {
                brickinfo = pending_node->node;
                rpc       = brickinfo->rpc;

        } else if (pending_node->type == GD_NODE_SHD) {
                shd       = pending_node->node;
                rpc       = shd->rpc;

        } else if (pending_node->type == GD_NODE_REBALANCE) {
                volinfo = pending_node->node;
                if (volinfo->defrag)
                        rpc = volinfo->defrag->rpc;

        } else if (pending_node->type == GD_NODE_NFS) {
                nfs = pending_node->node;
                rpc = nfs->rpc;

        } else {
                GF_ASSERT (0);
        }

out:
        return rpc;
}
