find_widget(int x, int y) {
    for (iterator i=begin(); i!=end(); ++i) {
        Widget *w = *i;
        if (w->get_area().contains(x,y)) {
            Container *c = dynamic_cast<Container *> (w);
            if (c) {
                w = c->find_widget (x, y);
                return w ? w : c;
            }
            return w;
        }
    }
    return 0;
}
