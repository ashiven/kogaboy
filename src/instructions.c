#include "../include/instructions.h"

#include <stdint.h>

// == Inst(kind=ADD, target=A, bit_index=7, jump_cond=NOT_ZERO, ld_target=LO_A, ld_source=LO_A)
#define NOT_FOUND_INST {0, 0, 7, 0, 0, 0}

// NOLINTBEGIN
// Source: https://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html
Instruction inst_from_byte(uint8_t byte) {
    switch (byte) {
        /* ADD */
        case 0x80:
            return new_add(B);
        case 0x81:
            return new_add(C);
        case 0x82:
            return new_add(D);
        case 0x83:
            return new_add(E);
        case 0x84:
            return new_add(H);
        case 0x85:
            return new_add(L);
        case 0x86:
            return new_add(HL);
        case 0x87:
            return new_add(A);

        /* ADDHL */
        case 0x09:
            return new_addhl(BC);
        case 0x19:
            return new_addhl(DE);
        case 0x29:
            return new_addhl(HL);
        case 0x39:
            // TODO:
            // return new_addhl(SP);

        /* ADC */
        case 0x88:
            return new_adc(B);
        case 0x89:
            return new_adc(C);
        case 0x8A:
            return new_adc(D);
        case 0x8B:
            return new_adc(E);
        case 0x8C:
            return new_adc(H);
        case 0x8D:
            return new_adc(L);
        case 0x8E:
            return new_adc(HL);
        case 0x8F:
            return new_adc(A);

        /* SUB */
        case 0x90:
            return new_sub(B);
        case 0x91:
            return new_sub(C);
        case 0x92:
            return new_sub(D);
        case 0x93:
            return new_sub(E);
        case 0x94:
            return new_sub(H);
        case 0x95:
            return new_sub(L);
        case 0x96:
            return new_sub(HL);
        case 0x97:
            return new_sub(A);

        /* SBC */
        case 0x98:
            return new_sbc(B);
        case 0x99:
            return new_sbc(C);
        case 0x9A:
            return new_sbc(D);
        case 0x9B:
            return new_sbc(E);
        case 0x9C:
            return new_sbc(H);
        case 0x9D:
            return new_sbc(L);
        case 0x9E:
            return new_sbc(HL);
        case 0x9F:
            return new_sbc(A);

        /* AND */
        case 0xA0:
            return new_and(B);
        case 0xA1:
            return new_and(C);
        case 0xA2:
            return new_and(D);
        case 0xA3:
            return new_and(E);
        case 0xA4:
            return new_and(H);
        case 0xA5:
            return new_and(L);
        case 0xA6:
            return new_and(HL);
        case 0xA7:
            return new_and(A);

        /* OR */
        case 0xB0:
            return new_or(B);
        case 0xB1:
            return new_or(C);
        case 0xB2:
            return new_or(D);
        case 0xB3:
            return new_or(E);
        case 0xB4:
            return new_or(H);
        case 0xB5:
            return new_or(L);
        case 0xB6:
            return new_or(HL);
        case 0xB7:
            return new_or(A);

        /* XOR */
        case 0xA8:
            return new_xor(B);
        case 0xA9:
            return new_xor(C);
        case 0xAA:
            return new_xor(D);
        case 0xAB:
            return new_xor(E);
        case 0xAC:
            return new_xor(H);
        case 0xAD:
            return new_xor(L);
        case 0xAE:
            return new_xor(HL);
        case 0xAF:
            return new_xor(A);

        /* CP */
        case 0xB8:
            return new_cp(B);
        case 0xB9:
            return new_cp(C);
        case 0xBA:
            return new_cp(D);
        case 0xBB:
            return new_cp(E);
        case 0xBC:
            return new_cp(H);
        case 0xBD:
            return new_cp(L);
        case 0xBE:
            return new_cp(HL);
        case 0xBF:
            return new_cp(A);

        /* INC */
        case 0x03:
            return new_inc(BC);
        case 0x13:
            return new_inc(DE);
        case 0x23:
            return new_inc(HL);
        case 0x33:
            // TODO:
            // return new_inc(SP);
        case 0x04:
            return new_inc(B);
        case 0x14:
            return new_inc(D);
        case 0x24:
            return new_inc(H);
        case 0x34:
            return new_inc(HL);
        case 0x0C:
            return new_inc(C);
        case 0x1C:
            return new_inc(E);
        case 0x2C:
            return new_inc(L);
        case 0x3C:
            return new_inc(A);

        /* DEC */
        case 0x0B:
            return new_inc(BC);
        case 0x1B:
            return new_inc(DE);
        case 0x2B:
            return new_inc(HL);
        case 0x3B:
            // TODO:
            // return new_inc(SP);
        case 0x05:
            return new_inc(B);
        case 0x15:
            return new_inc(D);
        case 0x25:
            return new_inc(H);
        case 0x35:
            return new_inc(HL);
        case 0x0D:
            return new_inc(C);
        case 0x1D:
            return new_inc(E);
        case 0x2D:
            return new_inc(L);
        case 0x3D:
            return new_inc(A);

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

        /* LD_REG */
        case 0x40:
            return new_ld(LO_B, LO_B);
        case 0x41:
            return new_ld(LO_B, LO_C);
        case 0x42:
            return new_ld(LO_B, LO_D);
        case 0x43:
            return new_ld(LO_B, LO_E);
        case 0x44:
            return new_ld(LO_B, LO_H);
        case 0x45:
            return new_ld(LO_B, LO_L);
        case 0x47:
            return new_ld(LO_B, LO_A);
        case 0x48:
            return new_ld(LO_C, LO_B);
        case 0x49:
            return new_ld(LO_C, LO_C);
        case 0x4A:
            return new_ld(LO_C, LO_D);
        case 0x4B:
            return new_ld(LO_C, LO_E);
        case 0x4C:
            return new_ld(LO_C, LO_H);
        case 0x4D:
            return new_ld(LO_C, LO_L);
        case 0x4F:
            return new_ld(LO_C, LO_A);

        case 0x50:
            return new_ld(LO_D, LO_B);
        case 0x51:
            return new_ld(LO_D, LO_C);
        case 0x52:
            return new_ld(LO_D, LO_D);
        case 0x53:
            return new_ld(LO_D, LO_E);
        case 0x54:
            return new_ld(LO_D, LO_H);
        case 0x55:
            return new_ld(LO_D, LO_L);
        case 0x57:
            return new_ld(LO_D, LO_A);
        case 0x58:
            return new_ld(LO_E, LO_B);
        case 0x59:
            return new_ld(LO_E, LO_C);
        case 0x5A:
            return new_ld(LO_E, LO_D);
        case 0x5B:
            return new_ld(LO_E, LO_E);
        case 0x5C:
            return new_ld(LO_E, LO_H);
        case 0x5D:
            return new_ld(LO_E, LO_L);
        case 0x5F:
            return new_ld(LO_E, LO_A);

        case 0x60:
            return new_ld(LO_H, LO_B);
        case 0x61:
            return new_ld(LO_H, LO_C);
        case 0x62:
            return new_ld(LO_H, LO_D);
        case 0x63:
            return new_ld(LO_H, LO_E);
        case 0x64:
            return new_ld(LO_H, LO_H);
        case 0x65:
            return new_ld(LO_H, LO_L);
        case 0x67:
            return new_ld(LO_H, LO_A);
        case 0x68:
            return new_ld(LO_L, LO_B);
        case 0x69:
            return new_ld(LO_L, LO_C);
        case 0x6A:
            return new_ld(LO_L, LO_D);
        case 0x6B:
            return new_ld(LO_L, LO_E);
        case 0x6C:
            return new_ld(LO_L, LO_H);
        case 0x6D:
            return new_ld(LO_L, LO_L);
        case 0x6F:
            return new_ld(LO_L, LO_A);

        case 0x78:
            return new_ld(LO_A, LO_B);
        case 0x79:
            return new_ld(LO_A, LO_C);
        case 0x7A:
            return new_ld(LO_A, LO_D);
        case 0x7B:
            return new_ld(LO_A, LO_E);
        case 0x7C:
            return new_ld(LO_A, LO_H);
        case 0x7D:
            return new_ld(LO_A, LO_L);
        case 0x7F:
            return new_ld(LO_A, LO_A);

        /* LD_D8 */
        case 0x06:
            return new_ld(LO_B, LO_D8);
        case 0x16:
            return new_ld(LO_D, LO_D8);
        case 0x26:
            return new_ld(LO_H, LO_D8);
        case 0x0E:
            return new_ld(LO_C, LO_D8);
        case 0x1E:
            return new_ld(LO_E, LO_D8);
        case 0x2E:
            return new_ld(LO_L, LO_D8);
        case 0x3E:
            return new_ld(LO_A, LO_D8);

        /* LD_D16 */
        case 0x01:
            return new_ld(LO_BC, LO_D8);
        case 0x11:
            return new_ld(LO_DE, LO_D8);
        case 0x21:
            return new_ld(LO_HL, LO_D8);
        case 0x31:
            return new_ld(LO_SP, LO_D8);

        /* LD_D8_IND */
        case 0x36:
            return new_ld(LO_HL_IND, LO_D8);

        /* LD_IND */
        case 0x02:
            return new_ld(LO_BC_IND, LO_A);
        case 0x12:
            return new_ld(LO_DE_IND, LO_A);
        case 0x0A:
            return new_ld(LO_A, LO_BC_IND);
        case 0x1A:
            return new_ld(LO_A, LO_DE_IND);
        case 0x46:
            return new_ld(LO_B, LO_HL_IND);
        case 0x56:
            return new_ld(LO_D, LO_HL_IND);
        case 0x66:
            return new_ld(LO_H, LO_HL_IND);
        case 0x4E:
            return new_ld(LO_C, LO_HL_IND);
        case 0x5E:
            return new_ld(LO_E, LO_HL_IND);
        case 0x6E:
            return new_ld(LO_L, LO_HL_IND);
        case 0x7E:
            return new_ld(LO_A, LO_HL_IND);
        case 0x70:
            return new_ld(LO_HL_IND, LO_B);
        case 0x71:
            return new_ld(LO_HL_IND, LO_C);
        case 0x72:
            return new_ld(LO_HL_IND, LO_D);
        case 0x73:
            return new_ld(LO_HL_IND, LO_E);
        case 0x74:
            return new_ld(LO_HL_IND, LO_H);
        case 0x75:
            return new_ld(LO_HL_IND, LO_L);
        case 0x77:
            return new_ld(LO_HL_IND, LO_A);

        /* LD_ADDR */
        case 0xEA:
            return new_ld(LO_A16_IND, LO_A);
        case 0xFA:
            return new_ld(LO_A, LO_A16_IND);

        /* LD_INC */
        case 0x22:
            return new_ld(LO_HL_INC_IND, LO_A);
        case 0x2A:
            return new_ld(LO_A, LO_HL_INC_IND);

        /* LD_DEC */
        case 0x32:
            return new_ld(LO_HL_DEC_IND, LO_A);
        case 0x3A:
            return new_ld(LO_A, LO_HL_DEC_IND);

        /* LDH_IND */
        case 0xE2:
            return new_ldh(LO_C_IND, LO_A);
        case 0xF2:
            return new_ldh(LO_A, LO_C_IND);

        /* LDH_ADDR */
        case 0xE0:
            return new_ldh(LO_A8_IND, LO_A);
        case 0xF0:
            return new_ldh(LO_A, LO_A8_IND);
    }

    Instruction not_found = NOT_FOUND_INST;
    return not_found;
}

