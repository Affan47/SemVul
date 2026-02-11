globus_l_gfs_be_daemon(
    globus_gfs_embed_handle_t           handle)
{
    char *                              contact_string;
    char *                              interface;
    globus_result_t                     result;
    globus_xio_stack_t                  stack;
    globus_xio_attr_t                   attr;
    GlobusGFSName(globus_l_gfs_be_daemon);
    GlobusGFSDebugEnter();

    result = globus_xio_driver_load("tcp", &globus_l_gfs_tcp_driver);
    if(result != GLOBUS_SUCCESS)
    {
        goto error;
    }

    result = globus_xio_stack_init(&stack, NULL);
    if(result != GLOBUS_SUCCESS)
    {
        goto error;
    }

    result = globus_xio_stack_push_driver(stack, globus_l_gfs_tcp_driver);
    if(result != GLOBUS_SUCCESS)
    {
        goto error;
    }

    result = globus_xio_attr_init(&attr);
    if(result != GLOBUS_SUCCESS)
    {
        goto stack_error;
    }
    if((interface = globus_i_gfs_config_string("control_interface")) != NULL)
    {
        result = globus_xio_attr_cntl(
            attr,
            globus_l_gfs_tcp_driver,
            GLOBUS_XIO_TCP_SET_INTERFACE,
            interface);
        if(result != GLOBUS_SUCCESS)
        {
            goto attr_error;
        }
    }
    result = globus_xio_attr_cntl(
        attr,
        globus_l_gfs_tcp_driver,
        GLOBUS_XIO_TCP_SET_PORT,
        globus_i_gfs_config_int("port"));
    if(result != GLOBUS_SUCCESS)
    {
        goto attr_error;
    }

    result = globus_xio_attr_cntl(
        attr,
        globus_l_gfs_tcp_driver,
        GLOBUS_XIO_TCP_SET_REUSEADDR,
        GLOBUS_TRUE);
    if(result != GLOBUS_SUCCESS)
    {
        goto attr_error;
    }

    result = globus_xio_server_create(&handle->xio_server, attr, stack);
    if(result != GLOBUS_SUCCESS)
    {
        goto attr_error;
    }

    result = globus_xio_server_get_contact_string(
        handle->xio_server,
        &contact_string);
    if(result != GLOBUS_SUCCESS)
    {
        goto server_error;
    }
    globus_gfs_config_set_ptr("contact_string", contact_string);

    result = globus_xio_server_register_accept(
        handle->xio_server,
        globus_l_gfs_server_accept_cb,
        handle);
    if(result != GLOBUS_SUCCESS)
    {
        goto contact_error;
    }
    handle->outstanding++;

    handle->xio_server_accepting = GLOBUS_TRUE;
    globus_xio_stack_destroy(stack);
    globus_xio_attr_destroy(attr);

    GlobusGFSDebugExit();
    return GLOBUS_SUCCESS;

contact_error:
    globus_free(contact_string);
server_error:
    globus_xio_server_close(handle->xio_server);
attr_error:
    globus_xio_attr_destroy(attr);
stack_error:
    globus_xio_stack_destroy(stack);
error:
    GlobusGFSDebugExitWithError();
    return result;
}
