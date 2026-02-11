fprintROWS ()
{
  struct row_s *pRow;


  for (pRow = LV_row; pRow != NULL; pRow = pRow->next) {
    fprintf (DEF_FILE,
             "ROW %s %s %ld %ld %s DO %ld BY %ld STEP %ld %ld ;\n",
             pRow->rowName,
             pRow->rowType,
             pRow->x,
             pRow->y,
             DEF_orient2a(pRow->orient),
             pRow->doNumber,
             pRow->byNumber,
             pRow->stepX,
             pRow->stepY);
  }
}
