launch_location_from_file (NemoFile *file)
{
	LaunchLocation *location;
	location = g_new (LaunchLocation, 1);
	location->file = nemo_file_ref (file);
	location->uri = nemo_file_get_uri (file);

	return location;
}
