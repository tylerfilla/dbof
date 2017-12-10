/*
 * DBOF
 * Copyright 2017 glyre
 */

#ifndef DBOF_DBOF_H
#define DBOF_DBOF_H

#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * The canonical set of all object types defined in the DBOF specification.
 */
typedef enum
{
    DBOF_TYPE_NULL,
    DBOF_TYPE_SIGNED_BYTE,
    DBOF_TYPE_UNSIGNED_BYTE,
    DBOF_TYPE_SIGNED_INTEGER,
    DBOF_TYPE_UNSIGNED_INTEGER,
    DBOF_TYPE_SIGNED_LONG_INTEGER,
    DBOF_TYPE_UNSIGNED_LONG_INTEGER,
    DBOF_TYPE_BOOLEAN,
    DBOF_TYPE_SINGLE_FLOAT,
    DBOF_TYPE_DOUBLE_FLOAT,
    DBOF_TYPE_CHARACTER,
    DBOF_TYPE_UTF8_STRING,
    DBOF_TYPE_TYPED_ARRAY,
    DBOF_TYPE_UNTYPED_ARRAY,
    DBOF_TYPE_TYPED_MAP,
    DBOF_TYPE_UNTYPED_MAP
} dbof_type;

//
// Short name aliases for canonical types
//

#define DBOF_TYPE_BYTE      DBOF_TYPE_SIGNED_BYTE
#define DBOF_TYPE_UBYTE     DBOF_TYPE_UNSIGNED_BYTE
#define DBOF_TYPE_INT       DBOF_TYPE_SIGNED_INTEGER
#define DBOF_TYPE_UINT      DBOF_TYPE_UNSIGNED_INTEGER
#define DBOF_TYPE_LONG      DBOF_TYPE_SIGNED_LONG_INTEGER
#define DBOF_TYPE_ULONG     DBOF_TYPE_UNSIGNED_LONG_INTEGER
#define DBOF_TYPE_BOOL      DBOF_TYPE_BOOLEAN
#define DBOF_TYPE_FLOAT     DBOF_TYPE_SINGLE_FLOAT
#define DBOF_TYPE_DOUBLE    DBOF_TYPE_DOUBLE_FLOAT
#define DBOF_TYPE_CHAR      DBOF_TYPE_CHARACTER
#define DBOF_TYPE_STRING    DBOF_TYPE_UTF8_STRING
#define DBOF_TYPE_ARRAY     DBOF_TYPE_TYPED_ARRAY
#define DBOF_TYPE_UARRAY    DBOF_TYPE_UNTYPED_ARRAY
#define DBOF_TYPE_MAP       DBOF_TYPE_TYPED_MAP
#define DBOF_TYPE_UMAP      DBOF_TYPE_UNTYPED_MAP

//
// Object types
//

/**
 * The base type for all in-memory DBOF objects.
 */
typedef void* dbof_object;

/**
 * The null value object type (type ID 0).
 */
typedef dbof_object dbof_object_null;

/**
 * The signed byte value object type (type ID 1).
 */
typedef dbof_object dbof_object_signed_byte;

/**
 * The unsigned byte value object type (type ID 2).
 */
typedef dbof_object dbof_object_unsigned_byte;

/**
 * The signed integer value object type (type ID 3).
 */
typedef dbof_object dbof_object_signed_integer;

/**
 * The unsigned integer value object type (type ID 4).
 */
typedef dbof_object dbof_object_unsigned_integer;

/**
 * The signed long integer value object type (type ID 5).
 */
typedef dbof_object dbof_object_signed_long_integer;

/**
 * The unsigned long integer value object type (type ID 6).
 */
typedef dbof_object dbof_object_unsigned_long_integer;

/**
 * The Boolean value object type (type ID 7).
 */
typedef dbof_object dbof_object_boolean;

/**
 * The single-precision floating point number value object type (type ID 8).
 */
typedef dbof_object dbof_object_single_float;

/**
 * The double-precision floating point number value object type (type ID 9).
 */
typedef dbof_object dbof_object_double_float;

/**
 * The Unicode character codepoint value object type (type ID 10).
 */
typedef dbof_object dbof_object_character;

/**
 * The UTF-8 string value object type (type ID 11).
 */
typedef dbof_object dbof_object_utf8_string;

/**
 * The typed array container object type (type ID 128).
 */
typedef dbof_object dbof_object_typed_array;

/**
 * The untyped array container object type (type ID 129).
 */
typedef dbof_object dbof_object_untyped_array;

/**
 * The typed map container object type (type ID 130).
 */
typedef dbof_object dbof_object_typed_map;

/**
 * The untyped map container object type (type ID 131).
 */
typedef dbof_object dbof_object_untyped_map;

//
// Short name aliases for object types
//

/** Alias for <code>dbof_object_signed_byte</code>. */
typedef dbof_object_signed_byte dbof_object_byte;

/** Alias for <code>dbof_object_unsigned_byte</code>. */
typedef dbof_object_unsigned_byte dbof_object_ubyte;

/** Alias for <code>dbof_object_signed_integer</code>. */
typedef dbof_object_signed_integer dbof_object_int;

/** Alias for <code>dbof_object_unsigned_integer</code>. */
typedef dbof_object_unsigned_integer dbof_object_uint;

/** Alias for <code>dbof_object_signed_long_integer</code>. */
typedef dbof_object_signed_long_integer dbof_object_long;

/** Alias for <code>dbof_object_unsigned_long_integer</code>. */
typedef dbof_object_unsigned_long_integer dbof_object_ulong;

/** Alias for <code>dbof_object_boolean</code>. */
typedef dbof_object_boolean dbof_object_bool;

/** Alias for <code>dbof_object_single_float</code>. */
typedef dbof_object_single_float dbof_object_float;

/** Alias for <code>dbof_object_double_float</code>. */
typedef dbof_object_double_float dbof_object_double;

/** Alias for <code>dbof_object_character</code>. */
typedef dbof_object_character dbof_object_char;

/** Alias for <code>dbof_object_utf8_string</code>. */
typedef dbof_object_utf8_string dbof_object_string;

/** The typed array container object type (type ID 128). */
typedef dbof_object_typed_array dbof_object_array;

