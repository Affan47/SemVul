Execute () {
    FontVar* _fontVar = (FontVar*) GetEditor()->GetState("FontVar");

    if (_fontVar != nil) {
        _fontVar->SetFont(GetFont());
    }
    Command::Execute();
}
