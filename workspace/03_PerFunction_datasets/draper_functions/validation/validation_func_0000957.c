apartment_free (gpointer data)
{
	Apartment *apt;
	GList *l;

	g_assert (data != NULL);
	apt = (Apartment*)data;

	g_return_if_fail (GKM_IS_MANAGER (apt->session_manager));


	for (l = apt->sessions; l; l = g_list_next (l)) {


		g_return_if_fail (GKM_IS_SESSION (l->data));
		g_return_if_fail (gkm_session_get_apartment (l->data) == apt->apt_id);
		g_return_if_fail (gkm_session_get_manager (l->data) == apt->session_manager);
		g_return_if_fail (gkm_session_get_logged_in (l->data) == apt->logged_in);

		g_object_unref (l->data);
	}

	g_list_free (apt->sessions);
	g_object_unref (apt->session_manager);

	g_slice_free (Apartment, apt);
}
