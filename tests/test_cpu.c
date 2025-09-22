#include <assert.h>
#include <stdint.h>

#include "../include/cpu.h"

#define BIN(binary) (__extension__ binary)

void test_add(void) {
    CPU cpu = new_cpu();

    Instruction Iset = new_set(0, B);
    execute(&cpu, &Iset);
    assert(cpu.registers.b == BIN(0b00000001));

    Instruction Iset2 = new_set(1, B);
    execute(&cpu, &Iset2);
    assert(cpu.registers.b == BIN(0b00000011));

    Instruction Iset3 = new_set(2, B);
    execute(&cpu, &Iset3);
    assert(cpu.registers.b == BIN(0b00000111));

    Instruction Iset4 = new_set(3, B);
    execute(&cpu, &Iset4);
    assert(cpu.registers.b == BIN(0b00001111));

    Instruction Iset5 = new_set(0, A);
    execute(&cpu, &Iset5);
    assert(cpu.registers.a == BIN(0b00000001));

    Instruction Iadd = new_add(B);
    execute(&cpu, &Iadd);
    assert(cpu.registers.a == BIN(0b00010000));
    assert(cpu.registers.f == BIN(0b00100000));
}

void test_addhl(void) {
    CPU cpu = new_cpu();

    // NOTE: set(3, HL) doesn't exist as a real instruction
    Instruction Iset = new_set(3, HL);
    execute(&cpu, &Iset);
    assert(get_hl(&cpu.registers) == BIN(0b0000000000001000));

    Instruction Iaddhl = new_add_hl(HL);
    execute(&cpu, &Iaddhl);
    assert(get_hl(&cpu.registers) == BIN(0b0000000000010000));
}

void test_adc(void) {
    CPU cpu = new_cpu();

    Instruction Iset = new_set(3, B);
    execute(&cpu, &Iset);
    assert(cpu.registers.b == BIN(0b00001000));

    Instruction Iset2 = new_set(4, F);
    execute(&cpu, &Iset2);
    assert(cpu.registers.f == BIN(0b00010000));
    cpu.flag_reg.carry = true;

    Instruction Iadc = new_adc(B);
    execute(&cpu, &Iadc);
    assert(cpu.registers.a == BIN(0b00001001));
    assert(cpu.registers.f == BIN(0b00000000));
}

void test_sub(void) {
    CPU cpu = new_cpu();

    Instruction Iset = new_set(3, B);
    execute(&cpu, &Iset);
    assert(cpu.registers.b == BIN(0b00001000));

    Instruction Iset2 = new_set(3, A);
    execute(&cpu, &Iset2);
    assert(cpu.registers.a == BIN(0b00001000));

    Instruction Isub = new_sub(B);
    execute(&cpu, &Isub);
    assert(cpu.registers.a == BIN(0b00000000));
    assert(cpu.registers.f == BIN(0b11000000));
}

void test_sbc(void) {
    CPU cpu = new_cpu();

    Instruction Iset = new_set(3, B);
    execute(&cpu, &Iset);
    assert(cpu.registers.b == BIN(0b00001000));

    Instruction Iset2 = new_set(3, A);
    execute(&cpu, &Iset2);
    assert(cpu.registers.a == BIN(0b00001000));

    Instruction Iset3 = new_set(4, F);
    execute(&cpu, &Iset3);
    assert(cpu.registers.f == BIN(0b00010000));
    cpu.flag_reg.carry = true;

    Instruction Isbc = new_sbc(B);
    execute(&cpu, &Isbc);
    assert(cpu.registers.a == BIN(0b11111111));
    assert(cpu.registers.f == BIN(0b01110000));
}

void test_and(void) {
    CPU cpu = new_cpu();

    Instruction Iset = new_set(3, B);
    execute(&cpu, &Iset);
    assert(cpu.registers.b == BIN(0b00001000));

    Instruction Iset2 = new_set(4, A);
    execute(&cpu, &Iset2);
    assert(cpu.registers.a == BIN(0b00010000));

    Instruction Iand = new_and(B);
    execute(&cpu, &Iand);
    assert(cpu.registers.a == BIN(0b00000001));
    assert(cpu.registers.f == BIN(0b00100000));
}

