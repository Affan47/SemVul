find_in_layout(int mode, char target, int *fx, int *fy, char **layout, RMParms *RP) {
    int M;
    int i, j;

    *fx = -1;
    *fy = -1;


    if (mode < 1 || mode > 4)
        M = RANDOM()%4+1;
    else
        M = mode;


    switch (M) {
    case 1: {
        for (i = 1; i < RP->Xsize; i++)
            for (j = 1; j < RP->Ysize; j++) {
                if (layout[i][j] == target) {
                    *fx = i;
                    *fy = j;
                    return;
                }
            }
        break;
    }

    case 2: {
        for (i = RP->Xsize-2; i > 0; i--)
            for (j = 1; j < RP->Ysize-1; j++) {
                if (layout[i][j] == target) {
                    *fx = i;
                    *fy = j;
                    return;
                }
            }
        break;
    }

    case 3: {
        for (i = 1; i < RP->Xsize-1; i++)
            for (j = RP->Ysize-2; j > 0; j--) {
                if (layout[i][j] == target) {
                    *fx = i;
                    *fy = j;
                    return;
                }
            }
        break;
    }

    case 4: {
        for (i = RP->Xsize-2; i > 0; i--)
            for (j = RP->Ysize-2; j > 0; j--) {
                if (layout[i][j] == target) {
                    *fx = i;
                    *fy = j;
                    return;
                }
            }
        break;
    }
    }
}
