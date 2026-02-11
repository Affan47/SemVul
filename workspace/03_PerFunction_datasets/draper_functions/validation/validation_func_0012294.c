mca_btl_sctp_component_accept(void)
{
    if(mca_btl_sctp_component.sctp_if_11) {

        while(true) {
            opal_socklen_t addrlen = sizeof(struct sockaddr_in);
            struct sockaddr_in addr;
            mca_btl_sctp_event_t *event;
            int rc, sd = accept(mca_btl_sctp_component.sctp_listen_sd, (struct sockaddr*)&addr, &addrlen);
            if(sd < 0) {
                if(opal_socket_errno == EINTR) {
                    continue;
                }
                if(opal_socket_errno == ECONNRESET || opal_socket_errno == EBADF) {

                    close(sd);
                }
                else if(opal_socket_errno != EAGAIN && opal_socket_errno != EWOULDBLOCK) {
                    BTL_ERROR(("accept() failed with errno %d.", opal_socket_errno));
                }
                return;
            }

            if((rc = mca_btl_sctp_set_socket_options(sd)) != OMPI_SUCCESS) {
                BTL_ERROR(("failed to set socket options"));
                return;
            }


            event = OBJ_NEW(mca_btl_sctp_event_t);
            opal_event_set(opal_event_base, &event->event, sd, OPAL_EV_READ, mca_btl_sctp_component_recv_handler, event);
            opal_event_add(&event->event, 0);
        }
    }

    else {


        mca_btl_sctp_event_t *event;
        int sd = mca_btl_sctp_component.sctp_listen_sd;

        if(sd < 0) {
            BTL_ERROR(("mca_btl_sctp_component_accept(): Invalid socket descriptor.\n"));
        }


        event = OBJ_NEW(mca_btl_sctp_event_t);
        opal_event_set(opal_event_base, &event->event, sd, OPAL_EV_READ, mca_btl_sctp_recv_handler, event);
        opal_event_add(&event->event, 0);
    }
}
