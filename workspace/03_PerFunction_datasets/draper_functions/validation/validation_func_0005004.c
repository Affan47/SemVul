fso_gsm_gsm_network_service_real_get_time_report_finish (FreeSmartphoneGSMNetwork* base, GAsyncResult* _res_, gint* time, gint* timestamp, gint* zone, gint* zonestamp, GError** error) {
	FsoGsmGsmNetworkServiceGetTimeReportData* _data_;
	if (g_simple_async_result_propagate_error (G_SIMPLE_ASYNC_RESULT (_res_), error)) {
		return;
	}
	_data_ = g_simple_async_result_get_op_res_gpointer (G_SIMPLE_ASYNC_RESULT (_res_));
	if (time) {
		*time = _data_->time;
	}
	if (timestamp) {
		*timestamp = _data_->timestamp;
	}
	if (zone) {
		*zone = _data_->zone;
	}
	if (zonestamp) {
		*zonestamp = _data_->zonestamp;
	}
}
