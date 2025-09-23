#include "../../include/instructions.h"

// NOLINTBEGIN
// Source: https://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html
Instruction inst_from_byte(uint8_t byte) {
    switch (byte) {
        /* ADD */
        case 0x80:
            return new_add(O_B);
        case 0x81:
            return new_add(O_C);
        case 0x82:
            return new_add(O_D);
        case 0x83:
            return new_add(O_E);
        case 0x84:
            return new_add(O_H);
        case 0x85:
            return new_add(O_L);
        case 0x86:
            // TODO: this needs to be HL indirect
            return new_add(O_HL);
        case 0x87:
            return new_add(O_A);

        /* ADDHL */
        case 0x09:
            return new_add_hl(O_BC);
        case 0x19:
            return new_add_hl(O_DE);
        case 0x29:
            return new_add_hl(O_HL);
        case 0x39:
            return new_add_hl(O_SP);

        /* ADC */
        case 0x88:
            return new_adc(O_B);
        case 0x89:
            return new_adc(O_C);
        case 0x8A:
            return new_adc(O_D);
        case 0x8B:
            return new_adc(O_E);
        case 0x8C:
            return new_adc(O_H);
        case 0x8D:
            return new_adc(O_L);
        case 0x8E:
            // TODO: this needs to be HL indirect
            return new_adc(O_HL);
        case 0x8F:
            return new_adc(O_A);

        /* SUB */
        case 0x90:
            return new_sub(O_B);
        case 0x91:
            return new_sub(O_C);
        case 0x92:
            return new_sub(O_D);
        case 0x93:
            return new_sub(O_E);
        case 0x94:
            return new_sub(O_H);
        case 0x95:
            return new_sub(O_L);
        case 0x96:
            // TODO: this needs to be HL indirect
            return new_sub(O_HL);
        case 0x97:
            return new_sub(O_A);

        /* SBC */
        case 0x98:
            return new_sbc(O_B);
        case 0x99:
            return new_sbc(O_C);
        case 0x9A:
            return new_sbc(O_D);
        case 0x9B:
            return new_sbc(O_E);
        case 0x9C:
            return new_sbc(O_H);
        case 0x9D:
            return new_sbc(O_L);
        case 0x9E:
            // TODO: this needs to be HL indirect
            return new_sbc(O_HL);
        case 0x9F:
            return new_sbc(O_A);

        /* AND */
        case 0xA0:
            return new_and(O_B);
        case 0xA1:
            return new_and(O_C);
        case 0xA2:
            return new_and(O_D);
        case 0xA3:
            return new_and(O_E);
        case 0xA4:
            return new_and(O_H);
        case 0xA5:
            return new_and(O_L);
        case 0xA6:
            return new_and(O_HL);
        case 0xA7:
            return new_and(O_A);

        /* OR */
        case 0xB0:
            return new_or(O_B);
        case 0xB1:
            return new_or(O_C);
        case 0xB2:
            return new_or(O_D);
        case 0xB3:
            return new_or(O_E);
        case 0xB4:
            return new_or(O_H);
        case 0xB5:
            return new_or(O_L);
        case 0xB6:
            return new_or(O_HL);
        case 0xB7:
            return new_or(O_A);

        /* XOR */
        case 0xA8:
            return new_xor(O_B);
        case 0xA9:
            return new_xor(O_C);
        case 0xAA:
            return new_xor(O_D);
        case 0xAB:
            return new_xor(O_E);
        case 0xAC:
            return new_xor(O_H);
        case 0xAD:
            return new_xor(O_L);
        case 0xAE:
            return new_xor(O_HL);
        case 0xAF:
            return new_xor(O_A);

        /* CP */
        case 0xB8:
            return new_cp(O_B);
        case 0xB9:
            return new_cp(O_C);
        case 0xBA:
            return new_cp(O_D);
        case 0xBB:
            return new_cp(O_E);
        case 0xBC:
            return new_cp(O_H);
        case 0xBD:
            return new_cp(O_L);
        case 0xBE:
            return new_cp(O_HL);
        case 0xBF:
            return new_cp(O_A);

        /* INC */
        case 0x03:
            return new_inc(O_BC);
        case 0x13:
            return new_inc(O_DE);
        case 0x23:
            return new_inc(O_HL);
        case 0x33:
            return new_inc(O_SP);
        case 0x04:
            return new_inc(O_B);
        case 0x14:
            return new_inc(O_D);
        case 0x24:
            return new_inc(O_H);
        case 0x34:
            // TODO: should be HL indirect (addr at HL)
            return new_inc(O_HL);
        case 0x0C:
            return new_inc(O_C);
        case 0x1C:
            return new_inc(O_E);
        case 0x2C:
            return new_inc(O_L);
        case 0x3C:
            return new_inc(O_A);

        /* DEC */
        case 0x0B:
            return new_dec(O_BC);
        case 0x1B:
            return new_dec(O_DE);
        case 0x2B:
            return new_dec(O_HL);
        case 0x3B:
            return new_dec(O_SP);
        case 0x05:
            return new_dec(O_B);
        case 0x15:
            return new_dec(O_D);
        case 0x25:
            return new_dec(O_H);
        case 0x35:
            // TODO: should be HL indirect (addr at HL)
            return new_dec(O_HL);
        case 0x0D:
            return new_dec(O_C);
        case 0x1D:
            return new_dec(O_E);
        case 0x2D:
            return new_dec(O_L);
        case 0x3D:
            return new_dec(O_A);

        /* CCF */
        case 0x3F:
            return new_ccf();

        /* SCF */
        case 0x37:
            return new_scf();

        /* RRA */
        case 0x1F:
            return new_rra();

        /* RLA */
        case 0x17:
            return new_rla();

        /* RRCA */
        case 0x0F:
            return new_rrca();

        /* RLCA */
        case 0x07:
            return new_rlca();

        /* CPL */
        case 0x2F:
            return new_cpl();

        /* JP */
        case 0xC2:
            return new_jp(NOT_ZERO);
        case 0xD2:
            return new_jp(NOT_CARRY);
        case 0xC3:
            return new_jp(ALWAYS);
        case 0xCA:
            return new_jp(ZERO);
        case 0xDA:
            return new_jp(CARRY);

        /* JPHL */
        case 0xE9:
            return new_jphl();

        /* JR */
        case 0x20:
            return new_jr(NOT_ZERO);
        case 0x30:
            return new_jr(NOT_CARRY);
        case 0x18:
            return new_jr(ALWAYS);
        case 0x28:
            return new_jr(ZERO);
        case 0x38:
            return new_jr(CARRY);

        /* LD_REG */
        case 0x40:
            return new_ld(O_B, O_B);
        case 0x41:
            return new_ld(O_B, O_C);
        case 0x42:
            return new_ld(O_B, O_D);
        case 0x43:
            return new_ld(O_B, O_E);
        case 0x44:
            return new_ld(O_B, O_H);
        case 0x45:
            return new_ld(O_B, O_L);
        case 0x47:
            return new_ld(O_B, O_A);
        case 0x48:
            return new_ld(O_C, O_B);
        case 0x49:
            return new_ld(O_C, O_C);
        case 0x4A:
            return new_ld(O_C, O_D);
        case 0x4B:
            return new_ld(O_C, O_E);
        case 0x4C:
            return new_ld(O_C, O_H);
        case 0x4D:
            return new_ld(O_C, O_L);
        case 0x4F:
            return new_ld(O_C, O_A);

        case 0x50:
            return new_ld(O_D, O_B);
        case 0x51:
            return new_ld(O_D, O_C);
        case 0x52:
            return new_ld(O_D, O_D);
        case 0x53:
            return new_ld(O_D, O_E);
        case 0x54:
            return new_ld(O_D, O_H);
        case 0x55:
            return new_ld(O_D, O_L);
        case 0x57:
            return new_ld(O_D, O_A);
        case 0x58:
            return new_ld(O_E, O_B);
        case 0x59:
            return new_ld(O_E, O_C);
        case 0x5A:
            return new_ld(O_E, O_D);
        case 0x5B:
            return new_ld(O_E, O_E);
        case 0x5C:
            return new_ld(O_E, O_H);
        case 0x5D:
            return new_ld(O_E, O_L);
        case 0x5F:
            return new_ld(O_E, O_A);

        case 0x60:
            return new_ld(O_H, O_B);
        case 0x61:
            return new_ld(O_H, O_C);
        case 0x62:
            return new_ld(O_H, O_D);
        case 0x63:
            return new_ld(O_H, O_E);
        case 0x64:
            return new_ld(O_H, O_H);
        case 0x65:
            return new_ld(O_H, O_L);
        case 0x67:
            return new_ld(O_H, O_A);
        case 0x68:
            return new_ld(O_L, O_B);
        case 0x69:
            return new_ld(O_L, O_C);
        case 0x6A:
            return new_ld(O_L, O_D);
        case 0x6B:
            return new_ld(O_L, O_E);
        case 0x6C:
            return new_ld(O_L, O_H);
        case 0x6D:
            return new_ld(O_L, O_L);
        case 0x6F:
            return new_ld(O_L, O_A);

        case 0x78:
            return new_ld(O_A, O_B);
        case 0x79:
            return new_ld(O_A, O_C);
        case 0x7A:
            return new_ld(O_A, O_D);
        case 0x7B:
            return new_ld(O_A, O_E);
        case 0x7C:
            return new_ld(O_A, O_H);
        case 0x7D:
            return new_ld(O_A, O_L);
        case 0x7F:
            return new_ld(O_A, O_A);

        /* LD_D8 */
        case 0x06:
            return new_ld(O_B, O_D8);
        case 0x16:
            return new_ld(O_D, O_D8);
        case 0x26:
            return new_ld(O_H, O_D8);
        case 0x0E:
            return new_ld(O_C, O_D8);
        case 0x1E:
            return new_ld(O_E, O_D8);
        case 0x2E:
            return new_ld(O_L, O_D8);
        case 0x3E:
            return new_ld(O_A, O_D8);

        /* LD_D16 */
        case 0x01:
            return new_ld(O_BC, O_D16);
        case 0x11:
            return new_ld(O_DE, O_D16);
        case 0x21:
            return new_ld(O_HL, O_D16);
        case 0x31:
            return new_ld(O_SP, O_D16);

        /* LD_D8_IND */
        case 0x36:
            return new_ld(O_HL_IND, O_D8);

        /* LD_IND */
        case 0x02:
            return new_ld(O_BC_IND, O_A);
        case 0x12:
            return new_ld(O_DE_IND, O_A);
        case 0x0A:
            return new_ld(O_A, O_BC_IND);
        case 0x1A:
            return new_ld(O_A, O_DE_IND);
        case 0x46:
            return new_ld(O_B, O_HL_IND);
        case 0x56:
            return new_ld(O_D, O_HL_IND);
        case 0x66:
            return new_ld(O_H, O_HL_IND);
        case 0x4E:
            return new_ld(O_C, O_HL_IND);
        case 0x5E:
            return new_ld(O_E, O_HL_IND);
        case 0x6E:
            return new_ld(O_L, O_HL_IND);
        case 0x7E:
            return new_ld(O_A, O_HL_IND);
        case 0x70:
            return new_ld(O_HL_IND, O_B);
        case 0x71:
            return new_ld(O_HL_IND, O_C);
        case 0x72:
            return new_ld(O_HL_IND, O_D);
        case 0x73:
            return new_ld(O_HL_IND, O_E);
        case 0x74:
            return new_ld(O_HL_IND, O_H);
        case 0x75:
            return new_ld(O_HL_IND, O_L);
        case 0x77:
            return new_ld(O_HL_IND, O_A);

        /* LD_ADDR */
        case 0xEA:
            return new_ld(O_A16_IND, O_A);
        case 0xFA:
            return new_ld(O_A, O_A16_IND);

        /* LD_INC */
        case 0x22:
            return new_ld(O_HL_INC_IND, O_A);
        case 0x2A:
            return new_ld(O_A, O_HL_INC_IND);

        /* LD_DEC */
        case 0x32:
            return new_ld(O_HL_DEC_IND, O_A);
        case 0x3A:
            return new_ld(O_A, O_HL_DEC_IND);

        /* LDH_IND */
        case 0xE2:
            return new_ldh(O_C_IND, O_A);
        case 0xF2:
            return new_ldh(O_A, O_C_IND);

        /* LDH_ADDR */
        case 0xE0:
            return new_ldh(O_A8_IND, O_A);
        case 0xF0:
            return new_ldh(O_A, O_A8_IND);

        /* PUSH */
        case 0xC5:
            return new_push(O_BC);
        case 0xD5:
            return new_push(O_DE);
        case 0xE5:
            return new_push(O_HL);
        case 0xF5:
            return new_push(O_AF);

        /* POP */
        case 0xC1:
            return new_pop(O_BC);
        case 0xD1:
            return new_pop(O_DE);
        case 0xE1:
            return new_pop(O_HL);
        case 0xF1:
            return new_pop(O_AF);

        /* CALL */
        case 0xC4:
            return new_call(NOT_ZERO);
        case 0xD4:
            return new_call(NOT_CARRY);
        case 0xCC:
            return new_call(ZERO);
        case 0xDC:
            return new_call(CARRY);
        case 0xCD:
            return new_call(ALWAYS);

        /* RET */
        case 0xC0:
            return new_ret(NOT_ZERO);
        case 0xD0:
            return new_ret(NOT_CARRY);
        case 0xC8:
            return new_ret(ZERO);
        case 0xD8:
            return new_ret(CARRY);
        case 0xC9:
            return new_ret(ALWAYS);

        /* NOP */
        case 0x00:
            return new_nop();
    }

    Instruction not_found = NOT_FOUND_INST;
    return not_found;
}

