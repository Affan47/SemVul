opengl_error_string()
{
	GLenum error = GL_NO_ERROR;

	error = glGetError();

	if ( error != GL_NO_ERROR ) {
		return (const char *)gluErrorString(error);
	}

	return NULL;
}
