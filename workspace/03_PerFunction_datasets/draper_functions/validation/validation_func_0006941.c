BlockRedraw() {
    if (BB.Row == -1 || BE.Row == -1) return 0;
    Draw(BB.Row, BE.Row);
    return 1;
}
