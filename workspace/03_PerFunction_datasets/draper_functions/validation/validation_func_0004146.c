gwy_3d_window_key_pressed(GtkWidget *widget,
                          GdkEventKey *event)
{
    enum {
        important_mods = GDK_CONTROL_MASK | GDK_MOD1_MASK | GDK_RELEASE_MASK
    };
    Gwy3DWindow *gwy3dwindow;
    gboolean (*method)(GtkWidget*, GdkEventKey*);
    guint state, key;

    gwy_debug("state = %u, keyval = %u", event->state, event->keyval);
    gwy3dwindow = GWY_3D_WINDOW(widget);
    state = event->state & important_mods;
    key = event->keyval;


    if (state == GDK_CONTROL_MASK && (key == GDK_C || key == GDK_c)) {
        gwy_3d_window_copy_to_clipboard(gwy3dwindow);
        return TRUE;
    }

    if (!gwy3dwindow->controls_full && !state) {
        Gwy3DMovement movement = GWY_3D_MOVEMENT_NONE;

        if (key == GDK_R || key == GDK_r)
            movement = GWY_3D_MOVEMENT_ROTATION;
        else if (key == GDK_S || key == GDK_s)
            movement = GWY_3D_MOVEMENT_SCALE;
        else if (key == GDK_V || key == GDK_v)
            movement = GWY_3D_MOVEMENT_DEFORMATION;
        else if (key == GDK_L || key == GDK_l)
            movement = GWY_3D_MOVEMENT_LIGHT;

        if (movement != GWY_3D_MOVEMENT_NONE) {
            gtk_button_clicked(GTK_BUTTON(gwy3dwindow->buttons[movement]));
            return TRUE;
        }
    }

    method = GTK_WIDGET_CLASS(gwy_3d_window_parent_class)->key_press_event;
    return method ? method(widget, event) : FALSE;
}
