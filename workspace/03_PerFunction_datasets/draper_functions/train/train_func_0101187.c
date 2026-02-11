QRinput_Struct_appendInput(QRinput_Struct *s, QRinput *input)
{
	QRinput_InputList *e;

	if(input->mqr) {
		errno = EINVAL;
		return -1;
	}

	e = QRinput_InputList_newEntry(input);
	if(e == NULL) return -1;

	s->size++;
	if(s->tail == NULL) {
		s->head = e;
		s->tail = e;
	} else {
		s->tail->next = e;
		s->tail = e;
	}

	return s->size;
}
