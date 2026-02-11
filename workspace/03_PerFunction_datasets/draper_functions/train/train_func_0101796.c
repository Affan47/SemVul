deleteCube(VimosCube *Cube)
{
  if (Cube != NULL) {
    deleteAllDescriptors(Cube->descs);
    if (Cube->data != NULL) {
      pil_free(Cube->data);
    }
    pil_free(Cube);
  }
}
