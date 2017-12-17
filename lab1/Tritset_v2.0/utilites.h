#pragma once
#ifndef TRITSET_V2_UTILITES_H
#define TRITSET_V2_UTILITES_H

typedef unsigned int uint;

enum Trit_num { Unknown = 0, False = 1, True = 2 };

const uint BYTE_SIZE = 8;
const uint TRIT_SIZE = 2;

void assign(uint* arr, uint size);

template <unsigned long N>
  struct binary
  {
	       static unsigned const value
		 = binary<N / 10>::value << 1   // prepend higher bits
		 | N % 10;                    // to lowest bit
	   };

   template <>                           // specialization
struct binary<0>                      // terminates recursion
{
	 static unsigned const value = 0;
};
unsigned const three = binary<11>::value;

#endif //TRITSET_V2_UTILITES_H