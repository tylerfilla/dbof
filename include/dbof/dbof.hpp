/*
 * DBOF
 * Copyright 2017 glyre
 */

//
// NOTICE
// This is a header-only C++11 wrapper around the library that only adds language conveniences, not new functionality.
// No C++ code is actually compiled into the DBOF library itself.
//

#ifndef __cplusplus
#error "C++ header included from C source."
#endif

#ifndef DBOF_DBOF_HPP
#define DBOF_DBOF_HPP

#include "dbof.h"

namespace dbof
{

namespace type
{

/**
 * A DBOF object type constant wrapper. Similar in purpose to <code>dbof_type</code> from the C API.
 */
class type_constant
{
    dbof_type _c_type;

public:
    explicit type_constant(dbof_type _c_type) : _c_type(_c_type)
    {}

    /**
     * @return The wrapped C-style type constant
     */
    dbof_type c_type() const
    { return _c_type; }

    /**
     * @return True if the object is of a container type, otherwise false
     */
    bool container() const
    { return dbof_is_container_type(_c_type) != 0; }

    /**
     * @return True if the object is of a value type, otherwise false
     */
    bool value() const
    { return dbof_is_value_type(_c_type) != 0; }

    bool operator==(const type_constant& rhs) const
    { return _c_type == rhs._c_type; }
};

//
// Full names
//

/**
 * The C++-style version of the C-style <code>DBOF_TYPE_NULL</code> type constant.
 */
static const type_constant null(DBOF_TYPE_NULL);

/**
 * The C++-style version of the C-style <code>DBOF_TYPE_SIGNED_BYTE</code> type constant.
 */
static const type_constant signed_byte(DBOF_TYPE_SIGNED_BYTE);

/**
 * The C++-style version of the C-style <code>DBOF_TYPE_UNSIGNED_BYTE</code> type constant.
 */
static const type_constant unsigned_byte(DBOF_TYPE_UNSIGNED_BYTE);

/**
 * The C++-style version of the C-style <code>DBOF_TYPE_SIGNED_INTEGER</code> type constant.
 */
static const type_constant signed_integer(DBOF_TYPE_SIGNED_INTEGER);

/**
 * The C++-style version of the C-style <code>DBOF_TYPE_UNSIGNED_INTEGER</code> type constant.
 */
static const type_constant unsigned_integer(DBOF_TYPE_UNSIGNED_INTEGER);

/**
 * The C++-style version of the C-style <code>DBOF_TYPE_SIGNED_LONG_INTEGER</code> type constant.
 */
static const type_constant signed_long_integer(DBOF_TYPE_SIGNED_LONG_INTEGER);

/** The C++-style version of the C-style <code>DBOF_TYPE_UNSIGNED_LONG_INTEGER</code> type constant.
 */
static const type_constant unsigned_long_integer(DBOF_TYPE_UNSIGNED_LONG_INTEGER);

/**
 * The C++-style version of the C-style <code>DBOF_TYPE_BOOLEAN</code> type constant.
 */
static const type_constant boolean(DBOF_TYPE_BOOLEAN);

/**
 * The C++-style version of the C-style <code>DBOF_TYPE_SINGLE_FLOAT</code> type constant.
 */
static const type_constant single_float(DBOF_TYPE_SINGLE_FLOAT);

/**
 * The C++-style version of the C-style <code>DBOF_TYPE_DOUBLE_FLOAT</code> type constant.
 */
static const type_constant double_float(DBOF_TYPE_DOUBLE_FLOAT);

/**
 * The C++-style version of the C-style <code>DBOF_TYPE_CHARACTER</code> type constant.
 */
static const type_constant character(DBOF_TYPE_CHARACTER);

/**
 * The C++-style version of the C-style <code>DBOF_TYPE_UTF8_STRING</code> type constant.
 */
static const type_constant utf8_string(DBOF_TYPE_UTF8_STRING);

/**
 * The C++-style version of the C-style <code>DBOF_TYPE_TYPED_ARRAY</code> type constant.
 */
static const type_constant typed_array(DBOF_TYPE_TYPED_ARRAY);

/**
 * The C++-style version of the C-style <code>DBOF_TYPE_UNTYPED_ARRAY</code> type constant.
 */
static const type_constant untyped_array(DBOF_TYPE_UNTYPED_ARRAY);

/**
 * The C++-style version of the C-style <code>DBOF_TYPE_TYPED_MAP</code> type constant.
 */
static const type_constant typed_map(DBOF_TYPE_TYPED_MAP);

/**
 * The C++-style version of the C-style <code>DBOF_TYPE_UNTYPED_MAP</code> type constant.
 */
static const type_constant untyped_map(DBOF_TYPE_UNTYPED_MAP);

//
// Short name aliases
//

/** Alias for <code>signed_byte</code>. */
static const auto _byte = signed_byte;

/** Alias for <code>unsigned_byte</code>. */
static const auto _ubyte = unsigned_byte;

/** Alias for <code>signed_integer</code>. */
static const auto _int = signed_integer;

/** Alias for <code>unsigned_integer</code>. */
static const auto _uint = unsigned_integer;

/** Alias for <code>signed_long_integer</code>. */
static const auto _long = signed_long_integer;

/** Alias for <code>unsigned_long_integer</code>. */
static const auto _ulong = unsigned_long_integer;

/** Alias for <code>boolean</code>. */
static const auto _bool = boolean;

/** Alias for <code>single_float</code>. */
static const auto _float = single_float;

/** Alias for <code>double_float</code>. */
static const auto _double = double_float;

/** Alias for <code>character</code>. */
static const auto _char = character;

/** Alias for <code>utf8_string</code>. */
static const auto _string = utf8_string;

/** Alias for <code>typed_array</code>. */
static const auto _array = typed_array;

/** Alias for <code>untyped_array</code>. */
static const auto _uarray = untyped_array;

/** Alias for <code>typed_map</code>. */
static const auto _map = typed_map;

/** Alias for <code>untyped_map</code>. */
static const auto _umap = untyped_map;

} // namespace type

/**
 * A DBOF object wrapper. Similar in purpose to <code>dbof_object</code> from the C API.
 */
struct object
{
protected:
    const type::type_constant& _type;
    const dbof_object _c_obj;

