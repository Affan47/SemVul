hdp_update_sdp_record(struct hdp_adapter *adapter, GSList *app_list)
{
	sdp_record_t *sdp_record;
	bdaddr_t addr;

	if (adapter->sdp_handler > 0)
		remove_record_from_server(adapter->sdp_handler);

	if (app_list == NULL) {
		adapter->sdp_handler = 0;
		return TRUE;
	}

	sdp_record = sdp_record_alloc();
	if (sdp_record == NULL)
		return FALSE;

	if (adapter->sdp_handler > 0)
		sdp_record->handle = adapter->sdp_handler;
	else
		sdp_record->handle = 0xffffffff;

	if (is_app_role(app_list, HDP_SINK))
		set_sdp_services_uuid(sdp_record, HDP_SINK);
	if (is_app_role(app_list, HDP_SOURCE))
		set_sdp_services_uuid(sdp_record, HDP_SOURCE);

	if (!register_service_protocols(adapter, sdp_record))
		goto fail;
	if (!register_service_profiles(sdp_record))
		goto fail;
	if (!register_service_additional_protocols(adapter, sdp_record))
		goto fail;

	sdp_set_info_attr(sdp_record, HDP_SERVICE_NAME, HDP_SERVICE_PROVIDER,
							HDP_SERVICE_DSC);
	if (!register_service_sup_features(app_list, sdp_record))
		goto fail;
	if (!register_data_exchange_spec(sdp_record))
		goto fail;

	register_mcap_features(sdp_record);

	if (sdp_set_record_state(sdp_record, adapter->record_state++) < 0)
		goto fail;

	adapter_get_address(adapter->btd_adapter, &addr);

	if (add_record_to_server(&addr, sdp_record) < 0)
		goto fail;
	adapter->sdp_handler = sdp_record->handle;
	return TRUE;

fail:
	if (sdp_record != NULL)
		sdp_record_free(sdp_record);
	return FALSE;
}
