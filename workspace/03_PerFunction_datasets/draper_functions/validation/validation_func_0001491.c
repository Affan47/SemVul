newObjectObject(void)
{
  VimosObjectObject *newObject;


  newObject = (VimosObjectObject *) pil_malloc(sizeof(VimosObjectObject));


  if (newObject == NULL) {
    cpl_msg_error("newObjectObject","Allocation Error");
    return(NULL);
  }


  newObject->slitNo   = 0;
  newObject->IFUslitNo = 0;
  newObject->IFUfibNo = 0;
  newObject->rowNum   = 0;
  newObject->objNo    = 0;
  newObject->objX     = 0.0;
  newObject->objY     = 0.0;
  newObject->objRA    = 0.0;
  newObject->objDec   = 0.0;

  newObject->prev = newObject->next = NULL;


  return(newObject);

}
