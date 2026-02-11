onDestructionStarted(WindowEventArgs& e)
{

    Window* p = getParent();
    if (p && p->testClassName("MenuItem"))
    {
        static_cast<MenuItem*>(p)->setPopupMenu(0);
    }
    MenuBase::onDestructionStarted(e);
}
