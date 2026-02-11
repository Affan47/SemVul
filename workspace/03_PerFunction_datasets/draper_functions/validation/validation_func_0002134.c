gst_object_unparent (GstObject * object)
{
  GstObject *parent;

  g_return_if_fail (GST_IS_OBJECT (object));

  GST_OBJECT_LOCK (object);
  parent = object->parent;

  if (G_LIKELY (parent != NULL)) {
    GST_CAT_TRACE_OBJECT (GST_CAT_REFCOUNTING, object, "unparent");
    object->parent = NULL;
    GST_OBJECT_UNLOCK (object);


    gst_object_unref (object);
  } else {
    GST_OBJECT_UNLOCK (object);
  }
}