/** The untyped array container object type (type ID 129). */
typedef dbof_object_untyped_array dbof_object_uarray;

/** The typed map container object type (type ID 130). */
typedef dbof_object_typed_map dbof_object_map;

/** The untyped map container object type (type ID 131). */
typedef dbof_object_untyped_map dbof_object_umap;

//
// Implementation-defined types for in-memory storage of value object values
//
// These are used as standardized types for use in the storage of value objects in-memory and for return values and
// parameters in accessor (getter/setter) and manipulation functions.
//

/**
 * The type for signed byte object values.
 */
typedef int8_t dbof_signed_byte;

/**
 * The type for unsigned byte object values.
 */
typedef uint8_t dbof_unsigned_byte;

/**
 * The type for signed integer object values.
 */
typedef int32_t dbof_signed_integer;

/**
 * The type for unsigned integer object values.
 */
typedef uint32_t dbof_unsigned_integer;

/**
 * The type for signed long integer object values.
 */
typedef int64_t dbof_signed_long_integer;

/**
 * The type for unsigned long integer object values.
 */
typedef uint64_t dbof_unsigned_long_integer;

/**
 * The type for Boolean object values.
 */
typedef uint8_t dbof_boolean;

/**
 * The type for single-precision floating point number object values.
 */
typedef float dbof_single_float;

/**
 * The type for double-precision floating point number object values.
 */
typedef double dbof_double_float;

/**
 * The type for Unicode character codepoint object values.
 */
typedef uint32_t dbof_character;

/**
 * The type for UTF-8 string object values.
 */
typedef const char* dbof_utf8_string;

//
// Short name aliases for value object value types
//

/** Alias for <code>dbof_signed_byte</code>. */
typedef dbof_signed_byte dbof_byte;

/** Alias for <code>dbof_unsigned_byte</code>. */
typedef dbof_unsigned_byte dbof_ubyte;

/** Alias for <code>dbof_signed_integer</code>. */
typedef dbof_signed_integer dbof_int;

/** Alias for <code>dbof_unsigned_integer</code>. */
typedef dbof_unsigned_integer dbof_uint;

/** Alias for <code>dbof_signed_long_integer</code>. */
typedef dbof_signed_long_integer dbof_long;

/** Alias for <code>dbof_unsigned_long_integer</code>. */
typedef dbof_unsigned_long_integer dbof_ulong;

/** Alias for <code>dbof_boolean</code>. */
typedef dbof_boolean dbof_bool;

/** Alias for <code>dbof_single_float</code>. */
typedef dbof_single_float dbof_float;

/** Alias for <code>dbof_double_float</code>. */
typedef dbof_double_float dbof_double;

/** Alias for <code>dbof_character</code>. */
typedef dbof_character dbof_char;

/** Alias for <code>dbof_utf8_string</code>. */
typedef dbof_utf8_string dbof_string;

/**
 * Implementation detail. The type for sizes of strings.
 */
typedef size_t dbof_string_size;

/**
 * Implementation detail. The type for sizes of containers (arrays and maps).
 */
typedef size_t dbof_container_size;

//
// Type functions
//

/**
 * Determine if an object type is of the value category.
 *
 * @param type The object type
 * @return Nonzero if such is the case, zero otherwise
 */
int dbof_is_value_type(dbof_type type)
{
    switch (type)
    {
    case DBOF_TYPE_NULL:
    case DBOF_TYPE_SIGNED_BYTE:
    case DBOF_TYPE_UNSIGNED_BYTE:
    case DBOF_TYPE_SIGNED_INTEGER:
    case DBOF_TYPE_UNSIGNED_INTEGER:
    case DBOF_TYPE_SIGNED_LONG_INTEGER:
    case DBOF_TYPE_UNSIGNED_LONG_INTEGER:
    case DBOF_TYPE_BOOLEAN:
    case DBOF_TYPE_SINGLE_FLOAT:
    case DBOF_TYPE_DOUBLE_FLOAT:
    case DBOF_TYPE_CHARACTER:
    case DBOF_TYPE_UTF8_STRING:
        return 1;
    case DBOF_TYPE_TYPED_ARRAY:
    case DBOF_TYPE_UNTYPED_ARRAY:
    case DBOF_TYPE_TYPED_MAP:
    case DBOF_TYPE_UNTYPED_MAP:
    default:
        return 0;
    }
}

/**
 * Determine if an object type is of the container category.
 *
 * @param type The object type
 * @return Nonzero if such is the case, zero otherwise
 */
int dbof_is_container_type(dbof_type type)
{
    switch (type)
    {
    case DBOF_TYPE_TYPED_ARRAY:
    case DBOF_TYPE_UNTYPED_ARRAY:
    case DBOF_TYPE_TYPED_MAP:
    case DBOF_TYPE_UNTYPED_MAP:
        return 1;
    case DBOF_TYPE_NULL:
    case DBOF_TYPE_SIGNED_BYTE:
    case DBOF_TYPE_UNSIGNED_BYTE:
    case DBOF_TYPE_SIGNED_INTEGER:
    case DBOF_TYPE_UNSIGNED_INTEGER:
    case DBOF_TYPE_SIGNED_LONG_INTEGER:
    case DBOF_TYPE_UNSIGNED_LONG_INTEGER:
    case DBOF_TYPE_BOOLEAN:
    case DBOF_TYPE_SINGLE_FLOAT:
    case DBOF_TYPE_DOUBLE_FLOAT:
    case DBOF_TYPE_CHARACTER:
    case DBOF_TYPE_UTF8_STRING:
    default:
        return 0;
    }
}

/**
 * Get the type of an object.
 *
 * @param object The object in question
 * @return The object type
 */
extern dbof_type dbof_typeof(dbof_object object);

/**
 * Test if an object is of a given type.
 *
 * @param object The object
 * @param type The object type
 * @return Nonzero if such is the case, zero otherwise
 */
inline int dbof_is(dbof_object object, dbof_type type)
{
    return dbof_typeof(object) == type;
}

/**
 * Test if two objects are of the same type.
 *
 * @param a The first object
 * @param b The second object
 * @return Nonzero if such is the case, zero otherwise
 */
inline int dbof_same_type(dbof_object a, dbof_object b)
{
    return dbof_typeof(a) == dbof_typeof(b);
}

