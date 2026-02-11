maxValue(unsigned short colval) {
   return colval == 65535 ? 0xFF : static_cast<unsigned char>(colval/0xFF);
}

}
