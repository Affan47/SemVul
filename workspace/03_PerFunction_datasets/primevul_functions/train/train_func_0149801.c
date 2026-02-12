x86_emulate_insn(struct x86_emulate_ctxt *ctxt, struct x86_emulate_ops *ops)
{
	unsigned long memop = 0;
	u64 msr_data;
	unsigned long saved_eip = 0;
	struct decode_cache *c = &ctxt->decode;
	unsigned int port;
	int io_dir_in;
	int rc = 0;

	ctxt->interruptibility = 0;


	memcpy(c->regs, ctxt->vcpu->arch.regs, sizeof c->regs);
	saved_eip = c->eip;

	if (((c->d & ModRM) && (c->modrm_mod != 3)) || (c->d & MemAbs))
		memop = c->modrm_ea;

	if (c->rep_prefix && (c->d & String)) {

		if (c->regs[VCPU_REGS_RCX] == 0) {
			kvm_rip_write(ctxt->vcpu, c->eip);
			goto done;
		}


		if ((c->b == 0xa6) || (c->b == 0xa7) ||
				(c->b == 0xae) || (c->b == 0xaf)) {
			if ((c->rep_prefix == REPE_PREFIX) &&
				((ctxt->eflags & EFLG_ZF) == 0)) {
					kvm_rip_write(ctxt->vcpu, c->eip);
					goto done;
			}
			if ((c->rep_prefix == REPNE_PREFIX) &&
				((ctxt->eflags & EFLG_ZF) == EFLG_ZF)) {
				kvm_rip_write(ctxt->vcpu, c->eip);
				goto done;
			}
		}
		c->regs[VCPU_REGS_RCX]--;
		c->eip = kvm_rip_read(ctxt->vcpu);
	}

	if (c->src.type == OP_MEM) {
		c->src.ptr = (unsigned long *)memop;
		c->src.val = 0;
		rc = ops->read_emulated((unsigned long)c->src.ptr,
					&c->src.val,
					c->src.bytes,
					ctxt->vcpu);
		if (rc != 0)
			goto done;
		c->src.orig_val = c->src.val;
	}

	if ((c->d & DstMask) == ImplicitOps)
		goto special_insn;


	if (c->dst.type == OP_MEM) {
		c->dst.ptr = (unsigned long *)memop;
		c->dst.bytes = (c->d & ByteOp) ? 1 : c->op_bytes;
		c->dst.val = 0;
		if (c->d & BitOp) {
			unsigned long mask = ~(c->dst.bytes * 8 - 1);

			c->dst.ptr = (void *)c->dst.ptr +
						   (c->src.val & mask) / 8;
		}
		if (!(c->d & Mov) &&

		    ((rc = ops->read_emulated((unsigned long)c->dst.ptr,
					   &c->dst.val,
					  c->dst.bytes, ctxt->vcpu)) != 0))
			goto done;
	}
	c->dst.orig_val = c->dst.val;

special_insn:

	if (c->twobyte)
		goto twobyte_insn;

	switch (c->b) {
	case 0x00 ... 0x05:
	      add:
		emulate_2op_SrcV("add", c->src, c->dst, ctxt->eflags);
		break;
	case 0x06:
		emulate_push_sreg(ctxt, VCPU_SREG_ES);
		break;
	case 0x07:
		rc = emulate_pop_sreg(ctxt, ops, VCPU_SREG_ES);
		if (rc != 0)
			goto done;
		break;
	case 0x08 ... 0x0d:
	      or:
		emulate_2op_SrcV("or", c->src, c->dst, ctxt->eflags);
		break;
	case 0x0e:
		emulate_push_sreg(ctxt, VCPU_SREG_CS);
		break;
	case 0x10 ... 0x15:
	      adc:
		emulate_2op_SrcV("adc", c->src, c->dst, ctxt->eflags);
		break;
	case 0x16:
		emulate_push_sreg(ctxt, VCPU_SREG_SS);
		break;
	case 0x17:
		rc = emulate_pop_sreg(ctxt, ops, VCPU_SREG_SS);
		if (rc != 0)
			goto done;
		break;
	case 0x18 ... 0x1d:
	      sbb:
		emulate_2op_SrcV("sbb", c->src, c->dst, ctxt->eflags);
		break;
	case 0x1e:
		emulate_push_sreg(ctxt, VCPU_SREG_DS);
		break;
	case 0x1f:
		rc = emulate_pop_sreg(ctxt, ops, VCPU_SREG_DS);
		if (rc != 0)
			goto done;
		break;
	case 0x20 ... 0x25:
	      and:
		emulate_2op_SrcV("and", c->src, c->dst, ctxt->eflags);
		break;
	case 0x28 ... 0x2d:
	      sub:
		emulate_2op_SrcV("sub", c->src, c->dst, ctxt->eflags);
		break;
	case 0x30 ... 0x35:
	      xor:
		emulate_2op_SrcV("xor", c->src, c->dst, ctxt->eflags);
		break;
	case 0x38 ... 0x3d:
	      cmp:
		emulate_2op_SrcV("cmp", c->src, c->dst, ctxt->eflags);
		break;
	case 0x40 ... 0x47:
		emulate_1op("inc", c->dst, ctxt->eflags);
		break;
	case 0x48 ... 0x4f:
		emulate_1op("dec", c->dst, ctxt->eflags);
		break;
	case 0x50 ... 0x57:
		emulate_push(ctxt);
		break;
	case 0x58 ... 0x5f:
	pop_instruction:
		rc = emulate_pop(ctxt, ops, &c->dst.val, c->op_bytes);
		if (rc != 0)
			goto done;
		break;
	case 0x60:
		emulate_pusha(ctxt);
		break;
	case 0x61:
		rc = emulate_popa(ctxt, ops);
		if (rc != 0)
			goto done;
		break;
	case 0x63:
		if (ctxt->mode != X86EMUL_MODE_PROT64)
			goto cannot_emulate;
		c->dst.val = (s32) c->src.val;
		break;
	case 0x68:
	case 0x6a:
		emulate_push(ctxt);
		break;
	case 0x6c:
	case 0x6d:
		 if (kvm_emulate_pio_string(ctxt->vcpu,
				1,
				(c->d & ByteOp) ? 1 : c->op_bytes,
				c->rep_prefix ?
				address_mask(c, c->regs[VCPU_REGS_RCX]) : 1,
				(ctxt->eflags & EFLG_DF),
				register_address(c, es_base(ctxt),
						 c->regs[VCPU_REGS_RDI]),
				c->rep_prefix,
				c->regs[VCPU_REGS_RDX]) == 0) {
			c->eip = saved_eip;
			return -1;
		}
		return 0;
	case 0x6e:
	case 0x6f:
		if (kvm_emulate_pio_string(ctxt->vcpu,
				0,
				(c->d & ByteOp) ? 1 : c->op_bytes,
				c->rep_prefix ?
				address_mask(c, c->regs[VCPU_REGS_RCX]) : 1,
				(ctxt->eflags & EFLG_DF),
					 register_address(c,
					  seg_override_base(ctxt, c),
						 c->regs[VCPU_REGS_RSI]),
				c->rep_prefix,
				c->regs[VCPU_REGS_RDX]) == 0) {
			c->eip = saved_eip;
			return -1;
		}
		return 0;
	case 0x70 ... 0x7f:
		if (test_cc(c->b, ctxt->eflags))
			jmp_rel(c, c->src.val);
		break;
	case 0x80 ... 0x83:
		switch (c->modrm_reg) {
		case 0:
			goto add;
		case 1:
			goto or;
		case 2:
			goto adc;
		case 3:
			goto sbb;
		case 4:
			goto and;
		case 5:
			goto sub;
		case 6:
			goto xor;
		case 7:
			goto cmp;
		}
		break;
	case 0x84 ... 0x85:
		emulate_2op_SrcV("test", c->src, c->dst, ctxt->eflags);
		break;
	case 0x86 ... 0x87:
	xchg:

		switch (c->dst.bytes) {
		case 1:
			*(u8 *) c->src.ptr = (u8) c->dst.val;
			break;
		case 2:
			*(u16 *) c->src.ptr = (u16) c->dst.val;
			break;
		case 4:
			*c->src.ptr = (u32) c->dst.val;
			break;
		case 8:
			*c->src.ptr = c->dst.val;
			break;
		}


		c->dst.val = c->src.val;
		c->lock_prefix = 1;
		break;
	case 0x88 ... 0x8b:
		goto mov;
	case 0x8c: {
		struct kvm_segment segreg;

		if (c->modrm_reg <= 5)
			kvm_get_segment(ctxt->vcpu, &segreg, c->modrm_reg);
		else {
			printk(KERN_INFO "0x8c: Invalid segreg in modrm byte 0x%02x\n",
			       c->modrm);
			goto cannot_emulate;
		}
		c->dst.val = segreg.selector;
		break;
	}
	case 0x8d:
		c->dst.val = c->modrm_ea;
		break;
	case 0x8e: {
		uint16_t sel;
		int type_bits;
		int err;

		sel = c->src.val;
		if (c->modrm_reg == VCPU_SREG_SS)
			toggle_interruptibility(ctxt, X86_SHADOW_INT_MOV_SS);

		if (c->modrm_reg <= 5) {
			type_bits = (c->modrm_reg == 1) ? 9 : 1;
			err = kvm_load_segment_descriptor(ctxt->vcpu, sel,
							  type_bits, c->modrm_reg);
		} else {
			printk(KERN_INFO "Invalid segreg in modrm byte 0x%02x\n",
					c->modrm);
			goto cannot_emulate;
		}

		if (err < 0)
			goto cannot_emulate;

		c->dst.type = OP_NONE;
		break;
	}
	case 0x8f:
		rc = emulate_grp1a(ctxt, ops);
		if (rc != 0)
			goto done;
		break;
	case 0x90:
		if (!(c->rex_prefix & 1)) {
			c->dst.type = OP_NONE;
			break;
		}
	case 0x91 ... 0x97:
		c->src.type = c->dst.type = OP_REG;
		c->src.bytes = c->dst.bytes = c->op_bytes;
		c->src.ptr = (unsigned long *) &c->regs[VCPU_REGS_RAX];
		c->src.val = *(c->src.ptr);
		goto xchg;
	case 0x9c:
		c->src.val =  (unsigned long) ctxt->eflags;
		emulate_push(ctxt);
		break;
	case 0x9d:
		c->dst.type = OP_REG;
		c->dst.ptr = (unsigned long *) &ctxt->eflags;
		c->dst.bytes = c->op_bytes;
		goto pop_instruction;
	case 0xa0 ... 0xa1:
		c->dst.ptr = (unsigned long *)&c->regs[VCPU_REGS_RAX];
		c->dst.val = c->src.val;
		break;
	case 0xa2 ... 0xa3:
		c->dst.val = (unsigned long)c->regs[VCPU_REGS_RAX];
		break;
	case 0xa4 ... 0xa5:
		c->dst.type = OP_MEM;
		c->dst.bytes = (c->d & ByteOp) ? 1 : c->op_bytes;
		c->dst.ptr = (unsigned long *)register_address(c,
						   es_base(ctxt),
						   c->regs[VCPU_REGS_RDI]);
		if ((rc = ops->read_emulated(register_address(c,
					   seg_override_base(ctxt, c),
					c->regs[VCPU_REGS_RSI]),
					&c->dst.val,
					c->dst.bytes, ctxt->vcpu)) != 0)
			goto done;
		register_address_increment(c, &c->regs[VCPU_REGS_RSI],
				       (ctxt->eflags & EFLG_DF) ? -c->dst.bytes
							   : c->dst.bytes);
		register_address_increment(c, &c->regs[VCPU_REGS_RDI],
				       (ctxt->eflags & EFLG_DF) ? -c->dst.bytes
							   : c->dst.bytes);
		break;
	case 0xa6 ... 0xa7:
		c->src.type = OP_NONE;
		c->src.bytes = (c->d & ByteOp) ? 1 : c->op_bytes;
		c->src.ptr = (unsigned long *)register_address(c,
				       seg_override_base(ctxt, c),
						   c->regs[VCPU_REGS_RSI]);
		if ((rc = ops->read_emulated((unsigned long)c->src.ptr,
						&c->src.val,
						c->src.bytes,
						ctxt->vcpu)) != 0)
			goto done;

		c->dst.type = OP_NONE;
		c->dst.bytes = (c->d & ByteOp) ? 1 : c->op_bytes;
		c->dst.ptr = (unsigned long *)register_address(c,
						   es_base(ctxt),
						   c->regs[VCPU_REGS_RDI]);
		if ((rc = ops->read_emulated((unsigned long)c->dst.ptr,
						&c->dst.val,
						c->dst.bytes,
						ctxt->vcpu)) != 0)
			goto done;

		DPRINTF("cmps: mem1=0x%p mem2=0x%p\n", c->src.ptr, c->dst.ptr);

		emulate_2op_SrcV("cmp", c->src, c->dst, ctxt->eflags);

		register_address_increment(c, &c->regs[VCPU_REGS_RSI],
				       (ctxt->eflags & EFLG_DF) ? -c->src.bytes
								  : c->src.bytes);
		register_address_increment(c, &c->regs[VCPU_REGS_RDI],
				       (ctxt->eflags & EFLG_DF) ? -c->dst.bytes
								  : c->dst.bytes);

		break;
	case 0xaa ... 0xab:
		c->dst.type = OP_MEM;
		c->dst.bytes = (c->d & ByteOp) ? 1 : c->op_bytes;
		c->dst.ptr = (unsigned long *)register_address(c,
						   es_base(ctxt),
						   c->regs[VCPU_REGS_RDI]);
		c->dst.val = c->regs[VCPU_REGS_RAX];
		register_address_increment(c, &c->regs[VCPU_REGS_RDI],
				       (ctxt->eflags & EFLG_DF) ? -c->dst.bytes
							   : c->dst.bytes);
		break;
	case 0xac ... 0xad:
		c->dst.type = OP_REG;
		c->dst.bytes = (c->d & ByteOp) ? 1 : c->op_bytes;
		c->dst.ptr = (unsigned long *)&c->regs[VCPU_REGS_RAX];
		if ((rc = ops->read_emulated(register_address(c,
						 seg_override_base(ctxt, c),
						 c->regs[VCPU_REGS_RSI]),
						 &c->dst.val,
						 c->dst.bytes,
						 ctxt->vcpu)) != 0)
			goto done;
		register_address_increment(c, &c->regs[VCPU_REGS_RSI],
				       (ctxt->eflags & EFLG_DF) ? -c->dst.bytes
							   : c->dst.bytes);
		break;
	case 0xae ... 0xaf:
		DPRINTF("Urk! I don't handle SCAS.\n");
		goto cannot_emulate;
	case 0xb0 ... 0xbf:
		goto mov;
	case 0xc0 ... 0xc1:
		emulate_grp2(ctxt);
		break;
	case 0xc3:
		c->dst.type = OP_REG;
		c->dst.ptr = &c->eip;
		c->dst.bytes = c->op_bytes;
		goto pop_instruction;
	case 0xc6 ... 0xc7:
	mov:
		c->dst.val = c->src.val;
		break;
	case 0xcb:
		rc = emulate_ret_far(ctxt, ops);
		if (rc)
			goto done;
		break;
	case 0xd0 ... 0xd1:
		c->src.val = 1;
		emulate_grp2(ctxt);
		break;
	case 0xd2 ... 0xd3:
		c->src.val = c->regs[VCPU_REGS_RCX];
		emulate_grp2(ctxt);
		break;
	case 0xe4:
	case 0xe5:
		port = c->src.val;
		io_dir_in = 1;
		goto do_io;
	case 0xe6:
	case 0xe7:
		port = c->src.val;
		io_dir_in = 0;
		goto do_io;
	case 0xe8:  {
		long int rel = c->src.val;
		c->src.val = (unsigned long) c->eip;
		jmp_rel(c, rel);
		emulate_push(ctxt);
		break;
	}
	case 0xe9:
		goto jmp;
	case 0xea:
		if (kvm_load_segment_descriptor(ctxt->vcpu, c->src2.val, 9,
					VCPU_SREG_CS) < 0) {
			DPRINTF("jmp far: Failed to load CS descriptor\n");
			goto cannot_emulate;
		}

		c->eip = c->src.val;
		break;
	case 0xeb:
	      jmp:
		jmp_rel(c, c->src.val);
		c->dst.type = OP_NONE;
		break;
	case 0xec:
	case 0xed:
		port = c->regs[VCPU_REGS_RDX];
		io_dir_in = 1;
		goto do_io;
	case 0xee:
	case 0xef:
		port = c->regs[VCPU_REGS_RDX];
		io_dir_in = 0;
	do_io:	if (kvm_emulate_pio(ctxt->vcpu, io_dir_in,
				   (c->d & ByteOp) ? 1 : c->op_bytes,
				   port) != 0) {
			c->eip = saved_eip;
			goto cannot_emulate;
		}
		break;
	case 0xf4:
		ctxt->vcpu->arch.halt_request = 1;
		break;
	case 0xf5:

		ctxt->eflags ^= EFLG_CF;
		c->dst.type = OP_NONE;
		break;
	case 0xf6 ... 0xf7:
		rc = emulate_grp3(ctxt, ops);
		if (rc != 0)
			goto done;
		break;
	case 0xf8:
		ctxt->eflags &= ~EFLG_CF;
		c->dst.type = OP_NONE;
		break;
	case 0xfa:
		ctxt->eflags &= ~X86_EFLAGS_IF;
		c->dst.type = OP_NONE;
		break;
	case 0xfb:
		toggle_interruptibility(ctxt, X86_SHADOW_INT_STI);
		ctxt->eflags |= X86_EFLAGS_IF;
		c->dst.type = OP_NONE;
		break;
	case 0xfc:
		ctxt->eflags &= ~EFLG_DF;
		c->dst.type = OP_NONE;
		break;
	case 0xfd:
		ctxt->eflags |= EFLG_DF;
		c->dst.type = OP_NONE;
		break;
	case 0xfe ... 0xff:
		rc = emulate_grp45(ctxt, ops);
		if (rc != 0)
			goto done;
		break;
	}

writeback:
	rc = writeback(ctxt, ops);
	if (rc != 0)
		goto done;


	memcpy(ctxt->vcpu->arch.regs, c->regs, sizeof c->regs);
	kvm_rip_write(ctxt->vcpu, c->eip);

done:
	if (rc == X86EMUL_UNHANDLEABLE) {
		c->eip = saved_eip;
		return -1;
	}
	return 0;

twobyte_insn:
	switch (c->b) {
	case 0x01:
		switch (c->modrm_reg) {
			u16 size;
			unsigned long address;

		case 0:
			if (c->modrm_mod != 3 || c->modrm_rm != 1)
				goto cannot_emulate;

			rc = kvm_fix_hypercall(ctxt->vcpu);
			if (rc)
				goto done;


			c->eip = kvm_rip_read(ctxt->vcpu);

			c->dst.type = OP_NONE;
			break;
		case 2:
			rc = read_descriptor(ctxt, ops, c->src.ptr,
					     &size, &address, c->op_bytes);
			if (rc)
				goto done;
			realmode_lgdt(ctxt->vcpu, size, address);

			c->dst.type = OP_NONE;
			break;
		case 3:
			if (c->modrm_mod == 3) {
				switch (c->modrm_rm) {
				case 1:
					rc = kvm_fix_hypercall(ctxt->vcpu);
					if (rc)
						goto done;
					break;
				default:
					goto cannot_emulate;
				}
			} else {
				rc = read_descriptor(ctxt, ops, c->src.ptr,
						     &size, &address,
						     c->op_bytes);
				if (rc)
					goto done;
				realmode_lidt(ctxt->vcpu, size, address);
			}

			c->dst.type = OP_NONE;
			break;
		case 4:
			c->dst.bytes = 2;
			c->dst.val = realmode_get_cr(ctxt->vcpu, 0);
			break;
		case 6:
			realmode_lmsw(ctxt->vcpu, (u16)c->src.val,
				      &ctxt->eflags);
			c->dst.type = OP_NONE;
			break;
		case 7:
			emulate_invlpg(ctxt->vcpu, memop);

			c->dst.type = OP_NONE;
			break;
		default:
			goto cannot_emulate;
		}
		break;
	case 0x05:
		if (emulate_syscall(ctxt) == -1)
			goto cannot_emulate;
		else
			goto writeback;
		break;
	case 0x06:
		emulate_clts(ctxt->vcpu);
		c->dst.type = OP_NONE;
		break;
	case 0x08:
	case 0x09:
	case 0x0d:
	case 0x18:
		c->dst.type = OP_NONE;
		break;
	case 0x20:
		if (c->modrm_mod != 3)
			goto cannot_emulate;
		c->regs[c->modrm_rm] =
				realmode_get_cr(ctxt->vcpu, c->modrm_reg);
		c->dst.type = OP_NONE;
		break;
	case 0x21:
		if (c->modrm_mod != 3)
			goto cannot_emulate;
		rc = emulator_get_dr(ctxt, c->modrm_reg, &c->regs[c->modrm_rm]);
		if (rc)
			goto cannot_emulate;
		c->dst.type = OP_NONE;
		break;
	case 0x22:
		if (c->modrm_mod != 3)
			goto cannot_emulate;
		realmode_set_cr(ctxt->vcpu,
				c->modrm_reg, c->modrm_val, &ctxt->eflags);
		c->dst.type = OP_NONE;
		break;
	case 0x23:
		if (c->modrm_mod != 3)
			goto cannot_emulate;
		rc = emulator_set_dr(ctxt, c->modrm_reg,
				     c->regs[c->modrm_rm]);
		if (rc)
			goto cannot_emulate;
		c->dst.type = OP_NONE;
		break;
	case 0x30:

		msr_data = (u32)c->regs[VCPU_REGS_RAX]
			| ((u64)c->regs[VCPU_REGS_RDX] << 32);
		rc = kvm_set_msr(ctxt->vcpu, c->regs[VCPU_REGS_RCX], msr_data);
		if (rc) {
			kvm_inject_gp(ctxt->vcpu, 0);
			c->eip = kvm_rip_read(ctxt->vcpu);
		}
		rc = X86EMUL_CONTINUE;
		c->dst.type = OP_NONE;
		break;
	case 0x32:

		rc = kvm_get_msr(ctxt->vcpu, c->regs[VCPU_REGS_RCX], &msr_data);
		if (rc) {
			kvm_inject_gp(ctxt->vcpu, 0);
			c->eip = kvm_rip_read(ctxt->vcpu);
		} else {
			c->regs[VCPU_REGS_RAX] = (u32)msr_data;
			c->regs[VCPU_REGS_RDX] = msr_data >> 32;
		}
		rc = X86EMUL_CONTINUE;
		c->dst.type = OP_NONE;
		break;
	case 0x34:
		if (emulate_sysenter(ctxt) == -1)
			goto cannot_emulate;
		else
			goto writeback;
		break;
	case 0x35:
		if (emulate_sysexit(ctxt) == -1)
			goto cannot_emulate;
		else
			goto writeback;
		break;
	case 0x40 ... 0x4f:
		c->dst.val = c->dst.orig_val = c->src.val;
		if (!test_cc(c->b, ctxt->eflags))
			c->dst.type = OP_NONE;
		break;
	case 0x80 ... 0x8f:
		if (test_cc(c->b, ctxt->eflags))
			jmp_rel(c, c->src.val);
		c->dst.type = OP_NONE;
		break;
	case 0xa0:
		emulate_push_sreg(ctxt, VCPU_SREG_FS);
		break;
	case 0xa1:
		rc = emulate_pop_sreg(ctxt, ops, VCPU_SREG_FS);
		if (rc != 0)
			goto done;
		break;
	case 0xa3:
	      bt:
		c->dst.type = OP_NONE;

		c->src.val &= (c->dst.bytes << 3) - 1;
		emulate_2op_SrcV_nobyte("bt", c->src, c->dst, ctxt->eflags);
		break;
	case 0xa4:
	case 0xa5:
		emulate_2op_cl("shld", c->src2, c->src, c->dst, ctxt->eflags);
		break;
	case 0xa8:
		emulate_push_sreg(ctxt, VCPU_SREG_GS);
		break;
	case 0xa9:
		rc = emulate_pop_sreg(ctxt, ops, VCPU_SREG_GS);
		if (rc != 0)
			goto done;
		break;
	case 0xab:
	      bts:

		c->src.val &= (c->dst.bytes << 3) - 1;
		emulate_2op_SrcV_nobyte("bts", c->src, c->dst, ctxt->eflags);
		break;
	case 0xac:
	case 0xad:
		emulate_2op_cl("shrd", c->src2, c->src, c->dst, ctxt->eflags);
		break;
	case 0xae:
		break;
	case 0xb0 ... 0xb1:


		c->src.orig_val = c->src.val;
		c->src.val = c->regs[VCPU_REGS_RAX];
		emulate_2op_SrcV("cmp", c->src, c->dst, ctxt->eflags);
		if (ctxt->eflags & EFLG_ZF) {

			c->dst.val = c->src.orig_val;
		} else {

			c->dst.type = OP_REG;
			c->dst.ptr = (unsigned long *)&c->regs[VCPU_REGS_RAX];
		}
		break;
	case 0xb3:
	      btr:

		c->src.val &= (c->dst.bytes << 3) - 1;
		emulate_2op_SrcV_nobyte("btr", c->src, c->dst, ctxt->eflags);
		break;
	case 0xb6 ... 0xb7:
		c->dst.bytes = c->op_bytes;
		c->dst.val = (c->d & ByteOp) ? (u8) c->src.val
						       : (u16) c->src.val;
		break;
	case 0xba:
		switch (c->modrm_reg & 3) {
		case 0:
			goto bt;
		case 1:
			goto bts;
		case 2:
			goto btr;
		case 3:
			goto btc;
		}
		break;
	case 0xbb:
	      btc:

		c->src.val &= (c->dst.bytes << 3) - 1;
		emulate_2op_SrcV_nobyte("btc", c->src, c->dst, ctxt->eflags);
		break;
	case 0xbe ... 0xbf:
		c->dst.bytes = c->op_bytes;
		c->dst.val = (c->d & ByteOp) ? (s8) c->src.val :
							(s16) c->src.val;
		break;
	case 0xc3:
		c->dst.bytes = c->op_bytes;
		c->dst.val = (c->op_bytes == 4) ? (u32) c->src.val :
							(u64) c->src.val;
		break;
	case 0xc7:
		rc = emulate_grp9(ctxt, ops, memop);
		if (rc != 0)
			goto done;
		c->dst.type = OP_NONE;
		break;
	}
	goto writeback;

cannot_emulate:
	DPRINTF("Cannot emulate %02x\n", c->b);
	c->eip = saved_eip;
	return -1;
}
