#include <assert.h>

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

    Instruction Iset = new_set(3, HL);
    execute(&cpu, &Iset);
    assert(get_hl(&cpu.registers) == BIN(0b0000000000001000));

    Instruction Iaddhl = new_addhl(HL);
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

// TODO: test cases for jump instructions, load instructions, and call instructions.

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
}
