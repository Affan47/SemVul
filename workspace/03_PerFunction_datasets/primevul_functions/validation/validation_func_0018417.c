static void hci_sync_conn_complete_evt(struct hci_dev *hdev,
				       struct sk_buff *skb)
{
	struct hci_ev_sync_conn_complete *ev = (void *) skb->data;
	struct hci_conn *conn;

	BT_DBG("%s status 0x%2.2x", hdev->name, ev->status);

	hci_dev_lock(hdev);

	conn = hci_conn_hash_lookup_ba(hdev, ev->link_type, &ev->bdaddr);
	if (!conn) {
		if (ev->link_type == ESCO_LINK)
			goto unlock;


		conn = hci_conn_hash_lookup_ba(hdev, ESCO_LINK, &ev->bdaddr);
		if (!conn)
			goto unlock;
	}

	switch (ev->status) {
	case 0x00:
		conn->handle = __le16_to_cpu(ev->handle);
		conn->state  = BT_CONNECTED;
		conn->type   = ev->link_type;

		hci_debugfs_create_conn(conn);
		hci_conn_add_sysfs(conn);
		break;

	case 0x10:
	case 0x0d:
	case 0x11:
	case 0x1c:
	case 0x1a:
	case 0x1e:
	case 0x1f:
	case 0x20:
		if (conn->out) {
			conn->pkt_type = (hdev->esco_type & SCO_ESCO_MASK) |
					(hdev->esco_type & EDR_ESCO_MASK);
			if (hci_setup_sync(conn, conn->link->handle))
				goto unlock;
		}


	default:
		conn->state = BT_CLOSED;
		break;
	}

	bt_dev_dbg(hdev, "SCO connected with air mode: %02x", ev->air_mode);

	switch (conn->setting & SCO_AIRMODE_MASK) {
	case SCO_AIRMODE_CVSD:
		if (hdev->notify)
			hdev->notify(hdev, HCI_NOTIFY_ENABLE_SCO_CVSD);
		break;
	case SCO_AIRMODE_TRANSP:
		if (hdev->notify)
			hdev->notify(hdev, HCI_NOTIFY_ENABLE_SCO_TRANSP);
		break;
	}

	hci_connect_cfm(conn, ev->status);
	if (ev->status)
		hci_conn_del(conn);

unlock:
	hci_dev_unlock(hdev);
}
