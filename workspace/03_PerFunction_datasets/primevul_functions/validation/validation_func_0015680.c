void __hci_req_pause_adv_instances(struct hci_request *req)
{
	bt_dev_dbg(req->hdev, "Pausing advertising instances");


	__hci_req_disable_advertising(req);


	if (!ext_adv_capable(req->hdev))
		cancel_adv_timeout(req->hdev);
}
