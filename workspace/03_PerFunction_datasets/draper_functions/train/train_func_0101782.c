modelPrintP   ( void * modelptr, FILE * fp )
{
  model_t * mp = ( model_t * ) modelptr;

  if ( !mp ) return;

  fprintf ( fp, "#\n");
  fprintf ( fp, "# modelID %d\n", mp->self);
  fprintf ( fp, "#\n");
  fprintf ( fp, "self          = %d\n", mp->self );
  fprintf ( fp, "used          = %d\n", mp->used );
  fprintf ( fp, "instID        = %d\n", mp->instID );
  fprintf ( fp, "modelgribID   = %d\n", mp->modelgribID );
  fprintf ( fp, "name          = %s\n", mp->name ? mp->name : "NN" );
}
