RemoveData 	(DBObjData *remData)

	{
	DBRegion initRegion;
	DBObjData *data;
	DBObjMetaEntry *metaEntry;

	DataLIST->Remove (remData);

	ExtentVAR = initRegion;
	for (data = DataLIST->First ();data != (DBObjData *) NULL;data = DataLIST->Next ())
		{
		ExtentVAR.Expand (data->Extent ());
		if (data->LinkedData () == remData) data->LinkedData ((DBObjData *) NULL);
		}
	metaEntry = MetaLIST->Item (remData->Name ());
	if (strlen (remData->FileName ()) == 0) MetaLIST->Delete (metaEntry);
	}