/**
 * Test if two objects are of types of the same category.
 *
 * @param a The first object
 * @param b The second object
 * @return Nonzero if such is the case, zero otherwise
 */
int dbof_same_category(dbof_object a, dbof_object b)
{
    dbof_type type_a = dbof_typeof(a);
    dbof_type type_b = dbof_typeof(b);

    if (dbof_is_value_type(type_a) && dbof_is_value_type(type_b))
    {
        return 1;
    }
    if (dbof_is_container_type(type_a) && dbof_is_container_type(type_b))
    {
        return 1;
    }

    return 0;
}

//
// Object core functions
//

/**
 * A set of functionality-intercepting hooks.
 */
typedef void* dbof_hooks;

/**
 * Parameters for new object creation.
 */
typedef struct
{
    dbof_hooks hooks;
} dbof_new_ex_params;

/**
 * Create a new DBOF object of the given type.
 *
 * @param type The object type
 * @return The object
 */
extern dbof_object dbof_new(dbof_type type);

/**
 * Create a new DBOF object of the given type with the given parameters.
 *
 * @param type The object type
 * @param params Object creation parameters
 * @return The object
 */
extern dbof_object dbof_new_ex(dbof_type type, dbof_new_ex_params* params);

/**
 * Delete a DBOF object.
 *
 * Calling dbof_delete(NULL) has no effect.
 *
 * @param object The object
 */
extern void dbof_delete(dbof_object object);

/**
 * Calculate the hash code of a given object.
 *
 * Some rules apply for two objects A and B. Let H(A) mean dbof_hashcode(A), H(B) mean dbof_hashcode(B), and E(A, B)
 * mean dbof_equals(A, B).
 * <ul>
 * <li>If E(A, B), then H(A) == H(B).</li>
 * <li>If A and/or B change such that E(A, B) == false, H(A) != H(B).</li>
 * </ul>
 *
 * The result of this function is not guaranteed to be consistent across architectures, compilers, or even between two
 * running copies of the library.
 *
 * Calling dbof_hashcode(NULL) will return 0, but this is a valid hash code for non-null inputs as well.
 *
 * @param object The object
 * @return The hash code
 */
extern int dbof_hash(dbof_object object);

/**
 * Test if two objects are equal.
 *
 * @param a The first object
 * @param b The second object
 * @return Nonzero if the objects are equal, zero otherwise
 */
extern int dbof_equals(dbof_object a, dbof_object b);

//
// Object manipulation functions
//

/**
 * Get the value of a signed byte object.
 *
 * @param object The object
 * @return The value
 */
extern dbof_signed_byte dbof_get_value_signed_byte(dbof_object_signed_byte object);

/** Alias for <code>dbof_get_value_signed_byte(object)</code>. */
inline dbof_byte dbof_get_value_byte(dbof_object_byte object)
{ return dbof_get_value_signed_byte(object); }

/**
 * Set the value of a signed byte object.
 *
 * @param object The object
 * @param value The value
 */
extern void dbof_set_value_signed_byte(dbof_object_signed_byte object, dbof_signed_byte value);

/** Alias for <code>dbof_set_value_signed_byte(object, value)</code>. */
inline void dbof_set_value_byte(dbof_object_byte object, dbof_byte value)
{ dbof_set_value_signed_byte(object, value); }

/**
 * Get the value of an unsigned byte object.
 *
 * @param object The object
 * @return The value
 */
extern dbof_unsigned_byte dbof_get_value_unsigned_byte(dbof_object_unsigned_byte object);

/** Alias for <code>dbof_get_value_unsigned_byte(object)</code>. */
inline dbof_ubyte dbof_get_value_ubyte(dbof_object_ubyte object)
{ return dbof_get_value_unsigned_byte(object); }

/**
 * Set the value of an unsigned byte object.
 *
 * @param object The object
 * @param value The value
 */
extern void dbof_set_value_unsigned_byte(dbof_object_unsigned_byte object, dbof_unsigned_byte value);

/** Alias for <code>dbof_set_value_unsigned_byte(object, value)</code>. */
inline void dbof_set_value_ubyte(dbof_object_ubyte object, dbof_ubyte value)
{ dbof_set_value_unsigned_byte(object, value); }

/**
 * Get the value of a signed integer object.
 *
 * @param object The object
 * @return The value
 */
extern dbof_signed_integer dbof_get_value_signed_integer(dbof_object_signed_integer object);

/** Alias for <code>dbof_get_value_signed_integer(object)</code>. */
inline dbof_int dbof_get_value_int(dbof_object_int object)
{ return dbof_get_value_signed_integer(object); }

/**
 * Set the value of a signed integer object.
 *
 * @param object The object
 * @param value The value
 */
extern void dbof_set_value_signed_integer(dbof_object_signed_integer object, dbof_signed_integer value);

/** Alias for <code>dbof_set_value_signed_integer(object, value)</code>. */
inline void dbof_set_value_int(dbof_object_int object, dbof_int value)
{ dbof_set_value_signed_integer(object, value); }

/**
 * Get the value of an unsigned integer object.
 *
 * @param object The object
 * @return The value
 */
extern dbof_unsigned_integer dbof_get_value_unsigned_integer(dbof_object_unsigned_integer object);

/** Alias for <code>dbof_get_value_unsigned_integer(object)</code>. */
inline dbof_uint dbof_get_value_uint(dbof_object_uint object)
{ return dbof_get_value_unsigned_integer(object); }

/**
 * Set the value of an unsigned integer object.
 *
 * @param object The object
 * @param value The value
 */
extern void dbof_set_value_unsigned_integer(dbof_object_unsigned_integer object, dbof_unsigned_integer value);

/** Alias for <code>dbof_set_value_unsigned_integer(object, value)</code>. */
inline void dbof_set_value_uint(dbof_object_uint object, dbof_uint value)
{ dbof_set_value_unsigned_integer(object, value); }

/**
 * Get the value of a signed long integer object.
 *
 * @param object The object
 * @return The value
 */
extern dbof_signed_long_integer dbof_get_value_signed_long_integer(dbof_object_signed_long_integer object);

/** Alias for <code>dbof_get_value_signed_long_integer(object)</code>. */
inline dbof_long dbof_get_value_long(dbof_object_long object)
{ return dbof_get_value_signed_long_integer(object); }

