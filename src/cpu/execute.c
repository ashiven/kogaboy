#include <stdint.h>

#include "../../include/cpu.h"

// TODO: decrease code repetition in arithmetic ops via indirection of code coming after res = ...

void add(CPU *cpu, enum Operand source) {
    uint8_t acc = get_reg(cpu, A);
    uint8_t val = get_reg(cpu, (enum RegisterName)source);
    // This will wrap around i.e.
    // acc = 1111_1111 and val = 0000_0010
    // --> res = 0000_0001
    uint8_t res = acc + val;

    bool zero = res == 0;
    bool subtract = false;
    bool half_carry = (acc & HBYTE_M) + (val & HBYTE_M) > HBYTE_M;
    bool carry = acc + val > BYTE_M;
    update_flags(cpu, zero, subtract, half_carry, carry);

    set_reg(cpu, A, res);
}

void add_hl(CPU *cpu, enum Operand source) {
    uint16_t acc = get_reg(cpu, HL);
    // val is one of the 16 bit regs: BC, DE, HL, SP
    uint16_t val = get_reg(cpu, (enum RegisterName)source);
    uint16_t res = acc + val;

    bool zero = res == 0;
    bool subtract = false;
    bool half_carry = (acc & BYTE_M) + (val & BYTE_M) > BYTE_M;
    bool carry = acc + val > BBYTE_M;
    update_flags(cpu, zero, subtract, half_carry, carry);

    set_reg(cpu, HL, res);
}

void add_ind(CPU *cpu) {
    uint8_t acc = get_reg(cpu, A);
    uint16_t addr = get_reg(cpu, HL);
    uint8_t val = cpu->memory[addr];
    uint8_t res = acc + val;

    bool zero = res == 0;
    bool subtract = false;
    bool half_carry = (acc & HBYTE_M) + (val & HBYTE_M) > HBYTE_M;
    bool carry = acc + val > BYTE_M;
    update_flags(cpu, zero, subtract, half_carry, carry);

    set_reg(cpu, A, res);
}

void add_d8(CPU *cpu) {
    uint8_t acc = get_reg(cpu, A);
    uint8_t val = read_byte(cpu);
    uint8_t res = acc + val;

    bool zero = res == 0;
    bool subtract = false;
    bool half_carry = (acc & HBYTE_M) + (val & HBYTE_M) > HBYTE_M;
    bool carry = acc + val > BYTE_M;
    update_flags(cpu, zero, subtract, half_carry, carry);

    set_reg(cpu, A, res);
}

void adc(CPU *cpu, enum Operand source) {
    uint8_t acc = get_reg(cpu, A);
    uint8_t val = get_reg(cpu, (enum RegisterName)source);
    uint8_t car = get_carry(&cpu->flag_reg);
    uint8_t res = acc + val + car;

    bool zero = res == 0;
    bool subtract = false;
    bool half_carry = (acc & HBYTE_M) + (val & HBYTE_M) + (car & HBYTE_M) > HBYTE_M;
    bool carry = acc + val + car > BYTE_M;
    update_flags(cpu, zero, subtract, half_carry, carry);

    set_reg(cpu, A, res);
}

void adc_ind(CPU *cpu) {
    uint8_t acc = get_reg(cpu, A);
    uint16_t addr = get_reg(cpu, HL);
    uint8_t val = cpu->memory[addr];
    uint8_t car = get_carry(&cpu->flag_reg);
    uint8_t res = acc + val + car;

    bool zero = res == 0;
    bool subtract = false;
    bool half_carry = (acc & HBYTE_M) + (val & HBYTE_M) + (car & HBYTE_M) > HBYTE_M;
    bool carry = acc + val + car > BYTE_M;
    update_flags(cpu, zero, subtract, half_carry, carry);

    set_reg(cpu, A, res);
}

void adc_d8(CPU *cpu) {
    uint8_t acc = get_reg(cpu, A);
    uint8_t val = read_byte(cpu);
    uint8_t car = get_carry(&cpu->flag_reg);
    uint8_t res = acc + val + car;

    bool zero = res == 0;
    bool subtract = false;
    bool half_carry = (acc & HBYTE_M) + (val & HBYTE_M) + (car & HBYTE_M) > HBYTE_M;
    bool carry = acc + val + car > BYTE_M;
    update_flags(cpu, zero, subtract, half_carry, carry);

    set_reg(cpu, A, res);
}

