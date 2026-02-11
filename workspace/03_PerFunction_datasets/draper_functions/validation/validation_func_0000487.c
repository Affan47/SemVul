SMBus_set_pec(SMBus *self, PyObject *val, void *closure)
{
	int pec;

	pec = PyObject_IsTrue(val);

	if (val == NULL) {
		PyErr_SetString(PyExc_TypeError,
			"Cannot delete attribute");
		return -1;
	}
	else if (pec == -1) {
		PyErr_SetString(PyExc_TypeError,
			"The pec attribute must be a boolean.");
		return -1;
	}

	if (self->pec != pec) {
		if (ioctl(self->fd, I2C_PEC, pec)) {
			PyErr_SetFromErrno(PyExc_IOError);
			return -1;
		}
		self->pec = pec;
	}

	return 0;
}
