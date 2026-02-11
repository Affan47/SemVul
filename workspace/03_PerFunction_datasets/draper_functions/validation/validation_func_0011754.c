pk_package_print (PkPackage *package)
{
	PkPackagePrivate *priv = package->priv;
	g_return_if_fail (PK_IS_PACKAGE (package));
	g_print ("%s-%s.%s\t%s\t%s\n",
		 priv->package_id_split[PK_PACKAGE_ID_NAME],
		 priv->package_id_split[PK_PACKAGE_ID_VERSION],
		 priv->package_id_split[PK_PACKAGE_ID_ARCH],
		 priv->package_id_split[PK_PACKAGE_ID_DATA],
		 package->priv->summary);
}