/**
 * Set the value of a signed long integer object.
 *
 * @param object The object
 * @param value The value
 */
extern void dbof_set_value_signed_long_integer(dbof_object_signed_long_integer object, dbof_signed_long_integer value);

/** Alias for <code>dbof_set_value_signed_long_integer(object, value)</code>. */
inline void dbof_set_value_long(dbof_object_long object, dbof_long value)
{ dbof_set_value_signed_long_integer(object, value); }

/**
 * Get the value of an unsigned long integer object.
 *
 * @param object The object
 * @return The value
 */
extern dbof_unsigned_long_integer dbof_get_value_unsigned_long_integer(dbof_object_unsigned_long_integer object);

/** Alias for <code>dbof_get_value_unsigned_long_integer(object)</code>. */
inline dbof_ulong dbof_get_value_ulong(dbof_object_ulong object)
{ return dbof_get_value_unsigned_long_integer(object); }

/**
 * Set the value of an unsigned long integer object.
 *
 * @param object The object
 * @param value The value
 */
extern void dbof_set_value_unsigned_long_integer(dbof_object_unsigned_long_integer object,
        dbof_unsigned_long_integer value);

/** Alias for <code>dbof_set_value_unsigned_long_integer(object, value)</code>. */
inline void dbof_set_value_ulong(dbof_object_ulong object, dbof_ulong value)
{ dbof_set_value_unsigned_long_integer(object, value); }

/**
 * Get the value of a Boolean object.
 *
 * @param object The object
 * @return The value
 */
extern dbof_boolean dbof_get_value_boolean(dbof_object_boolean object);

/** Alias for <code>dbof_get_value_boolean(object)</code>. */
inline dbof_bool dbof_get_value_bool(dbof_object_bool object)
{ return dbof_get_value_boolean(object); }

/**
 * Set the value of a Boolean object.
 *
 * @param object The object
 * @param value The value
 */
extern void dbof_set_value_boolean(dbof_object_boolean object, dbof_boolean value);

/** Alias for <code>dbof_set_value_boolean(object, value)</code>. */
inline void dbof_set_value_bool(dbof_object_bool object, dbof_bool value)
{ dbof_set_value_boolean(object, value); }

/**
 * Get the value of a single float object.
 *
 * @param object The object
 * @return The value
 */
extern dbof_single_float dbof_get_value_single_float(dbof_object_single_float object);

/** Alias for <code>dbof_get_value_single_float(object)</code>. */
inline dbof_float dbof_get_value_float(dbof_object_float object)
{ return dbof_get_value_single_float(object); }

/**
 * Set the value of a single float object.
 *
 * @param object The object
 * @param value The value
 */
extern void dbof_set_value_single_float(dbof_object_single_float object, dbof_single_float value);

/** Alias for <code>dbof_set_value_single_float(object, value)</code>. */
inline void dbof_set_value_float(dbof_object_float object, dbof_float value)
{ dbof_set_value_single_float(object, value); }

/**
 * Get the value of a double float object.
 *
 * @param object The object
 * @return The value
 */
extern dbof_double_float dbof_get_value_double_float(dbof_object_double_float object);

/** Alias for <code>dbof_get_value_double_float(object)</code>. */
inline dbof_double dbof_get_value_double(dbof_object_double object)
{ return dbof_get_value_double_float(object); }

/**
 * Set the value of a double float object.
 *
 * @param object The object
 * @param value The value
 */
extern void dbof_set_value_double_float(dbof_object_double_float object, dbof_double_float value);

/** Alias for <code>dbof_set_value_double_float(object, value)</code>. */
inline void dbof_set_value_double(dbof_object_double object, dbof_double value)
{ dbof_set_value_double_float(object, value); }

/**
 * Get the value of a character object.
 *
 * @param object The object
 * @return The value
 */
extern dbof_character dbof_get_value_character(dbof_object_character object);

/** Alias for <code>dbof_get_value_character(code)</code>. */
inline dbof_char dbof_get_value_char(dbof_object_char object)
{ return dbof_get_value_character(object); }

/**
 * Set the value of a character object.
 *
 * @param object The object
 * @param value The value
 */
extern void dbof_set_value_character(dbof_object_character object, dbof_character value);

/** Alias for <code>dbof_set_value_character(object, value)</code>. */
inline void dbof_set_value_char(dbof_object_char object, dbof_char value)
{ dbof_set_value_character(object, value); }

/**
 * Get the value of a UTF-8 string object.
 *
 * @param object The object
 * @return The value
 */
extern dbof_utf8_string dbof_get_value_utf8_string(dbof_object_utf8_string object);

/** Alias for <code>dbof_get_value_utf8_string(object)</code>. */
inline dbof_string dbof_get_value_string(dbof_object_string object)
{ return dbof_get_value_utf8_string(object); }

/**
 * Set the value of a UTF-8 string object.
 *
 * @param object The object
 * @param value The value
 */
extern void dbof_set_value_utf8_string(dbof_object_utf8_string object, dbof_utf8_string value);

/** Alias for <code>dbof_set_value_utf8_string(object, value)</code>. */
inline void dbof_set_value_string(dbof_object_string object, const dbof_string value)
{ dbof_set_value_utf8_string(object, value); }

/**
 * Get the capacity of a typed array.
 *
 * @param array The typed array
 * @return Its capacity
 */
extern dbof_container_size dbof_typed_array_get_capacity(dbof_object_typed_array array);

/** Alias for <code>dbof_typed_array_get_capacity(array)</code>. */
inline dbof_container_size dbof_array_get_capacity(dbof_object_array array)
{ return dbof_typed_array_get_capacity(array); }

/**
 * Get the size of a typed array.
 *
 * @param array The typed array
 * @return Its size
 */
extern dbof_container_size dbof_typed_array_get_size(dbof_object_typed_array array);

/** Alias for <code>dbof_typed_array_get_size(array)</code>. */
inline dbof_container_size dbof_array_get_size(dbof_object_array array)
{ return dbof_typed_array_get_size(array); }

/**
 * Determine if a typed array is empty.
 *
 * @param array The typed array
 * @return Nonzero if such is the case, otherwise zero
 */
