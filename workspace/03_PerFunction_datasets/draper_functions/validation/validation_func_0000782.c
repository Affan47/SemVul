MovePrevTab() {
    int P = CP.Col;

    if (P > 0) {
        P = ((P - 1) / BFI(this, BFI_TabSize)) * BFI(this, BFI_TabSize);
        return SetPos(P, CP.Row);
    } else return 0;
}
