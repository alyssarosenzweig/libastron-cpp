#ifndef __DVALUE_HPP_
#define __DVALUE_HPP_

#include <stdio.h>
#include <iostream>
#include <stdint.h>

// DValue provides a general purpose, Distributed Value type
// (typedef, struct, union, and basic OOP magic)

enum DVType {
  d_uint8,
  d_uint16,
  d_uint32,
  d_uint64,
  d_int8,
  d_int16,
  d_int32,
  d_int64,
  d_float32,
  d_string,
};

enum DVHighType {
  dh_uint,
  dh_int,
  dh_string,
  dh_double,
};

typedef struct {
  DVType d_type;
  DVHighType d_hightype;
  union {
    uint64_t v_uint;
    int64_t v_int;
    double v_double;
  };

  // TODO: optimize not having a huge string in here
  std::string v_string; // declared out of the union due to compiler internals
} DValue;

// generic constructor method for DValue

#define DValue_init_generic(typename, hightypename, valuefield, value) \
      { \
        DValue ret; \
        ret.d_type = typename; \
        ret.d_hightype = hightypename; \
        ret.valuefield = value; \
        return ret; \
      }

// type constructor table. pile of macros. deal with it

#define $(fancyStr) dstring(fancyStr)
DValue dstring(std::string str);
DValue duint8(uint8_t v);
DValue duint16(uint16_t v);
DValue duint32(uint32_t v);
DValue duint64(uint64_t v);
DValue dint8(int8_t v);
DValue dint16(int16_t v);
DValue dint32(int32_t v);
DValue dint64(int64_t v);
DValue dfloat32(float v);

// typeless printf, basically
void dprint(DValue v);

#endif