void sub(CPU *cpu, enum Operand source) {
    uint8_t acc = get_reg(cpu, A);
    uint8_t val = get_reg(cpu, (enum RegisterName)source);
    uint8_t res = acc - val;

    bool zero = res == 0;
    bool subtract = true;
    bool half_carry = (acc & HBYTE_M) < (val & HBYTE_M);
    bool carry = acc < val;
    update_flags(cpu, zero, subtract, half_carry, carry);

    set_reg(cpu, A, res);
}

void sub_ind(CPU *cpu) {
    uint8_t acc = get_reg(cpu, A);
    uint16_t addr = get_reg(cpu, HL);
    uint8_t val = cpu->memory[addr];
    uint8_t res = acc - val;

    bool zero = res == 0;
    bool subtract = true;
    bool half_carry = (acc & HBYTE_M) < (val & HBYTE_M);
    bool carry = acc < val;
    update_flags(cpu, zero, subtract, half_carry, carry);

    set_reg(cpu, A, res);
}

void sub_d8(CPU *cpu) {
    uint8_t acc = get_reg(cpu, A);
    uint8_t val = read_byte(cpu);
    uint8_t res = acc - val;

    bool zero = res == 0;
    bool subtract = true;
    bool half_carry = (acc & HBYTE_M) < (val & HBYTE_M);
    bool carry = acc < val;
    update_flags(cpu, zero, subtract, half_carry, carry);

    set_reg(cpu, A, res);
}

void sbc(CPU *cpu, enum Operand source) {
    uint8_t acc = get_reg(cpu, A);
    uint8_t val = get_reg(cpu, (enum RegisterName)source);
    uint8_t car = get_carry(&cpu->flag_reg);
    uint8_t res = acc - val - car;

    bool zero = res == 0;
    bool subtract = true;
    bool half_carry = (acc & HBYTE_M) < (val & HBYTE_M) + (car & HBYTE_M);
    bool carry = acc < (val + car);
    update_flags(cpu, zero, subtract, half_carry, carry);

    set_reg(cpu, A, res);
}

void sbc_ind(CPU *cpu) {
    uint8_t acc = get_reg(cpu, A);
    uint16_t addr = get_reg(cpu, HL);
    uint8_t val = cpu->memory[addr];
    uint8_t car = get_carry(&cpu->flag_reg);
    uint8_t res = acc - val - car;

    bool zero = res == 0;
    bool subtract = true;
    bool half_carry = (acc & HBYTE_M) < (val & HBYTE_M) + (car & HBYTE_M);
    bool carry = acc < (val + car);
    update_flags(cpu, zero, subtract, half_carry, carry);

    set_reg(cpu, A, res);
}

void sbc_d8(CPU *cpu) {
    uint8_t acc = get_reg(cpu, A);
    uint8_t val = read_byte(cpu);
    uint8_t car = get_carry(&cpu->flag_reg);
    uint8_t res = acc - val - car;

    bool zero = res == 0;
    bool subtract = true;
    bool half_carry = (acc & HBYTE_M) < (val & HBYTE_M) + (car & HBYTE_M);
    bool carry = acc < (val + car);
    update_flags(cpu, zero, subtract, half_carry, carry);

    set_reg(cpu, A, res);
}

void and_(CPU *cpu, enum Operand source) {
    uint8_t acc = get_reg(cpu, A);
    uint8_t val = get_reg(cpu, (enum RegisterName)source);
    uint8_t res = acc && val;

    bool zero = res == 0;
    bool subtract = false;
    bool half_carry = true;
    bool carry = false;
    update_flags(cpu, zero, subtract, half_carry, carry);

    set_reg(cpu, A, res);
}

void and_ind(CPU *cpu) {
    uint8_t acc = get_reg(cpu, A);
    uint16_t addr = get_reg(cpu, HL);
    uint8_t val = cpu->memory[addr];
    uint8_t res = acc && val;

    bool zero = res == 0;
    bool subtract = false;
    bool half_carry = true;
    bool carry = false;
    update_flags(cpu, zero, subtract, half_carry, carry);

    set_reg(cpu, A, res);
}

