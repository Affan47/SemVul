createRenderer(RenderArena* arena, RenderStyle*)
{
    return new (arena) RenderSVGTSpan(this);
}
