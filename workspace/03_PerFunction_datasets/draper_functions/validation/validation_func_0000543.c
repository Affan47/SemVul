Reorient () {
    if (
        _orientation == Rotated ||
        _orientation == Landscape ||
        _orientation == Horizontal
    ) {
        Coord l, b, r, t;
        GetGraphicBox(l, b, r, t);
        Graphic* g = GraphicBlock::GetGraphic();

        g->Rotate(-90., l, b);
        g->Translate(0., r-l);
    }
}