void and_d8(CPU *cpu) {
    uint8_t acc = get_reg(cpu, A);
    uint8_t val = read_byte(cpu);
    uint8_t res = acc && val;

    bool zero = res == 0;
    bool subtract = false;
    bool half_carry = true;
    bool carry = false;
    update_flags(cpu, zero, subtract, half_carry, carry);

    set_reg(cpu, A, res);
}

void or_(CPU *cpu, enum Operand source) {
    uint8_t acc = get_reg(cpu, A);
    uint8_t val = get_reg(cpu, (enum RegisterName)source);
    uint8_t res = acc || val;

    bool zero = res == 0;
    bool subtract = false;
    bool half_carry = true;
    bool carry = false;
    update_flags(cpu, zero, subtract, half_carry, carry);

    set_reg(cpu, A, res);
}

void or_ind(CPU *cpu) {
    uint8_t acc = get_reg(cpu, A);
    uint16_t addr = get_reg(cpu, HL);
    uint8_t val = cpu->memory[addr];
    uint8_t res = acc || val;

    bool zero = res == 0;
    bool subtract = false;
    bool half_carry = true;
    bool carry = false;
    update_flags(cpu, zero, subtract, half_carry, carry);

    set_reg(cpu, A, res);
}

void or_d8(CPU *cpu) {
    uint8_t acc = get_reg(cpu, A);
    uint8_t val = read_byte(cpu);
    uint8_t res = acc || val;

    bool zero = res == 0;
    bool subtract = false;
    bool half_carry = true;
    bool carry = false;
    update_flags(cpu, zero, subtract, half_carry, carry);

    set_reg(cpu, A, res);
}

void xor_(CPU *cpu, enum Operand source) {
    uint8_t acc = get_reg(cpu, A);
    uint8_t val = get_reg(cpu, (enum RegisterName)source);
    uint8_t res = acc ^ val;

    bool zero = res == 0;
    bool subtract = false;
    bool half_carry = true;
    bool carry = false;
    update_flags(cpu, zero, subtract, half_carry, carry);

    set_reg(cpu, A, res);
}

void xor_ind(CPU *cpu) {
    uint8_t acc = get_reg(cpu, A);
    uint16_t addr = get_reg(cpu, HL);
    uint8_t val = cpu->memory[addr];
    uint8_t res = acc ^ val;

    bool zero = res == 0;
    bool subtract = false;
    bool half_carry = true;
    bool carry = false;
    update_flags(cpu, zero, subtract, half_carry, carry);

    set_reg(cpu, A, res);
}

void xor_d8(CPU *cpu) {
    uint8_t acc = get_reg(cpu, A);
    uint8_t val = read_byte(cpu);
    uint8_t res = acc ^ val;

    bool zero = res == 0;
    bool subtract = false;
    bool half_carry = true;
    bool carry = false;
    update_flags(cpu, zero, subtract, half_carry, carry);

    set_reg(cpu, A, res);
}

void cp(CPU *cpu, enum Operand source) {
    uint8_t acc = get_reg(cpu, A);
    uint8_t val = get_reg(cpu, (enum RegisterName)source);
    uint8_t res = acc - val;

    bool zero = res == 0;
    bool subtract = true;
    bool half_carry = (acc & HBYTE_M) < (val & HBYTE_M);
    bool carry = acc < val;
    update_flags(cpu, zero, subtract, half_carry, carry);
}

void cp_ind(CPU *cpu) {
    uint8_t acc = get_reg(cpu, A);
    uint16_t addr = get_reg(cpu, HL);
    uint8_t val = cpu->memory[addr];
    uint8_t res = acc - val;

    bool zero = res == 0;
    bool subtract = true;
    bool half_carry = (acc & HBYTE_M) < (val & HBYTE_M);
    bool carry = acc < val;
    update_flags(cpu, zero, subtract, half_carry, carry);
}

void cp_d8(CPU *cpu) {
    uint8_t acc = get_reg(cpu, A);
    uint8_t val = read_byte(cpu);
    uint8_t res = acc - val;

    bool zero = res == 0;
    bool subtract = true;
    bool half_carry = (acc & HBYTE_M) < (val & HBYTE_M);
    bool carry = acc < val;
    update_flags(cpu, zero, subtract, half_carry, carry);
}

