#include "../include/cpu.h"

#include <stdint.h>
#include <stdio.h>

#define HBYTE_M 0xF
#define BYTE_M 0xFF
#define BBYTE_M 0xFFFF
#define UPPER_BYTE_M 0xFF00

#define MSB_IDX 7
#define PREFIX_BYTE 0xCB
#define BYTE_SIZE 8

// Source:
// https://stackoverflow.com/questions/111928/is-there-a-printf-converter-to-print-in-binary-format
#define PRIbin "%c%c%c%c_%c%c%c%c"
#define BYTE_TO_BIN(byte)                                                                      \
    ((byte) & 0x80 ? '1' : '0'), ((byte) & 0x40 ? '1' : '0'), ((byte) & 0x20 ? '1' : '0'),     \
        ((byte) & 0x10 ? '1' : '0'), ((byte) & 0x08 ? '1' : '0'), ((byte) & 0x04 ? '1' : '0'), \
        ((byte) & 0x02 ? '1' : '0'), ((byte) & 0x01 ? '1' : '0')

CPU new_cpu(void) {
    Registers regs = new_regs();
    FlagRegister flag_reg = new_flag_reg();
    CPU cpu = {regs, flag_reg, 0, 0, {0}};
    return cpu;
}

void step(CPU *cpu) {
    uint8_t inst_byte = cpu->memory[cpu->prog_count];

    Instruction inst;

    // Prefix instructions start with 0xCB
    if (inst_byte == PREFIX_BYTE) {
        inst_byte = cpu->memory[cpu->prog_count + 1];
        inst = pf_inst_from_byte(inst_byte);
    } else {
        inst = inst_from_byte(inst_byte);
    }

    cpu->prog_count = execute(cpu, &inst);
}

