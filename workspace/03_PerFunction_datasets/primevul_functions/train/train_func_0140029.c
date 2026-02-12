static netdev_features_t bnx2x_features_check(struct sk_buff *skb,
					      struct net_device *dev,
					      netdev_features_t features)
{


	if (unlikely(skb_is_gso(skb) &&
		     (skb_shinfo(skb)->gso_size > 9000) &&
		     !skb_gso_validate_mac_len(skb, 9700)))
		features &= ~NETIF_F_GSO_MASK;

	features = vlan_features_check(skb, features);
	return vxlan_features_check(skb, features);
}
