
      unsigned int scalar() {
        if (mempos>=mem._width) { mem.resize(-200,1,1,1,0); memtype.resize(mem._width,1,1,1,0); }
        return mempos++;
}
