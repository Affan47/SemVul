gwy_resource_editor_changed(GtkTreeSelection *selection,
                            GwyResourceEditor *editor)
{
    GwyResource *resource;
    GtkTreeModel *model;
    GtkTreeIter iter;
    guint state = 0;

    gwy_debug("");
    if (gtk_tree_selection_get_selected(selection, &model, &iter)) {
        state |= SELECTED_ANY;
        gtk_tree_model_get(model, &iter, 0, &resource, -1);
        if (gwy_resource_get_is_modifiable(resource))
            state |= SELECTED_EDITABLE;
    }
    gwy_sensitivity_group_set_state(editor->sensgroup, SELECTED_MASK, state);
}
