upload_fire_upload_info_changed(struct upload *u)
{
    LISTENER_EMIT(upload_info_changed, (u->upload_handle));
}