Instruction pf_inst_from_byte(uint8_t byte) {
    switch (byte) {
        /* BIT */
        case 0x40:
            return new_bit(0, B);
        case 0x41:
            return new_bit(0, C);
        case 0x42:
            return new_bit(0, D);
        case 0x43:
            return new_bit(0, E);
        case 0x44:
            return new_bit(0, H);
        case 0x45:
            return new_bit(0, L);
        case 0x46:
            return new_bit(0, HL);
        case 0x47:
            return new_bit(0, A);
        case 0x48:
            return new_bit(1, B);
        case 0x49:
            return new_bit(1, C);
        case 0x4A:
            return new_bit(1, D);
        case 0x4B:
            return new_bit(1, E);
        case 0x4C:
            return new_bit(1, H);
        case 0x4D:
            return new_bit(1, L);
        case 0x4E:
            return new_bit(1, HL);
        case 0x4F:
            return new_bit(1, A);

        case 0x50:
            return new_bit(2, B);
        case 0x51:
            return new_bit(2, C);
        case 0x52:
            return new_bit(2, D);
        case 0x53:
            return new_bit(2, E);
        case 0x54:
            return new_bit(2, H);
        case 0x55:
            return new_bit(2, L);
        case 0x56:
            return new_bit(2, HL);
        case 0x57:
            return new_bit(2, A);
        case 0x58:
            return new_bit(3, B);
        case 0x59:
            return new_bit(3, C);
        case 0x5A:
            return new_bit(3, D);
        case 0x5B:
            return new_bit(3, E);
        case 0x5C:
            return new_bit(3, H);
        case 0x5D:
            return new_bit(3, L);
        case 0x5E:
            return new_bit(3, HL);
        case 0x5F:
            return new_bit(3, A);

        case 0x60:
            return new_bit(4, B);
        case 0x61:
            return new_bit(4, C);
        case 0x62:
            return new_bit(4, D);
        case 0x63:
            return new_bit(4, E);
        case 0x64:
            return new_bit(4, H);
        case 0x65:
            return new_bit(4, L);
        case 0x66:
            return new_bit(4, HL);
        case 0x67:
            return new_bit(4, A);
        case 0x68:
            return new_bit(5, B);
        case 0x69:
            return new_bit(5, C);
        case 0x6A:
            return new_bit(5, D);
        case 0x6B:
            return new_bit(5, E);
        case 0x6C:
            return new_bit(5, H);
        case 0x6D:
            return new_bit(5, L);
        case 0x6E:
            return new_bit(5, HL);
        case 0x6F:
            return new_bit(5, A);

        case 0x70:
            return new_bit(6, B);
        case 0x71:
            return new_bit(6, C);
        case 0x72:
            return new_bit(6, D);
        case 0x73:
            return new_bit(6, E);
        case 0x74:
            return new_bit(6, H);
        case 0x75:
            return new_bit(6, L);
        case 0x76:
            return new_bit(6, HL);
        case 0x77:
            return new_bit(6, A);
        case 0x78:
            return new_bit(7, B);
        case 0x79:
            return new_bit(7, C);
        case 0x7A:
            return new_bit(7, D);
        case 0x7B:
            return new_bit(7, E);
        case 0x7C:
            return new_bit(7, H);
        case 0x7D:
            return new_bit(7, L);
        case 0x7E:
            return new_bit(7, HL);
        case 0x7F:
            return new_bit(7, A);

        /* RESET */
        case 0x80:
            return new_reset(0, B);
        case 0x81:
            return new_reset(0, C);
        case 0x82:
            return new_reset(0, D);
        case 0x83:
            return new_reset(0, E);
        case 0x84:
            return new_reset(0, H);
        case 0x85:
            return new_reset(0, L);
        case 0x86:
            return new_reset(0, HL);
        case 0x87:
            return new_reset(0, A);
        case 0x88:
            return new_reset(1, B);
        case 0x89:
            return new_reset(1, C);
        case 0x8A:
            return new_reset(1, D);
        case 0x8B:
            return new_reset(1, E);
        case 0x8C:
            return new_reset(1, H);
        case 0x8D:
            return new_reset(1, L);
        case 0x8E:
            return new_reset(1, HL);
        case 0x8F:
            return new_reset(1, A);

        case 0x90:
            return new_reset(2, B);
        case 0x91:
            return new_reset(2, C);
        case 0x92:
            return new_reset(2, D);
        case 0x93:
            return new_reset(2, E);
        case 0x94:
            return new_reset(2, H);
        case 0x95:
            return new_reset(2, L);
        case 0x96:
            return new_reset(2, HL);
        case 0x97:
            return new_reset(2, A);
        case 0x98:
            return new_reset(3, B);
        case 0x99:
            return new_reset(3, C);
        case 0x9A:
            return new_reset(3, D);
        case 0x9B:
            return new_reset(3, E);
        case 0x9C:
            return new_reset(3, H);
        case 0x9D:
            return new_reset(3, L);
        case 0x9E:
            return new_reset(3, HL);
        case 0x9F:
            return new_reset(3, A);

        case 0xA0:
            return new_reset(4, B);
        case 0xA1:
            return new_reset(4, C);
        case 0xA2:
            return new_reset(4, D);
        case 0xA3:
            return new_reset(4, E);
        case 0xA4:
            return new_reset(4, H);
        case 0xA5:
            return new_reset(4, L);
        case 0xA6:
            return new_reset(4, HL);
        case 0xA7:
            return new_reset(4, A);
        case 0xA8:
            return new_reset(5, B);
        case 0xA9:
            return new_reset(5, C);
        case 0xAA:
            return new_reset(5, D);
        case 0xAB:
            return new_reset(5, E);
        case 0xAC:
            return new_reset(5, H);
        case 0xAD:
            return new_reset(5, L);
        case 0xAE:
            return new_reset(5, HL);
        case 0xAF:
            return new_reset(5, A);

        case 0xB0:
            return new_reset(6, B);
        case 0xB1:
            return new_reset(6, C);
        case 0xB2:
            return new_reset(6, D);
        case 0xB3:
            return new_reset(6, E);
        case 0xB4:
            return new_reset(6, H);
        case 0xB5:
            return new_reset(6, L);
        case 0xB6:
            return new_reset(6, HL);
        case 0xB7:
            return new_reset(6, A);
        case 0xB8:
            return new_reset(7, B);
        case 0xB9:
            return new_reset(7, C);
        case 0xBA:
            return new_reset(7, D);
        case 0xBB:
            return new_reset(7, E);
        case 0xBC:
            return new_reset(7, H);
        case 0xBD:
            return new_reset(7, L);
        case 0xBE:
            return new_reset(7, HL);
        case 0xBF:
            return new_reset(7, A);

        /* SET */
        case 0xC0:
            return new_set(0, B);
        case 0xC1:
            return new_set(0, C);
        case 0xC2:
            return new_set(0, D);
        case 0xC3:
            return new_set(0, E);
        case 0xC4:
            return new_set(0, H);
        case 0xC5:
            return new_set(0, L);
        case 0xC6:
            return new_set(0, HL);
        case 0xC7:
            return new_set(0, A);
        case 0xC8:
            return new_set(1, B);
        case 0xC9:
            return new_set(1, C);
        case 0xCA:
            return new_set(1, D);
        case 0xCB:
            return new_set(1, E);
        case 0xCC:
            return new_set(1, H);
        case 0xCD:
            return new_set(1, L);
        case 0xCE:
            return new_set(1, HL);
        case 0xCF:
            return new_set(1, A);

        case 0xD0:
            return new_set(2, B);
        case 0xD1:
            return new_set(2, C);
        case 0xD2:
            return new_set(2, D);
        case 0xD3:
            return new_set(2, E);
        case 0xD4:
            return new_set(2, H);
        case 0xD5:
            return new_set(2, L);
        case 0xD6:
            return new_set(2, HL);
        case 0xD7:
            return new_set(2, A);
        case 0xD8:
            return new_set(3, B);
        case 0xD9:
            return new_set(3, C);
        case 0xDA:
            return new_set(3, D);
        case 0xDB:
            return new_set(3, E);
        case 0xDC:
            return new_set(3, H);
        case 0xDD:
            return new_set(3, L);
        case 0xDE:
            return new_set(3, HL);
        case 0xDF:
            return new_set(3, A);

        case 0xE0:
            return new_set(4, B);
        case 0xE1:
            return new_set(4, C);
        case 0xE2:
            return new_set(4, D);
        case 0xE3:
            return new_set(4, E);
        case 0xE4:
            return new_set(4, H);
        case 0xE5:
            return new_set(4, L);
        case 0xE6:
            return new_set(4, HL);
        case 0xE7:
            return new_set(4, A);
        case 0xE8:
            return new_set(5, B);
        case 0xE9:
            return new_set(5, C);
        case 0xEA:
            return new_set(5, D);
        case 0xEB:
            return new_set(5, E);
        case 0xEC:
            return new_set(5, H);
        case 0xED:
            return new_set(5, L);
        case 0xEE:
            return new_set(5, HL);
        case 0xEF:
            return new_set(5, A);

        case 0xF0:
            return new_set(6, B);
        case 0xF1:
            return new_set(6, C);
        case 0xF2:
            return new_set(6, D);
        case 0xF3:
            return new_set(6, E);
        case 0xF4:
            return new_set(6, H);
        case 0xF5:
            return new_set(6, L);
        case 0xF6:
            return new_set(6, HL);
        case 0xF7:
            return new_set(6, A);
        case 0xF8:
            return new_set(7, B);
        case 0xF9:
            return new_set(7, C);
        case 0xFA:
            return new_set(7, D);
        case 0xFB:
            return new_set(7, E);
        case 0xFC:
            return new_set(7, H);
        case 0xFD:
            return new_set(7, L);
        case 0xFE:
            return new_set(7, HL);
        case 0xFF:
            return new_set(7, A);

        /* SRL */
        case 0x38:
            return new_srl(B);
        case 0x39:
            return new_srl(C);
        case 0x3A:
            return new_srl(D);
        case 0x3B:
            return new_srl(E);
        case 0x3C:
            return new_srl(H);
        case 0x3D:
            return new_srl(L);
        case 0x3E:
            return new_srl(HL);
        case 0x3F:
            return new_srl(A);

        /* RR */
        case 0x18:
            return new_rr(B);
        case 0x19:
            return new_rr(C);
        case 0x1A:
            return new_rr(D);
        case 0x1B:
            return new_rr(E);
        case 0x1C:
            return new_rr(H);
        case 0x1D:
            return new_rr(L);
        case 0x1E:
            return new_rr(HL);
        case 0x1F:
            return new_rr(A);

        /* RL */
        case 0x10:
            return new_rl(B);
        case 0x11:
            return new_rl(C);
        case 0x12:
            return new_rl(D);
        case 0x13:
            return new_rl(E);
        case 0x14:
            return new_rl(H);
        case 0x15:
            return new_rl(L);
        case 0x16:
            return new_rl(HL);
        case 0x17:
            return new_rl(A);

        /* RRC */
        case 0x08:
            return new_rrc(B);
        case 0x09:
            return new_rrc(C);
        case 0x0A:
            return new_rrc(D);
        case 0x0B:
            return new_rrc(E);
        case 0x0C:
            return new_rrc(H);
        case 0x0D:
            return new_rrc(L);
        case 0x0E:
            return new_rrc(HL);
        case 0x0F:
            return new_rrc(A);

        /* RLC */
        case 0x00:
            return new_rlc(B);
        case 0x01:
            return new_rlc(C);
        case 0x02:
            return new_rlc(D);
        case 0x03:
            return new_rlc(E);
        case 0x04:
            return new_rlc(H);
        case 0x05:
            return new_rlc(L);
        case 0x06:
            return new_rlc(HL);
        case 0x07:
            return new_rlc(A);

        /* SRA */
        case 0x28:
            return new_sra(B);
        case 0x29:
            return new_sra(C);
        case 0x2A:
            return new_sra(D);
        case 0x2B:
            return new_sra(E);
        case 0x2C:
            return new_sra(H);
        case 0x2D:
            return new_sra(L);
        case 0x2E:
            return new_sra(HL);
        case 0x2F:
            return new_sra(A);

        /* SLA */
        case 0x20:
            return new_sla(B);
        case 0x21:
            return new_sla(C);
        case 0x22:
            return new_sla(D);
        case 0x23:
            return new_sla(E);
        case 0x24:
            return new_sla(H);
        case 0x25:
            return new_sla(L);
        case 0x26:
            return new_sla(HL);
        case 0x27:
            return new_sla(A);

        /* SWAP */
        case 0x30:
            return new_swap(B);
        case 0x31:
            return new_swap(C);
        case 0x32:
            return new_swap(D);
        case 0x33:
            return new_swap(E);
        case 0x34:
            return new_swap(H);
        case 0x35:
            return new_swap(L);
        case 0x36:
            return new_swap(HL);
        case 0x37:
            return new_swap(A);
    }

    Instruction not_found = NOT_FOUND_INST;
    return not_found;
}
// NOLINTEND

