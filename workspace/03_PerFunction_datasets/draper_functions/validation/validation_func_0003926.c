mei_hbm_fw_add_cl_req(struct mei_device *dev,
			      struct hbm_add_client_request *req)
{
	int ret;
	u8 status = MEI_HBMS_SUCCESS;

	BUILD_BUG_ON(sizeof(struct hbm_add_client_request) !=
			sizeof(struct hbm_props_response));

	ret = mei_hbm_me_cl_add(dev, (struct hbm_props_response *)req);
	if (ret)
		status = !MEI_HBMS_SUCCESS;

	return mei_hbm_add_cl_resp(dev, req->me_addr, status);
}