void inc(CPU *cpu, enum Operand target) {
    uint16_t val = get_reg(cpu, (enum RegisterName)target);
    uint16_t res = val + 1;

    // Flags are only affected when incrementing
    // a byte register as opposed to a 2-byte register.
    // TODO: Look into zero if the values inside of the
    // registers are actually representations of signed integers
    if (target < O_AF) {
        bool zero = false;
        bool subtract = false;
        bool half_carry = (val & HBYTE_M) + 1 > HBYTE_M;
        bool carry = cpu->flag_reg.carry;
        update_flags(cpu, zero, subtract, half_carry, carry);
    }

    set_reg(cpu, (enum RegisterName)target, res);  // NOLINT
}

void inc_ind(CPU *cpu) {
    uint16_t addr = get_reg(cpu, HL);
    uint8_t val = cpu->memory[addr];
    uint16_t res = val + 1;

    bool zero = false;
    bool subtract = false;
    bool half_carry = (val & HBYTE_M) + 1 > HBYTE_M;
    bool carry = cpu->flag_reg.carry;
    update_flags(cpu, zero, subtract, half_carry, carry);

    cpu->memory[addr] = res;
}

void dec(CPU *cpu, enum Operand target) {
    uint16_t val = get_reg(cpu, (enum RegisterName)target);
    uint16_t res = val - 1;

    // TODO: same as above
    if (target < O_AF) {
        bool zero = res == 0;
        bool subtract = true;
        bool half_carry = (val & HBYTE_M) >= 1;
        bool carry = cpu->flag_reg.carry;
        update_flags(cpu, zero, subtract, half_carry, carry);
    }

    set_reg(cpu, (enum RegisterName)target, res);  // NOLINT
}

void dec_ind(CPU *cpu) {
    uint16_t addr = get_reg(cpu, HL);
    uint8_t val = cpu->memory[addr];
    uint16_t res = val - 1;

    bool zero = res == 0;
    bool subtract = true;
    bool half_carry = (val & HBYTE_M) >= 1;
    bool carry = cpu->flag_reg.carry;
    update_flags(cpu, zero, subtract, half_carry, carry);

    cpu->memory[addr] = res;
}

void ccf(CPU *cpu) {
    bool zero = cpu->flag_reg.zero;
    bool subtract = false;
    bool half_carry = false;
    bool carry = !cpu->flag_reg.carry;
    update_flags(cpu, zero, subtract, half_carry, carry);
}

void scf(CPU *cpu) {
    bool zero = cpu->flag_reg.zero;
    bool subtract = false;
    bool half_carry = false;
    bool carry = true;
    update_flags(cpu, zero, subtract, half_carry, carry);
}

/* Rotate A right through carry
 * - lsb becomes new carry
 * - carry becomes new msb
 * - the rest of the bits are right shifted
 *
 * c   b7 b6 b5 b4 b3 b2 b1 b0
 *
 * b0  c b7 b6 b5 b4 b3 b2 b1
 */
void rra(CPU *cpu) {
    uint8_t acc = get_reg(cpu, A);
    uint8_t lsb = acc & 1;
    uint8_t car = get_carry(&cpu->flag_reg);
    uint8_t res = car << MSB_IDX | acc >> 1;

    bool zero = res == 0;
    bool subtract = false;
    bool half_carry = false;
    bool carry = lsb == 1;
    update_flags(cpu, zero, subtract, half_carry, carry);

    set_reg(cpu, A, res);
}

/* Rotate A left through carry
 * - msb becomes new carry
 * - carry becomes new lsb
 * - the rest of the bits are left shifted
 *
 * c   b7 b6 b5 b4 b3 b2 b1 b0
 *
 * b7  b6 b5 b4 b3 b2 b1 b0 c
 */
void rla(CPU *cpu) {
    uint8_t acc = get_reg(cpu, A);
    uint8_t msb = (acc >> MSB_IDX) & 1;
    uint8_t car = get_carry(&cpu->flag_reg);
    uint8_t res = acc << 1 | car;

    bool zero = res == 0;
    bool subtract = false;
    bool half_carry = false;
    bool carry = msb == 1;
    update_flags(cpu, zero, subtract, half_carry, carry);

    set_reg(cpu, A, res);
}

/* Rotate A right and set carry to lsb
 * - lsb becomes new carry
 * - the rest of the bits are right shifted
 *
 * c   b7 b6 b5 b4 b3 b2 b1 b0
 *
 * b0  b0 b7 b6 b5 b4 b3 b2 b1
 */
