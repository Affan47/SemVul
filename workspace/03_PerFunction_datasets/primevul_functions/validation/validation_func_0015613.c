u8 append_local_name(struct hci_dev *hdev, u8 *ptr, u8 ad_len)
{
	size_t short_len;
	size_t complete_len;


	if ((HCI_MAX_AD_LENGTH - ad_len) < HCI_MAX_SHORT_NAME_LENGTH + 3)
		return ad_len;


	complete_len = strlen(hdev->dev_name);
	if (complete_len && complete_len <= HCI_MAX_SHORT_NAME_LENGTH)
		return eir_append_data(ptr, ad_len, EIR_NAME_COMPLETE,
				       hdev->dev_name, complete_len + 1);


	short_len = strlen(hdev->short_name);
	if (short_len)
		return eir_append_data(ptr, ad_len, EIR_NAME_SHORT,
				       hdev->short_name, short_len + 1);


	if (complete_len) {
		u8 name[HCI_MAX_SHORT_NAME_LENGTH + 1];

		memcpy(name, hdev->dev_name, HCI_MAX_SHORT_NAME_LENGTH);
		name[HCI_MAX_SHORT_NAME_LENGTH] = '\0';

		return eir_append_data(ptr, ad_len, EIR_NAME_SHORT, name,
				       sizeof(name));
	}

	return ad_len;
}
