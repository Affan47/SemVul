DeleteAllFields ()

	{
	DBObjRecord *record;

	FieldPTR->DeleteAll ();
	RecordLengthVAR = 0;
	for (record = First ();record != (DBObjRecord *) NULL;record = Next ())
		record->Realloc (RecordLengthVAR);
	}
