getICValues(icp, data, len, nest, offset, sepp)
IMIC *icp;
char *data;
int len;
int nest;
int offset;
int *sepp;
{
    unsigned int id;
    ICAttribute *attrp;
    IMConnection *conn = icp->im->connection;
    int byte_order = conn->byte_order;
    char *org_data = data;
    int r;

    TRACE(("imlib:getICValues()\n"));

    while (len >= 2) {
	id = getC16(data, byte_order);
	data += 2;
	len -= 2;

	if (id > numIcAttributes) {

	    DPRINT(("invalid IC attribute ID (%d) specified\n", id));
	    IMCancelRequest(conn, offset);
	    IMSendError(conn, IMBadSomething, icp->im->id, icp->id,
			"invalid IC attribute ID");
	    return -1;
	}

	attrp = &icAttributes[id];
	if (attrp->type == TYPE_SEPARATOR) {

	    *sepp = 1;
	    return data - org_data;
	}

	if (!(attrp->valid_ops & OP_G)) {
	    DPRINT(("invalid operation (get) for IC attr %d\n", id));
	    IMCancelRequest(conn, offset);
	    IMSendError(conn, IMBadSomething, icp->im->id, icp->id,
			"invalid operation (ICGetValues) for this attribute");
	    return -1;
	}

	r = (*attrp->get_proc)(icp, id, nest, offset, data, len);


	if (r < 0) return -1;

	data += r;
	len -= r;
    }
    *sepp = 0;
    return data - org_data;
}
