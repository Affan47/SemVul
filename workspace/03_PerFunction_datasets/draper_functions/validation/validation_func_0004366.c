setFocusWidget(QWidget *widget)
{
  if (!widget)
    return;

  if (focused_widget != widget) {
#if 0
    if (focused_widget) {
      char *rstr;
      hime_im_client_focus_out2(hime_ch, &rstr);
      if (rstr) {
          QString inputText = QString::fromUtf8(rstr);
          QInputMethodEvent commit_event;
          commit_event.setCommitString (inputText);
          sendEvent (commit_event);

          QList<QAttribute> preedit_attributes;
          QInputMethodEvent im_event (QString::fromUtf8(""), preedit_attributes);
          sendEvent (im_event);
      }
    }
    focused_widget = widget;
#else
    hime_im_client_focus_out(hime_ch);
#endif
  }

  if (hime_ch) {
    hime_im_client_set_window(hime_ch, widget->winId());
  }

  QInputContext::setFocusWidget (widget);

  if (hime_ch)
    hime_im_client_focus_in(hime_ch);
}
