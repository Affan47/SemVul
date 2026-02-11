nemo_icon_container_for_each (NemoIconContainer *container,
				  NemoIconCallback callback,
				  gpointer callback_data)
{
	CallbackAndData callback_and_data;

	g_return_if_fail (NEMO_IS_ICON_CONTAINER (container));

	callback_and_data.callback = callback;
	callback_and_data.callback_data = callback_data;

	g_list_foreach (container->details->icons,
			call_icon_callback, &callback_and_data);
}