void test_or(void) {
    CPU cpu = new_cpu();

    Instruction Iset = new_set(3, B);
    execute(&cpu, &Iset);
    assert(cpu.registers.b == BIN(0b00001000));

    Instruction Iset2 = new_set(4, A);
    execute(&cpu, &Iset2);
    assert(cpu.registers.a == BIN(0b00010000));

    Instruction Ior = new_and(B);
    execute(&cpu, &Ior);
    assert(cpu.registers.a == BIN(0b00000001));
    assert(cpu.registers.f == BIN(0b00100000));
}

void test_xor(void) {
    CPU cpu = new_cpu();

    Instruction Iset = new_set(3, B);
    execute(&cpu, &Iset);
    assert(cpu.registers.b == BIN(0b00001000));

    Instruction Iset2 = new_set(4, A);
    execute(&cpu, &Iset2);
    assert(cpu.registers.a == BIN(0b00010000));

    Instruction Ixor = new_xor(B);
    execute(&cpu, &Ixor);
    assert(cpu.registers.a == BIN(0b00011000));
    assert(cpu.registers.f == BIN(0b00100000));
}

void test_cp(void) {
    CPU cpu = new_cpu();

    Instruction Iset = new_set(3, B);
    execute(&cpu, &Iset);
    assert(cpu.registers.b == BIN(0b00001000));

    Instruction Iset2 = new_set(3, A);
    execute(&cpu, &Iset2);
    assert(cpu.registers.a == BIN(0b00001000));

    Instruction Icp = new_cp(B);
    execute(&cpu, &Icp);
    assert(cpu.registers.f == BIN(0b11000000));
}

void test_inc(void) {
    CPU cpu = new_cpu();

    // NOTE: set(3, HL) doesn't exist as a real instruction
    Instruction Iset = new_set(3, HL);
    execute(&cpu, &Iset);
    assert(get_hl(&cpu.registers) == BIN(0b0000000000001000));

    Instruction Iinc = new_inc(HL);
    execute(&cpu, &Iinc);
    assert(get_hl(&cpu.registers) == BIN(0b0000000000001001));
    assert(cpu.registers.f == BIN(0b00000000));

    Instruction Iset2 = new_set(3, B);
    execute(&cpu, &Iset2);
    assert(cpu.registers.b == BIN(0b00001000));

    Instruction Iinc2 = new_inc(B);
    execute(&cpu, &Iinc2);
    assert(cpu.registers.b == BIN(0b00001001));
    assert(cpu.registers.f == BIN(0b00000000));
}

void test_dec(void) {
    CPU cpu = new_cpu();

    // NOTE: set(3, HL) doesn't exist as a real instruction
    Instruction Iset = new_set(3, HL);
    execute(&cpu, &Iset);
    assert(get_hl(&cpu.registers) == BIN(0b0000000000001000));

    Instruction Idec = new_dec(HL);
    execute(&cpu, &Idec);
    assert(get_hl(&cpu.registers) == BIN(0b0000000000000111));
    assert(cpu.registers.f == BIN(0b00000000));

    Instruction Iset2 = new_set(3, B);
    execute(&cpu, &Iset2);
    assert(cpu.registers.b == BIN(0b00001000));

    Instruction Idec2 = new_dec(B);
    execute(&cpu, &Idec2);
    assert(cpu.registers.b == BIN(0b00000111));
    assert(cpu.registers.f == BIN(0b01100000));
}

void test_ccf(void) {
    CPU cpu = new_cpu();

    Instruction Iset = new_set(4, F);
    execute(&cpu, &Iset);
    assert(cpu.registers.f == BIN(0b00010000));
    cpu.flag_reg.carry = true;

    Instruction Iccf = new_ccf();
    execute(&cpu, &Iccf);
    assert(cpu.registers.f == BIN(0b00000000));
}

void test_scf(void) {
    CPU cpu = new_cpu();

    Instruction Iscf = new_scf();
    execute(&cpu, &Iscf);
    assert(cpu.registers.f == BIN(0b00010000));
}

void test_rra(void) {
    CPU cpu = new_cpu();

    Instruction Iset = new_set(0, A);
    execute(&cpu, &Iset);
    assert(cpu.registers.a == BIN(0b00000001));

    Instruction Irra = new_rra();
    execute(&cpu, &Irra);
    assert(cpu.registers.a == BIN(0b00000000));
    assert(cpu.registers.f == BIN(0b10010000));
}