void rrca(CPU *cpu) {
    uint8_t acc = get_reg(cpu, A);
    uint8_t lsb = acc & 1;
    uint8_t res = lsb << MSB_IDX | acc >> 1;

    bool zero = res == 0;
    bool subtract = false;
    bool half_carry = false;
    bool carry = lsb == 1;
    update_flags(cpu, zero, subtract, half_carry, carry);

    set_reg(cpu, A, res);
}

/* Rotate A left and set carry to msb
 * - msb becomes new carry
 * - the rest of the bits are left shifted
 *
 * c   b7 b6 b5 b4 b3 b2 b1 b0
 *
 * b7  b6 b5 b4 b3 b2 b1 b0 b7
 */
void rlca(CPU *cpu) {
    uint8_t acc = get_reg(cpu, A);
    uint8_t msb = (acc >> MSB_IDX) & 1;
    uint8_t res = acc << 1 | msb;

    bool zero = res == 0;
    bool subtract = false;
    bool half_carry = false;
    bool carry = msb == 1;
    update_flags(cpu, zero, subtract, half_carry, carry);

    set_reg(cpu, A, res);
}

void cpl(CPU *cpu) {
    uint8_t acc = get_reg(cpu, A);
    uint8_t res = ~acc;

    bool zero = cpu->flag_reg.zero;
    bool subtract = true;
    bool half_carry = true;
    bool carry = cpu->flag_reg.carry;
    update_flags(cpu, zero, subtract, half_carry, carry);

    set_reg(cpu, A, res);
}

void bit(CPU *cpu, uint8_t bit_index, enum Operand target) {  // NOLINT
    uint8_t val = get_reg(cpu, (enum RegisterName)target);
    uint8_t bit = (val >> bit_index) & 1;

    bool zero = bit == 0;
    bool subtract = false;
    bool half_carry = true;
    bool carry = cpu->flag_reg.carry;
    update_flags(cpu, zero, subtract, half_carry, carry);
}

/* Reset bit at bit_index to 0
 * For example, to reset b6:
 *
 * b7 b6 b5 b4 b3 b2 b1 b0
 *
 * &
 *
 * 1  0  1  1  1  1  1  1
 * */
void reset(CPU *cpu, uint8_t bit_index, enum Operand target) {  // NOLINT
    uint8_t val = get_reg(cpu, (enum RegisterName)target);
    uint8_t res = val & ~(1 << bit_index);

    set_reg(cpu, (enum RegisterName)target, res);  // NOLINT
}

/* Set bit at bit_index to 1
 * For example, to set b6:
 *
 * b7 b6 b5 b4 b3 b2 b1 b0
 *
 * |
 *
 * 0  1  0  0  0  0  0  0
 * */
void set(CPU *cpu, uint8_t bit_index, enum Operand target) {  // NOLINT
    uint8_t val = get_reg(cpu, (enum RegisterName)target);
    uint8_t res = val | (1 << bit_index);

    set_reg(cpu, (enum RegisterName)target, res);  // NOLINT
}

/* Shift target right into carry
 * - lsb becomes new carry
 * - msb becomes 0
 * - the rest of the bits are right shifted
 *
 * c   b7 b6 b5 b4 b3 b2 b1 b0
 *
 * b0  0 b7 b6 b5 b4 b3 b2 b1
 */
void srl(CPU *cpu, enum Operand target) {
    uint8_t val = get_reg(cpu, (enum RegisterName)target);
    uint8_t lsb = val & 1;
    uint8_t res = val >> 1;

    bool zero = res == 0;
    bool subtract = false;
    bool half_carry = false;
    bool carry = lsb == 1;
    update_flags(cpu, zero, subtract, half_carry, carry);

    set_reg(cpu, (enum RegisterName)target, res);  // NOLINT
}

/* Rotate target right through carry
 * - lsb becomes new carry
 * - carry becomes new msb
 * - the rest of the bits are right shifted
 *
 * c   b7 b6 b5 b4 b3 b2 b1 b0
 *
 * b0  c b7 b6 b5 b4 b3 b2 b1
 */
void rr(CPU *cpu, enum Operand target) {
    uint8_t val = get_reg(cpu, (enum RegisterName)target);
    uint8_t lsb = val & 1;
    uint8_t car = get_carry(&cpu->flag_reg);
    uint8_t res = car << MSB_IDX | val >> 1;

    bool zero = res == 0;
    bool subtract = false;
    bool half_carry = false;
    bool carry = lsb == 1;
    update_flags(cpu, zero, subtract, half_carry, carry);

    set_reg(cpu, (enum RegisterName)target, res);  // NOLINT
}

