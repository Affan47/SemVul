show_between(bool)
{
  int n;

  long long displaytime;

  struct annotationblock *annot;


  if(list->count() < 2)
  {
    return;
  }

  annot = mainwindow->annotationlist[file_num];

  n = list->currentRow();

  if(n >= (list->count() - 1))
  {
    return;
  }

  while(n--)
  {
    annot = annot->next_annotation;
  }

  displaytime = annot->onset;

  annot = annot->next_annotation;

  displaytime -= annot->onset;

  if(displaytime < 0)
  {
    displaytime *= -1;
  }

  if(displaytime < 1000)
  {
    return;
  }

  mainwindow->pagetime = displaytime;

  annotation_selected(list->currentItem(), 0);
}