Instruction new_add(enum RegisterName target) {
    Instruction add = {ADD, target, 0, ALWAYS, LO_A, LO_A};
    return add;
}

Instruction new_addhl(enum RegisterName target) {
    Instruction addhl = {ADDHL, target, 0, ALWAYS, LO_A, LO_A};
    return addhl;
}

Instruction new_adc(enum RegisterName target) {
    Instruction adc = {ADC, target, 0, ALWAYS, LO_A, LO_A};
    return adc;
}

Instruction new_sub(enum RegisterName target) {
    Instruction sub = {SUB, target, 0, ALWAYS, LO_A, LO_A};
    return sub;
}

Instruction new_sbc(enum RegisterName target) {
    Instruction sbc = {SBC, target, 0, ALWAYS, LO_A, LO_A};
    return sbc;
}

Instruction new_and(enum RegisterName target) {
    Instruction and = {AND, target, 0, ALWAYS, LO_A, LO_A};
    return and;
}

Instruction new_or(enum RegisterName target) {
    Instruction or_ = {OR, target, 0, ALWAYS, LO_A, LO_A};
    return or_;
}

Instruction new_xor(enum RegisterName target) {
    Instruction xor = {XOR, target, 0, ALWAYS, LO_A, LO_A};
    return xor;
}