Instruction pf_inst_from_byte(uint8_t byte) {
    switch (byte) {
        /* BIT */
        case 0x40:
            return new_bit(0, O_B);
        case 0x41:
            return new_bit(0, O_C);
        case 0x42:
            return new_bit(0, O_D);
        case 0x43:
            return new_bit(0, O_E);
        case 0x44:
            return new_bit(0, O_H);
        case 0x45:
            return new_bit(0, O_L);
        case 0x46:
            return new_bit(0, O_HL);
        case 0x47:
            return new_bit(0, O_A);
        case 0x48:
            return new_bit(1, O_B);
        case 0x49:
            return new_bit(1, O_C);
        case 0x4A:
            return new_bit(1, O_D);
        case 0x4B:
            return new_bit(1, O_E);
        case 0x4C:
            return new_bit(1, O_H);
        case 0x4D:
            return new_bit(1, O_L);
        case 0x4E:
            return new_bit(1, O_HL);
        case 0x4F:
            return new_bit(1, O_A);

        case 0x50:
            return new_bit(2, O_B);
        case 0x51:
            return new_bit(2, O_C);
        case 0x52:
            return new_bit(2, O_D);
        case 0x53:
            return new_bit(2, O_E);
        case 0x54:
            return new_bit(2, O_H);
        case 0x55:
            return new_bit(2, O_L);
        case 0x56:
            return new_bit(2, O_HL);
        case 0x57:
            return new_bit(2, O_A);
        case 0x58:
            return new_bit(3, O_B);
        case 0x59:
            return new_bit(3, O_C);
        case 0x5A:
            return new_bit(3, O_D);
        case 0x5B:
            return new_bit(3, O_E);
        case 0x5C:
            return new_bit(3, O_H);
        case 0x5D:
            return new_bit(3, O_L);
        case 0x5E:
            return new_bit(3, O_HL);
        case 0x5F:
            return new_bit(3, O_A);

        case 0x60:
            return new_bit(4, O_B);
        case 0x61:
            return new_bit(4, O_C);
        case 0x62:
            return new_bit(4, O_D);
        case 0x63:
            return new_bit(4, O_E);
        case 0x64:
            return new_bit(4, O_H);
        case 0x65:
            return new_bit(4, O_L);
        case 0x66:
            return new_bit(4, O_HL);
        case 0x67:
            return new_bit(4, O_A);
        case 0x68:
            return new_bit(5, O_B);
        case 0x69:
            return new_bit(5, O_C);
        case 0x6A:
            return new_bit(5, O_D);
        case 0x6B:
            return new_bit(5, O_E);
        case 0x6C:
            return new_bit(5, O_H);
        case 0x6D:
            return new_bit(5, O_L);
        case 0x6E:
            return new_bit(5, O_HL);
        case 0x6F:
            return new_bit(5, O_A);

        case 0x70:
            return new_bit(6, O_B);
        case 0x71:
            return new_bit(6, O_C);
        case 0x72:
            return new_bit(6, O_D);
        case 0x73:
            return new_bit(6, O_E);
        case 0x74:
            return new_bit(6, O_H);
        case 0x75:
            return new_bit(6, O_L);
        case 0x76:
            return new_bit(6, O_HL);
        case 0x77:
            return new_bit(6, O_A);
        case 0x78:
            return new_bit(7, O_B);
        case 0x79:
            return new_bit(7, O_C);
        case 0x7A:
            return new_bit(7, O_D);
        case 0x7B:
            return new_bit(7, O_E);
        case 0x7C:
            return new_bit(7, O_H);
        case 0x7D:
            return new_bit(7, O_L);
        case 0x7E:
            return new_bit(7, O_HL);
        case 0x7F:
            return new_bit(7, O_A);

        /* RESET */
        case 0x80:
            return new_reset(0, O_B);
        case 0x81:
            return new_reset(0, O_C);
        case 0x82:
            return new_reset(0, O_D);
        case 0x83:
            return new_reset(0, O_E);
        case 0x84:
            return new_reset(0, O_H);
        case 0x85:
            return new_reset(0, O_L);
        case 0x86:
            return new_reset(0, O_HL);
        case 0x87:
            return new_reset(0, O_A);
        case 0x88:
            return new_reset(1, O_B);
        case 0x89:
            return new_reset(1, O_C);
        case 0x8A:
            return new_reset(1, O_D);
        case 0x8B:
            return new_reset(1, O_E);
        case 0x8C:
            return new_reset(1, O_H);
        case 0x8D:
            return new_reset(1, O_L);
        case 0x8E:
            return new_reset(1, O_HL);
        case 0x8F:
            return new_reset(1, O_A);

        case 0x90:
            return new_reset(2, O_B);
        case 0x91:
            return new_reset(2, O_C);
        case 0x92:
            return new_reset(2, O_D);
        case 0x93:
            return new_reset(2, O_E);
        case 0x94:
            return new_reset(2, O_H);
        case 0x95:
            return new_reset(2, O_L);
        case 0x96:
            return new_reset(2, O_HL);
        case 0x97:
            return new_reset(2, O_A);
        case 0x98:
            return new_reset(3, O_B);
        case 0x99:
            return new_reset(3, O_C);
        case 0x9A:
            return new_reset(3, O_D);
        case 0x9B:
            return new_reset(3, O_E);
        case 0x9C:
            return new_reset(3, O_H);
        case 0x9D:
            return new_reset(3, O_L);
        case 0x9E:
            return new_reset(3, O_HL);
        case 0x9F:
            return new_reset(3, O_A);

        case 0xA0:
            return new_reset(4, O_B);
        case 0xA1:
            return new_reset(4, O_C);
        case 0xA2:
            return new_reset(4, O_D);
        case 0xA3:
            return new_reset(4, O_E);
        case 0xA4:
            return new_reset(4, O_H);
        case 0xA5:
            return new_reset(4, O_L);
        case 0xA6:
            return new_reset(4, O_HL);
        case 0xA7:
            return new_reset(4, O_A);
        case 0xA8:
            return new_reset(5, O_B);
        case 0xA9:
            return new_reset(5, O_C);
        case 0xAA:
            return new_reset(5, O_D);
        case 0xAB:
            return new_reset(5, O_E);
        case 0xAC:
            return new_reset(5, O_H);
        case 0xAD:
            return new_reset(5, O_L);
        case 0xAE:
            return new_reset(5, O_HL);
        case 0xAF:
            return new_reset(5, O_A);

        case 0xB0:
            return new_reset(6, O_B);
        case 0xB1:
            return new_reset(6, O_C);
        case 0xB2:
            return new_reset(6, O_D);
        case 0xB3:
            return new_reset(6, O_E);
        case 0xB4:
            return new_reset(6, O_H);
        case 0xB5:
            return new_reset(6, O_L);
        case 0xB6:
            return new_reset(6, O_HL);
        case 0xB7:
            return new_reset(6, O_A);
        case 0xB8:
            return new_reset(7, O_B);
        case 0xB9:
            return new_reset(7, O_C);
        case 0xBA:
            return new_reset(7, O_D);
        case 0xBB:
            return new_reset(7, O_E);
        case 0xBC:
            return new_reset(7, O_H);
        case 0xBD:
            return new_reset(7, O_L);
        case 0xBE:
            return new_reset(7, O_HL);
        case 0xBF:
            return new_reset(7, O_A);

        /* SET */
        case 0xC0:
            return new_set(0, O_B);
        case 0xC1:
            return new_set(0, O_C);
        case 0xC2:
            return new_set(0, O_D);
        case 0xC3:
            return new_set(0, O_E);
        case 0xC4:
            return new_set(0, O_H);
        case 0xC5:
            return new_set(0, O_L);
        case 0xC6:
            return new_set(0, O_HL);
        case 0xC7:
            return new_set(0, O_A);
        case 0xC8:
            return new_set(1, O_B);
        case 0xC9:
            return new_set(1, O_C);
        case 0xCA:
            return new_set(1, O_D);
        case 0xCB:
            return new_set(1, O_E);
        case 0xCC:
            return new_set(1, O_H);
        case 0xCD:
            return new_set(1, O_L);
        case 0xCE:
            return new_set(1, O_HL);
        case 0xCF:
            return new_set(1, O_A);

        case 0xD0:
            return new_set(2, O_B);
        case 0xD1:
            return new_set(2, O_C);
        case 0xD2:
            return new_set(2, O_D);
        case 0xD3:
            return new_set(2, O_E);
        case 0xD4:
            return new_set(2, O_H);
        case 0xD5:
            return new_set(2, O_L);
        case 0xD6:
            return new_set(2, O_HL);
        case 0xD7:
            return new_set(2, O_A);
        case 0xD8:
            return new_set(3, O_B);
        case 0xD9:
            return new_set(3, O_C);
        case 0xDA:
            return new_set(3, O_D);
        case 0xDB:
            return new_set(3, O_E);
        case 0xDC:
            return new_set(3, O_H);
        case 0xDD:
            return new_set(3, O_L);
        case 0xDE:
            return new_set(3, O_HL);
        case 0xDF:
            return new_set(3, O_A);

        case 0xE0:
            return new_set(4, O_B);
        case 0xE1:
            return new_set(4, O_C);
        case 0xE2:
            return new_set(4, O_D);
        case 0xE3:
            return new_set(4, O_E);
        case 0xE4:
            return new_set(4, O_H);
        case 0xE5:
            return new_set(4, O_L);
        case 0xE6:
            return new_set(4, O_HL);
        case 0xE7:
            return new_set(4, O_A);
        case 0xE8:
            return new_set(5, O_B);
        case 0xE9:
            return new_set(5, O_C);
        case 0xEA:
            return new_set(5, O_D);
        case 0xEB:
            return new_set(5, O_E);
        case 0xEC:
            return new_set(5, O_H);
        case 0xED:
            return new_set(5, O_L);
        case 0xEE:
            return new_set(5, O_HL);
        case 0xEF:
            return new_set(5, O_A);

        case 0xF0:
            return new_set(6, O_B);
        case 0xF1:
            return new_set(6, O_C);
        case 0xF2:
            return new_set(6, O_D);
        case 0xF3:
            return new_set(6, O_E);
        case 0xF4:
            return new_set(6, O_H);
        case 0xF5:
            return new_set(6, O_L);
        case 0xF6:
            return new_set(6, O_HL);
        case 0xF7:
            return new_set(6, O_A);
        case 0xF8:
            return new_set(7, O_B);
        case 0xF9:
            return new_set(7, O_C);
        case 0xFA:
            return new_set(7, O_D);
        case 0xFB:
            return new_set(7, O_E);
        case 0xFC:
            return new_set(7, O_H);
        case 0xFD:
            return new_set(7, O_L);
        case 0xFE:
            return new_set(7, O_HL);
        case 0xFF:
            return new_set(7, O_A);

        /* SRL */
        case 0x38:
            return new_srl(O_B);
        case 0x39:
            return new_srl(O_C);
        case 0x3A:
            return new_srl(O_D);
        case 0x3B:
            return new_srl(O_E);
        case 0x3C:
            return new_srl(O_H);
        case 0x3D:
            return new_srl(O_L);
        case 0x3E:
            return new_srl(O_HL);
        case 0x3F:
            return new_srl(O_A);

        /* RR */
        case 0x18:
            return new_rr(O_B);
        case 0x19:
            return new_rr(O_C);
        case 0x1A:
            return new_rr(O_D);
        case 0x1B:
            return new_rr(O_E);
        case 0x1C:
            return new_rr(O_H);
        case 0x1D:
            return new_rr(O_L);
        case 0x1E:
            return new_rr(O_HL);
        case 0x1F:
            return new_rr(O_A);

        /* RL */
        case 0x10:
            return new_rl(O_B);
        case 0x11:
            return new_rl(O_C);
        case 0x12:
            return new_rl(O_D);
        case 0x13:
            return new_rl(O_E);
        case 0x14:
            return new_rl(O_H);
        case 0x15:
            return new_rl(O_L);
        case 0x16:
            return new_rl(O_HL);
        case 0x17:
            return new_rl(O_A);

        /* RRC */
        case 0x08:
            return new_rrc(O_B);
        case 0x09:
            return new_rrc(O_C);
        case 0x0A:
            return new_rrc(O_D);
        case 0x0B:
            return new_rrc(O_E);
        case 0x0C:
            return new_rrc(O_H);
        case 0x0D:
            return new_rrc(O_L);
        case 0x0E:
            return new_rrc(O_HL);
        case 0x0F:
            return new_rrc(O_A);

        /* RLC */
        case 0x00:
            return new_rlc(O_B);
        case 0x01:
            return new_rlc(O_C);
        case 0x02:
            return new_rlc(O_D);
        case 0x03:
            return new_rlc(O_E);
        case 0x04:
            return new_rlc(O_H);
        case 0x05:
            return new_rlc(O_L);
        case 0x06:
            return new_rlc(O_HL);
        case 0x07:
            return new_rlc(O_A);

        /* SRA */
        case 0x28:
            return new_sra(O_B);
        case 0x29:
            return new_sra(O_C);
        case 0x2A:
            return new_sra(O_D);
        case 0x2B:
            return new_sra(O_E);
        case 0x2C:
            return new_sra(O_H);
        case 0x2D:
            return new_sra(O_L);
        case 0x2E:
            return new_sra(O_HL);
        case 0x2F:
            return new_sra(O_A);

        /* SLA */
        case 0x20:
            return new_sla(O_B);
        case 0x21:
            return new_sla(O_C);
        case 0x22:
            return new_sla(O_D);
        case 0x23:
            return new_sla(O_E);
        case 0x24:
            return new_sla(O_H);
        case 0x25:
            return new_sla(O_L);
        case 0x26:
            return new_sla(O_HL);
        case 0x27:
            return new_sla(O_A);

        /* SWAP */
        case 0x30:
            return new_swap(O_B);
        case 0x31:
            return new_swap(O_C);
        case 0x32:
            return new_swap(O_D);
        case 0x33:
            return new_swap(O_E);
        case 0x34:
            return new_swap(O_H);
        case 0x35:
            return new_swap(O_L);
        case 0x36:
            return new_swap(O_HL);
        case 0x37:
            return new_swap(O_A);
    }

    Instruction not_found = NOT_FOUND_INST;
    return not_found;
}
// NOLINTEND

