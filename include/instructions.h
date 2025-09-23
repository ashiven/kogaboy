#include <stdint.h>

#define NOT_FOUND_INST {0, 0, 0, 0, 0}

// TODO: JR, LD_SP, EI, DI, HALT, RST...
enum InstructionKind {  // NOLINT
    /* Arithmetic Instructions */
    ADD,    /*Add target to register A*/
    ADD_HL, /*Add 16-bit target to register HL*/
    ADD_IND,
    ADD_D8,
    ADC, /*Add target and value of carry flag to register A*/
    ADC_IND,
    ADC_D8,
    SUB, /*Subtract target from register A*/
    SUB_IND,
    SUB_D8,
    SBC, /*Subtract target and carry flag from register A*/
    SBC_IND,
    SBC_D8,
    AND, /*Bitwise AND between target and register A*/
    AND_IND,
    AND_D8,
    OR, /*Bitwise OR between target and register A*/
    OR_IND,
    OR_D8,
    XOR, /*Bitwise XOR between target and register A*/
    XOR_IND,
    XOR_D8,
    CP, /*Subtract without storing the result in A*/
    CP_IND,
    CP_D8,
    INC, /*Increment the value in target by 1*/
    INC_IND,
    DEC, /*Decrement the value in target by 1*/
    DEC_IND,
    CCF,  /*Toggle value of the carry flag*/
    SCF,  /*Set carry flag to true*/
    RRA,  /*Bit rotate right register A through carry flag*/
    RLA,  /*Bit rotate left register A through carry flag*/
    RRCA, /*Bit rotate right register A and set carry flag*/
    RLCA, /*Bit rotate left register A and set carry flag*/
    CPL,  /*Toggle every bit of the A register*/

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
    JP,    /*Conditionally jump to a 16-bit address*/
    JP_HL, /*Conditionally jump to the address in register HL*/
    JR,    /*Conditionally jump to program counter adjusted by an 8-bit signed integer*/

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

    /* No Op Instruction */
    NOP /*Do nothing*/
};

enum JumpCondition {  // NOLINT
    NOT_ZERO,
    ZERO,
    NOT_CARRY,
    CARRY,
    ALWAYS,
};

// NOTE: Make sure that the order of the registers matches that in
// enum Operand so we can use them interchangeably to refer to registers.
// (Remember that the underlying type of an enum is simply an integer)
enum Operand {  // NOLINT
    O_A,
    O_B,
    O_C,
    O_D,
    O_E,
    O_F,
    O_H,
    O_L,
    O_AF,
    O_BC,
    O_DE,
    O_HL,
    O_SP,
    O_C_IND,
    O_BC_IND,
    O_DE_IND,
    O_HL_IND,
    O_HL_INC_IND,
    O_HL_DEC_IND,
    O_D8,
    O_D16,
    O_A8_IND,
    O_A16_IND,
};

// TODO: embed generic Instruction inside of specific
// instructions like: ArithInstr, PrefixInstr, JumpInstr, LoadInstr ...
typedef struct {
    enum InstructionKind kind;

    /* Prefix Instructions */
    uint8_t bit_index;

    /* Jump Instructions */
    enum JumpCondition jump_cond;

    /* Load Instructions */
    enum Operand target;
    enum Operand source;
} Instruction;

/* Instruction Decoding */
Instruction inst_from_byte(uint8_t byte);
Instruction pf_inst_from_byte(uint8_t byte);

/* Arithmetic Instructions */
Instruction new_add(enum Operand source);
Instruction new_adc(enum Operand source);
Instruction new_sub(enum Operand source);
Instruction new_sbc(enum Operand source);
Instruction new_and(enum Operand source);
Instruction new_or(enum Operand source);
Instruction new_xor(enum Operand source);
Instruction new_cp(enum Operand source);
Instruction new_inc(enum Operand target);
Instruction new_dec(enum Operand target);
Instruction new_ccf(void);
Instruction new_scf(void);
Instruction new_rra(void);
Instruction new_rla(void);
Instruction new_rrca(void);
Instruction new_rlca(void);
Instruction new_cpl(void);

/* Prefix Instructions - Bits, Shifts, and Rotations */
Instruction new_bit(uint8_t bit_index, enum Operand target);
Instruction new_reset(uint8_t bit_index, enum Operand target);
Instruction new_set(uint8_t bit_index, enum Operand target);
Instruction new_srl(enum Operand target);
Instruction new_rr(enum Operand target);
Instruction new_rl(enum Operand target);
Instruction new_rrc(enum Operand target);
Instruction new_rlc(enum Operand target);
Instruction new_sra(enum Operand target);
Instruction new_sla(enum Operand target);
Instruction new_swap(enum Operand target);

/* Jump Instructions */
Instruction new_jp(enum JumpCondition jump_cond);
Instruction new_jp_hl(void);
Instruction new_jr(enum JumpCondition jump_cond);

/* Load Instructions */
Instruction new_ld(enum Operand target, enum Operand source);
Instruction new_ldh(enum Operand target, enum Operand source);

/* Stack Instructions */
Instruction new_push(enum Operand source);
Instruction new_pop(enum Operand target);

/* Call and Return Instructions */
Instruction new_call(enum JumpCondition jump_cond);
Instruction new_ret(enum JumpCondition jump_cond);
// Instruction new_reti(enum JumpCondition jump_cond);

/* No Op Instruction */
Instruction new_nop(void);
