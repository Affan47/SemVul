kwritev(enum iscsi_uevent_e type, struct iovec *iovp, int count)
{
	int i, rc;
	struct nlmsghdr *nlh;
	struct msghdr msg;
	int datalen = 0;

	log_debug(7, "in %s", __FUNCTION__);

	for (i = 0; i < count; i++) {
		datalen += iovp[i].iov_len;
	}

	if (xmitbuf && type != ISCSI_UEVENT_SEND_PDU) {
		for (i = 0; i < count; i++) {
			memcpy(xmitbuf + xmitlen,
			       iovp[i].iov_base, iovp[i].iov_len);
			xmitlen += iovp[i].iov_len;
		}
		return datalen;
	}

	nlh = nlm_sendbuf;
	memset(nlh, 0, NLMSG_SPACE(0));

	datalen = 0;
	for (i = 1; i < count; i++)
		datalen += iovp[i].iov_len;

	nlh->nlmsg_len = datalen + sizeof(*nlh);
	nlh->nlmsg_pid = getpid();
	nlh->nlmsg_flags = 0;
	nlh->nlmsg_type = type;

	iovp[0].iov_base = (void *)nlh;
	iovp[0].iov_len = sizeof(*nlh);

	memset(&msg, 0, sizeof(msg));
	msg.msg_name= (void*)&dest_addr;
	msg.msg_namelen = sizeof(dest_addr);
	msg.msg_iov = iovp;
	msg.msg_iovlen = count;

	do {


		rc = sendmsg(ctrl_fd, &msg, 0);
		if (rc == -ENOMEM) {
			log_debug(1, "sendmsg: alloc_skb() failed");
			sleep(1);
		} else if (rc < 0) {
			log_error("sendmsg: bug? ctrl_fd %d", ctrl_fd);
			exit(rc);
		}
	} while (rc < 0);

	return rc;
}
