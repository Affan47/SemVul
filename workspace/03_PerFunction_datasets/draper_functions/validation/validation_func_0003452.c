amitk_objects_read_xml(xmlNodePtr node_list, FILE * study_file, gchar **perror_buf) {

  GList * objects;
  AmitkObject * object;
  gchar * filename=NULL;
  guint64 location;
  guint64 size;

  if (node_list == NULL) return NULL;


  objects = amitk_objects_read_xml(node_list->next, study_file, perror_buf);


  if (study_file == NULL)
    filename = xml_get_string(node_list, "object_file");
  else
    xml_get_location_and_size(node_list, "object_location_and_size", &location, &size, perror_buf);

  object = amitk_object_read_xml(filename, study_file, location, size, perror_buf);
  if (object != NULL) objects = g_list_prepend(objects, object);
  if (filename != NULL) g_free(filename);

  return objects;
}