Instruction new_add(enum Operand source) {
    Instruction add = {ADD, 0, 0, O_A, source};
    return add;
}

Instruction new_add_hl(enum Operand source) {
    Instruction addhl = {ADD_HL, 0, 0, O_A, source};
    return addhl;
}

Instruction new_adc(enum Operand source) {
    Instruction adc = {ADC, 0, 0, O_A, source};
    return adc;
}

Instruction new_sub(enum Operand source) {
    Instruction sub = {SUB, 0, 0, O_A, source};
    return sub;
}

Instruction new_sbc(enum Operand source) {
    Instruction sbc = {SBC, 0, 0, O_A, source};
    return sbc;
}

Instruction new_and(enum Operand source) {
    Instruction and = {AND, 0, 0, O_A, source};
    return and;
}

Instruction new_or(enum Operand source) {
    Instruction or_ = {OR, 0, 0, O_A, source};
    return or_;
}

Instruction new_xor(enum Operand source) {
    Instruction xor = {XOR, 0, 0, O_A, source};
    return xor;
}

Instruction new_cp(enum Operand source) {
    Instruction cp_ = {CP, 0, 0, O_A, source};
    return cp_;
}

Instruction new_inc(enum Operand target) {
    Instruction inc = {INC, 0, 0, O_A, target};
    return inc;
}

