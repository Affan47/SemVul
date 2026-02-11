setIcon(const QString &name, const PsiIcon &icon)
{
	detach();

	PsiIcon *newIcon = new PsiIcon(icon);

	d->remove(name);
	d->append( name, newIcon );
}
