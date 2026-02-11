GetMenu(int which) {
    if (which < 0 || which >= EM_MENUS)
        return 0;
    if (Menu[which] || Parent == 0)
        return Menu[which];
    else
        return Parent->GetMenu(which);
}