void test_rla(void) {
    CPU cpu = new_cpu();

    Instruction Iset = new_set(0, A);
    execute(&cpu, &Iset);
    assert(cpu.registers.a == BIN(0b00000001));

    Instruction Iset2 = new_set(4, F);
    execute(&cpu, &Iset2);
    assert(cpu.registers.f == BIN(0b00010000));
    cpu.flag_reg.carry = true;

    Instruction Irla = new_rla();
    execute(&cpu, &Irla);
    assert(cpu.registers.a == BIN(0b00000011));
    assert(cpu.registers.f == BIN(0b00000000));
}

void test_rrca(void) {
    CPU cpu = new_cpu();

    Instruction Iset = new_set(0, A);
    execute(&cpu, &Iset);
    assert(cpu.registers.a == BIN(0b00000001));

    Instruction Irrca = new_rrca();
    execute(&cpu, &Irrca);
    assert(cpu.registers.a == BIN(0b10000000));
    assert(cpu.registers.f == BIN(0b00010000));
}

void test_rlca(void) {
    CPU cpu = new_cpu();

    Instruction Iset = new_set(0, A);
    execute(&cpu, &Iset);
    assert(cpu.registers.a == BIN(0b00000001));

    Instruction Iset2 = new_set(4, F);
    execute(&cpu, &Iset2);
    assert(cpu.registers.f == BIN(0b00010000));
    cpu.flag_reg.carry = true;

    Instruction Irlca = new_rlca();
    execute(&cpu, &Irlca);
    assert(cpu.registers.a == BIN(0b00000010));
    assert(cpu.registers.f == BIN(0b00000000));
}

void test_cpl(void) {
    CPU cpu = new_cpu();

    Instruction Iset = new_set(0, A);
    execute(&cpu, &Iset);
    assert(cpu.registers.a == BIN(0b00000001));

    Instruction Icpl = new_cpl();
    execute(&cpu, &Icpl);
    assert(cpu.registers.a == BIN(0b11111110));
    assert(cpu.registers.f == BIN(0b01100000));
}

void test_bit(void) {
    CPU cpu = new_cpu();

    Instruction Iset = new_set(3, A);
    execute(&cpu, &Iset);
    assert(cpu.registers.a == BIN(0b00001000));

    Instruction Ibit = new_bit(3, A);
    execute(&cpu, &Ibit);
    assert(cpu.registers.f == BIN(0b00100000));
}

void test_reset(void) {
    CPU cpu = new_cpu();

    Instruction Iset = new_set(3, A);
    execute(&cpu, &Iset);
    assert(cpu.registers.a == BIN(0b00001000));

    Instruction Ireset = new_reset(3, A);
    execute(&cpu, &Ireset);
    assert(cpu.registers.a == BIN(0b00000000));
    assert(cpu.registers.f == BIN(0b00000000));
}

void test_set(void) {
    CPU cpu = new_cpu();

    Instruction Iset = new_set(3, A);
    execute(&cpu, &Iset);
    assert(cpu.registers.a == BIN(0b00001000));
    assert(cpu.registers.f == BIN(0b00000000));
}

void test_srl(void) {
    CPU cpu = new_cpu();

    Instruction Iset = new_set(0, B);
    execute(&cpu, &Iset);
    assert(cpu.registers.b == BIN(0b00000001));

    Instruction Iset2 = new_set(7, B);  // NOLINT
    execute(&cpu, &Iset2);
    assert(cpu.registers.b == BIN(0b10000001));

    Instruction Isrl = new_srl(B);
    execute(&cpu, &Isrl);
    assert(cpu.registers.b == BIN(0b01000000));
    assert(cpu.registers.f == BIN(0b00010000));
}

void test_rr(void) {
    CPU cpu = new_cpu();

    Instruction Iset = new_set(3, B);
    execute(&cpu, &Iset);
    assert(cpu.registers.b == BIN(0b00001000));

    Instruction Iset2 = new_set(4, F);
    execute(&cpu, &Iset2);
    assert(cpu.registers.f == BIN(0b00010000));
    cpu.flag_reg.carry = true;

    Instruction Irr = new_rr(B);
    execute(&cpu, &Irr);
    assert(cpu.registers.b == BIN(0b10000100));
    assert(cpu.registers.f == BIN(0b00000000));
}