    explicit object(const type::type_constant& _type, const dbof_object _c_obj) : _type(_type), _c_obj(_c_obj)
    {}

public:
    object(const object& other) = delete;

    object(const object&& other) = delete;

    ~object()
    { dbof_delete(_c_obj); }

    /**
     * @return The type of the object
     */
    const type::type_constant& type() const
    { return _type; }

    /**
     * @return The wrapped C-style object (its lifetime still managed by this wrapper)
     */
    dbof_object c_obj() const
    { return _c_obj; }

    bool operator==(const object& rhs) const
    { return dbof_equals(_c_obj, rhs._c_obj) != 0; }
};

//
// Full names
//

struct null;
struct signed_byte;
struct unsigned_byte;
struct signed_integer;
struct unsigned_integer;
struct signed_long_integer;
struct unsigned_long_integer;
struct boolean;
struct single_float;
struct double_float;
struct character;
struct utf8_string;
struct typed_array;
struct untyped_array;
struct typed_map;
struct untyped_map;

//
// Short name aliases
//

typedef signed_byte _byte;
typedef unsigned_byte _ubyte;
typedef signed_integer _int;
typedef unsigned_integer _uint;
typedef signed_long_integer _long;
typedef unsigned_long_integer _ulong;
typedef boolean _bool;
typedef single_float _float;
typedef double_float _double;
typedef character _char;
typedef utf8_string _string;
typedef typed_array _array;
typedef untyped_array _uarray;
typedef typed_map _map;
typedef untyped_map _umap;

/**
 * Convert a C-style DBOF object to a C++-style DBOF object by wrapping it. The memory semantics of this function are
 * pretty raw. By passing in a C-style object (necessarily dynamically allocated), the caller relinquishes control over
 * its lifetime. In exchange, however, the caller is now responsible for deleting the returned wrapper object with the
 * <code>delete</code> operator when it otherwise would have been needed to use the <code>dbof_delete()</code> function.
 *
 * A shared pointer should not be returned, as that would complicate the implementation of container object wrappers.
 *
 * @param c_obj The C-style object
 * @return The C++-style object
 */
object* wrap(dbof_object c_obj);

//
// Object wrappers
//

/**
 * A null object.
 *
 * Type ID 0
 */
struct null : public object
{
    null() : null(dbof_new(DBOF_TYPE_NULL))
    {}

