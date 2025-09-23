#include "../../include/cpu.h"

#include <stdint.h>
#include <stdio.h>

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
            add(cpu, instruction->source);
            return cpu->prog_count + 1;
        case ADD_HL:
            add_hl(cpu, instruction->source);
            return cpu->prog_count + 1;
        case ADD_IND:
            add_ind(cpu);
            return cpu->prog_count + 1;
        case ADD_D8:
            add_d8(cpu);
            return cpu->prog_count + 2;
        case ADC:
            adc(cpu, instruction->source);
            return cpu->prog_count + 1;
        case ADC_IND:
            adc_ind(cpu);
            return cpu->prog_count + 1;
        case ADC_D8:
            adc_d8(cpu);
            return cpu->prog_count + 2;
        case SUB:
            sub(cpu, instruction->source);
            return cpu->prog_count + 1;
        case SUB_IND:
            sub_ind(cpu);
            return cpu->prog_count + 1;
        case SUB_D8:
            sub_d8(cpu);
            return cpu->prog_count + 2;
        case SBC:
            sbc(cpu, instruction->source);
            return cpu->prog_count + 1;
        case SBC_IND:
            sbc_ind(cpu);
            return cpu->prog_count + 1;
        case SBC_D8:
            sbc_d8(cpu);
            return cpu->prog_count + 2;
        case AND:
            and_(cpu, instruction->source);
            return cpu->prog_count + 1;
        case AND_IND:
            and_ind(cpu);
            return cpu->prog_count + 1;
        case AND_D8:
            and_d8(cpu);
            return cpu->prog_count + 2;
        case OR:
            or_(cpu, instruction->source);
            return cpu->prog_count + 1;
        case OR_IND:
            or_ind(cpu);
            return cpu->prog_count + 1;
        case OR_D8:
            or_d8(cpu);
            return cpu->prog_count + 2;
        case XOR:
            xor_(cpu, instruction->source);
            return cpu->prog_count + 1;
        case XOR_IND:
            xor_ind(cpu);
            return cpu->prog_count + 1;
        case XOR_D8:
            xor_d8(cpu);
            return cpu->prog_count + 2;
        case CP:
            cp(cpu, instruction->source);
            return cpu->prog_count + 1;
        case CP_IND:
            cp_ind(cpu);
            return cpu->prog_count + 1;
        case CP_D8:
            cp_d8(cpu);
            return cpu->prog_count + 2;
        case INC:
            inc(cpu, instruction->source);
            return cpu->prog_count + 1;
        case INC_IND:
            inc_ind(cpu);
            return cpu->prog_count + 1;
        case DEC:
            dec(cpu, instruction->source);
            return cpu->prog_count + 1;
        case DEC_IND:
            dec_ind(cpu);
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
        case JP_HL:
            return jp_hl(cpu);
        case JR:
            return jr(cpu, instruction->jump_cond);

        /* Load Instructions */
        case LD_REG:
            ld_reg(cpu, instruction->target, instruction->source);
            return cpu->prog_count + 1;
        case LD_D8:
            ld_d8(cpu, instruction->target);
            return cpu->prog_count + 2;
        case LD_D16:
            ld_d16(cpu, instruction->target);
            return cpu->prog_count + 3;
        case LD_D8_IND:
            ld_d8_ind(cpu);
            return cpu->prog_count + 2;
        case LD_IND:
            ld_ind(cpu, instruction->target, instruction->source);
            return cpu->prog_count + 1;
        case LD_ADDR:
            ld_addr(cpu, instruction->target, instruction->source);
            return cpu->prog_count + 3;
        case LD_INC:
            ld_inc(cpu, instruction->target, instruction->source);
            return cpu->prog_count + 1;
        case LD_DEC:
            ld_dec(cpu, instruction->target, instruction->source);
            return cpu->prog_count + 1;
        case LDH_IND:
            ldh_ind(cpu, instruction->target, instruction->source);
            return cpu->prog_count + 2;
        case LDH_ADDR:
            ldh_addr(cpu, instruction->target, instruction->source);
            return cpu->prog_count + 2;

        /* Stack Instructions */
        case PUSH:
            push(cpu, instruction->source);
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

uint16_t get_reg(CPU *cpu, enum RegisterName reg) {
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

void set_reg(CPU *cpu, enum RegisterName reg, uint16_t val) {  // NOLINT
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

void print_reg(CPU *cpu, enum RegisterName reg) {  // NOLINT
    if (reg <= L) {
        uint8_t val = get_reg(cpu, reg);
        printf("%s: " PRIbin "\n", reg_name(reg), BYTE_TO_BIN(val));
    } else {
        uint16_t val = get_reg(cpu, reg);
        printf("%s: " PRIbin "_" PRIbin "\n", reg_name(reg),
               BYTE_TO_BIN((uint8_t)(val >> BYTE_SIZE)), BYTE_TO_BIN((uint8_t)val));
    }
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

uint8_t read_byte(CPU *cpu) {
    uint8_t byte = cpu->memory[cpu->prog_count + 1];

    return byte;
}

uint16_t read_bbyte(CPU *cpu) {
    uint8_t bbyte_lower = cpu->memory[cpu->prog_count + 1];
    uint8_t bbyte_upper = cpu->memory[cpu->prog_count + 2];
    uint16_t bbyte = (uint16_t)bbyte_upper << BYTE_SIZE | (uint16_t)bbyte_lower;

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
