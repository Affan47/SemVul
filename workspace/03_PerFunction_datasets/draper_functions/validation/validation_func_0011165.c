P_Window_To_Widget (Object w) {
    Check_Type (w, T_Window);
    return Make_Widget_Foreign (XtWindowToWidget (WINDOW(w)->dpy,
        WINDOW(w)->win));
}
