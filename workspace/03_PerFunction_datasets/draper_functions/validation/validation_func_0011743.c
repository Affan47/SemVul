set_group_state(struct widget *pBeginGroupWidgetList,
		     struct widget *pEndGroupWidgetList, enum widget_state state)
{
  struct widget *pTmpWidget = pEndGroupWidgetList;
  while (pTmpWidget) {
    set_wstate(pTmpWidget, state);
    if (pTmpWidget == pBeginGroupWidgetList) {
      break;
    }
    pTmpWidget = pTmpWidget->prev;
  }
}