uint16_t execute(CPU *cpu, const Instruction *instruction) {
    switch (instruction->kind) {
        /* Arithmetic Instructions */
        case ADD:
            add(cpu, instruction->target);
            return cpu->prog_count + 1;
        case ADDHL:
            addhl(cpu, instruction->target);
            return cpu->prog_count + 1;
        case ADC:
            adc(cpu, instruction->target);
            return cpu->prog_count + 1;
        case SUB:
            sub(cpu, instruction->target);
            return cpu->prog_count + 1;
        case SBC:
            sbc(cpu, instruction->target);
            return cpu->prog_count + 1;
        case AND:
            and_(cpu, instruction->target);
            return cpu->prog_count + 1;
        case OR:
            or_(cpu, instruction->target);
            return cpu->prog_count + 1;
        case XOR:
            xor_(cpu, instruction->target);
            return cpu->prog_count + 1;
        case CP:
            cp(cpu, instruction->target);
            return cpu->prog_count + 1;
        case INC:
            inc(cpu, instruction->target);
            return cpu->prog_count + 1;
        case DEC:
            dec(cpu, instruction->target);
            return cpu->prog_count + 1;
        case CCF:
            ccf(cpu);
            return cpu->prog_count + 1;
        case SCF:
            scf(cpu);
            return cpu->prog_count + 1;
        case RRA:
            rra(cpu);
            return cpu->prog_count + 1;
        case RLA:
            rla(cpu);
            return cpu->prog_count + 1;
        case RRCA:
            rrca(cpu);
            return cpu->prog_count + 1;
        case RLCA:
            rlca(cpu);
            return cpu->prog_count + 1;
        case CPL:
            cpl(cpu);
            return cpu->prog_count + 1;

        /* Prefix Instructions */
        case BIT:
            bit(cpu, instruction->bit_index, instruction->target);
            return cpu->prog_count + 2;
        case RESET:
            reset(cpu, instruction->bit_index, instruction->target);
            return cpu->prog_count + 2;
        case SET:
            set(cpu, instruction->bit_index, instruction->target);
            return cpu->prog_count + 2;
        case SRL:
            srl(cpu, instruction->target);
            return cpu->prog_count + 2;
        case RR:
            rr(cpu, instruction->target);
            return cpu->prog_count + 2;
        case RL:
            rl(cpu, instruction->target);
            return cpu->prog_count + 2;
        case RRC:
            rrc(cpu, instruction->target);
            return cpu->prog_count + 2;
        case RLC:
            rlc(cpu, instruction->target);
            return cpu->prog_count + 2;
        case SRA:
            sra(cpu, instruction->target);
            return cpu->prog_count + 2;
        case SLA:
            sla(cpu, instruction->target);
            return cpu->prog_count + 2;
        case SWAP:
            swap(cpu, instruction->target);
            return cpu->prog_count + 2;

        /* Jump Instructions */
        case JP:
            return jp(cpu, instruction->jump_cond);
        case JPHL:
            return jphl(cpu);

        /* Load Instructions */
        case LD_REG:
            ld_reg(cpu, instruction->ld_target, instruction->ld_source);
            return cpu->prog_count + 1;
        case LD_D8:
            ld_d8(cpu, instruction->ld_target);
            return cpu->prog_count + 2;
        case LD_D16:
            ld_d16(cpu, instruction->ld_target);
            return cpu->prog_count + 3;
        case LD_D8_IND:
            ld_d8_ind(cpu);
            return cpu->prog_count + 2;
        case LD_IND:
            ld_ind(cpu, instruction->ld_target, instruction->ld_source);
            return cpu->prog_count + 1;
        case LD_ADDR:
            ld_addr(cpu, instruction->ld_target, instruction->ld_source);
            return cpu->prog_count + 3;
        case LD_INC:
            ld_inc(cpu, instruction->ld_target, instruction->ld_source);
            return cpu->prog_count + 1;
        case LD_DEC:
            ld_dec(cpu, instruction->ld_target, instruction->ld_source);
            return cpu->prog_count + 1;
        case LDH_IND:
            ldh_ind(cpu, instruction->ld_target, instruction->ld_source);
            return cpu->prog_count + 2;
        case LDH_ADDR:
            ldh_addr(cpu, instruction->ld_target, instruction->ld_source);
            return cpu->prog_count + 2;

        /* Stack Instructions */
        case PUSH:
            push(cpu, instruction->target);
            return cpu->prog_count + 1;
        case POP:
            pop(cpu, instruction->target);
            return cpu->prog_count + 1;

        /* Call and Return Instructions */
        case CALL:
            return call(cpu, instruction->jump_cond);
        case RET:
            return ret(cpu, instruction->jump_cond);

        /* No Op Instruction */
        case NOP:
            return cpu->prog_count + 1;
    }

    return 0;
}

uint8_t get_reg(CPU *cpu, enum RegisterName reg) {
    switch (reg) {
        case A:
            return cpu->registers.a;
        case B:
            return cpu->registers.b;
        case C:
            return cpu->registers.c;
        case D:
            return cpu->registers.d;
        case E:
            return cpu->registers.e;
        case F:
            return cpu->registers.f;
        case H:
            return cpu->registers.h;
        case L:
            return cpu->registers.l;
        case AF:
            return get_af(&cpu->registers);
        case BC:
            return get_bc(&cpu->registers);
        case DE:
            return get_de(&cpu->registers);
        case HL:
            return get_hl(&cpu->registers);
        case SP:
            return cpu->stack_pointer;
    }
    return 0;
}

void set_reg(CPU *cpu, enum RegisterName reg, uint8_t val) {  // NOLINT
    switch (reg) {
        case A:
            cpu->registers.a = val;
            break;
        case B:
            cpu->registers.b = val;
            break;
        case C:
            cpu->registers.c = val;
            break;
        case D:
            cpu->registers.d = val;
            break;
        case E:
            cpu->registers.e = val;
            break;
        case F:
            cpu->registers.f = val;
            break;
        case H:
            cpu->registers.h = val;
            break;
        case L:
            cpu->registers.l = val;
            break;
        case AF:
            set_af(&cpu->registers, val);
            break;
        case BC:
            set_bc(&cpu->registers, val);
            break;
        case DE:
            set_de(&cpu->registers, val);
            break;
        case HL:
            set_hl(&cpu->registers, val);
            break;
        case SP:
            cpu->stack_pointer = val;
    }
}

