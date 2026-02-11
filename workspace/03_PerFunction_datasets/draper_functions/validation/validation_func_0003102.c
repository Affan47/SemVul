Interpret (Command* cmd) {
    TextGraphic* gr = (TextGraphic*) GetGraphic();

    if (cmd->IsA(BRUSH_CMD) || cmd->IsA(PATTERN_CMD)) {


    } else if (cmd->IsA(FONT_CMD)) {
        PSFont* font = ((FontCmd*) cmd)->GetFont();
        cmd->Store(this, new VoidData(gr->GetFont()));
        gr->SetFont(font);
        gr->SetLineHeight(font->GetLineHt());
        Notify();

    } else {
        OverlayComp::Interpret(cmd);
    }
}