/* Rotate target left through carry
 * - msb becomes new carry
 * - carry becomes new lsb
 * - the rest of the bits are left shifted
 *
 * c   b7 b6 b5 b4 b3 b2 b1 b0
 *
 * b7  b6 b5 b4 b3 b2 b1 b0 c
 */
void rl(CPU *cpu, enum Operand target) {
    uint8_t val = get_reg(cpu, (enum RegisterName)target);
    uint8_t msb = (val >> MSB_IDX) & 1;
    uint8_t car = get_carry(&cpu->flag_reg);
    uint8_t res = val << 1 | car;

    bool zero = res == 0;
    bool subtract = false;
    bool half_carry = false;
    bool carry = msb == 1;
    update_flags(cpu, zero, subtract, half_carry, carry);

    set_reg(cpu, (enum RegisterName)target, res);  // NOLINT
}

/* Rotate target right and set carry to lsb
 * - lsb becomes new carry
 * - the rest of the bits are right shifted
 *
 * c   b7 b6 b5 b4 b3 b2 b1 b0
 *
 * b0  b0 b7 b6 b5 b4 b3 b2 b1
 */
void rrc(CPU *cpu, enum Operand target) {
    uint8_t val = get_reg(cpu, (enum RegisterName)target);
    uint8_t lsb = val & 1;
    uint8_t res = (lsb << MSB_IDX) | val >> 1;

    bool zero = res == 0;
    bool subtract = false;
    bool half_carry = false;
    bool carry = lsb == 1;
    update_flags(cpu, zero, subtract, half_carry, carry);

    set_reg(cpu, (enum RegisterName)target, res);  // NOLINT
}

/* Rotate A left and set carry to msb
 * - msb becomes new carry
 * - the rest of the bits are left shifted
 *
 * c   b7 b6 b5 b4 b3 b2 b1 b0
 *
 * b7  b6 b5 b4 b3 b2 b1 b0 b7
 */
void rlc(CPU *cpu, enum Operand target) {
    uint8_t val = get_reg(cpu, (enum RegisterName)target);
    uint8_t msb = (val >> MSB_IDX) & 1;
    uint8_t res = val << 1 | msb;

    bool zero = res == 0;
    bool subtract = false;
    bool half_carry = false;
    bool carry = msb == 1;
    update_flags(cpu, zero, subtract, half_carry, carry);

    set_reg(cpu, (enum RegisterName)target, res);  // NOLINT
}

/* Shift target right into carry (also sign extend)
 * - lsb becomes new carry
 * - msb is duplicated
 * - bits are right shifted
 *
 * c  b7 b6 b5 b4 b3 b2 b1 b0
 *
 * b0 b7 b7 b6 b5 b4 b3 b2 b1
 */
void sra(CPU *cpu, enum Operand target) {
    uint8_t val = get_reg(cpu, (enum RegisterName)target);
    uint8_t lsb = val & 1;
    uint8_t msb = (val >> MSB_IDX) & 1;
    uint8_t res = msb << MSB_IDX | val >> 1;

    bool zero = res == 0;
    bool subtract = false;
    bool half_carry = false;
    bool carry = lsb == 1;
    update_flags(cpu, zero, subtract, half_carry, carry);

    set_reg(cpu, (enum RegisterName)target, res);  // NOLINT
}

/* Shift target left into carry
 * - msb becomes new carry
 *
 * c  b7 b6 b5 b4 b3 b2 b1 b0
 *
 * b7 b6 b5 b4 b3 b2 b1 b0 0
 */
void sla(CPU *cpu, enum Operand target) {
    uint8_t val = get_reg(cpu, (enum RegisterName)target);
    uint8_t msb = (val >> MSB_IDX) & 1;
    uint8_t res = val << 1;

    bool zero = res == 0;
    bool subtract = false;
    bool half_carry = false;
    bool carry = msb == 1;
    update_flags(cpu, zero, subtract, half_carry, carry);

    set_reg(cpu, (enum RegisterName)target, res);  // NOLINT
}

