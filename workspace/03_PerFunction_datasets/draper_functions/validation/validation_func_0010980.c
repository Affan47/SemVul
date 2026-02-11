Copy() {
    MoveFrameCmd* copy = new MoveFrameCmd(CopyControlInfo(), _requestmotion, _allowbg);
    copy->wraparound(wraparound());
    InitCopy(copy);
    return copy;
}
