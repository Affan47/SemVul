Reconfig() {
    kit_->push_style();
    kit_->style(style_);
    Painter* p = new Painter(output);
    p->SetColors(kit_->foreground(), kit_->background());
    p->SetFont(kit_->font());
    Resource::unref(output);
    output = p;
    StringEditor::Reconfig();
    kit_->pop_style();
}