    null(dbof_object_null _c_obj) : object(type::null, _c_obj)
    {}
};

/**
 * A signed byte object.
 *
 * Type ID 1
 */
struct signed_byte : public object
{
    signed_byte() : signed_byte(dbof_new(DBOF_TYPE_SIGNED_BYTE))
    {}

    signed_byte(dbof_object_signed_byte _c_obj) : object(type::signed_byte, _c_obj)
    {}

    explicit signed_byte(dbof_signed_byte value) : signed_byte()
    { set(value); }

    dbof_signed_byte get() const
    { return dbof_get_value_signed_byte(_c_obj); }

    void set(dbof_signed_byte value)
    { dbof_set_value_signed_byte(_c_obj, value); }
};

/**
 * An unsigned byte object.
 *
 * Type ID 2
 */
struct unsigned_byte : public object
{
    unsigned_byte() : unsigned_byte(dbof_new(DBOF_TYPE_UNSIGNED_BYTE))
    {}

    unsigned_byte(dbof_object_unsigned_byte _c_obj) : object(type::unsigned_byte, _c_obj)
    {}

    explicit unsigned_byte(dbof_unsigned_byte value) : unsigned_byte()
    { set(value); }

    dbof_unsigned_byte get() const
    { return dbof_get_value_unsigned_byte(_c_obj); }

    void set(dbof_unsigned_byte value)
    { dbof_set_value_unsigned_byte(_c_obj, value); }
};

/**
 * A signed integer object.
 *
 * Type ID 3
 */
struct signed_integer : public object
{
    signed_integer() : signed_integer(dbof_new(DBOF_TYPE_SIGNED_INTEGER))
    {}

    signed_integer(dbof_object_signed_integer _c_obj) : object(type::signed_integer, _c_obj)
    {}

    explicit signed_integer(dbof_signed_integer value) : signed_integer()
    { set(value); }

    dbof_signed_integer get() const
    { return dbof_get_value_signed_integer(_c_obj); }

    void set(dbof_signed_integer value)
    { dbof_set_value_signed_integer(_c_obj, value); }
};

/**
 * An unsigned integer object.
 *
 * Type ID 4
 */
struct unsigned_integer : public object
{
    unsigned_integer() : unsigned_integer(dbof_new(DBOF_TYPE_UNSIGNED_INTEGER))
    {}

    unsigned_integer(dbof_object_unsigned_integer _c_obj) : object(type::unsigned_integer, _c_obj)
    {}

    explicit unsigned_integer(dbof_unsigned_integer value) : unsigned_integer()
    { set(value); }

    dbof_unsigned_integer get() const
    { return dbof_get_value_unsigned_integer(_c_obj); }

    void set(dbof_unsigned_integer value)
    { dbof_set_value_unsigned_integer(_c_obj, value); }
};

/**
 * A signed long integer object.
 *
 * Type ID 5
 */
struct signed_long_integer : public object
{
    signed_long_integer() : signed_long_integer(dbof_new(DBOF_TYPE_SIGNED_LONG_INTEGER))
    {}

    signed_long_integer(dbof_object_signed_long_integer _c_obj) : object(type::signed_long_integer, _c_obj)
    {}

