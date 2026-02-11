mtn_get_be_distributed(Slapi_PBlock *pb, mapping_tree_node * target_node,
    Slapi_DN *target_sdn, int * flag_stop)
{
    int index;
    *flag_stop = 0;

    if (target_node->mtn_dstr_plg)
    {
        index = (*target_node->mtn_dstr_plg)(pb, target_sdn,
                 target_node->mtn_backend_names, target_node->mtn_be_count,
                 target_node->mtn_subtree, target_node->mtn_be_states, target_node->mtn_dstr_plg_rootmode);

        if (index == SLAPI_BE_ALL_BACKENDS)
        {


            index = 0;
        }


	else if (index == SLAPI_BE_NO_BACKEND || index == SLAPI_BE_REMOTE_BACKEND)
	{

	}

        else if ((index >= target_node->mtn_be_count) || (index < 0))
        {
                LDAPDebug(LDAP_DEBUG_ANY,
                    "Warning: distribution plugin returned wrong backend"
                    " : %d for entry %s at node %s\n",
                     index, slapi_sdn_get_ndn(target_sdn),
                     slapi_sdn_get_ndn(target_node->mtn_subtree));
            	index = 0;
        }
        else
        {


            *flag_stop = 1;
        }
    }
    else
    {


        LDAPDebug(LDAP_DEBUG_ANY,
        "Warning: distribution plugin not configured at node : %s\n",
        slapi_sdn_get_ndn(target_node->mtn_subtree), 0, 0);
        index = 0;
    }

    return index;
}
