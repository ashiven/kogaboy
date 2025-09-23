#include <stdint.h>

#include "instructions.h"
#include "registers.h"

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
void add(CPU *cpu, enum Operand source);
void add_hl(CPU *cpu, enum Operand source);
void add_ind(CPU *cpu);
void add_d8(CPU *cpu);
void adc(CPU *cpu, enum Operand source);
void adc_ind(CPU *cpu);
void adc_d8(CPU *cpu);
void sub(CPU *cpu, enum Operand source);
void sub_ind(CPU *cpu);
void sub_d8(CPU *cpu);
void sbc(CPU *cpu, enum Operand source);
void sbc_ind(CPU *cpu);
void sbc_d8(CPU *cpu);
void and_(CPU *cpu, enum Operand source);
void and_ind(CPU *cpu);
void and_d8(CPU *cpu);
void or_(CPU *cpu, enum Operand source);
void or_ind(CPU *cpu);
void or_d8(CPU *cpu);
void xor_(CPU *cpu, enum Operand source);
void xor_ind(CPU *cpu);
void xor_d8(CPU *cpu);
void cp(CPU *cpu, enum Operand source);
void cp_ind(CPU *cpu);
void cp_d8(CPU *cpu);
void inc(CPU *cpu, enum Operand target);
void inc_ind(CPU *cpu);
void dec(CPU *cpu, enum Operand target);
void dec_ind(CPU *cpu);
void ccf(CPU *cpu);
void scf(CPU *cpu);
void rra(CPU *cpu);
void rla(CPU *cpu);
void rrca(CPU *cpu);
void rlca(CPU *cpu);
void cpl(CPU *cpu);

void bit(CPU *cpu, uint8_t bit_index, enum Operand target);
void reset(CPU *cpu, uint8_t bit_index, enum Operand target);
void set(CPU *cpu, uint8_t bit_index, enum Operand target);
void srl(CPU *cpu, enum Operand target);
void rr(CPU *cpu, enum Operand target);
void rl(CPU *cpu, enum Operand target);
void rrc(CPU *cpu, enum Operand target);
void rlc(CPU *cpu, enum Operand target);
void sra(CPU *cpu, enum Operand target);
void sla(CPU *cpu, enum Operand target);
void swap(CPU *cpu, enum Operand target);

bool jump_test(const CPU *cpu, enum JumpCondition jump_cond);
uint16_t jp(CPU *cpu, enum JumpCondition jump_cond);
uint16_t jp_hl(CPU *cpu);
uint16_t jr(CPU *cpu, enum JumpCondition jump_cond);

void ld_reg(CPU *cpu, enum Operand target, enum Operand source);
void ld_d8(CPU *cpu, enum Operand target);
void ld_d16(CPU *cpu, enum Operand target);
void ld_d8_ind(CPU *cpu);
void ld_ind(CPU *cpu, enum Operand target, enum Operand source);
void ld_addr(CPU *cpu, enum Operand target, enum Operand source);
void ld_inc(CPU *cpu, enum Operand target, enum Operand source);
void ld_dec(CPU *cpu, enum Operand target, enum Operand source);
void ldh_ind(CPU *cpu, enum Operand target, enum Operand source);
void ldh_addr(CPU *cpu, enum Operand target, enum Operand source);

void push(CPU *cpu, enum Operand source);
void pop(CPU *cpu, enum Operand target);

uint16_t call(CPU *cpu, enum JumpCondition jump_cond);
uint16_t ret(CPU *cpu, enum JumpCondition jump_cond);
