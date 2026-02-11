Copy () {
    Command* copy = new ScaleCmd(CopyControlInfo(), _sx, _sy, _align);
    InitCopy(copy);
    return copy;
}