extern int dbof_typed_array_is_empty(dbof_object_typed_array array);

/** Alias for <code>dbof_typed_array_is_empty(array)</code>. */
inline int dbof_array_is_empty(dbof_object_array array)
{ return dbof_typed_array_is_empty(array); }

/**
 * Get the type of a typed array.
 *
 * @param array The typed array
 * @return Its type
 */
extern dbof_type dbof_typed_array_get_type(dbof_object_typed_array array);

/** Alias for <code>dbof_typed_array_get_type(array)</code>. */
inline dbof_type dbof_array_get_type(dbof_object_array array)
{ return dbof_typed_array_get_type(array); }

/**
 * Set the type of a typed array. The array must be empty for this to take effect.
 *
 * @param array The typed array
 * @param type The new type
 */
extern void dbof_typed_array_set_type(dbof_object_typed_array array, dbof_type type);

/** Alias for <code>dbof_typed_array_set_type(array, type)</code>. */
inline void dbof_array_set_type(dbof_object_array array, dbof_type type)
{ dbof_typed_array_set_type(array, type); }

/**
 * Request that a typed array occupy as little space in memory as possible. This may increase the likelihood of a
 * reallocation on the next insertion.
 *
 * @param array The typed array
 */
extern void dbof_typed_array_shrink_to_fit(dbof_object_typed_array array);

/** Alias for <code>dbof_typed_array_shrink_to_fit(array)</code>. */
inline void dbof_array_shrink_to_fit(dbof_object_array array)
{ dbof_typed_array_shrink_to_fit(array); }

/**
 * Get an element of a typed array.
 *
 * This function does not perform bounds checking. It can only be used to modify nonempty arrays such that
 * <code>index</code> lies in the interval <code>[0, size)</code>, where <code>size > 0</code> is the current size of
 * the array.
 *
 * @param array The typed array
 * @param index The element index
 * @return The element
 */
extern dbof_object dbof_typed_array_get(dbof_object_typed_array array, dbof_container_size index);

/** Alias for <code>dbof_typed_array_get(array, index)</code>. */
inline dbof_object dbof_array_get(dbof_object_array array, dbof_container_size index)
{ return dbof_typed_array_get(array, index); }

/**
 * Set an element of a typed array.
 *
 * This function does not perform bounds checking. It can only be used to modify nonempty arrays such that
 * <code>index</code> lies in the interval <code>[0, size)</code>, where <code>size > 0</code> is the current size of
 * the array.
 *
 * Furthermore, the object must be of the type associated with the array.
 *
 * Warning: This function may overwrite a pointer to dynamically-allocated memory. It is your responsibility to know
 * what information is being overwritten. Use #dbof_typed_array_get(array, index) prior if this concerns you.
 *
 * @param array The typed array
 * @param index The element index
 * @param object The new element
 */
extern void dbof_typed_array_set(dbof_object_typed_array array, dbof_container_size index, dbof_object object);

/** Alias for <code>dbof_typed_array_set(array, index, object)</code>. */
inline void dbof_array_set(dbof_object_array array, dbof_container_size index, dbof_object object)
{ dbof_typed_array_set(array, index, object); }

/**
 * Insert an element to a typed array.
 *
 * The caller relinquishes ownership of the object's memory.
 *
 * @param array The typed array
 * @param index The target index
 * @param object The new object
 */
extern void dbof_typed_array_insert(dbof_object_typed_array array, dbof_container_size index, dbof_object object);

/** Alias for <code>dbof_typed_array_insert(array, index, object)</code>. */
inline void dbof_array_insert(dbof_object_array array, dbof_container_size index, dbof_object object)
{ dbof_typed_array_insert(array, index, object); }

/**
 * Remove an element from a typed array.
 *
 * The caller assumes ownership of the object's memory.
 *
 * @param array The untyped array
 * @param index The target index
 * @return The old object
 */
extern dbof_object dbof_typed_array_remove(dbof_object_typed_array array, dbof_container_size index);

/** Alias for <code>dbof_typed_array_remove</code>. */
inline dbof_object dbof_array_remove(dbof_object_array array, dbof_container_size index)
{ return dbof_typed_array_remove(array, index); }

/**
 * Add an object to the back of a typed array.
 *
 * @param array The typed array
 * @param object The new object
 */
extern void dbof_typed_array_push_back(dbof_object_typed_array array, dbof_object object);

/** Alias for <code>dbof_typed_array_push_back(array, object)</code>. */
inline void dbof_array_push(dbof_object_array array, dbof_object object)
{ dbof_typed_array_push_back(array, object); }

/**
 * Remove the last object from a typed array.
 *
 * @param array The typed array
 * @return The removed object
 */
extern dbof_object dbof_typed_array_pop_back(dbof_object_typed_array array);

/** Alias for <code>dbof_typed_array_pop_back(array)</code>. */
inline dbof_object dbof_array_pop(dbof_object_array array)
{ return dbof_typed_array_pop_back(array); }

/**
 * Get the capacity of an untyped array.
 *
 * @param array The untyped array
 * @return Its capacity
 */
extern dbof_container_size dbof_untyped_array_get_capacity(dbof_object_untyped_array array);

/** Alias for <code>dbof_untyped_array_get_capacity(array)</code>. */
inline dbof_container_size dbof_uarray_get_capacity(dbof_object_uarray array)
{ return dbof_untyped_array_get_capacity(array); }

/**
 * Get the size of an untyped array.
 *
 * @param array The untyped array
 * @return Its size
 */
extern dbof_container_size dbof_untyped_array_get_size(dbof_object_untyped_array array);

/** Alias for <code>dbof_untyped_array_get_size(array)</code>. */
inline dbof_container_size dbof_uarray_get_size(dbof_object_uarray array)
{ return dbof_untyped_array_get_size(array); }

/**
 * Determine if an untyped array is empty.
 *
 * @param map The untyped array
 * @return Nonzero if such is the case, otherwise zero
 */
extern int dbof_untyped_array_is_empty(dbof_object_untyped_array map);

/** Alias for <code>dbof_untyped_array_is_empty(array)</code>. */
inline int dbof_uarray_is_empty(dbof_object_uarray array)
{ return dbof_untyped_array_is_empty(array); }

