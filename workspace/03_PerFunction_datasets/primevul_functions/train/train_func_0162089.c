static uint32_t gic_dist_readb(void *opaque, hwaddr offset, MemTxAttrs attrs)
{
    GICState *s = (GICState *)opaque;
    uint32_t res;
    int irq;
    int i;
    int cpu;
    int cm;
    int mask;

    cpu = gic_get_current_cpu(s);
    cm = 1 << cpu;
    if (offset < 0x100) {
        if (offset == 0) {
            if (s->security_extn && !attrs.secure) {


                return extract32(s->ctlr, 1, 1);
            } else {
                return s->ctlr;
            }
        }
        if (offset == 4)

            return ((s->num_irq / 32) - 1)
                    | ((s->num_cpu - 1) << 5)
                    | (s->security_extn << 10);
        if (offset < 0x08)
            return 0;
        if (offset >= 0x80) {


            res = 0;
            if (!(s->security_extn && !attrs.secure) && gic_has_groups(s)) {

                irq = (offset - 0x080) * 8;
                if (irq >= s->num_irq) {
                    goto bad_reg;
                }
                for (i = 0; i < 8; i++) {
                    if (GIC_DIST_TEST_GROUP(irq + i, cm)) {
                        res |= (1 << i);
                    }
                }
            }
            return res;
        }
        goto bad_reg;
    } else if (offset < 0x200) {

        if (offset < 0x180)
            irq = (offset - 0x100) * 8;
        else
            irq = (offset - 0x180) * 8;
        if (irq >= s->num_irq)
            goto bad_reg;
        res = 0;
        for (i = 0; i < 8; i++) {
            if (s->security_extn && !attrs.secure &&
                !GIC_DIST_TEST_GROUP(irq + i, 1 << cpu)) {
                continue;
            }

            if (GIC_DIST_TEST_ENABLED(irq + i, cm)) {
                res |= (1 << i);
            }
        }
    } else if (offset < 0x300) {

        if (offset < 0x280)
            irq = (offset - 0x200) * 8;
        else
            irq = (offset - 0x280) * 8;
        if (irq >= s->num_irq)
            goto bad_reg;
        res = 0;
        mask = (irq < GIC_INTERNAL) ?  cm : ALL_CPU_MASK;
        for (i = 0; i < 8; i++) {
            if (s->security_extn && !attrs.secure &&
                !GIC_DIST_TEST_GROUP(irq + i, 1 << cpu)) {
                continue;
            }

            if (gic_test_pending(s, irq + i, mask)) {
                res |= (1 << i);
            }
        }
    } else if (offset < 0x400) {

        if (offset < 0x380) {
            irq = (offset - 0x300) * 8;
        } else if (s->revision == 2) {
            irq = (offset - 0x380) * 8;
        } else {
            goto bad_reg;
        }

        if (irq >= s->num_irq)
            goto bad_reg;
        res = 0;
        mask = (irq < GIC_INTERNAL) ?  cm : ALL_CPU_MASK;
        for (i = 0; i < 8; i++) {
            if (s->security_extn && !attrs.secure &&
                !GIC_DIST_TEST_GROUP(irq + i, 1 << cpu)) {
                continue;
            }

            if (GIC_DIST_TEST_ACTIVE(irq + i, mask)) {
                res |= (1 << i);
            }
        }
    } else if (offset < 0x800) {

        irq = (offset - 0x400);
        if (irq >= s->num_irq)
            goto bad_reg;
        res = gic_dist_get_priority(s, cpu, irq, attrs);
    } else if (offset < 0xc00) {

        if (s->num_cpu == 1 && s->revision != REV_11MPCORE) {

            res = 0;
        } else {
            irq = (offset - 0x800);
            if (irq >= s->num_irq) {
                goto bad_reg;
            }
            if (irq < 29 && s->revision == REV_11MPCORE) {
                res = 0;
            } else if (irq < GIC_INTERNAL) {
                res = cm;
            } else {
                res = GIC_DIST_TARGET(irq);
            }
        }
    } else if (offset < 0xf00) {

        irq = (offset - 0xc00) * 4;
        if (irq >= s->num_irq)
            goto bad_reg;
        res = 0;
        for (i = 0; i < 4; i++) {
            if (s->security_extn && !attrs.secure &&
                !GIC_DIST_TEST_GROUP(irq + i, 1 << cpu)) {
                continue;
            }

            if (GIC_DIST_TEST_MODEL(irq + i)) {
                res |= (1 << (i * 2));
            }
            if (GIC_DIST_TEST_EDGE_TRIGGER(irq + i)) {
                res |= (2 << (i * 2));
            }
        }
    } else if (offset < 0xf10) {
        goto bad_reg;
    } else if (offset < 0xf30) {
        if (s->revision == REV_11MPCORE) {
            goto bad_reg;
        }

        if (offset < 0xf20) {

            irq = (offset - 0xf10);
        } else {
            irq = (offset - 0xf20);

        }

        if (s->security_extn && !attrs.secure &&
            !GIC_DIST_TEST_GROUP(irq, 1 << cpu)) {
            res = 0;
        } else {
            res = s->sgi_pending[irq][cpu];
        }
    } else if (offset < 0xfd0) {
        goto bad_reg;
    } else if (offset < 0x1000) {
        if (offset & 3) {
            res = 0;
        } else {
            switch (s->revision) {
            case REV_11MPCORE:
                res = gic_id_11mpcore[(offset - 0xfd0) >> 2];
                break;
            case 1:
                res = gic_id_gicv1[(offset - 0xfd0) >> 2];
                break;
            case 2:
                res = gic_id_gicv2[(offset - 0xfd0) >> 2];
                break;
            default:
                res = 0;
            }
        }
    } else {
        g_assert_not_reached();
    }
    return res;
bad_reg:
    qemu_log_mask(LOG_GUEST_ERROR,
                  "gic_dist_readb: Bad offset %x\n", (int)offset);
    return 0;
}
