active_connections_changed (NMClient *client, GParamSpec *pspec, gpointer user_data)
{
	const GPtrArray *connections;
	int i, j;

	g_print ("Active connections changed:\n");
	connections = nm_client_get_active_connections (client);
	for (i = 0; connections && (i < connections->len); i++) {
		NMActiveConnection *connection;
		const GPtrArray *devices;

		connection = g_ptr_array_index (connections, i);
		g_print ("    %s\n", nm_object_get_path (NM_OBJECT (connection)));
		devices = nm_active_connection_get_devices (connection);
		for (j = 0; devices && j < devices->len; j++)
			g_print ("           %s\n", nm_device_get_udi (g_ptr_array_index (devices, j)));
		if (NM_IS_VPN_CONNECTION (connection))
			g_print ("           VPN base connection: %s\n", nm_active_connection_get_specific_object (connection));
	}
}
