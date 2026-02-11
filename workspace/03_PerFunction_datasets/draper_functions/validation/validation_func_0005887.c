getKeyWords(FXString & keywords) const {
  if (gui_sort_keywords.no()){
    keywords+=FXString(gui_sort_keywords[0]).trim();
    for (FXint i=1;i<gui_sort_keywords.no();i++) {
      keywords+=";" + FXString(gui_sort_keywords[i]).trim();
      }
    }
  }