void test_rl(void) {
    CPU cpu = new_cpu();

    Instruction Iset = new_set(3, B);
    execute(&cpu, &Iset);
    assert(cpu.registers.b == BIN(0b00001000));

    Instruction Iset2 = new_set(4, F);
    execute(&cpu, &Iset2);
    assert(cpu.registers.f == BIN(0b00010000));
    cpu.flag_reg.carry = true;

    Instruction Irl = new_rl(B);
    execute(&cpu, &Irl);
    assert(cpu.registers.b == BIN(0b00010001));
    assert(cpu.registers.f == BIN(0b00000000));
}

void test_rrc(void) {
    CPU cpu = new_cpu();

    Instruction Iset = new_set(3, B);
    execute(&cpu, &Iset);
    assert(cpu.registers.b == BIN(0b00001000));

    Instruction Iset2 = new_set(4, F);
    execute(&cpu, &Iset2);
    assert(cpu.registers.f == BIN(0b00010000));
    cpu.flag_reg.carry = true;

    Instruction Irrc = new_rrc(B);
    execute(&cpu, &Irrc);
    assert(cpu.registers.b == BIN(0b00000100));
    assert(cpu.registers.f == BIN(0b00000000));
}

void test_rlc(void) {
    CPU cpu = new_cpu();

    Instruction Iset = new_set(3, B);
    execute(&cpu, &Iset);
    assert(cpu.registers.b == BIN(0b00001000));

    Instruction Iset2 = new_set(4, F);
    execute(&cpu, &Iset2);
    assert(cpu.registers.f == BIN(0b00010000));
    cpu.flag_reg.carry = true;

    Instruction Irlc = new_rlc(B);
    execute(&cpu, &Irlc);
    assert(cpu.registers.b == BIN(0b00010000));
    assert(cpu.registers.f == BIN(0b00000000));
}

void test_sra(void) {
    CPU cpu = new_cpu();

    Instruction Iset = new_set(3, B);
    execute(&cpu, &Iset);
    assert(cpu.registers.b == BIN(0b00001000));

    Instruction Iset2 = new_set(7, B);  // NOLINT
    execute(&cpu, &Iset2);
    assert(cpu.registers.b == BIN(0b10001000));

    Instruction Iset3 = new_set(4, F);
    execute(&cpu, &Iset3);
    assert(cpu.registers.f == BIN(0b00010000));
    cpu.flag_reg.carry = true;

    Instruction Isra = new_sra(B);
    execute(&cpu, &Isra);
    assert(cpu.registers.b == BIN(0b11000100));
    assert(cpu.registers.f == BIN(0b00000000));
}

void test_sla(void) {
    CPU cpu = new_cpu();

    Instruction Iset = new_set(3, B);
    execute(&cpu, &Iset);
    assert(cpu.registers.b == BIN(0b00001000));

    Instruction Iset2 = new_set(7, B);  // NOLINT
    execute(&cpu, &Iset2);
    assert(cpu.registers.b == BIN(0b10001000));

    Instruction Iset3 = new_set(4, F);
    execute(&cpu, &Iset3);
    assert(cpu.registers.f == BIN(0b00010000));
    cpu.flag_reg.carry = true;

    Instruction Isla = new_sla(B);
    execute(&cpu, &Isla);
    assert(cpu.registers.b == BIN(0b00010000));
    assert(cpu.registers.f == BIN(0b00010000));
}

void test_swap(void) {
    CPU cpu = new_cpu();

    Instruction Iset = new_set(3, B);
    execute(&cpu, &Iset);
    assert(cpu.registers.b == BIN(0b00001000));

    Instruction Iset2 = new_set(1, B);
    execute(&cpu, &Iset2);
    assert(cpu.registers.b == BIN(0b00001010));

    Instruction Iswap = new_swap(B);
    execute(&cpu, &Iswap);
    assert(cpu.registers.b == BIN(0b10100000));
}

