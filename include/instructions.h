#include <stdint.h>

#include "../include/registers.h"

// TODO: JR, LD_SP, EI, DI, HALT, RST...
enum InstructionKind {  // NOLINT
    /* Arithmetic Instructions */
    ADD,   /*Add target to register A*/
    ADDHL, /*Add target to register HL*/
    ADC,   /*Add target and value of carry flag to register A*/
    SUB,   /*Subtract target from register A*/
    SBC,   /*Subtract target and carry flag from register A*/
    AND,   /*Bitwise AND between target and register A*/
    OR,    /*Bitwise OR between target and register A*/
    XOR,   /*Bitwise XOR between target and register A*/
    CP,    /*Subtract without storing the result in A*/
    INC,   /*Increment the value in target by 1*/
    DEC,   /*Decrement the value in target by 1*/
    CCF,   /*Toggle value of the carry flag*/
    SCF,   /*Set carry flag to true*/
    RRA,   /*Bit rotate right register A through carry flag*/
    RLA,   /*Bit rotate left register A through carry flag*/
    RRCA,  /*Bit rotate right register A and set carry flag*/
    RLCA,  /*Bit rotate left register A and set carry flag*/
    CPL,   /*Toggle every bit of the A register*/

    /* Prefix Instructions */
    BIT,   /*Test whether a specific bit of target register is set*/
    RESET, /*Reset a bit of target to 0*/
    SET,   /*Set a bit of target to 1*/
    SRL,   /*Logic shift target to the right by 1*/
    RR,    /*Bit rotate right target through carry flag*/
    RL,    /*Bit rotate left target through carry flag*/
    RRC,   /*Bit rotate right target and set carry flag*/
    RLC,   /*Bit rotate left target and set carry flag*/
    SRA,   /*Arithmetic shift target to the right by 1*/
    SLA,   /*Arithmetic shift target to the left by 1*/
    SWAP,  /*Swap the upper and lower halfs (4 Bits each) of the target*/

    /* Jump Instructions */
    JP,   /*Jump to 8 or 16 bit-adjusted address based on a condition*/
    JPHL, /*Jump to the address in register HL*/

    /* Load Instructions */
    LD_REG,    /*Load the value from one register into another*/
    LD_D8,     /*Load an immediate 8-bit value into a register*/
    LD_D16,    /*Load an immediate 16-bit value into a register*/
    LD_D8_IND, /*Load an immediate 8-bit value into an address (stored in HL)*/
    LD_IND,    /*Load or store the value at an address (stored in a 16 bit reg)*/
    LD_ADDR,   /*Load or store the value at an address (u16 immediate value)*/
    LD_INC,    /*Load or store the value at an address (stored in HL) and then increment HL*/
    LD_DEC,    /*Load or store the value at an address (stored in HL) and then decrement HL*/
    LDH_IND,   /*Load or store the value at an address (u8 from register C LSB + 0xFF MSB)*/
    LDH_ADDR,  /*Load or store the value at an address (u8 immediate LSB + 0xFF MSB)*/

    /* Stack Instructions */
    PUSH, /*Push a 16-bit register onto the stack*/
    POP,  /*Pop a 16-bit value from the stack and store it in a 16-bit register*/

    /* Call and Return Instructions */
    CALL, /*Conditionally jump to an address marking the start of a function, storing the current PC
             on the stack*/
    RET,  /*Conditionally return from a function call by popping the previously stored PC from the
             stack and jumping to it*/
};

enum JumpCondition {  // NOLINT
    NOT_ZERO,
    ZERO,
    NOT_CARRY,
    CARRY,
    ALWAYS,
};

// NOTE: Make sure that the order of the registers matches that in
// enum RegisterName so we can use them interchangeably to refer to registers.
// (Remember that the underlying type of an enum is simply an integer)
enum LoadOperand {  // NOLINT
    LO_A,
    LO_B,
    LO_C,
    LO_D,
    LO_E,
    LO_F,
    LO_H,
    LO_L,
    LO_AF,
    LO_BC,
    LO_DE,
    LO_HL,
    LO_SP,
    LO_C_IND,
    LO_BC_IND,
    LO_DE_IND,
    LO_HL_IND,
    LO_HL_INC_IND,
    LO_HL_DEC_IND,
    LO_D8,
    LO_D16,
    LO_A8_IND,
    LO_A16_IND,
};

// TODO: embed generic Instruction inside of specific
// instructions like: ArithInstr, PrefixInstr, JumpInstr, LoadInstr ...
typedef struct {
    enum InstructionKind kind;

    /* Arithmetic & Prefix Instructions */
    enum RegisterName target;

    /* Prefix Instructions */
    uint8_t bit_index;

    /* Jump Instructions */
    enum JumpCondition jump_cond;

    /* Load Instructions */
    enum LoadOperand ld_target;
    enum LoadOperand ld_source;
} Instruction;

/* Instruction Decoding */
Instruction inst_from_byte(uint8_t byte);
Instruction pf_inst_from_byte(uint8_t byte);

/* Arithmetic Instructions */
Instruction new_add(enum RegisterName target);
Instruction new_addhl(enum RegisterName target);
Instruction new_adc(enum RegisterName target);
Instruction new_sub(enum RegisterName target);
Instruction new_sbc(enum RegisterName target);
Instruction new_and(enum RegisterName target);
Instruction new_or(enum RegisterName target);
Instruction new_xor(enum RegisterName target);
Instruction new_cp(enum RegisterName target);
Instruction new_inc(enum RegisterName target);
Instruction new_dec(enum RegisterName target);
Instruction new_ccf(void);
Instruction new_scf(void);
Instruction new_rra(void);
Instruction new_rla(void);
Instruction new_rrca(void);
Instruction new_rlca(void);
Instruction new_cpl(void);

/* Prefix Instructions - Bits, Shifts, and Rotations */
Instruction new_bit(uint8_t bit_index, enum RegisterName target);
Instruction new_reset(uint8_t bit_index, enum RegisterName target);
Instruction new_set(uint8_t bit_index, enum RegisterName target);
Instruction new_srl(enum RegisterName target);
Instruction new_rr(enum RegisterName target);
Instruction new_rl(enum RegisterName target);
Instruction new_rrc(enum RegisterName target);
Instruction new_rlc(enum RegisterName target);
Instruction new_sra(enum RegisterName target);
Instruction new_sla(enum RegisterName target);
Instruction new_swap(enum RegisterName target);

/* Jump Instructions */
Instruction new_jp(enum JumpCondition jump_cond);
Instruction new_jphl(void);
// Instruction new_jr(enum JumpCondition jump_cond);

/* Load Instructions */
Instruction new_ld(enum LoadOperand ld_target, enum LoadOperand ld_source);
Instruction new_ldh(enum LoadOperand ld_target, enum LoadOperand ld_source);

/* Stack Instructions */
Instruction new_push(enum RegisterName target);
Instruction new_pop(enum RegisterName target);

/* Call and Return Instructions */
Instruction new_call(enum JumpCondition jump_cond);
Instruction new_ret(enum JumpCondition jump_cond);
// Instruction new_reti(enum JumpCondition jump_cond);
