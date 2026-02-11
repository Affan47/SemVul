SetUri(const FUUri& uri)
{
	entityId = TO_STRING(uri.GetFragment());
    entityId = FCDObjectWithId::CleanId(entityId);
	FCDPlaceHolder* documentPlaceHolder = NULL;

	if (uri.IsFile())
	{
		fstring fileUrl = GetDocument()->GetFileManager()->GetCurrentUri().MakeAbsolute(uri.GetAbsolutePath());

		documentPlaceHolder = GetDocument()->GetExternalReferenceManager()->FindPlaceHolder(fileUrl);
		if (documentPlaceHolder == NULL)
		{
			documentPlaceHolder = GetDocument()->GetExternalReferenceManager()->AddPlaceHolder(fileUrl);
		}
	}
	SetPlaceHolder(documentPlaceHolder);
	SetDirtyFlag();
}
