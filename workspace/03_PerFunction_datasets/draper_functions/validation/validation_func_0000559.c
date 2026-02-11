project_free(gpointer data)
{
struct project_pak *project = data;

g_assert(project != NULL);

g_free(project->label);
g_free(project->path);
g_slist_free(project->models);
g_slist_free(project->configs);


g_hash_table_destroy(project->data);

g_free(project);
}