Instruction new_cp(enum RegisterName target) {
    Instruction cp_ = {CP, target, 0, ALWAYS, LO_A, LO_A};
    return cp_;
}

Instruction new_inc(enum RegisterName target) {
    Instruction inc = {INC, target, 0, ALWAYS, LO_A, LO_A};
    return inc;
}

Instruction new_dec(enum RegisterName target) {
    Instruction dec = {DEC, target, 0, ALWAYS, LO_A, LO_A};
    return dec;
}

Instruction new_ccf(void) {
    Instruction ccf = {CCF, 0, 0, ALWAYS, LO_A, LO_A};
    return ccf;
}

Instruction new_scf(void) {
    Instruction scf = {SCF, 0, 0, ALWAYS, LO_A, LO_A};
    return scf;
}

Instruction new_rra(void) {
    Instruction rra = {RRA, 0, 0, ALWAYS, LO_A, LO_A};
    return rra;
}

Instruction new_rla(void) {
    Instruction rla = {RLA, 0, 0, ALWAYS, LO_A, LO_A};
    return rla;
}

Instruction new_rrca(void) {
    Instruction rrca = {RRCA, 0, 0, ALWAYS, LO_A, LO_A};
    return rrca;
}

Instruction new_rlca(void) {
    Instruction rrla = {RLCA, 0, 0, ALWAYS, LO_A, LO_A};
    return rrla;
}

