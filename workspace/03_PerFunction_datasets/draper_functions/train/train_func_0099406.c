timeout (void)
{
	gdk_threads_enter();
	if (!GTK_IS_IMAGE(_image)) {
		gdk_threads_leave();
		_timetag = 0;
		return false;
	}
	_current = (_current+1)%_frame.size();
	if (_frame.size())
		gtk_image_set_from_pixbuf (_image, _frame[_current]);
	gdk_threads_leave();
	return true;
}