/**
 * Request that an untyped array occupy as little space in memory as possible. This may increase the likelihood of a
 * reallocation on the next insertion.
 *
 * @param array The untyped array
 */
extern void dbof_untyped_array_shrink_to_fit(dbof_object_untyped_array array);

/** Alias for <code>dbof_untyped_array_shrink_to_fit(array)</code>. */
inline void dbof_uarray_shrink_to_fit(dbof_object_uarray array)
{ dbof_untyped_array_shrink_to_fit(array); }

/**
 * Get an element of an untyped array.
 *
 * This function does not perform bounds checking. It can only be used to modify nonempty arrays such that
 * <code>index</code> lies in the interval <code>[0, size)</code>, where <code>size > 0</code> is the current size of
 * the array.
 *
 * @param array The untyped array
 * @param index The element index
 * @return The element
 */
extern dbof_object dbof_untyped_array_get(dbof_object_untyped_array array, dbof_container_size index);

/** Alias for <code>dbof_untyped_array_get(array, index)</code>. */
inline dbof_object dbof_uarray_get(dbof_object_uarray array, dbof_container_size index)
{ return dbof_untyped_array_get(array, index); }

/**
 * Set an element of an untyped array.
 *
 * This function does not perform bounds checking. It can only be used to modify nonempty arrays such that
 * <code>index</code> lies in the interval <code>[0, size)</code>, where <code>size > 0</code> is the current size of
 * the array.
 *
 * Warning: This function may overwrite a pointer to dynamically-allocated memory. It is your responsibility to know
 * what information is being overwritten. Use #dbof_untyped_array_get(array, index) prior if this concerns you.
 *
 * @param array The untyped array
 * @param index The element index
 * @param object The new element
 */
extern void dbof_untyped_array_set(dbof_object_untyped_array array, dbof_container_size index, dbof_object object);

/** Alias for <code>dbof_untyped_array_set(array, index, object)</code>. */
inline void dbof_uarray_set(dbof_object_uarray array, dbof_container_size index, dbof_object object)
{ dbof_untyped_array_set(array, index, object); }

/**
 * Insert an element to an untyped array.
 *
 * The caller relinquishes ownership of the object's memory.
 *
 * @param array The untyped array
 * @param index The target index
 * @param object The new object
 */
extern void dbof_untyped_array_insert(dbof_object_untyped_array array, dbof_container_size index, dbof_object object);

/** Alias for <code>dbof_untyped_array_insert(array, index, object)</code>. */
inline void dbof_uarray_insert(dbof_object_uarray array, dbof_container_size index, dbof_object object)
{ dbof_untyped_array_insert(array, index, object); }

/**
 * Remove an element from an untyped array.
 *
 * The caller assumes ownership of the object's memory.
 *
 * @param array The untyped array
 * @param index The target index
 * @return The old object
 */
extern dbof_object dbof_untyped_array_remove(dbof_object_untyped_array array, dbof_container_size index);

/** Alias for <code>dbof_untyped_array_remove</code>. */
inline dbof_object dbof_uarray_remove(dbof_object_uarray array, dbof_container_size index)
{ return dbof_untyped_array_remove(array, index); }

/**
 * Add an object to the back of an untyped array.
 *
 * @param array The untyped array
 * @param object The new object
 */
extern void dbof_untyped_array_push_back(dbof_object_untyped_array array, dbof_object object);

/** Alias for <code>dbof_untyped_array_push_back(array, object)</code>. */
inline void dbof_uarray_push(dbof_object_uarray array, dbof_object object)
{ dbof_untyped_array_push_back(array, object); }

/**
 * Remove the last object from a untyped array.
 *
 * @param array The untyped array
 * @return The removed object
 */
extern dbof_object dbof_untyped_array_pop_back(dbof_object_untyped_array array);

/** Alias for <code>dbof_untyped_array_pop_back(array)</code>. */
inline dbof_object dbof_uarray_pop(dbof_object_uarray array)
{ return dbof_untyped_array_pop_back(array); }

/**
 * Get the capacity of a typed map. This is the pre-allocated space for non-colliding entries.
 *
 * @param map The typed map
 * @return Its capacity
 */
extern dbof_container_size dbof_typed_map_get_capacity(dbof_object_typed_map map);

/** Alias for <code>dbof_typed_map_get_capacity(map)</code>. */
inline dbof_container_size dbof_map_get_capacity(dbof_object_map map)
{ return dbof_typed_map_get_capacity(map); }

/**
 * Get the size of a typed map. This is the total number of entries currently in the map.
 *
 * @param map The typed map
 * @return Its size
 */
extern dbof_container_size dbof_typed_map_get_size(dbof_object_typed_map map);

/** Alias for <code>dbof_typed_map_get_size(map)</code>. */
inline dbof_container_size dbof_map_get_size(dbof_object_map map)
{ return dbof_typed_map_get_size(map); }

/**
 * Determine if a typed map is empty.
 *
 * @param map The typed map
 * @return Nonzero if such is the case, otherwise zero
 */
extern int dbof_typed_map_is_empty(dbof_object_typed_map map);

/** Alias for <code>dbof_typed_map_is_empty(map)</code>. */
inline int dbof_map_is_empty(dbof_object_map map)
{ return dbof_typed_map_is_empty(map); }

/**
 * Get the key type of a typed map.
 *
 * @param map The typed map
 * @return The key type
 */
extern dbof_type dbof_typed_map_get_key_type(dbof_object_typed_map map);

/** Alias for <code>dbof_typed_map_get_key_type(map)</code>. */
inline dbof_type dbof_type_dbof_map_get_key_type(dbof_object_map map)
{ return dbof_typed_map_get_key_type(map); }

/**
 * Set the key type of a typed map. The map must be empty for this to take effect.
 *
 * @param map The typed map
 * @param key_type The key type
 */
extern void dbof_typed_map_set_key_type(dbof_object_typed_map map, dbof_type key_type);

/** Alias for <code>dbof_typed_map_set_key_type(map, key_type)</code>. */
inline void dbof_map_set_key_type(dbof_object_map map, dbof_type key_type)
{ dbof_typed_map_set_key_type(map, key_type); }

/**
 * Get the value type of a typed map.
 *
 * @param map The typed map
 * @return The value type
 */
