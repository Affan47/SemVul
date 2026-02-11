enet_symbol_rescale (ENetSymbol * symbol)
{
    enet_uint16 total = 0;
    for (;;)
    {
        symbol -> count -= symbol->count >> 1;
        symbol -> under = symbol -> count;
        if (symbol -> left)
          symbol -> under += enet_symbol_rescale (symbol + symbol -> left);
        total += symbol -> under;
        if (! symbol -> right) break;
        symbol += symbol -> right;
    }
    return total;
}