Instruction new_dec(enum Operand target) {
    Instruction dec = {DEC, 0, 0, O_A, target};
    return dec;
}

Instruction new_ccf(void) {
    Instruction ccf = {CCF, 0, 0, O_A, 0};
    return ccf;
}

Instruction new_scf(void) {
    Instruction scf = {SCF, 0, 0, O_A, 0};
    return scf;
}

Instruction new_rra(void) {
    Instruction rra = {RRA, 0, 0, O_A, 0};
    return rra;
}

Instruction new_rla(void) {
    Instruction rla = {RLA, 0, 0, O_A, 0};
    return rla;
}

Instruction new_rrca(void) {
    Instruction rrca = {RRCA, 0, 0, O_A, 0};
    return rrca;
}

Instruction new_rlca(void) {
    Instruction rrla = {RLCA, 0, 0, O_A, 0};
    return rrla;
}

Instruction new_cpl(void) {
    Instruction cpl = {CPL, 0, 0, O_A, 0};
    return cpl;
}

Instruction new_bit(uint8_t bit_index, enum Operand target) {
    Instruction bit = {BIT, bit_index, 0, target, 0};
    return bit;
}

Instruction new_reset(uint8_t bit_index, enum Operand target) {
    Instruction reset = {RESET, bit_index, 0, target, 0};
    return reset;
}

