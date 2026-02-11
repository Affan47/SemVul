display(Renderer& renderer, const Transform& base)
{
    const Transform xform = base * transform();

    if (_def) _def->display(renderer, xform);
    else _shape->display(renderer, xform);
    clear_invalidated();
}
