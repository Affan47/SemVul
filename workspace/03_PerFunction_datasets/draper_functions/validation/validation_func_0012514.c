mwifiex_usb_disconnect(struct usb_interface *intf)
{
	struct usb_card_rec *card = usb_get_intfdata(intf);
	struct mwifiex_adapter *adapter;

	if (!card || !card->adapter) {
		pr_err("%s: card or card->adapter is NULL\n", __func__);
		return;
	}

	adapter = card->adapter;
	if (!adapter->priv_num)
		return;

	if (user_rmmod) {
#ifdef CONFIG_PM
		if (adapter->is_suspended)
			mwifiex_usb_resume(intf);
#endif

		mwifiex_deauthenticate_all(adapter);

		mwifiex_init_shutdown_fw(mwifiex_get_priv(adapter,
							  MWIFIEX_BSS_ROLE_ANY),
					 MWIFIEX_FUNC_SHUTDOWN);
	}

	mwifiex_usb_free(card);

	mwifiex_dbg(adapter, FATAL,
		    "%s: removing card\n", __func__);
	mwifiex_remove_card(adapter, &add_remove_card_sem);

	usb_set_intfdata(intf, NULL);
	usb_put_dev(interface_to_usbdev(intf));
	kfree(card);

	return;
}
