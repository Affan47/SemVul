Document_is_tag(Document *self)
{
	if (iks_type(self->doc) == IKS_TAG) {
		Py_INCREF(Py_True);
		return Py_True;
	} else {
		Py_INCREF(Py_False);
		return Py_False;
	}
}
