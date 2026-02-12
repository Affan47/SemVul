bool zx_isZxLiquidTx(const EthereumSignTx *msg) {
    if (memcmp(msg->to.bytes, UNISWAP_ROUTER_ADDRESS, 20) == 0) {

        if (isAddLiquidityEthCall(msg)) return true;

        if (isRemoveLiquidityEthCall(msg)) return true;
    }
    return false;
}