Instruction new_set(uint8_t bit_index, enum Operand target) {
    Instruction set = {SET, bit_index, 0, target, 0};
    return set;
}

Instruction new_srl(enum Operand target) {
    Instruction srl = {SRL, 0, 0, target, 0};
    return srl;
}

Instruction new_rr(enum Operand target) {
    Instruction rr_ = {RR, 0, 0, target, 0};
    return rr_;
}

Instruction new_rl(enum Operand target) {
    Instruction rl_ = {RL, 0, 0, target, 0};
    return rl_;
}

Instruction new_rrc(enum Operand target) {
    Instruction rrc = {RRC, 0, 0, target, 0};
    return rrc;
}

Instruction new_rlc(enum Operand target) {
    Instruction rlc = {RLC, 0, 0, target, 0};
    return rlc;
}

Instruction new_sra(enum Operand target) {
    Instruction sra = {SRA, 0, 0, target, 0};
    return sra;
}

Instruction new_sla(enum Operand target) {
    Instruction sla = {SLA, 0, 0, target, 0};
    return sla;
}

Instruction new_swap(enum Operand target) {
    Instruction swap = {SWAP, 0, 0, target, 0};
    return swap;
}

Instruction new_jp(enum JumpCondition jump_cond) {
    Instruction jump = {JP, 0, jump_cond, 0, 0};
    return jump;
}