extern dbof_type dbof_typed_map_get_value_type(dbof_object_typed_map map);

/** Alias for <code>dbof_typed_map_get_value_type(map)</code>. */
inline dbof_type dbof_map_get_value_type(dbof_object_map map)
{ return dbof_typed_map_get_value_type(map); }

/**
 * Set the value type of a typed map. The map type must be empty for this to take effect.
 *
 * @param map The typed map
 * @param value_type The value type
 */
extern void dbof_typed_map_set_value_type(dbof_object_typed_map map, dbof_type value_type);

/** Alias for <code>dbof_typed_map_set_value_type(map, value_type)</code>. */
inline void dbof_map_set_value_type(dbof_object_map map, dbof_type value_type)
{ dbof_typed_map_set_value_type(map, value_type); }

/**
 * Get a value from a typed map for the given key.
 *
 * @param map The typed map
 * @param key The key
 * @return The value
 */
extern dbof_object dbof_typed_map_get(dbof_object_typed_map map, dbof_object key);

/** Alias for <code>dbof_typed_map_get(map, key)</code>. */
inline dbof_object dbof_map_get(dbof_object_map map, dbof_object key)
{ return dbof_typed_map_get(map, key); }

/**
 * Put a value into a typed map with the given key.
 *
 * The caller relinquishes ownership of the object's memory.
 *
 * @param map The typed map
 * @param key The key
 * @param value The value
 */
extern void dbof_typed_map_put(dbof_object_typed_map map, dbof_object key, dbof_object value);

/** Alias for <code>dbof_typed_map_put(map, key, value)</code>. */
inline void dbof_map_put(dbof_object_map map, dbof_object key, dbof_object value)
{ dbof_typed_map_put(map, key, value); }

/**
 * Remove a value from a typed map for the given key.
 *
 * The caller assumes ownership of the object's memory.
 *
 * @param map The typed map
 * @param key The key
 * @return The value
 */
extern dbof_object dbof_typed_map_remove(dbof_object_typed_map map, dbof_object key);

/** Alias for <code>dbof_typed_map_remove(map, key)</code>. */
inline dbof_object dbof_map_remove(dbof_object_map map, dbof_object key)
{ return dbof_typed_map_remove(map, key); }

/**
 * Determine if a typed map already has an entry for the given key.
 *
 * @param map The typed map
 * @param key The key in question
 * @return Nonzero if such is the case, otherwise zero
 */
extern int dbof_typed_map_has_key(dbof_object_typed_map map, dbof_object key);

/** Alias for <code>dbof_typed_map_has_key(map, key)</code>. */
inline int dbof_map_has_key(dbof_object_map map, dbof_object key)
{ return dbof_typed_map_has_key(map, key); }

/**
 * Get the capacity of an untyped map. This is the pre-allocated space for non-colliding entries.
 *
 * @param map The untyped map
 * @return Its capacity
 */
extern dbof_container_size dbof_untyped_map_get_capacity(dbof_object_untyped_map map);

/** Alias for <code>dbof_untyped_map_get_capacity(map)</code>. */
inline dbof_container_size dbof_umap_get_capacity(dbof_object_umap map)
{ return dbof_untyped_map_get_capacity(map); }

/**
 * Get the size of an untyped map. This is the total number of entries currently in the map.
 *
 * @param map The untyped map
 * @return Its size
 */
extern dbof_container_size dbof_untyped_map_get_size(dbof_object_untyped_map map);

/** Alias for <code>dbof_untyped_map_get_size(map)</code>. */
inline dbof_container_size dbof_umap_get_size(dbof_object_umap map)
{ return dbof_untyped_map_get_size(map); }

/**
 * Determine if an untyped map is empty.
 *
 * @param map The untyped map
 * @return Nonzero if such is the case, otherwise zero
 */
extern int dbof_untyped_map_is_empty(dbof_object_untyped_map map);

/** Alias for <code>dbof_untyped_map_is_empty(map)</code>. */
inline int dbof_umap_is_empty(dbof_object_umap map)
{ return dbof_untyped_map_is_empty(map); }

/**
 * Get a value from an untyped map for the given key.
 *
 * @param map The untyped map
 * @param key The key
 * @return The value
 */
extern dbof_object dbof_untyped_map_get(dbof_object_untyped_map map, dbof_object key);

/** Alias for <code>dbof_untyped_map_get(map, key)</code>. */
inline dbof_object dbof_umap_get(dbof_object_umap map, dbof_object key)
{ return dbof_untyped_map_get(map, key); }

/**
 * Put a value into an untyped map with the given key.
 *
 * The caller relinquishes ownership of the object's memory.
 *
 * @param map The untyped map
 * @param key The key
 * @param value The value
 */
extern void dbof_untyped_map_put(dbof_object_untyped_map map, dbof_object key, dbof_object value);

/** Alias for <code>dbof_untyped_map_put(map, key, value)</code>. */
inline void dbof_umap_put(dbof_object_umap map, dbof_object key, dbof_object value)
{ dbof_untyped_map_put(map, key, value); }

/**
 * Remove a value from an untyped map for the given key.
 *
 * The caller assumes ownership of the object's memory.
 *
 * @param map The untyped map
 * @param key The key
 * @return The value
 */
extern dbof_object dbof_untyped_map_remove(dbof_object_untyped_map map, dbof_object key);

/** Alias for <code>dbof_untyped_map_remove(map, key)</code>. */
inline dbof_object dbof_umap_remove(dbof_object_umap map, dbof_object key)
{ return dbof_untyped_map_remove(map, key); }

/**
 * Determine if an untyped map already has an entry for the given key.
 *
 * @param map The untyped map
 * @param key The key in question
 * @return Nonzero if such is the case, otherwise zero
 */
extern int dbof_untyped_map_has_key(dbof_object_untyped_map map, dbof_object key);

/** Alias for <code>dbof_untyped_map_has_key(map, key)</code>. */
inline int dbof_umap_has_key(dbof_object_umap map, dbof_object key)
{ return dbof_untyped_map_has_key(map, key); }

//
// Object hook definitions
//

/**
 * Hooks for signed byte objects.
 */
