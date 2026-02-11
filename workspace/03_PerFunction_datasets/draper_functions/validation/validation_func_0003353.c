stFree(
  char *key,
  char *value,
  char *arg)
{
    if (value != NULL) {
	FREE(value);
    }
    return(ST_CONTINUE);

}