Instruction new_jphl(void) {
    Instruction jumphl = {JPHL, 0, ALWAYS, 0, 0};
    return jumphl;
}

Instruction new_jr(enum JumpCondition jump_cond) {
    Instruction jumpr = {JR, 0, jump_cond, 0, 0};
    return jumpr;
}

Instruction new_ld(enum Operand target, enum Operand source) {  // NOLINT
    enum InstructionKind load_kind;

    if (target == O_HL_IND && source == O_D8) {
        load_kind = LD_D8_IND;
    } else if (source == O_D8) {
        load_kind = LD_D8;
    } else if (source == O_D16) {
        load_kind = LD_D16;
    } else if (target == O_A16_IND || source == O_A16_IND) {
        load_kind = LD_ADDR;
    } else if ((O_BC_IND <= target && target <= O_HL_IND) ||
               (O_BC_IND <= source && source <= O_HL_IND)) {
        load_kind = LD_IND;
    } else if (target == O_HL_INC_IND || source == O_HL_INC_IND) {
        load_kind = LD_INC;
    } else if (target == O_HL_DEC_IND || source == O_HL_DEC_IND) {
        load_kind = LD_DEC;
    } else {
        load_kind = LD_REG;
    }

    Instruction load = {load_kind, 0, 0, target, source};
    return load;
}

Instruction new_ldh(enum Operand target, enum Operand source) {  // NOLINT
    enum InstructionKind loadh_kind;

    if (target == O_C_IND || source == O_C_IND) {
        loadh_kind = LDH_IND;
    } else {
        loadh_kind = LDH_ADDR;
    }

    Instruction loadh = {loadh_kind, 0, 0, target, source};
    return loadh;
}

Instruction new_push(enum Operand source) {
    Instruction push = {PUSH, 0, 0, 0, source};
    return push;
}

Instruction new_pop(enum Operand target) {
    Instruction pop = {POP, 0, 0, target, 0};
    return pop;
}

Instruction new_call(enum JumpCondition jump_cond) {
    Instruction call = {CALL, 0, jump_cond, 0, 0};
    return call;
}

Instruction new_ret(enum JumpCondition jump_cond) {
    Instruction ret = {RET, 0, jump_cond, 0, 0};
    return ret;
}

Instruction new_nop(void) {
    Instruction nop = {NOP, 0, 0, 0, 0};
    return nop;
}
