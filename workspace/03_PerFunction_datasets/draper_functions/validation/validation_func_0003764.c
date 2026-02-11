cb_config_add_check_callback(Slapi_PBlock *pb, Slapi_Entry* e, Slapi_Entry* e2, int *returncode,
        char *returntext, void *arg)
{
        Slapi_Attr              *attr = NULL;
        Slapi_Value             *sval;
        struct berval *          bval;
        int                     i;
        cb_backend      *cb = (cb_backend *) arg;

        CB_ASSERT (cb!=NULL);

        for (slapi_entry_first_attr(e, &attr); attr; slapi_entry_next_attr(e, attr, &attr)) {
                char * attr_name=NULL;
                slapi_attr_get_type(attr, &attr_name);

                if ( !strcasecmp ( attr_name, CB_CONFIG_GLOBAL_FORWARD_CTRLS )) {

                        i = slapi_attr_first_value(attr, &sval);
                        while (i != -1 ) {
                                bval = (struct berval *) slapi_value_get_berval(sval);
                                if (!cb_is_control_forwardable(cb,bval->bv_val)) {
                                        slapi_log_error(SLAPI_LOG_PLUGIN,CB_PLUGIN_SUBSYSTEM,
                                                "control %s can't be forwarded.\n",bval->bv_val);
                                        *returncode=LDAP_CONSTRAINT_VIOLATION;
                                        return SLAPI_DSE_CALLBACK_ERROR;
                                }
                                i = slapi_attr_next_value(attr, i, &sval);
                        }
                }
        }
        *returncode=LDAP_SUCCESS;
        return SLAPI_DSE_CALLBACK_OK;
}
