data_hub_service_get_data_providers (DataHubService* self, int* result_length1, GError** error) {
	g_return_val_if_fail (self != NULL, NULL);
	return DATA_HUB_SERVICE_GET_INTERFACE (self)->get_data_providers (self, result_length1, error);
}
