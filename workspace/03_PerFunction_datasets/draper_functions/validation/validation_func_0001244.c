async_context_free (AsyncContext *async_context)
{
	if (async_context->stream != NULL)
		g_object_unref (async_context->stream);

	g_slice_free (AsyncContext, async_context);
}
