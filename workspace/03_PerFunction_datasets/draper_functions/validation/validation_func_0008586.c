glmDelete(GLMmodel* model)
{
  GLMgroup* group;
  GLuint i;

  if (!(model))return;

  if (model->pathname)     free(model->pathname);
  if (model->mtllibname) free(model->mtllibname);
  if (model->vertices)     free(model->vertices);
  if (model->normals)  free(model->normals);
  if (model->texcoords)  free(model->texcoords);
  if (model->facetnorms) free(model->facetnorms);
  if (model->triangles)  free(model->triangles);
  if (model->materials) {
    for (i = 0; i < model->nummaterials; i++)
      free(model->materials[i].name);
  }
  free(model->materials);
  while(model->groups) {
    group = model->groups;
    model->groups = model->groups->next;
    free(group->name);
    free(group->triangles);
    free(group);
  }

  free(model);
}