    explicit signed_long_integer(dbof_signed_long_integer value) : signed_long_integer()
    { set(value); }

    dbof_signed_long_integer get() const
    { return dbof_get_value_signed_long_integer(_c_obj); }

    void set(dbof_signed_long_integer value)
    { dbof_set_value_signed_long_integer(_c_obj, value); }
};

/**
 * An unsigned long integer object.
 *
 * Type ID 6
 */
struct unsigned_long_integer : public object
{
    unsigned_long_integer() : unsigned_long_integer(dbof_new(DBOF_TYPE_UNSIGNED_LONG_INTEGER))
    {}

    unsigned_long_integer(dbof_object_unsigned_long_integer _c_obj) : object(type::unsigned_long_integer, _c_obj)
    {}

    explicit unsigned_long_integer(dbof_unsigned_long_integer value) : unsigned_long_integer()
    { set(value); }

    dbof_unsigned_long_integer get() const
    { return dbof_get_value_unsigned_long_integer(_c_obj); }

    void set(dbof_unsigned_long_integer value)
    { dbof_set_value_unsigned_long_integer(_c_obj, value); }
};

/**
 * A Boolean object.
 *
 * Type ID 7
 */
struct boolean : public object
{
    boolean() : boolean(dbof_new(DBOF_TYPE_BOOLEAN))
    {}

    boolean(dbof_object_boolean _c_obj) : object(type::boolean, _c_obj)
    {}

    explicit boolean(dbof_boolean value) : boolean()
    { set(value); }

    dbof_boolean get() const
    { return dbof_get_value_boolean(_c_obj); }

    void set(dbof_boolean value)
    { dbof_set_value_boolean(_c_obj, value); }
};

/**
 * A single float object.
 *
 * Type ID 8
 */
struct single_float : public object
{
    single_float() : single_float(dbof_new(DBOF_TYPE_SINGLE_FLOAT))
    {}

    single_float(dbof_object_single_float _c_obj) : object(type::single_float, _c_obj)
    {}

    explicit single_float(dbof_single_float value) : single_float()
    { set(value); }

    dbof_single_float get() const
    { return dbof_get_value_single_float(_c_obj); }

    void set(dbof_single_float value)
    { dbof_set_value_single_float(_c_obj, value); }
};

/**
 * A double float object.
 *
 * Type ID 9
 */
struct double_float : public object
{
    double_float() : double_float(dbof_new(DBOF_TYPE_DOUBLE_FLOAT))
    {}

    double_float(dbof_object_double_float _c_obj) : object(type::double_float, _c_obj)
    {}

    explicit double_float(dbof_double_float value) : double_float()
    { set(value); }

    dbof_double_float get() const
    { return dbof_get_value_double_float(_c_obj); }

    void set(dbof_double_float value)
    { dbof_set_value_double_float(_c_obj, value); }
};

/**
 * A character object.
 *
 * Type ID 10
 */
struct character : public object
{
    character() : character(dbof_new(DBOF_TYPE_CHARACTER))
    {}

    character(dbof_object_character _c_obj) : object(type::character, _c_obj)
    {}

    explicit character(dbof_character value) : character()
    { set(value); }

    dbof_character get() const
    { return dbof_get_value_character(_c_obj); }

    void set(dbof_character value)
    { dbof_set_value_character(_c_obj, value); }
};

/**
 * A UTF-8 string object.
 *
 * Type ID 11
 */
struct utf8_string : public object
{
    utf8_string() : utf8_string(dbof_new(DBOF_TYPE_UTF8_STRING))
    {}

    utf8_string(dbof_object_utf8_string _c_obj) : object(type::utf8_string, _c_obj)
    {}

    utf8_string(const utf8_string& other) : utf8_string()
    { set(other.get()); }

    utf8_string(const utf8_string&& other) noexcept : utf8_string(std::move(other._c_obj))
    {}

