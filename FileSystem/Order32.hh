#ifndef Deuterium_Filesystem_Order32_hh
#define Deuterium_Filesystem_Order32_hh
/** \file Order32.hh
    \author Kevin Wierman
    \brief Utilites to detect machine endianness.

    \usage The macro 032_HOST_ORDER returns the endian-ness of the machine.
           Values are defined for return values for machine endian-ness, and
           these can be used for detection.

           Example:
           ~~~
           switch(032_HOST_ORDER){
               case(O32_LITTLE_ENDIAN):
               ...
               break;
               case(O32_BIG_ENDIAN):
               ...
               break;
               case(O32_PDP_ENDIAN):
               ...
               break;
               default:
                throw logic_error("Cannot Detect Machine Endian-Ness");
                return;
           }
           ~~~
           
**/



#include <limits.h>
#include <stdint.h>

#if CHAR_BIT != 8
#error "unsupported char size"
#endif

enum
{
    O32_LITTLE_ENDIAN = 0x03020100ul,
    O32_BIG_ENDIAN = 0x00010203ul,
    O32_PDP_ENDIAN = 0x01000302ul
};

static const union {
  unsigned char bytes[4];
  uint32_t value;
} o32_host_order = { { 0, 1, 2, 3 } };

#define O32_HOST_ORDER (o32_host_order.value)

#endif
