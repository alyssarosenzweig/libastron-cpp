#ifndef __DVALUE_HPP_
#define __DVALUE_HPP_

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
  d_string,
};

enum DVHighType {
  dh_uint,
  dh_int,
  dh_string
};

typedef struct {
  DVType d_type;
  DVHighType d_hightype;
  union {
    uint64_t v_uint;
    int64_t v_int;
    char* v_string;
  };
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

DValue init_dstring(char* str) DValue_init_generic(d_string, dh_string, v_string, str)
DValue init_duint8(uint8_t v) DValue_init_generic(d_uint8, dh_uint, v_uint, v)
DValue init_duint16(uint16_t v) DValue_init_generic(d_uint16, dh_uint, v_uint, v)
DValue init_duint32(uint32_t v) DValue_init_generic(d_uint32, dh_uint, v_uint, v)
DValue init_duint64(uint64_t v) DValue_init_generic(d_uint64, dh_uint, v_uint, v)
DValue init_dint8(int8_t v) DValue_init_generic(d_int8, dh_int, v_int, v)
DValue init_dint16(int16_t v) DValue_init_generic(d_int16, dh_int, v_int, v)
DValue init_dint32(int32_t v) DValue_init_generic(d_int32, dh_int, v_int, v)
DValue init_dint64(int64_t v) DValue_init_generic(d_int64, dh_int, v_int, v)

// debug stub
void dprint(DValue v) {
       if(v.d_hightype == dh_int) printf("%ld\n", v.v_int);
  else if(v.d_hightype == dh_uint) printf("%lu\n", v.v_uint);
  else if(v.d_hightype == dh_string) printf("%s\n", v.v_string);
  else printf("Cannot print DValue of hightype %d\n", v.d_hightype);
}

#endif