void print_reg(CPU *cpu, enum RegisterName reg) {
    uint8_t val = get_reg(cpu, reg);
    printf("%s: " PRIbin "\n", reg_name(reg), BYTE_TO_BIN(val));
}

void print_regs(CPU *cpu) {
    printf("----------------\n");
    for (int reg = A; reg <= HL; reg++) {
        print_reg(cpu, reg);
    }
    printf("----------------\n");
}

void update_flags(CPU *cpu, bool zero, bool subtract, bool half_carry, bool carry) {
    cpu->flag_reg.zero = zero;
    cpu->flag_reg.subtract = subtract;
    cpu->flag_reg.half_carry = half_carry;
    cpu->flag_reg.carry = carry;

    cpu->registers.f = flag_reg_to_byte(&cpu->flag_reg);
}

uint16_t read_addr(CPU *cpu) {
    uint8_t addr_lower = cpu->memory[cpu->prog_count + 1];
    uint8_t addr_upper = cpu->memory[cpu->prog_count + 2];
    uint16_t addr = ((uint16_t)addr_upper << BYTE_SIZE) | (uint16_t)addr_lower;

    return addr;
}

uint8_t read_byte(CPU *cpu) {
    uint8_t byte = cpu->memory[cpu->prog_count + 1];

    return byte;
}

uint16_t read_bbyte(CPU *cpu) {
    uint8_t bbyte_lower = cpu->memory[cpu->prog_count + 1];
    uint8_t bbyte_upper = cpu->memory[cpu->prog_count + 2];
    uint16_t bbyte = ((uint16_t)bbyte_upper << BYTE_SIZE) | (uint16_t)bbyte_lower;

    return bbyte;
}

void stack_push(CPU *cpu, uint16_t val) {
    uint8_t val_upper = (UPPER_BYTE_M & val) >> BYTE_SIZE;
    uint8_t val_lower = BYTE_M & val;

    cpu->stack_pointer -= 1;
    cpu->memory[cpu->stack_pointer] = val_upper;

    cpu->stack_pointer -= 1;
    cpu->memory[cpu->stack_pointer] = val_lower;
}

uint16_t stack_pop(CPU *cpu) {
    uint8_t val_lower = cpu->memory[cpu->stack_pointer];
    cpu->stack_pointer += 1;

    uint8_t val_upper = cpu->memory[cpu->stack_pointer];
    cpu->stack_pointer += 1;

    uint16_t val = (val_upper << BYTE_SIZE) | val_lower;
    return val;
}

