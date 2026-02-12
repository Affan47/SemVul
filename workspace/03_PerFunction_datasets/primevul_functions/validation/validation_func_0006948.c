encode_PUSH_VLAN(const struct ofpact_push_vlan *push_vlan,
                 enum ofp_version ofp_version, struct ofpbuf *out)
{
    if (ofp_version == OFP10_VERSION) {


    } else {
        put_OFPAT11_PUSH_VLAN(out, push_vlan->ethertype);
    }
}