void swap(CPU *cpu, enum Operand target) {
    uint8_t val = get_reg(cpu, (enum RegisterName)target);
    uint8_t lower_nibble = val & HBYTE_M;
    uint8_t upper_nibble = (val >> 4) & HBYTE_M;
    uint8_t res = lower_nibble << 4 | upper_nibble;

    bool zero = res == 0;
    bool subtract = false;
    bool half_carry = false;
    bool carry = false;
    update_flags(cpu, zero, subtract, half_carry, carry);

    set_reg(cpu, (enum RegisterName)target, res);  // NOLINT
}

bool jump_test(const CPU *cpu, enum JumpCondition jump_cond) {
    bool jump = false;
    switch (jump_cond) {
        case NOT_ZERO:
            if (!cpu->flag_reg.zero) {
                jump = true;
            }
            break;
        case ZERO:
            if (cpu->flag_reg.zero) {
                jump = true;
            }
            break;
        case NOT_CARRY:
            if (!cpu->flag_reg.carry) {
                jump = true;
            }
            break;
        case CARRY:
            if (cpu->flag_reg.carry) {
                jump = true;
            }
            break;
        case ALWAYS:
            jump = true;
    }
    return jump;
}

/* Based on the given jump condition, we jump to
 * the address specified in the following two bytes in memory.
 *
 * If the jump condition is not true, we simply increment
 * the program counter by the size of the instruction.
 * (1 byte for the instr + 2 bytes for the address)
 */
uint16_t jp(CPU *cpu, enum JumpCondition jump_cond) {
    uint16_t addr = read_bbyte(cpu);
    uint16_t next_pc = cpu->prog_count + 3;

    bool jump = jump_test(cpu, jump_cond);
    if (jump) {
        return addr;
    }

    return next_pc;
}

uint16_t jp_hl(CPU *cpu) {
    uint16_t addr = get_reg(cpu, HL);
    return addr;
}

uint16_t jr(CPU *cpu, enum JumpCondition jump_cond) {
    uint8_t offset = read_byte(cpu);
    int8_t offset_signed = (int8_t)offset;

    bool jump = jump_test(cpu, jump_cond);
    if (jump) {
        return cpu->prog_count + offset_signed;
    }

    return cpu->prog_count + 2;
}

void ld_reg(CPU *cpu, enum Operand target, enum Operand source) {  // NOLINT
    uint16_t res = get_reg(cpu, (enum RegisterName)source);
    set_reg(cpu, (enum RegisterName)target, res);
}

void ld_d8(CPU *cpu, enum Operand target) {
    uint8_t res = cpu->memory[cpu->prog_count + 1];
    set_reg(cpu, (enum RegisterName)target, res);
}

void ld_d16(CPU *cpu, enum Operand target) {
    uint16_t res = read_bbyte(cpu);
    set_reg(cpu, (enum RegisterName)target, res);
}

void ld_d8_ind(CPU *cpu) {
    uint8_t res = read_byte(cpu);
    uint16_t addr = get_reg(cpu, HL);
    cpu->memory[addr] = res;
}

void ld_ind(CPU *cpu, enum Operand target, enum Operand source) {  // NOLINT
    /* Load from address into register */
    if (O_BC_IND <= source && source <= O_HL_IND) {
        enum RegisterName addr_reg;
        if (source == O_BC_IND) {
            addr_reg = BC;
        } else if (source == O_DE_IND) {
            addr_reg = DE;
        } else {
            addr_reg = HL;
        }
        uint16_t addr = get_reg(cpu, addr_reg);
        uint8_t res = cpu->memory[addr];

        set_reg(cpu, (enum RegisterName)target, res);
    }

    /* Load from register into address */
    else if (O_BC_IND <= target && target <= O_HL_IND) {
        enum RegisterName addr_reg;
        if (target == O_BC_IND) {
            addr_reg = BC;
        } else if (target == O_DE_IND) {
            addr_reg = DE;
        } else {
            addr_reg = HL;
        }
        uint16_t addr = get_reg(cpu, addr_reg);
        uint8_t res = get_reg(cpu, (enum RegisterName)source);  // NOLINT

        cpu->memory[addr] = res;
    }
}