Instruction new_cpl(void) {
    Instruction cpl = {CPL, 0, 0, ALWAYS, LO_A, LO_A};
    return cpl;
}

Instruction new_bit(uint8_t bit_index, enum RegisterName target) {
    Instruction bit = {BIT, target, bit_index, ALWAYS, LO_A, LO_A};
    return bit;
}

Instruction new_reset(uint8_t bit_index, enum RegisterName target) {
    Instruction reset = {RESET, target, bit_index, ALWAYS, LO_A, LO_A};
    return reset;
}

Instruction new_set(uint8_t bit_index, enum RegisterName target) {
    Instruction set = {SET, target, bit_index, ALWAYS, LO_A, LO_A};
    return set;
}

Instruction new_srl(enum RegisterName target) {
    Instruction srl = {SRL, target, 0, ALWAYS, LO_A, LO_A};
    return srl;
}

Instruction new_rr(enum RegisterName target) {
    Instruction rr_ = {RR, target, 0, ALWAYS, LO_A, LO_A};
    return rr_;
}

Instruction new_rl(enum RegisterName target) {
    Instruction rl_ = {RL, target, 0, ALWAYS, LO_A, LO_A};
    return rl_;
}

Instruction new_rrc(enum RegisterName target) {
    Instruction rrc = {RRC, target, 0, ALWAYS, LO_A, LO_A};
    return rrc;
}

