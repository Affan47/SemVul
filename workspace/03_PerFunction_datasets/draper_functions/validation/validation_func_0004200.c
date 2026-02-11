gdl_dock_layout_save (GdlDockMaster *master,
                      xmlNodePtr     where)
{

	g_return_if_fail (master != NULL && where != NULL);


    gdl_dock_master_foreach_toplevel (master, TRUE,
                                      (GFunc) gdl_dock_layout_foreach_object_save,
                                      (gpointer) where);
}
