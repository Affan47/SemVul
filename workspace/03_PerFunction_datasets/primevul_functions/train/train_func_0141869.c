PyImaging_EncoderNew(int contextsize)
{
    ImagingEncoderObject *encoder;
    void *context;

    if(!PyType_Ready(&ImagingEncoderType) < 0)
        return NULL;

    encoder = PyObject_New(ImagingEncoderObject, &ImagingEncoderType);
    if (encoder == NULL)
	return NULL;


    memset(&encoder->state, 0, sizeof(encoder->state));


    if (contextsize > 0) {
	context = (void*) calloc(1, contextsize);
	if (!context) {
	    Py_DECREF(encoder);
	    (void) PyErr_NoMemory();
	    return NULL;
	}
    } else
	context = 0;


    encoder->state.context = context;


    encoder->lock = NULL;
    encoder->im = NULL;

    return encoder;
}
