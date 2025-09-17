#include <stdbool.h>
#include <stdint.h>

#define ZERO_BIT_POS 7
#define SUBTRACT_BIT_POS 6
#define HALF_CARRY_BIT_POS 5
#define CARRY_BIT_POS 4

// TODO: PC
enum RegisterName { A, B, C, D, E, F, H, L, AF, BC, DE, HL, SP };  // NOLINT

const char *reg_name(enum RegisterName reg);

typedef struct {
    uint8_t a;
    uint8_t b;
    uint8_t c;
    uint8_t d;
    uint8_t e;
    uint8_t f;
    uint8_t h;
    uint8_t l;
} Registers;

Registers new_regs(void);

uint16_t get_af(const Registers *regs);
void set_af(Registers *regs, uint16_t val);

uint16_t get_bc(const Registers *regs);
void set_bc(Registers *regs, uint16_t val);

uint16_t get_de(const Registers *regs);
void set_de(Registers *regs, uint16_t val);

uint16_t get_hl(const Registers *regs);
void set_hl(Registers *regs, uint16_t val);

typedef struct {
    bool zero;
    bool subtract;
    bool half_carry;
    bool carry;
} FlagRegister;

FlagRegister new_flag_reg(void);

uint8_t flag_reg_to_byte(FlagRegister *flag_reg);

FlagRegister byte_to_flag_reg(uint8_t byte);

uint8_t get_zero(FlagRegister *flag_reg);
uint8_t get_subtract(FlagRegister *flag_reg);
uint8_t get_half_carry(FlagRegister *flag_reg);
uint8_t get_carry(FlagRegister *flag_reg);
