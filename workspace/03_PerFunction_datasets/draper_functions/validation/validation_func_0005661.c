e_import_get_widget (EImport *import,
                     EImportTarget *target,
                     EImportImporter *importer)
{
	g_return_val_if_fail (importer != NULL, NULL);
	g_return_val_if_fail (target != NULL, NULL);

	return importer->get_widget (import, target, importer);
}
