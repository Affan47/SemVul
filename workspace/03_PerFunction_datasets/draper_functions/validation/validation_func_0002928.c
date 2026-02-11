ganv_circle_destroy(GtkObject* object)
{
	g_return_if_fail(object != NULL);
	g_return_if_fail(GANV_IS_CIRCLE(object));

	if (GTK_OBJECT_CLASS(parent_class)->destroy) {
		(*GTK_OBJECT_CLASS(parent_class)->destroy)(object);
	}
}
