#include <stdint.h>

#include "instructions.h"

#define MEMORY_SIZE 0xFFFF

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

typedef struct {
    Registers registers;
    FlagRegister flag_reg;
    uint16_t prog_count;
    uint16_t stack_pointer;
    uint8_t memory[MEMORY_SIZE];
} CPU;

CPU new_cpu(void);

/* Instruction execution */
void step(CPU *cpu);
uint16_t execute(CPU *cpu, const Instruction *instruction);

/* Register interactions */
uint16_t get_reg(CPU *cpu, enum RegisterName reg);
void set_reg(CPU *cpu, enum RegisterName reg, uint16_t val);
void print_reg(CPU *cpu, enum RegisterName reg);
void print_regs(CPU *cpu);
void update_flags(CPU *cpu, bool zero, bool subtract, bool half_carry, bool carry);

/* Memory interactions */
uint8_t read_byte(CPU *cpu);
uint16_t read_bbyte(CPU *cpu);

/* Stack interactions */
void stack_push(CPU *cpu, uint16_t val);
uint16_t stack_pop(CPU *cpu);

/* Instruction implementations */
void add(CPU *cpu, enum RegisterName target);
void addhl(CPU *cpu, enum RegisterName target);
void adc(CPU *cpu, enum RegisterName target);
void sub(CPU *cpu, enum RegisterName target);
void sbc(CPU *cpu, enum RegisterName target);
void and_(CPU *cpu, enum RegisterName target);
void or_(CPU *cpu, enum RegisterName target);
void xor_(CPU *cpu, enum RegisterName target);
void cp(CPU *cpu, enum RegisterName target);
void inc(CPU *cpu, enum RegisterName target);
void dec(CPU *cpu, enum RegisterName target);
void ccf(CPU *cpu);
void scf(CPU *cpu);
void rra(CPU *cpu);
void rla(CPU *cpu);
void rrca(CPU *cpu);
void rlca(CPU *cpu);
void cpl(CPU *cpu);

void bit(CPU *cpu, uint8_t bit_index, enum RegisterName target);
void reset(CPU *cpu, uint8_t bit_index, enum RegisterName target);
void set(CPU *cpu, uint8_t bit_index, enum RegisterName target);
void srl(CPU *cpu, enum RegisterName target);
void rr(CPU *cpu, enum RegisterName target);
void rl(CPU *cpu, enum RegisterName target);
void rrc(CPU *cpu, enum RegisterName target);
void rlc(CPU *cpu, enum RegisterName target);
void sra(CPU *cpu, enum RegisterName target);
void sla(CPU *cpu, enum RegisterName target);
void swap(CPU *cpu, enum RegisterName target);

bool jump_test(const CPU *cpu, enum JumpCondition jump_cond);
uint16_t jp(CPU *cpu, enum JumpCondition jump_cond);
uint16_t jphl(CPU *cpu);

void ld_reg(CPU *cpu, enum LoadOperand ld_target, enum LoadOperand ld_source);
void ld_d8(CPU *cpu, enum LoadOperand ld_target);
void ld_d16(CPU *cpu, enum LoadOperand ld_target);
void ld_d8_ind(CPU *cpu);
void ld_ind(CPU *cpu, enum LoadOperand ld_target, enum LoadOperand ld_source);
void ld_addr(CPU *cpu, enum LoadOperand ld_target, enum LoadOperand ld_source);
void ld_inc(CPU *cpu, enum LoadOperand ld_target, enum LoadOperand ld_source);
void ld_dec(CPU *cpu, enum LoadOperand ld_target, enum LoadOperand ld_source);
void ldh_ind(CPU *cpu, enum LoadOperand ld_target, enum LoadOperand ld_source);
void ldh_addr(CPU *cpu, enum LoadOperand ld_target, enum LoadOperand ld_source);

void push(CPU *cpu, enum RegisterName target);
void pop(CPU *cpu, enum RegisterName target);

uint16_t call(CPU *cpu, enum JumpCondition jump_cond);
uint16_t ret(CPU *cpu, enum JumpCondition jump_cond);