    explicit utf8_string(dbof_utf8_string value) : utf8_string()
    { dbof_set_value_utf8_string(_c_obj, value); }

    dbof_utf8_string get() const
    { return dbof_get_value_utf8_string(_c_obj); }

    void set(dbof_utf8_string value)
    { dbof_set_value_utf8_string(_c_obj, value); }
};

// TODO: We need to wrap the children of container types
// To do this, we need a way to iterate over these children
// To do that, we need to implement the container types in the library
// After all this, implement hooks so that changing C objects also changes the associated C++ wrapper

/**
 * A typed array object.
 *
 * Type ID 128
 */
struct typed_array : public object
{
    typed_array() : typed_array(dbof_new(DBOF_TYPE_TYPED_ARRAY))
    {}

    typed_array(dbof_object_typed_array _c_obj) : object(type::typed_array, _c_obj)
    {}

    void push_back(const object& obj)
    { dbof_typed_array_push_back(_c_obj, obj.c_obj()); }

    void pop_back()
    { dbof_typed_array_pop_back(_c_obj); }

    // FIXME: Need to store the wrappers themselves that manage the C-style objects
};

/**
 * An untyped array object.
 *
 * Type ID 129
 */
struct untyped_array : public object
{
    untyped_array() : untyped_array(dbof_new(DBOF_TYPE_UNTYPED_ARRAY))
    {}

    untyped_array(dbof_object_untyped_array _c_obj) : object(type::untyped_array, _c_obj)
    {}
};

/**
 * A typed map object.
 *
 * Type ID 130
 */
struct typed_map : public object
{
    typed_map() : typed_map(dbof_new(DBOF_TYPE_TYPED_MAP))
    {}

    typed_map(dbof_object_typed_map _c_obj) : object(type::typed_map, _c_obj)
    {}
};

/**
 * An untyped map object.
 *
 * Type ID 131
 */
struct untyped_map : public object
{
    untyped_map() : untyped_map(dbof_new(DBOF_TYPE_UNTYPED_MAP))
    {}

    untyped_map(dbof_object_untyped_map _c_obj) : object(type::untyped_map, _c_obj)
    {}
};

object* wrap(dbof_object c_obj)
{
    switch (dbof_typeof(c_obj))
    {
    case DBOF_TYPE_NULL:
        return new null(c_obj);
    case DBOF_TYPE_SIGNED_BYTE:
        return new signed_byte(c_obj);
    case DBOF_TYPE_UNSIGNED_BYTE:
        return new unsigned_byte(c_obj);
    case DBOF_TYPE_SIGNED_INTEGER:
        return new signed_integer(c_obj);
    case DBOF_TYPE_UNSIGNED_INTEGER:
        return new unsigned_integer(c_obj);
    case DBOF_TYPE_SIGNED_LONG_INTEGER:
        return new signed_long_integer(c_obj);
    case DBOF_TYPE_UNSIGNED_LONG_INTEGER:
        return new unsigned_long_integer(c_obj);
    case DBOF_TYPE_BOOLEAN:
        return new boolean(c_obj);
    case DBOF_TYPE_SINGLE_FLOAT:
        return new single_float(c_obj);
    case DBOF_TYPE_DOUBLE_FLOAT:
        return new double_float(c_obj);
    case DBOF_TYPE_CHARACTER:
        return new character(c_obj);
    case DBOF_TYPE_UTF8_STRING:
        return new utf8_string(c_obj);
    case DBOF_TYPE_TYPED_ARRAY:
        return new typed_array(c_obj);
    case DBOF_TYPE_UNTYPED_ARRAY:
        return new untyped_array(c_obj);
    case DBOF_TYPE_TYPED_MAP:
        return new typed_map(c_obj);
    case DBOF_TYPE_UNTYPED_MAP:
        return new untyped_map(c_obj);
    }
}

} // namespace dbof

#endif // #ifndef DBOF_DBOF_HPP