void test_jp() {
    CPU cpu = new_cpu();

    Instruction Iset = new_set(7, F);  // NOLINT
    execute(&cpu, &Iset);
    assert(cpu.registers.f == BIN(0b10000000));
    cpu.flag_reg.zero = true;

    Instruction Ijp = new_jp(ZERO);
    cpu.memory[cpu.prog_count + 1] = 0x10;  // LSB NOLINT
    cpu.memory[cpu.prog_count + 2] = 0xC0;  // MSB NOLINT
    uint16_t new_pc = execute(&cpu, &Ijp);
    assert(new_pc == 0xC010);
}

void test_jphl() {
    CPU cpu = new_cpu();

    // NOTE: set(2, HL) doesn't exist as a real instruction
    Instruction Iset = new_set(2, HL);  // NOLINT
    execute(&cpu, &Iset);
    assert(get_reg(&cpu, HL) == BIN(0b0000000000000100));

    Instruction Ijphl = new_jphl();
    uint16_t new_pc = execute(&cpu, &Ijphl);
    assert(new_pc == BIN(0b0000000000000100));
}

void test_jr() {
    CPU cpu = new_cpu();

    Instruction Iset = new_set(7, F);  // NOLINT
    execute(&cpu, &Iset);
    assert(cpu.registers.f == BIN(0b10000000));
    cpu.flag_reg.zero = true;

    cpu.prog_count = 0x0012;  // NOLINT

    Instruction Ijr = new_jr(ZERO);
    cpu.memory[cpu.prog_count + 1] = 0xFE;  // signed offset NOLINT
    uint16_t new_pc = execute(&cpu, &Ijr);
    assert(new_pc == 0x0010);
}

void test_ld_reg() {
    CPU cpu = new_cpu();

    Instruction Iset = new_set(5, B);  // NOLINT
    execute(&cpu, &Iset);
    assert(cpu.registers.b == BIN(0b00100000));

    Instruction Iset2 = new_set(3, C);  // NOLINT
    execute(&cpu, &Iset2);
    assert(cpu.registers.c == BIN(0b00001000));

    Instruction Ild = new_ld(LO_B, LO_C);
    execute(&cpu, &Ild);
    assert(cpu.registers.b == BIN(0b00001000));
}

void test_ld_d8() {
    CPU cpu = new_cpu();

    cpu.memory[cpu.prog_count + 1] = 0xFF;  // NOLINT

    Instruction Ild = new_ld(LO_C, LO_D8);
    execute(&cpu, &Ild);
    assert(cpu.registers.c == BIN(0b11111111));
}

void test_ld_d16() {
    CPU cpu = new_cpu();

    cpu.memory[cpu.prog_count + 1] = 0xCD;  // NOLINT
    cpu.memory[cpu.prog_count + 2] = 0xAB;  // NOLINT

    Instruction Ild = new_ld(LO_DE, LO_D16);
    execute(&cpu, &Ild);
    assert(get_de(&cpu.registers) == 0xABCD);
}

void test_ld_d8_ind() {
    CPU cpu = new_cpu();

    // NOTE: set(2, HL) doesn't exist as a real instruction
    Instruction Iset = new_set(2, HL);  // NOLINT
    execute(&cpu, &Iset);
    assert(get_reg(&cpu, HL) == BIN(0b0000000000000100));

    cpu.memory[cpu.prog_count + 1] = 0xEF;  // NOLINT

    Instruction Ild = new_ld(LO_HL_IND, LO_D8);
    execute(&cpu, &Ild);
    assert(cpu.memory[4] == 0xEF);
}

void test_ld_ind() {
    CPU cpu = new_cpu();

    // NOTE: set(2, BC) doesn't exist as a real instruction
    Instruction Iset = new_set(2, BC);  // NOLINT
    execute(&cpu, &Iset);
    assert(get_reg(&cpu, BC) == BIN(0b0000000000000100));

    cpu.memory[4] = 0xAB;  // NOLINT

    Instruction Ild = new_ld(LO_D, LO_BC_IND);
    execute(&cpu, &Ild);
    assert(cpu.registers.d == 0xAB);

    Instruction Iset2 = new_set(1, A);
    execute(&cpu, &Iset2);
    assert(cpu.registers.a == BIN(0b00000010));

    Instruction Ild2 = new_ld(LO_BC_IND, LO_A);
    execute(&cpu, &Ild2);
    assert(cpu.memory[4] == 0x02);
}