void ld_addr(CPU *cpu, enum Operand target, enum Operand source) {  // NOLINT
    /* Load from address into register */
    if (source == O_A16_IND) {
        uint16_t addr = read_bbyte(cpu);
        uint8_t res = cpu->memory[addr];
        set_reg(cpu, (enum RegisterName)target, res);
    }

    /* Load from register into address */
    else if (target == O_A16_IND) {
        uint16_t addr = read_bbyte(cpu);
        uint8_t res = get_reg(cpu, (enum RegisterName)source);
        cpu->memory[addr] = res;
    }
}

void ld_inc(CPU *cpu, enum Operand target, enum Operand source) {  // NOLINT
    /* Load from address into register */
    if (source == O_HL_INC_IND) {
        uint16_t addr = get_reg(cpu, HL);
        uint8_t res = cpu->memory[addr];
        set_reg(cpu, (enum RegisterName)target, res);
        set_reg(cpu, HL, addr + 1);
    }

    /* Load from register into address */
    else if (target == O_HL_INC_IND) {
        uint16_t addr = get_reg(cpu, HL);
        uint8_t res = get_reg(cpu, (enum RegisterName)source);
        cpu->memory[addr] = res;
        set_reg(cpu, HL, addr + 1);
    }
}

void ld_dec(CPU *cpu, enum Operand target, enum Operand source) {  // NOLINT
    /* Load from address into register */
    if (source == O_HL_DEC_IND) {
        uint16_t addr = get_reg(cpu, HL);
        uint8_t res = cpu->memory[addr];
        set_reg(cpu, (enum RegisterName)target, res);
        set_reg(cpu, HL, addr - 1);
    }

    /* Load from register into address */
    else if (target == O_HL_DEC_IND) {
        uint16_t addr = get_reg(cpu, HL);
        uint8_t res = get_reg(cpu, (enum RegisterName)source);
        cpu->memory[addr] = res;
        set_reg(cpu, HL, addr - 1);
    }
}

void ldh_ind(CPU *cpu, enum Operand target, enum Operand source) {  // NOLINT
    /* Load from half address into register */
    if (source == O_C_IND) {
        uint8_t lower_addr = get_reg(cpu, C);
        uint16_t addr = UPPER_BYTE_M | lower_addr;
        uint8_t res = cpu->memory[addr];
        set_reg(cpu, (enum RegisterName)target, res);
    }

    /* Load register into half address */
    else if (target == O_C_IND) {
        uint8_t lower_addr = get_reg(cpu, C);
        uint16_t addr = UPPER_BYTE_M | lower_addr;
        uint8_t res = get_reg(cpu, (enum RegisterName)source);
        cpu->memory[addr] = res;
    }
}

void ldh_addr(CPU *cpu, enum Operand target, enum Operand source) {  // NOLINT
    /* Load from half address into register */
    if (source == O_A8_IND) {
        uint8_t lower_addr = read_byte(cpu);
        uint16_t addr = UPPER_BYTE_M | lower_addr;
        uint8_t res = cpu->memory[addr];
        set_reg(cpu, (enum RegisterName)target, res);
    }

    /* Load register into half address */
    else if (target == O_A8_IND) {
        uint8_t lower_addr = read_byte(cpu);
        uint16_t addr = UPPER_BYTE_M | lower_addr;
        uint8_t res = get_reg(cpu, (enum RegisterName)source);
        cpu->memory[addr] = res;
    }
}

void push(CPU *cpu, enum Operand source) {
    uint16_t val = get_reg(cpu, (enum RegisterName)source);
    stack_push(cpu, val);
}

void pop(CPU *cpu, enum Operand target) {
    uint16_t val = stack_pop(cpu);

    /* Update flag register with F when popping AF */
    if (target == O_AF) {
        uint8_t val_lower = BYTE_M & val;
        cpu->flag_reg = byte_to_flag_reg(val_lower);
    }

    set_reg(cpu, (enum RegisterName)target, val);
}

uint16_t call(CPU *cpu, enum JumpCondition jump_cond) {
    uint16_t next_pc = cpu->prog_count + 3;

    bool jump = jump_test(cpu, jump_cond);
    if (jump) {
        stack_push(cpu, next_pc);
        uint16_t addr = read_bbyte(cpu);
        return addr;
    }

    return next_pc;
}

uint16_t ret(CPU *cpu, enum JumpCondition jump_cond) {
    uint16_t next_pc = cpu->prog_count + 1;

    bool jump = jump_test(cpu, jump_cond);
    if (jump) {
        return stack_pop(cpu);
    }

    return next_pc;
}
