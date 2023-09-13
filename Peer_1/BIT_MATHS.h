// file guard

#ifndef BIT_MATHS__H_
#define BIT_MATHS__H_


// bit masking -> functions like macros
#define SET_BIT(Var, Bit_No)	(Var |= (1 << Bit_No))
#define CLR_BIT(Var, Bit_No)	(Var &= ~(1 << Bit_No))
#define TOG_BIT(Var, Bit_No)	(Var ^= (1 << Bit_No))
#define GET_BIT(Var, Bit_No)	((Var >> Bit_No) & 1)


#endif
