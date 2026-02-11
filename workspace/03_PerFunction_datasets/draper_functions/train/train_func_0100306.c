storeSelf(char* buf) {
    SPtr<TIPv6Addr> addr;

    buf = writeUint16(buf, OptType);
    buf = writeUint16(buf, getSize()-4);
    AddrLst.first();
    while(addr=AddrLst.get())
	buf=addr->storeSelf(buf);
    return buf;
}