void test_ld_addr() {
    CPU cpu = new_cpu();

    cpu.memory[5] = 0x11;                   // NOLINT
    cpu.memory[cpu.prog_count + 1] = 0x05;  // addr LSB NOLINT
    cpu.memory[cpu.prog_count + 2] = 0x00;  // addr MSB NOLINT

    Instruction Ild = new_ld(LO_D, LO_A16_IND);
    execute(&cpu, &Ild);
    assert(cpu.registers.d == 0x11);

    Instruction Iset2 = new_set(1, A);
    execute(&cpu, &Iset2);
    assert(cpu.registers.a == BIN(0b00000010));

    Instruction Ild2 = new_ld(LO_A16_IND, LO_A);
    execute(&cpu, &Ild2);
    assert(cpu.memory[5] == 0x02);
}

void test_ld_inc() {
    CPU cpu = new_cpu();

    // NOTE: set(2, HL) doesn't exist as a real instruction
    Instruction Iset = new_set(2, HL);  // NOLINT
    execute(&cpu, &Iset);
    assert(get_reg(&cpu, HL) == BIN(0b0000000000000100));

    cpu.memory[4] = 0xAB;  // NOLINT

    Instruction Ild = new_ld(LO_B, LO_HL_INC_IND);
    execute(&cpu, &Ild);
    assert(cpu.registers.b == 0xAB);
    assert(get_reg(&cpu, HL) == BIN(0b0000000000000101));

    Instruction Iset2 = new_set(1, A);
    execute(&cpu, &Iset2);
    assert(cpu.registers.a == BIN(0b00000010));

    Instruction Ild2 = new_ld(LO_HL_INC_IND, LO_A);
    execute(&cpu, &Ild2);
    assert(cpu.memory[5] == 0x02);
    assert(get_reg(&cpu, HL) == BIN(0b0000000000000110));
}

void test_ld_dec() {
    CPU cpu = new_cpu();

    // NOTE: set(2, HL) doesn't exist as a real instruction
    Instruction Iset = new_set(2, HL);  // NOLINT
    execute(&cpu, &Iset);
    assert(get_reg(&cpu, HL) == BIN(0b0000000000000100));

    cpu.memory[4] = 0xAB;  // NOLINT

    Instruction Ild = new_ld(LO_B, LO_HL_DEC_IND);
    execute(&cpu, &Ild);
    assert(cpu.registers.b == 0xAB);
    assert(get_reg(&cpu, HL) == BIN(0b0000000000000011));

    Instruction Iset2 = new_set(1, A);
    execute(&cpu, &Iset2);
    assert(cpu.registers.a == BIN(0b00000010));

    Instruction Ild2 = new_ld(LO_HL_DEC_IND, LO_A);
    execute(&cpu, &Ild2);
    assert(cpu.memory[3] == 0x02);
    assert(get_reg(&cpu, HL) == BIN(0b0000000000000010));
}

void test_ldh_ind() {
    CPU cpu = new_cpu();

    Instruction Iset = new_set(2, C);  // NOLINT
    execute(&cpu, &Iset);
    assert(get_reg(&cpu, C) == BIN(0b00000100));

    cpu.memory[0xFF04] = 0xAB;  // NOLINT

    Instruction Ildh = new_ldh(LO_B, LO_C_IND);
    execute(&cpu, &Ildh);
    assert(cpu.registers.b == 0xAB);

    Instruction Iset2 = new_set(1, A);
    execute(&cpu, &Iset2);
    assert(cpu.registers.a == BIN(0b00000010));

    Instruction Ildh2 = new_ldh(LO_C_IND, LO_A);
    execute(&cpu, &Ildh2);
    assert(cpu.memory[0xFF04] == 0x02);
}

void test_ldh_addr() {
    CPU cpu = new_cpu();

    cpu.memory[0xFF04] = 0xAB;              // NOLINT
    cpu.memory[cpu.prog_count + 1] = 0x04;  // half addr

    Instruction Ildh = new_ldh(LO_B, LO_A8_IND);
    execute(&cpu, &Ildh);
    assert(cpu.registers.b == 0xAB);

    Instruction Iset2 = new_set(1, A);
    execute(&cpu, &Iset2);
    assert(cpu.registers.a == BIN(0b00000010));

    Instruction Ildh2 = new_ldh(LO_A8_IND, LO_A);
    execute(&cpu, &Ildh2);
    assert(cpu.memory[0xFF04] == 0x02);
}

