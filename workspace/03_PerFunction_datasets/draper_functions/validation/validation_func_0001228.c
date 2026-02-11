fold_expand(GtkWidget *scintilla, gint line, gboolean doExpand, gboolean force, gint visLevels, gint level)
{
  gint lineMaxSubord;
  gint levelLine;

  GtkScintilla *sci = GTK_SCINTILLA(scintilla);

  lineMaxSubord = gtk_scintilla_get_last_child(sci, line, level & SC_FOLDLEVELNUMBERMASK);

  while (line <= lineMaxSubord) {
    line++;
    if (force) {
      if (visLevels > 0) {
        gtk_scintilla_show_lines(sci, line, line);
      }
      else {
        gtk_scintilla_hide_lines(sci, line, line);
      }
    }
    else if (doExpand) {
      gtk_scintilla_show_lines(sci, line, line);
    }

    levelLine = level;

    if (levelLine == -1) {
      levelLine = gtk_scintilla_get_fold_level(sci, line);
    }

    if (levelLine & SC_FOLDLEVELHEADERFLAG) {
      if (force) {
        if (visLevels > 1) {
          gtk_scintilla_set_fold_expanded(sci, line, 1);
        }
        else {
          gtk_scintilla_set_fold_expanded(sci, line, 0);
        }

        fold_expand(scintilla, line, doExpand, force, visLevels - 1, 0);
      }
      else if (doExpand) {
        if (!gtk_scintilla_get_fold_expanded(sci, line)) {
          gtk_scintilla_set_fold_expanded(sci, line, 1);
        }

        fold_expand(scintilla, line, TRUE, force, visLevels - 1, 0);
      }
      else {
        fold_expand(scintilla, line, FALSE, force, visLevels - 1, 0);
      }
    }
    else {
      line++;
    }
  }
}
