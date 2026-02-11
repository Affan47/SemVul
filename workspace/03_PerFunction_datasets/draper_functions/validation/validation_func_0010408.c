xgifb_init(void)
{
	char *option = NULL;

	if (forcecrt2type != NULL)
		XGIfb_search_crt2type(forcecrt2type);
	if (fb_get_options("xgifb", &option))
		return -ENODEV;
	XGIfb_setup(option);

	return pci_register_driver(&xgifb_driver);
}
