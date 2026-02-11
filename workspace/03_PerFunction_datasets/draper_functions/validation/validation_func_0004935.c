draw (Canvas* c, Graphic* gs) {
    if (!gs->GetPattern()->None()) {
        update(gs);
        _p->FillEllipse(c, _x0, _y0, _r1, _r2);
    }
}