void test_push() {
    CPU cpu = new_cpu();
    // NOTE: we will assume that the stack begins at the end of memory (growing downwards)
    cpu.stack_pointer = 0xFFFE;  // NOLINT

    cpu.registers.a = 0xF0;  // NOLINT
    cpu.registers.f = 0x01;

    Instruction Ipush = new_push(AF);
    execute(&cpu, &Ipush);
    assert(cpu.memory[0xFFFD] == 0xF0);
    assert(cpu.memory[0xFFFC] == 0x01);
}

void test_pop() {
    CPU cpu = new_cpu();
    // NOTE: we will assume that the stack begins at the end of memory (growing downwards)
    cpu.stack_pointer = 0xFFFE;  // NOLINT

    cpu.registers.a = 0xF0;  // NOLINT
    cpu.registers.f = 0x10;  // NOLINT

    Instruction Ipush = new_push(AF);
    execute(&cpu, &Ipush);
    assert(cpu.memory[0xFFFD] == 0xF0);
    assert(cpu.memory[0xFFFC] == 0x10);

    cpu.registers.f = 0xFF;  // NOLINT

    Instruction Ipop = new_pop(AF);
    execute(&cpu, &Ipop);
    assert(get_reg(&cpu, AF) == 0xF010);
    assert(!cpu.flag_reg.zero);
    assert(!cpu.flag_reg.subtract);
    assert(!cpu.flag_reg.half_carry);
    assert(cpu.flag_reg.carry);
}

void test_call() {
    CPU cpu = new_cpu();
    // NOTE: we will assume that the stack begins at the end of memory (growing downwards)
    cpu.stack_pointer = 0xFFFE;  // NOLINT

    cpu.prog_count = 0xFF00;                // NOLINT
    cpu.memory[cpu.prog_count + 1] = 0xCD;  // NOLINT
    cpu.memory[cpu.prog_count + 2] = 0xAB;  // NOLINT

    Instruction Icall = new_call(NOT_ZERO);
    uint16_t next_pc = execute(&cpu, &Icall);

    assert(next_pc == 0xABCD);
    assert(cpu.memory[0xFFFD] == 0xFF);
    assert(cpu.memory[0xFFFC] == 0x03);
}

void test_ret() {
    CPU cpu = new_cpu();
    // NOTE: we will assume that the stack begins at the end of memory (growing downwards)
    cpu.stack_pointer = 0xFFFE;  // NOLINT

    cpu.prog_count = 0xFF00;                // NOLINT
    cpu.memory[cpu.prog_count + 1] = 0xCD;  // NOLINT
    cpu.memory[cpu.prog_count + 2] = 0xAB;  // NOLINT

    Instruction Icall = new_call(NOT_ZERO);
    uint16_t next_pc = execute(&cpu, &Icall);

    assert(next_pc == 0xABCD);
    assert(cpu.memory[0xFFFD] == 0xFF);
    assert(cpu.memory[0xFFFC] == 0x03);

    Instruction Iret = new_ret(NOT_CARRY);
    next_pc = execute(&cpu, &Iret);

    assert(next_pc == 0xFF03);
}

void test_nop() {
    CPU cpu = new_cpu();

    Instruction Inop = new_nop();
    uint16_t new_pc = execute(&cpu, &Inop);
    assert(new_pc == 1);
}

int main() {
    test_add();
    test_addhl();
    test_adc();
    test_sub();
    test_sbc();
    test_and();
    test_or();
    test_xor();
    test_cp();
    test_inc();
    test_dec();
    test_ccf();
    test_scf();
    test_rra();
    test_rla();
    test_rrca();
    test_rlca();
    test_cpl();

    test_bit();
    test_reset();
    test_set();
    test_srl();
    test_rr();
    test_rl();
    test_rrc();
    test_rlc();
    test_sra();
    test_sla();
    test_swap();

    test_jp();
    test_jphl();
    test_jr();

    test_ld_reg();
    test_ld_d8();
    test_ld_d16();
    test_ld_d8_ind();
    test_ld_ind();
    test_ld_addr();
    test_ld_inc();
    test_ld_dec();
    test_ldh_ind();
    test_ldh_addr();

    test_push();
    test_pop();

    test_call();
    test_ret();
    test_nop();
}