Instruction new_rlc(enum RegisterName target) {
    Instruction rlc = {RLC, target, 0, ALWAYS, LO_A, LO_A};
    return rlc;
}

Instruction new_sra(enum RegisterName target) {
    Instruction sra = {SRA, target, 0, ALWAYS, LO_A, LO_A};
    return sra;
}

Instruction new_sla(enum RegisterName target) {
    Instruction sla = {SLA, target, 0, ALWAYS, LO_A, LO_A};
    return sla;
}

Instruction new_swap(enum RegisterName target) {
    Instruction swap = {SWAP, target, 0, ALWAYS, LO_A, LO_A};
    return swap;
}

Instruction new_jp(enum JumpCondition jump_cond) {
    Instruction jump = {JP, A, 0, jump_cond, LO_A, LO_A};
    return jump;
}

Instruction new_jphl(void) {
    Instruction jumphl = {JPHL, A, 0, ALWAYS, LO_A, LO_A};
    return jumphl;
}

Instruction new_ld(enum LoadOperand ld_target, enum LoadOperand ld_source) {  // NOLINT
    enum InstructionKind load_kind;

    if (ld_target == LO_HL_IND && ld_source == LO_D8) {
        load_kind = LD_D8_IND;
    } else if (ld_source == LO_D8) {
        load_kind = LD_D8;
    } else if (ld_source == LO_D16) {
        load_kind = LD_D16;
    } else if (ld_target == LO_A16_IND || ld_source == LO_A16_IND) {
        load_kind = LD_ADDR;
    } else if ((LO_BC_IND <= ld_target && ld_target <= LO_HL_IND) ||
               (LO_BC_IND <= ld_source && ld_source <= LO_HL_IND)) {
        load_kind = LD_IND;
    } else if (ld_target == LO_HL_INC_IND || ld_source == LO_HL_INC_IND) {
        load_kind = LD_INC;
    } else if (ld_target == LO_HL_DEC_IND || ld_source == LO_HL_DEC_IND) {
        load_kind = LD_DEC;
    } else {
        load_kind = LD_REG;
    }

    Instruction load = {load_kind, A, 0, ALWAYS, ld_target, ld_source};
    return load;
}

Instruction new_ldh(enum LoadOperand ld_target, enum LoadOperand ld_source) {  // NOLINT
    enum InstructionKind loadh_kind;

    if (ld_target == LO_C_IND || ld_source == LO_C_IND) {
        loadh_kind = LDH_IND;
    } else {
        loadh_kind = LDH_ADDR;
    }

    Instruction loadh = {loadh_kind, A, 0, ALWAYS, ld_target, ld_source};
    return loadh;
}