typedef struct
{
    int (* get)(dbof_signed_byte* out_value);

    int (* set)(dbof_signed_byte value);
} dbof_hooks_object_signed_byte;

/**
 * Hooks for unsigned byte objects.
 */
typedef struct
{
    int (* get)(dbof_unsigned_byte* out_value);

    int (* set)(dbof_unsigned_byte value);
} dbof_hooks_object_unsigned_byte;

/**
 * Hooks for signed integer objects.
 */
typedef struct
{
    int (* get)(dbof_signed_integer* out_value);

    int (* set)(dbof_signed_integer value);
} dbof_hooks_object_signed_integer;

/**
 * Hooks for unsigned integer objects.
 */
typedef struct
{
    int (* get)(dbof_unsigned_integer* out_value);

    int (* set)(dbof_unsigned_integer value);
} dbof_hooks_object_unsigned_integer;

/**
 * Hooks for signed long integer objects.
 */
typedef struct
{
    int (* get)(dbof_signed_long_integer* out_value);

    int (* set)(dbof_signed_long_integer value);
} dbof_hooks_object_signed_long_integer;

/**
 * Hooks for unsigned long integer objects.
 */
typedef struct
{
    int (* get)(dbof_unsigned_long_integer* out_value);

    int (* set)(dbof_unsigned_long_integer value);
} dbof_hooks_object_unsigned_long_integer;

/**
 * Hooks for boolean objects.
 */
typedef struct
{
    int (* get)(dbof_boolean* out_value);

    int (* set)(dbof_boolean value);
} dbof_hooks_object_boolean;

/**
 * Hooks for single float objects.
 */
typedef struct
{
    int (* get)(dbof_single_float* out_value);

    int (* set)(dbof_single_float value);
} dbof_hooks_object_single_float;

/**
 * Hooks for double float objects.
 */
typedef struct
{
    int (* get)(dbof_double_float* out_value);

    int (* set)(dbof_double_float value);
} dbof_hooks_object_double_float;

/**
 * Hooks for character objects.
 */
typedef struct
{
    int (* get)(dbof_unsigned_long_integer* out_value);

    int (* set)(dbof_unsigned_long_integer value);
} dbof_hooks_object_character;

/**
 * Hooks for UTF-8 string objects.
 */
typedef struct
{
    int (* get)(dbof_utf8_string* out_value);

    int (* set)(dbof_utf8_string value);
} dbof_hooks_object_utf8_string;

/**
 * Hooks for typed array objects.
 */
typedef struct
{
    int (* get)(dbof_container_size index, dbof_object* out_object);

    int (* set)(dbof_container_size index);

    int (* push_back)(dbof_object element);

    int (* pop_back)(dbof_object element);

    int (* insert)(dbof_container_size index, dbof_object object);

    int (* remove)(dbof_container_size index);
} dbof_hooks_object_typed_array;

/**
 * Hooks for untyped array objects.
 */
typedef struct
{
    int (* get)(dbof_container_size index, dbof_object* out_object);

    int (* set)(dbof_container_size index);

    int (* push_back)(dbof_object element);

    int (* pop_back)(dbof_object element);

    int (* insert)(dbof_container_size index, dbof_object object);

    int (* remove)(dbof_container_size index);
} dbof_hooks_object_untyped_array;

/**
 * Hooks for typed map objects.
 */
typedef struct
{
    int (* put)(dbof_object key, dbof_object value);

    int (* get)(dbof_object key, dbof_object* out_object);
} dbof_hooks_object_typed_map;

/**
 * Hooks for untyped map objects.
 */
typedef struct
{
    int (* put)(dbof_object key, dbof_object value);

    int (* get)(dbof_object key, dbof_object* out_object);
} dbof_hooks_object_untyped_map;

//
// Object Serialization and Deserialization
//

/**
 * The default DBOF Serialization Format version for times when one isn't supplied. Usually the latest-and-greatest,
 * while most general version available for use.
 */
#define DBOF_SER_DEFAULT 1

/**
 * A configuration for reading (deserializing) DBOF objects. Implementations are expected to track position.
 */
typedef struct dbof_reader
{
    /**
     * Read the next block of raw data from the source.
     *
     * @param reader A reference to the reader
     * @param ptr The data buffer
     * @param size The size of the data buffer
     * @return The size actually read
     */
    size_t (* read)(struct dbof_reader* reader, char* ptr, size_t size);

    /**
     * Force the serialized object to be read using this DBOF Serialization Format version. This value will be ignored
     * if set to 0.
     */
    unsigned short use_version;

    /**
     * Set this to a nonzero value if you know the serialized object is not packed with a header. If set, the
     * force_version field MUST be set to a nonzero value, as well, or an error will occur.
     */
    int no_header;

    /**
     * Just a thing for general-purpose use. Put what you want here.
     */
    void* data;
} dbof_reader;

/**
 * A configuration for writing (serializing) DBOF objects. Implementations are expected to track position.
 */
typedef struct dbof_writer
{
    /**
     * Write the next block of raw data to the sink.
     *
     * @param writer A reference to the writer
     * @param ptr The data buffer
     * @param size The size to write
     * @return The size actually written
     */
    size_t (* write)(struct dbof_writer* writer, const char* ptr, size_t size);

    /**
     * Force the serialized object to be written using this DBOF Serialization Format version. This value will be
     * ignored if set to 0 and the object will be written using version DBOF_SER_LATEST by default.
     */
    unsigned short use_version;

    /**
     * Set this to a nonzero value if you do not wish the serialized object to be packed with a header. This is
     * technically non-conforming, and we make no guarantees about the serialized object's compatibility with other DBOF
     * implementations when used.
     */
    int no_header;

    /**
     * Just a thing for general-purpose use. Put what you want here.
     */
    void* data;
} dbof_writer;

/**
 * Read an object with the given reader.
 *
 * @param reader The reader
 * @return The read object or NULL if an error occurred
 */
extern dbof_object dbof_read(dbof_reader* reader);

/**
 * Write an object with the given writer.
 *
 * @param object The object to write
 * @param writer The writer
 * @return Zero upon success, otherwise nonzero
 */
extern int dbof_write(dbof_object object, dbof_writer* writer);

#ifdef __cplusplus
}
#endif

#endif // #ifndef DBOF_DBOF_H
