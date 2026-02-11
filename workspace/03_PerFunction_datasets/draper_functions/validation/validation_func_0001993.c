adcli_entry_ref (adcli_entry *entry)
{
	return_val_if_fail (entry != NULL, NULL);
	entry->refs++;
	return entry;

}
