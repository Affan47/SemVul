recv_vec8(vvp_net_ptr_t port, const vvp_vector8_t&bit)
{
      recv_vec4(port, reduce4(bit), 0);
}
