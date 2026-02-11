invisible(int gc, AW_pos x, AW_pos y, AW_bitset filteri, AW_CL clientdata1, AW_CL clientdata2) {
    if (filteri & filter) dot(x, y);
    return AW_device::invisible(gc,x,y,filteri,clientdata1,clientdata2);
}
