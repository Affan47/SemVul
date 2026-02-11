pkt_ctx_ip_analyze_l4(n_pkt_ctx_t *ctx)
{
   switch(ctx->ip_l4_proto) {
      case N_IP_PROTO_TCP:
         ctx->flags |= N_PKT_CTX_FLAG_L4_TCP;
         break;
      case N_IP_PROTO_UDP:
         ctx->flags |= N_PKT_CTX_FLAG_L4_UDP;
         break;
      case N_IP_PROTO_ICMP:
         ctx->flags |= N_PKT_CTX_FLAG_L4_ICMP;
         break;
   }

   return(TRUE);
}
