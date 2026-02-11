fcoe_validate_vport_create(struct fc_vport *vport)
{
	struct Scsi_Host *shost = vport_to_shost(vport);
	struct fc_lport *n_port = shost_priv(shost);
	struct fc_lport *vn_port;
	int rc = 0;
	char buf[32];

	mutex_lock(&n_port->lp_mutex);

	fcoe_wwn_to_str(vport->port_name, buf, sizeof(buf));

	if (!memcmp(&n_port->wwpn, &vport->port_name, sizeof(u64))) {
		LIBFCOE_TRANSPORT_DBG("vport WWPN 0x%s is same as that of the "
				      "base port WWPN\n", buf);
		rc = -EINVAL;
		goto out;
	}


	list_for_each_entry(vn_port, &n_port->vports, list) {
		if (!memcmp(&vn_port->wwpn, &vport->port_name, sizeof(u64))) {
			LIBFCOE_TRANSPORT_DBG("vport with given WWPN 0x%s "
					      "already exists\n", buf);
			rc = -EINVAL;
			break;
		}
	}
out:
	mutex_unlock(&n_port->lp_mutex);
	return rc;
}
