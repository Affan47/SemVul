xmlparser_gc_clear(XMLParserObject *self)
{
    EXPAT(ParserFree)(self->parser);

    Py_CLEAR(self->handle_close);
    Py_CLEAR(self->handle_pi);
    Py_CLEAR(self->handle_comment);
    Py_CLEAR(self->handle_end);
    Py_CLEAR(self->handle_data);
    Py_CLEAR(self->handle_start);
    Py_CLEAR(self->handle_doctype);

    Py_CLEAR(self->target);
    Py_CLEAR(self->entity);
    Py_CLEAR(self->names);

    return 0;
}