void add(CPU *cpu, enum RegisterName target) {
    uint8_t acc = get_reg(cpu, A);
    uint8_t val = get_reg(cpu, target);
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

void addhl(CPU *cpu, enum RegisterName target) {
    uint16_t acc = get_reg(cpu, HL);
    // val is one of the 16 bit regs: BC, DE, HL, SP
    uint16_t val = get_reg(cpu, target);
    uint16_t res = acc + val;

    bool zero = res == 0;
    bool subtract = false;
    bool half_carry = (acc & BYTE_M) + (val & BYTE_M) > BYTE_M;
    bool carry = acc + val > BBYTE_M;
    update_flags(cpu, zero, subtract, half_carry, carry);

    set_reg(cpu, HL, res);
}

void adc(CPU *cpu, enum RegisterName target) {
    uint8_t acc = get_reg(cpu, A);
    uint8_t val = get_reg(cpu, target);
    uint8_t car = get_carry(&cpu->flag_reg);
    uint8_t res = acc + val + car;

    bool zero = res == 0;
    bool subtract = false;
    bool half_carry = (acc & HBYTE_M) + (val & HBYTE_M) + (car & HBYTE_M) > HBYTE_M;
    bool carry = acc + val + car > BYTE_M;
    update_flags(cpu, zero, subtract, half_carry, carry);

    set_reg(cpu, A, res);
}

void sub(CPU *cpu, enum RegisterName target) {
    uint8_t acc = get_reg(cpu, A);
    uint8_t val = get_reg(cpu, target);
    uint8_t res = acc - val;

    bool zero = res == 0;
    bool subtract = true;
    bool half_carry = (acc & HBYTE_M) < (val & HBYTE_M);
    bool carry = acc < val;
    update_flags(cpu, zero, subtract, half_carry, carry);

    set_reg(cpu, A, res);
}

void sbc(CPU *cpu, enum RegisterName target) {
    uint8_t acc = get_reg(cpu, A);
    uint8_t val = get_reg(cpu, target);
    uint8_t car = get_carry(&cpu->flag_reg);
    uint8_t res = acc - val - car;

    bool zero = res == 0;
    bool subtract = true;
    bool half_carry = (acc & HBYTE_M) < (val & HBYTE_M) + (car & HBYTE_M);
    bool carry = acc < (val + car);
    update_flags(cpu, zero, subtract, half_carry, carry);

    set_reg(cpu, A, res);
}

void and_(CPU *cpu, enum RegisterName target) {
    uint8_t acc = get_reg(cpu, A);
    uint8_t val = get_reg(cpu, target);
    uint8_t res = acc && val;

    bool zero = res == 0;
    bool subtract = false;
    bool half_carry = true;
    bool carry = false;
    update_flags(cpu, zero, subtract, half_carry, carry);

    set_reg(cpu, A, res);
}

void or_(CPU *cpu, enum RegisterName target) {
    uint8_t acc = get_reg(cpu, A);
    uint8_t val = get_reg(cpu, target);
    uint8_t res = acc || val;

    bool zero = res == 0;
    bool subtract = false;
    bool half_carry = true;
    bool carry = false;
    update_flags(cpu, zero, subtract, half_carry, carry);

    set_reg(cpu, A, res);
}

void xor_(CPU *cpu, enum RegisterName target) {
    uint8_t acc = get_reg(cpu, A);
    uint8_t val = get_reg(cpu, target);
    uint8_t res = acc ^ val;

    bool zero = res == 0;
    bool subtract = false;
    bool half_carry = true;
    bool carry = false;
    update_flags(cpu, zero, subtract, half_carry, carry);

    set_reg(cpu, A, res);
}

void cp(CPU *cpu, enum RegisterName target) {
    uint8_t acc = get_reg(cpu, A);
    uint8_t val = get_reg(cpu, target);
    uint8_t res = acc - val;

    bool zero = res == 0;
    bool subtract = true;
    bool half_carry = (acc & HBYTE_M) < (val & HBYTE_M);
    bool carry = acc < val;
    update_flags(cpu, zero, subtract, half_carry, carry);
}

void inc(CPU *cpu, enum RegisterName target) {
    uint8_t val = get_reg(cpu, target);
    uint8_t res = val + 1;

    // Flags are only affected when incrementing
    // a byte register as opposed to a 2-byte register.
    // TODO: Look into zero if the values inside of the
    // registers are actually representations of signed integers
    if (target < AF) {
        bool zero = false;
        bool subtract = false;
        bool half_carry = (val & HBYTE_M) + 1 > HBYTE_M;
        bool carry = cpu->flag_reg.carry;
        update_flags(cpu, zero, subtract, half_carry, carry);
    }

    set_reg(cpu, target, res);  // NOLINT
}

void dec(CPU *cpu, enum RegisterName target) {
    uint8_t val = get_reg(cpu, target);
    uint8_t res = val - 1;

    // TODO: same as above
    if (target < AF) {
        bool zero = res == 0;
        bool subtract = true;
        bool half_carry = (val & HBYTE_M) >= 1;
        bool carry = cpu->flag_reg.carry;
        update_flags(cpu, zero, subtract, half_carry, carry);
    }

    set_reg(cpu, target, res);  // NOLINT
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

void bit(CPU *cpu, uint8_t bit_index, enum RegisterName target) {  // NOLINT
    uint8_t val = get_reg(cpu, target);
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
void reset(CPU *cpu, uint8_t bit_index, enum RegisterName target) {  // NOLINT
    uint8_t val = get_reg(cpu, target);
    uint8_t res = val & ~(1 << bit_index);

    set_reg(cpu, target, res);  // NOLINT
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
void set(CPU *cpu, uint8_t bit_index, enum RegisterName target) {  // NOLINT
    uint8_t val = get_reg(cpu, target);
    uint8_t res = val | (1 << bit_index);

    set_reg(cpu, target, res);  // NOLINT
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
void srl(CPU *cpu, enum RegisterName target) {
    uint8_t val = get_reg(cpu, target);
    uint8_t lsb = val & 1;
    uint8_t res = val >> 1;

    bool zero = res == 0;
    bool subtract = false;
    bool half_carry = false;
    bool carry = lsb == 1;
    update_flags(cpu, zero, subtract, half_carry, carry);

    set_reg(cpu, target, res);  // NOLINT
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
void rr(CPU *cpu, enum RegisterName target) {
    uint8_t val = get_reg(cpu, target);
    uint8_t lsb = val & 1;
    uint8_t car = get_carry(&cpu->flag_reg);
    uint8_t res = car << MSB_IDX | val >> 1;

    bool zero = res == 0;
    bool subtract = false;
    bool half_carry = false;
    bool carry = lsb == 1;
    update_flags(cpu, zero, subtract, half_carry, carry);

    set_reg(cpu, target, res);  // NOLINT
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
void rl(CPU *cpu, enum RegisterName target) {
    uint8_t val = get_reg(cpu, target);
    uint8_t msb = (val >> MSB_IDX) & 1;
    uint8_t car = get_carry(&cpu->flag_reg);
    uint8_t res = val << 1 | car;

    bool zero = res == 0;
    bool subtract = false;
    bool half_carry = false;
    bool carry = msb == 1;
    update_flags(cpu, zero, subtract, half_carry, carry);

    set_reg(cpu, target, res);  // NOLINT
}

/* Rotate target right and set carry to lsb
 * - lsb becomes new carry
 * - the rest of the bits are right shifted
 *
 * c   b7 b6 b5 b4 b3 b2 b1 b0
 *
 * b0  b0 b7 b6 b5 b4 b3 b2 b1
 */
void rrc(CPU *cpu, enum RegisterName target) {
    uint8_t val = get_reg(cpu, target);
    uint8_t lsb = val & 1;
    uint8_t res = (lsb << MSB_IDX) | val >> 1;

    bool zero = res == 0;
    bool subtract = false;
    bool half_carry = false;
    bool carry = lsb == 1;
    update_flags(cpu, zero, subtract, half_carry, carry);

    set_reg(cpu, target, res);  // NOLINT
}

/* Rotate A left and set carry to msb
 * - msb becomes new carry
 * - the rest of the bits are left shifted
 *
 * c   b7 b6 b5 b4 b3 b2 b1 b0
 *
 * b7  b6 b5 b4 b3 b2 b1 b0 b7
 */
void rlc(CPU *cpu, enum RegisterName target) {
    uint8_t val = get_reg(cpu, target);
    uint8_t msb = (val >> MSB_IDX) & 1;
    uint8_t res = val << 1 | msb;

    bool zero = res == 0;
    bool subtract = false;
    bool half_carry = false;
    bool carry = msb == 1;
    update_flags(cpu, zero, subtract, half_carry, carry);

    set_reg(cpu, target, res);  // NOLINT
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
void sra(CPU *cpu, enum RegisterName target) {
    uint8_t val = get_reg(cpu, target);
    uint8_t lsb = val & 1;
    uint8_t msb = (val >> MSB_IDX) & 1;
    uint8_t res = msb << MSB_IDX | val >> 1;

    bool zero = res == 0;
    bool subtract = false;
    bool half_carry = false;
    bool carry = lsb == 1;
    update_flags(cpu, zero, subtract, half_carry, carry);

    set_reg(cpu, target, res);  // NOLINT
}

/* Shift target left into carry
 * - msb becomes new carry
 *
 * c  b7 b6 b5 b4 b3 b2 b1 b0
 *
 * b7 b6 b5 b4 b3 b2 b1 b0 0
 */
void sla(CPU *cpu, enum RegisterName target) {
    uint8_t val = get_reg(cpu, target);
    uint8_t msb = (val >> MSB_IDX) & 1;
    uint8_t res = val << 1;

    bool zero = res == 0;
    bool subtract = false;
    bool half_carry = false;
    bool carry = msb == 1;
    update_flags(cpu, zero, subtract, half_carry, carry);

    set_reg(cpu, target, res);  // NOLINT
}

void swap(CPU *cpu, enum RegisterName target) {
    uint8_t val = get_reg(cpu, target);
    uint8_t lower_nibble = val & HBYTE_M;
    uint8_t upper_nibble = (val >> 4) & HBYTE_M;
    uint8_t res = lower_nibble << 4 | upper_nibble;

    bool zero = res == 0;
    bool subtract = false;
    bool half_carry = false;
    bool carry = false;
    update_flags(cpu, zero, subtract, half_carry, carry);

    set_reg(cpu, target, res);  // NOLINT
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
    uint16_t addr = read_addr(cpu);
    uint16_t next_pc = cpu->prog_count + 3;

    bool jump = jump_test(cpu, jump_cond);
    if (jump) {
        return addr;
    }

    return next_pc;
}

uint16_t jphl(CPU *cpu) {
    uint16_t addr = get_reg(cpu, HL);
    return addr;
}

void ld_reg(CPU *cpu, enum LoadOperand ld_target, enum LoadOperand ld_source) {  // NOLINT
    uint16_t res = get_reg(cpu, (enum RegisterName)ld_source);
    set_reg(cpu, (enum RegisterName)ld_target, res);
}

void ld_d8(CPU *cpu, enum LoadOperand ld_target) {
    uint8_t res = cpu->memory[cpu->prog_count + 1];
    set_reg(cpu, (enum RegisterName)ld_target, res);
}

void ld_d16(CPU *cpu, enum LoadOperand ld_target) {
    uint16_t res = read_bbyte(cpu);
    set_reg(cpu, (enum RegisterName)ld_target, res);
}

void ld_d8_ind(CPU *cpu) {
    uint8_t res = read_byte(cpu);
    uint16_t addr = get_reg(cpu, HL);
    cpu->memory[addr] = res;
}

void ld_ind(CPU *cpu, enum LoadOperand ld_target, enum LoadOperand ld_source) {  // NOLINT
    /* Load from address into register */
    if (LO_BC_IND <= ld_source && ld_source <= LO_HL_IND) {
        enum RegisterName addr_reg;
        if (ld_source == LO_BC_IND) {
            addr_reg = BC;
        } else if (ld_source == LO_DE_IND) {
            addr_reg = DE;
        } else {
            addr_reg = HL;
        }
        uint16_t addr = get_reg(cpu, addr_reg);
        uint8_t res = cpu->memory[addr];

        set_reg(cpu, (enum RegisterName)ld_target, res);
    }

    /* Load from register into address */
    else if (LO_BC_IND <= ld_target && ld_target <= LO_HL_IND) {
        enum RegisterName addr_reg;
        if (ld_target == LO_BC_IND) {
            addr_reg = BC;
        } else if (ld_target == LO_DE_IND) {
            addr_reg = DE;
        } else {
            addr_reg = HL;
        }
        uint16_t addr = get_reg(cpu, addr_reg);
        uint8_t res = get_reg(cpu, (enum RegisterName)ld_source);  // NOLINT

        cpu->memory[addr] = res;
    }
}

void ld_addr(CPU *cpu, enum LoadOperand ld_target, enum LoadOperand ld_source) {  // NOLINT
    /* Load from address into register */
    if (ld_source == LO_A16_IND) {
        uint16_t addr = read_addr(cpu);
        uint8_t res = cpu->memory[addr];
        set_reg(cpu, (enum RegisterName)ld_target, res);
    }

    /* Load from register into address */
    else if (ld_target == LO_A16_IND) {
        uint16_t addr = read_addr(cpu);
        uint8_t res = get_reg(cpu, (enum RegisterName)ld_source);
        cpu->memory[addr] = res;
    }
}

void ld_inc(CPU *cpu, enum LoadOperand ld_target, enum LoadOperand ld_source) {  // NOLINT
    /* Load from address into register */
    if (ld_source == LO_HL_INC_IND) {
        uint16_t addr = get_reg(cpu, HL);
        uint8_t res = cpu->memory[addr];
        set_reg(cpu, (enum RegisterName)ld_target, res);
        set_reg(cpu, HL, addr + 1);
    }

    /* Load from register into address */
    else if (ld_target == LO_HL_INC_IND) {
        uint16_t addr = get_reg(cpu, HL);
        uint8_t res = get_reg(cpu, (enum RegisterName)ld_source);
        cpu->memory[addr] = res;
        set_reg(cpu, HL, addr + 1);
    }
}

void ld_dec(CPU *cpu, enum LoadOperand ld_target, enum LoadOperand ld_source) {  // NOLINT
    /* Load from address into register */
    if (ld_source == LO_HL_INC_IND) {
        uint16_t addr = get_reg(cpu, HL);
        uint8_t res = cpu->memory[addr];
        set_reg(cpu, (enum RegisterName)ld_target, res);
        set_reg(cpu, HL, addr - 1);
    }

    /* Load from register into address */
    else if (ld_target == LO_HL_INC_IND) {
        uint16_t addr = get_reg(cpu, HL);
        uint8_t res = get_reg(cpu, (enum RegisterName)ld_source);
        cpu->memory[addr] = res;
        set_reg(cpu, HL, addr - 1);
    }
}

void ldh_ind(CPU *cpu, enum LoadOperand ld_target, enum LoadOperand ld_source) {  // NOLINT
    /* Load from half address into register */
    if (ld_source == LO_C_IND) {
        uint8_t lower_addr = get_reg(cpu, C);
        uint16_t addr = UPPER_BYTE_M | lower_addr;
        uint8_t res = cpu->memory[addr];
        set_reg(cpu, (enum RegisterName)ld_target, res);
    }

    /* Load register into half address */
    else if (ld_target == LO_C_IND) {
        uint8_t lower_addr = get_reg(cpu, C);
        uint16_t addr = UPPER_BYTE_M | lower_addr;
        uint8_t res = get_reg(cpu, (enum RegisterName)ld_source);
        cpu->memory[addr] = res;
    }
}

void ldh_addr(CPU *cpu, enum LoadOperand ld_target, enum LoadOperand ld_source) {  // NOLINT
    /* Load from half address into register */
    if (ld_source == LO_A8_IND) {
        uint8_t lower_addr = read_byte(cpu);
        uint16_t addr = UPPER_BYTE_M | lower_addr;
        uint8_t res = cpu->memory[addr];
        set_reg(cpu, (enum RegisterName)ld_target, res);
    }

    /* Load register into half address */
    else if (ld_target == LO_A8_IND) {
        uint8_t lower_addr = read_byte(cpu);
        uint16_t addr = UPPER_BYTE_M | lower_addr;
        uint8_t res = get_reg(cpu, (enum RegisterName)ld_source);
        cpu->memory[addr] = res;
    }
}

void push(CPU *cpu, enum RegisterName target) {
    uint16_t val = get_reg(cpu, target);
    stack_push(cpu, val);
}

void pop(CPU *cpu, enum RegisterName target) {
    uint16_t val = stack_pop(cpu);

    /* Update flag register with F when popping AF */
    if (target == AF) {
        uint8_t val_lower = BYTE_M & val;
        cpu->flag_reg = byte_to_flag_reg(val_lower);
        set_reg(cpu, F, val_lower);
    }

    set_reg(cpu, target, val);
}

uint16_t call(CPU *cpu, enum JumpCondition jump_cond) {
    uint16_t next_pc = cpu->prog_count + 3;

    bool jump = jump_test(cpu, jump_cond);
    if (jump) {
        stack_push(cpu, next_pc);
        uint16_t addr = read_addr(cpu);
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
