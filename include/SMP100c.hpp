#ifndef SMP100C_HPP
	#define SMP100C_HPP
	
	#include <SDL_thread.h>
	#include <SDL_mutex.h>
	
	#include "stupidVM.hpp"
	#include "stupidVM_SDL.hpp"
	#include "peripheral.hpp"
	#include "SMP100.hpp"
	
	class SMP100c {
		public:
			SMP100c (U16 ClockRate, U16 RAM);
			~SMP100c (void);
			void PeripheralFunc (PeripheralBus *bus);
			
			//"private"
			SMP100 *SMP;
			SDL_Thread *Thread;
			SDL_mutex *Halt;
			U16 RAMMask;
			U8 *RAM;
			Timer *timer;
			bool CleanupSig = false;
	};
#endif