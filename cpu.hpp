#include <stdint.h>
#define READ 1
#define WRITE 0
typedef uint_fast16_t Address;
typedef uint_fast8_t Word;
class SMP100 {
	
	public:
		struct Pair {
			Address addr;
			Word byte;
			bool RW;
		};
		
		struct Pair Bus;
		
		void SignalInt (short ID);
		void SignalReset (Address PrgStart);
		
		void Cycle (void);
		
		// "private" (needed public for the callbacks and stuff)
		struct {
			uint_fast16_t A;
			uint_fast16_t B;
			bool C;
			uint_fast32_t M;
			
			bool Carry;
			uint_fast32_t PC;
			uint_fast16_t IntRet;
			uint_fast8_t StackPtr;
			
			uint_fast8_t IStor;
			uint_fast16_t IStor2;
		} Reg;
		
		typedef void (* OpFunc) (SMP100 *);
		OpFunc Operation == NULL;
		
		static const OpFunc OpFuncs [];
		OpFunc LastOpFunc;
};
	

void SMP100::Cycle (void) {
	if (++ Operation == NULL)
		Operation = &Op_BeginCycle;
	
	Operation (this);
	
	if (Reg.A > 0xFF) {
		Reg.A &= 0xFF;
		Reg.Carry |= true;
	}
	if (Reg.B > 0xFF) {
		Reg.B &= 0xFF;
		Reg.Carry |= true;
	}
	if (Reg.M > 0xFFFF) {
		Reg.M &= 0xFFFF;
		Reg.Carry |= true;
	}
	if (Reg.PC > 0xFFFF) {
		Reg.PC &= 0xFFFF;
		Reg.Carry |= true;
	}
	if (Reg.StackPtr > 0xFF) {
		Reg.StackPtr &= 0xFF;
		Reg.Carry |= true;
	}
}
