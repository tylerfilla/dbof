/*
 * DBOF
 * Copyright 2017 glyre
 */

#include <stdlib.h>
#include <string.h>

#include <dbof/dbof.h>

#ifndef DBOF_MALLOC
/// malloc() override
#define DBOF_MALLOC malloc
#endif

#ifndef DBOF_CALLOC
/// calloc() override
#define DBOF_CALLOC calloc
#endif

#ifndef DBOF_REALLOC
/// realloc() override
#define DBOF_REALLOC realloc
#endif

#ifndef DBOF_FREE
/// free() override
#define DBOF_FREE free
#endif

#define malloc  DBOF_MALLOC
#define calloc  DBOF_CALLOC
#define realloc DBOF_REALLOC
#define free    DBOF_FREE

/**
 * Common base header for every in-memory DBOF object.
 */
struct __object_impl
{
    /**
     * The derived object type.
     */
    dbof_type type;
};

static void* __new_empty_object(dbof_type type, size_t size)
{
    struct __object_impl* object = calloc(1, size);

    if (object == NULL)
    {
        // ERROR: Out of memory
        return NULL;
    }

    object->type = type;
    return object;
}

/**
 * Implementation of a null object (type ID 0).
 */
struct __object_null_impl
{
    struct __object_impl base;
};

static struct __object_null_impl* __new_object_null()
{ return __new_empty_object(DBOF_TYPE_NULL, sizeof(struct __object_null_impl)); }

static void __delete_object_null(struct __object_null_impl* object)
{ free(object); }

static int __hash_object_null(struct __object_null_impl* object)
{ return 0; }

/**
 * Implementation of a signed byte object (type ID 1).
 */
struct __object_signed_byte_impl
{
    struct __object_impl base;
    dbof_signed_byte value;
};

static struct __object_signed_byte_impl* __new_object_signed_byte()
{ return __new_empty_object(DBOF_TYPE_SIGNED_BYTE, sizeof(struct __object_signed_byte_impl)); }

static void __delete_object_signed_byte(struct __object_signed_byte_impl* object)
{ free(object); }

static int __hash_object_signed_byte(struct __object_signed_byte_impl* object)
{ return object->value; }

/**
 * Implementation of an unsigned byte object (type ID 2).
 */
struct __object_unsigned_byte_impl
{
    struct __object_impl base;
    dbof_unsigned_byte value;
};

static struct __object_unsigned_byte_impl* __new_object_unsigned_byte()
{ return __new_empty_object(DBOF_TYPE_UNSIGNED_BYTE, sizeof(struct __object_unsigned_byte_impl)); }

static void __delete_object_unsigned_byte(struct __object_unsigned_byte_impl* object)
{ free(object); }

static int __hash_object_unsigned_byte(struct __object_unsigned_byte_impl* object)
{ return object->value; }

/**
 * Implementation of a signed integer object (type ID 3).
 */
struct __object_signed_integer_impl
{
    struct __object_impl base;
    dbof_signed_integer value;
};

static struct __object_signed_integer_impl* __new_object_signed_integer()
{ return __new_empty_object(DBOF_TYPE_SIGNED_INTEGER, sizeof(struct __object_signed_integer_impl)); }

static void __delete_object_signed_integer(struct __object_signed_integer_impl* object)
{ free(object); }

static int __hash_object_signed_integer(struct __object_signed_integer_impl* object)
{ return object->value; }

/**
 * Implementation an unsigned integer object (type ID 4).
 */
struct __object_unsigned_integer_impl
{
    struct __object_impl base;
    dbof_unsigned_integer value;
};

static struct __object_unsigned_integer_impl* __new_object_unsigned_integer()
{ return __new_empty_object(DBOF_TYPE_UNSIGNED_INTEGER, sizeof(struct __object_unsigned_integer_impl)); }

static void __delete_object_unsigned_integer(struct __object_unsigned_integer_impl* object)
{ free(object); }

static int __hash_object_unsigned_integer(struct __object_unsigned_integer_impl* object)
{ return object->value; }

/**
 * Implementation of a signed long integer object (type ID 5).
 */
struct __object_signed_long_integer_impl
{
    struct __object_impl base;
    dbof_signed_long_integer value;
};

static struct __object_signed_long_integer_impl* __new_object_signed_long_integer()
{ return __new_empty_object(DBOF_TYPE_SIGNED_LONG_INTEGER, sizeof(struct __object_signed_long_integer_impl)); }

static void __delete_object_signed_long_integer(struct __object_signed_long_integer_impl* object)
{ free(object); }

static int __hash_object_signed_long_integer(struct __object_signed_long_integer_impl* object)
{
    // Return the lower half XOR'd with the upper half of its unsigned self
    dbof_unsigned_long_integer un = (dbof_unsigned_long_integer) object->value;
    return (int) (un ^ (un >> (sizeof(dbof_unsigned_long_integer) * 8 / 2)));
}

/**
 * Implementation of an unsigned long integer object (type ID 6).
 */
struct __object_unsigned_long_integer_impl
{
    struct __object_impl base;
    dbof_unsigned_long_integer value;
};

static struct __object_unsigned_long_integer_impl* __new_object_unsigned_long_integer()
{ return __new_empty_object(DBOF_TYPE_UNSIGNED_LONG_INTEGER, sizeof(struct __object_unsigned_long_integer_impl)); }

static void __delete_object_unsigned_long_integer(struct __object_unsigned_long_integer_impl* object)
{ free(object); }

static int __hash_object_unsigned_long_integer(struct __object_unsigned_long_integer_impl* object)
{
    // Return the lower half of the value XOR'd with the upper half
    return (int) (object->value ^ (object->value >> (sizeof(dbof_unsigned_long_integer) * 8 / 2)));
}

/**
 * Implementation of a Boolean value object (type ID 7).
 */
struct __object_boolean_impl
{
    struct __object_impl base;
    dbof_boolean value;
};

static struct __object_boolean_impl* __new_object_boolean()
{ return __new_empty_object(DBOF_TYPE_BOOLEAN, sizeof(struct __object_boolean_impl)); }

static void __delete_object_boolean(struct __object_boolean_impl* object)
{ free(object); }

static int __hash_object_boolean(struct __object_boolean_impl* object)
{ return object->value ? 1231 : 1237; } // Inspired by Java's hashing for booleans

/**
 * Implementation of a single-precision floating point number object (type ID 8).
 */
struct __object_single_float_impl
{
    struct __object_impl base;
    dbof_single_float value;
};

static struct __object_single_float_impl* __new_object_single_float()
{ return __new_empty_object(DBOF_TYPE_SINGLE_FLOAT, sizeof(struct __object_single_float_impl)); }

static void __delete_object_single_float(struct __object_single_float_impl* object)
{ free(object); }

static int __hash_object_single_float(struct __object_single_float_impl* object)
{
    // We assume IEEE 754 binary32 format
    union
    {
        dbof_single_float in;
        uint32_t out;
    } cvt = { object->value };

    // Pull out the interesting parts
    const uint32_t MASK_EXPONENT = 0x7f800000u;
    const uint32_t MASK_MANTISSA = 0x007fffffu;
    uint32_t exponent = cvt.out & MASK_EXPONENT;
    uint32_t mantissa = cvt.out & MASK_MANTISSA;

    // By definition, NaNs have nonzero mantissas and have exponent fields full of ones
    if (exponent == MASK_EXPONENT && mantissa != 0)
    {
        return 0x7fc00000u;
    }

    return cvt.out;
}

/**
 * Implementation of a double-precision floating point number object (type ID 9).
 */
struct __object_double_float_impl
{
    struct __object_impl base;
    dbof_double_float value;
};

static struct __object_double_float_impl* __new_object_double_float()
{ return __new_empty_object(DBOF_TYPE_DOUBLE_FLOAT, sizeof(struct __object_double_float_impl)); }

static void __delete_object_double_float(struct __object_double_float_impl* object)
{ free(object); }

static int __hash_object_double_float(struct __object_double_float_impl* object)
{
    // We assume IEEE 754 binary64 format
    union
    {
        dbof_double_float in;
        uint64_t out;
    } cvt = { object->value };

    // Pull out the interesting parts
    const uint64_t MASK_EXPONENT = 0x7ff0000000000000ul;
    const uint64_t MASK_MANTISSA = 0x000ffffffffffffful;
    uint64_t exponent = cvt.out & MASK_EXPONENT;
    uint64_t mantissa = cvt.out & MASK_MANTISSA;

    // By definition, NaNs have nonzero mantissas and exponent fields full of ones
    if (exponent == MASK_EXPONENT && mantissa != 0)
    {
        uint64_t r = 0x7ff8000000000000ul;
        return (int) (r ^ (r >> 32));
    }

    return (int) (cvt.out ^ (cvt.out >> 32));
}

/**
 * Implementation of a Unicode character codepoint object (type ID 10).
 */
struct __object_character_impl
{
    struct __object_impl base;

    /**
     * The character value.
     */
    dbof_character value;
};

static struct __object_character_impl* __new_object_character()
{ return __new_empty_object(DBOF_TYPE_CHARACTER, sizeof(struct __object_character_impl)); }

static void __delete_object_character(struct __object_character_impl* object)
{ free(object); }

static int __hash_object_character(struct __object_character_impl* object)
{ return object->value; }

/**
 * Implementation of a UTF-8 string object (type ID 11).
 */
struct __object_utf8_string_impl
{
    struct __object_impl base;

    /**
     * The UTF-8 string value (as an array of bytes).
     */
    char* value;
};

static struct __object_utf8_string_impl* __new_object_utf8_string()
{ return __new_empty_object(DBOF_TYPE_UTF8_STRING, sizeof(struct __object_utf8_string_impl)); }

static void __delete_object_utf8_string(struct __object_utf8_string_impl* object)
{
    // Simply free the string memory
    free((void*) object->value);
    free(object);
}

static int __hash_object_utf8_string(struct __object_utf8_string_impl* object)
{
    // Maybe we'll eventually implement caching of hash codes? Will that really matter?
    int hash = 0;

    dbof_string_size i;
    dbof_string_size length = strlen(object->value);
    for (i = 0; i < length; ++i)
    {
        hash = object->value[i] + hash * 31;
    }

    return hash;
}

struct __internal_array_base
{
    struct __object_impl base;

    /**
     * The allocated capacity. Do not serialize.
     */
    dbof_container_size capacity;

    /**
     * The occupied size.
     */
    dbof_container_size size;

    /**
     * The children objects.
     */
    dbof_object* children;
};

static void __internal_array_base_construct(struct __internal_array_base* array)
{
    // TODO: Allow user to specify initial capacity
    dbof_container_size initial_capacity = 10;

    array->capacity = initial_capacity;
    array->size = 0;

    // Pre-allocate initial capacity
    array->children = calloc(array->capacity, sizeof(dbof_object));
}

static void __internal_array_base_destruct(struct __internal_array_base* array)
{
    // Delete each object individually
    for (dbof_container_size i = 0; i < array->size; ++i)
    {
        dbof_delete(array->children[i]);
    }

    // Free the child array itself
    free(array->children);
}

static dbof_container_size __internal_array_base_get_capacity(struct __internal_array_base* array)
{ return array->capacity; }

static dbof_container_size __internal_array_base_get_size(struct __internal_array_base* array)
{ return array->size; }

static int __internal_array_base_resize(struct __internal_array_base* array, dbof_container_size size)
{
    dbof_object* children = realloc(array->children, size * sizeof(dbof_object));

    // If reallocation failed, the resize fails
    if (children != NULL)
        return -1;

    array->children = children;
    array->capacity = size;

    return 0;
}

static void __internal_array_base_shrink_to_fit(struct __internal_array_base* array)
{
    if (array->size < array->capacity)
    {
        __internal_array_base_resize(array, array->size);
    }
}

static int __internal_array_base_ensure_space(struct __internal_array_base* array)
{
    // If we're at capacity, double it (TODO: Let user provide algo)
    if (array->size == array->capacity)
    {
        if (array->capacity == 0)
        {
            if (__internal_array_base_resize(array, 1))
                return -1;
        }

        if (__internal_array_base_resize(array, array->capacity * 2))
            return -1;
    }

    return 0;
}

static void __internal_array_base_maybe_downscale(struct __internal_array_base* array)
{
    // If we're using less than half of capacity, halve it (TODO: Let user provide algo)
    if (array->size < array->capacity / 2)
    {
        __internal_array_base_resize(array, array->capacity / 2);
    }
}

/**
 * Internal. Get the object at a specific index. Valid for <code>index</code> from <code>0</code> to
 * <code>array->size</code>, inclusive.
 */
static dbof_object __internal_array_base_get(struct __internal_array_base* array, dbof_container_size index)
{ return array->children[index]; }

/**
 * Internal. Set a specific index to the given object. Valid for <code>index</code> from <code>0</code> to
 * <code>array->size</code>, inclusive.
 */
static void __internal_array_base_set(struct __internal_array_base* array, dbof_container_size index,
        dbof_object object)
{ array->children[index] = object; }

static int __internal_array_base_insert(struct __internal_array_base* array, dbof_container_size index,
        dbof_object object)
{
    // Restrict index to last index + 1
    if (index > array->size)
        return -1;

    // Ensure we have enough capacity for another object or fail
    if (__internal_array_base_ensure_space(array))
        return -1;

    // If inserting in the middle of things, move children over starting at index
    if (index < array->size)
    {
        memmove(array->children + index + 1, array->children + index, (array->size - index) * sizeof(dbof_object));
    }

    __internal_array_base_set(array, index, object);
    array->size++;

    return 0;
}

static dbof_object __internal_array_base_remove(struct __internal_array_base* array, dbof_container_size index)
{
    // Restrict index to last index
    if (index >= array->size)
        return NULL;

    // Preserve the object
    dbof_object object = __internal_array_base_get(array, index);

    // Move children over, covering up the old object
    memmove(array->children + index, array->children + index + 1, (array->size - index) * sizeof(dbof_object));
    array->size--;

    // Downscale capacity if needed
    __internal_array_base_maybe_downscale(array);

    return object;
}

static int __internal_array_base_push_back(struct __internal_array_base* array, dbof_object object)
{
    // Ensure we have enough capacity for another object or fail
    if (__internal_array_base_ensure_space(array))
        return -1;

    // We can bypass insertion and just set
    __internal_array_base_set(array, array->size, object);
    array->size++;

    return 0;
}

static dbof_object __internal_array_base_pop_back(struct __internal_array_base* array)
{
    // Remove the last object
    dbof_object object = __internal_array_base_remove(array, array->size - 1);

    // Downscale capacity if needed
    __internal_array_base_maybe_downscale(array);

    return object;
}

/**
 * Implementation of a typed array object (type ID 128).
 */
struct __object_typed_array_impl
{
    struct __internal_array_base base;

    /**
     * The type for all children of the array.
     */
    dbof_type type;
};

static void __object_typed_array_impl_construct(struct __object_typed_array_impl* array)
{ __internal_array_base_construct((struct __internal_array_base*) array); }

static void __object_typed_array_impl_destruct(struct __object_typed_array_impl* array)
{ __internal_array_base_destruct((struct __internal_array_base*) array); }

static dbof_container_size __object_typed_array_impl_get_capacity(struct __object_typed_array_impl* array)
{ return __internal_array_base_get_capacity((struct __internal_array_base*) array); }

static dbof_container_size __object_typed_array_impl_get_size(struct __object_typed_array_impl* array)
{ return __internal_array_base_get_size((struct __internal_array_base*) array); }

static void __object_typed_array_impl_resize(struct __object_typed_array_impl* array, dbof_container_size size)
{ __internal_array_base_resize((struct __internal_array_base*) array, size); }

static int __object_typed_array_impl_is_empty(struct __object_typed_array_impl* array)
{ return __object_typed_array_impl_get_size(array) == 0; }

static dbof_type __object_typed_array_impl_get_type(struct __object_typed_array_impl* array)
{ return array->type; }

static void __object_typed_array_impl_set_type(struct __object_typed_array_impl* array, dbof_type type)
{
    // Only change the type if the array is empty
    if (__object_typed_array_impl_is_empty(array))
    {
        array->type = type;
    }
}

static void __object_typed_array_impl_shrink_to_fit(struct __object_typed_array_impl* array)
{ __internal_array_base_shrink_to_fit((struct __internal_array_base*) array); }

static dbof_object __object_typed_array_impl_get(struct __object_typed_array_impl* array, dbof_container_size index)
{ return __internal_array_base_get((struct __internal_array_base*) array, index); }

static void __object_typed_array_impl_set(struct __object_typed_array_impl* array, dbof_container_size index,
        dbof_object object)
{
    // Only valid for nonempty arrays, so always enforce matching types
    if (dbof_typeof(object) == array->type)
    {
        __internal_array_base_set((struct __internal_array_base*) array, index, object);
    }
}

void __object_typed_array_impl_insert(struct __object_typed_array_impl* array, dbof_container_size index,
        dbof_object object)
{ __internal_array_base_insert((struct __internal_array_base*) array, index, object); }

dbof_object __object_typed_array_impl_remove(struct __object_typed_array_impl* array, dbof_container_size index)
{ return __internal_array_base_remove((struct __internal_array_base*) array, index); }

static void __object_typed_array_impl_push_back(struct __object_typed_array_impl* array, dbof_object object)
{
    dbof_type type = dbof_typeof(object);

    // First child sets the type
    if (__object_typed_array_impl_is_empty(array))
    {
        array->type = type;
    }

    // Subsequent children must match the type
    if (type == array->type)
    {
        __internal_array_base_push_back((struct __internal_array_base*) array, object);
    }
}

static dbof_object __object_typed_array_impl_pop_back(struct __object_typed_array_impl* array)
{ return __internal_array_base_pop_back((struct __internal_array_base*) array); }

static struct __object_typed_array_impl* __new_object_typed_array()
{
    struct __object_typed_array_impl* array = __new_empty_object(DBOF_TYPE_TYPED_ARRAY,
            sizeof(struct __object_typed_array_impl));
    __object_typed_array_impl_construct(array);
    return array;
}

static void __delete_object_typed_array(struct __object_typed_array_impl* array)
{
    __object_typed_array_impl_destruct(array);
    free(array);
}

static int __hash_object_typed_array(struct __object_typed_array_impl* array)
{ return 0; } // TODO

/**
 * Implementation of an untyped array object (type ID 129).
 */
struct __object_untyped_array_impl
{
    struct __internal_array_base base;
};

static void __object_untyped_array_impl_construct(struct __object_untyped_array_impl* array)
{ __internal_array_base_construct((struct __internal_array_base*) array); }

static void __object_untyped_array_impl_destruct(struct __object_untyped_array_impl* array)
{ __internal_array_base_destruct((struct __internal_array_base*) array); }

static dbof_container_size __object_untyped_array_impl_get_capacity(struct __object_untyped_array_impl* array)
{ return __internal_array_base_get_capacity((struct __internal_array_base*) array); }

static dbof_container_size __object_untyped_array_impl_get_size(struct __object_untyped_array_impl* array)
{ return __internal_array_base_get_size((struct __internal_array_base*) array); }

static void __object_untyped_array_impl_resize(struct __object_untyped_array_impl* array, dbof_container_size size)
{ __internal_array_base_resize((struct __internal_array_base*) array, size); }

static int __object_untyped_array_impl_is_empty(struct __object_untyped_array_impl* array)
{ return __object_untyped_array_impl_get_size(array) == 0; }

static void __object_untyped_array_impl_shrink_to_fit(struct __object_untyped_array_impl* array)
{ __internal_array_base_shrink_to_fit((struct __internal_array_base*) array); }

static dbof_object __object_untyped_array_impl_get(struct __object_untyped_array_impl* array, dbof_container_size index)
{ return __internal_array_base_get((struct __internal_array_base*) array, index); }

static void __object_untyped_array_impl_set(struct __object_untyped_array_impl* array, dbof_container_size index,
        dbof_object object)
{ __internal_array_base_set((struct __internal_array_base*) array, index, object); }

void __object_untyped_array_impl_insert(struct __object_untyped_array_impl* array, dbof_container_size index,
        dbof_object object)
{ __internal_array_base_insert((struct __internal_array_base*) array, index, object); }

dbof_object __object_untyped_array_impl_remove(struct __object_untyped_array_impl* array, dbof_container_size index)
{ return __internal_array_base_remove((struct __internal_array_base*) array, index); }

static void __object_untyped_array_impl_push_back(struct __object_untyped_array_impl* array, dbof_object object)
{ __internal_array_base_push_back((struct __internal_array_base*) array, object); }

static dbof_object __object_untyped_array_impl_pop_back(struct __object_untyped_array_impl* array)
{ return __internal_array_base_pop_back((struct __internal_array_base*) array); }

static struct __object_untyped_array_impl* __new_object_untyped_array()
{
    struct __object_untyped_array_impl* array = __new_empty_object(DBOF_TYPE_UNTYPED_ARRAY,
            sizeof(struct __object_untyped_array_impl));
    __object_untyped_array_impl_construct(array);
    return array;
}

static void __delete_object_untyped_array(struct __object_untyped_array_impl* array)
{
    __object_untyped_array_impl_destruct(array);
    free(array);
}

static int __hash_object_untyped_array(struct __object_untyped_array_impl* array)
{ return 0; } // TODO

//
// NOTICE
// This map implementation uses a naive chaining hash table. An array of doubly-linked lists (chains) is allocated on
// construction. These chains are composed of map nodes. Each map node can hold a pointer to a map entry (a key-value
// pair) or NULL if it does not. Key hashing is used (of course) to place new entries into the table in a deterministic
// manner, and hash collisions are resolved by a linear search through the chain in question.
//

struct __map_node
{
    /**
     * The key object, if applicable.
     *
     * NULL if this node does not carry an entry.
     */
    dbof_object entry_key;

    /**
     * The value object, if applicable.
     *
     * Undefined if this node does not carry an entry.
     */
    dbof_object entry_value;

    /**
     * The previous node in this chain.
     *
     * NULL if this node is first and/or the only in the chain.
     */
    struct __map_node* chain_prev;

    /**
     * The next node in this chain.
     *
     * NULL if this node is last and/or the only in the chain.
     */
    struct __map_node* chain_next;
};

struct __internal_map_base
{
    struct __object_impl base;

    /**
     * The number of chains in the map.
     */
    dbof_container_size capacity;

    /**
     * The total number of entries in the map.
     */
    dbof_container_size size;

    /**
     * The heads of the chains in the hash table.
     */
    struct __map_node** table_heads;

    /**
     * The tails of the chains in the hash table.
     */
    struct __map_node** table_tails;
};

static void __internal_map_base_construct(struct __internal_map_base* map)
{
    // TODO: Allow user to specify the initial capacity
    dbof_container_size initial_capacity = 16;

    map->capacity = initial_capacity;
    map->size = 0;

    // Allocate array of chain head pointers (each NULL by default)
    // We'll allocate more nodes as needed
    map->table_heads = calloc(map->capacity, sizeof(struct __map_node*));
    map->table_tails = map->table_heads;
    for (dbof_container_size i = 0; i < map->capacity; ++i)
    {
        map->table_heads[i] = calloc(1, sizeof(struct __map_node));
    }
}

static void __internal_map_base_destruct(struct __internal_map_base* map)
{
    // Iterate over chains and delete every node
    struct __map_node* current;
    struct __map_node* next;
    for (dbof_container_size i = 0; i < map->capacity; ++i)
    {
        current = map->table_heads[i];
        do
        {
            next = current->chain_next;

            // If node has an entry, delete key and value objects
            // Here we rely on dbof_delete(NULL) being sane
            if (current->entry_key != NULL)
            {
                dbof_delete(current->entry_key);
                dbof_delete(current->entry_value);
                current->entry_key = NULL;
            }

            // Free the node
            free(current);
        } while ((current = next) != NULL);
    }

    // Free the table itself
    free(map->table_heads);
}

static dbof_container_size __internal_map_base_get_capacity(struct __internal_map_base* map)
{ return map->capacity; }

static dbof_container_size __internal_map_base_get_size(struct __internal_map_base* map)
{ return map->size; }

static int __internal_map_base_is_empty(struct __internal_map_base* map)
{ return map->size == 0; }

static dbof_object __internal_map_base_get(struct __internal_map_base* map, dbof_object key)
{
    // TODO: Get from the map
}

static void __internal_map_base_put(struct __internal_map_base* map, dbof_object key, dbof_object value)
{
    // TODO: Put to the map
}

static dbof_object __internal_map_base_remove(struct __internal_map_base* map, dbof_object key)
{
    // TODO: Remove from the map
}

static int __internal_map_base_has_key(struct __internal_map_base* map, dbof_object key)
{
    // TODO: Test for key
}

/**
 * Implementation of a typed map object (type ID 130).
 */
struct __object_typed_map_impl
{
    struct __internal_map_base base;

    /**
     * The type for all keys in the array.
     */
    dbof_type key_type;

    /**
     * The type for all values in the array.
     */
    dbof_type value_type;
};

static dbof_container_size __object_typed_map_impl_get_capacity(struct __object_typed_map_impl* map)
{ return __internal_map_base_get_capacity((struct __internal_map_base*) map); }

static dbof_container_size __object_typed_map_impl_get_size(struct __object_typed_map_impl* map)
{ return __internal_map_base_get_size((struct __internal_map_base*) map); }

static int __object_typed_map_impl_is_empty(struct __object_typed_map_impl* map)
{ return __internal_map_base_is_empty((struct __internal_map_base*) map); }

static dbof_type __object_typed_map_impl_get_key_type(struct __object_typed_map_impl* map)
{ return map->key_type; }

static void __object_typed_map_impl_set_key_type(struct __object_typed_map_impl* map, dbof_type key_type)
{
    // Only change the key type if the map is empty
    if (__object_typed_map_impl_is_empty(map))
    {
        map->key_type = key_type;
    }
}

static dbof_type __object_typed_map_impl_get_value_type(struct __object_typed_map_impl* map)
{ return map->value_type; }

static void __object_typed_map_impl_set_key_value(struct __object_typed_map_impl* map, dbof_type value_type)
{
    // Only change the value type if the map is empty
    if (__object_typed_map_impl_is_empty(map))
    {
        map->value_type = value_type;
    }
}

static dbof_object __object_typed_map_impl_get(struct __object_typed_map_impl* map, dbof_object key)
{ return __internal_map_base_get((struct __internal_map_base*) map, key); }

static void __object_typed_map_impl_put(struct __object_typed_map_impl* map, dbof_object key, dbof_object value)
{ __internal_map_base_put((struct __internal_map_base*) map, key, value); }

static dbof_object __object_typed_map_impl_remove(struct __object_typed_map_impl* map, dbof_object key)
{ return __internal_map_base_remove((struct __internal_map_base*) map, key); }

static int __object_typed_map_impl_has_key(struct __object_typed_map_impl* map, dbof_object key)
{ return __internal_map_base_has_key((struct __internal_map_base*) map, key); }

static struct __object_typed_map_impl* __new_object_typed_map()
{ return __new_empty_object(DBOF_TYPE_TYPED_MAP, sizeof(struct __object_typed_map_impl)); }

static void __delete_object_typed_map(struct __object_typed_map_impl* map)
{
    __internal_map_base_destruct((struct __internal_map_base*) map);
    free(map);
}

static int __hash_object_typed_map(struct __object_typed_map_impl* object)
{ return 0; } // TODO

/**
 * Implementation of an untyped map object (type ID 131).
 */
struct __object_untyped_map_impl
{
    struct __internal_map_base base;
};

static dbof_container_size __object_untyped_map_impl_get_capacity(struct __object_untyped_map_impl* map)
{ return __internal_map_base_get_capacity((struct __internal_map_base*) map); }

static dbof_container_size __object_untyped_map_impl_get_size(struct __object_untyped_map_impl* map)
{ return __internal_map_base_get_size((struct __internal_map_base*) map); }

static int __object_untyped_map_impl_is_empty(struct __object_untyped_map_impl* map)
{ return __internal_map_base_is_empty((struct __internal_map_base*) map); }

static dbof_object __object_untyped_map_impl_get(struct __object_untyped_map_impl* map, dbof_object key)
{ return __internal_map_base_get((struct __internal_map_base*) map, key); }

static void __object_untyped_map_impl_put(struct __object_untyped_map_impl* map, dbof_object key, dbof_object value)
{ __internal_map_base_put((struct __internal_map_base*) map, key, value); }

static dbof_object __object_untyped_map_impl_remove(struct __object_untyped_map_impl* map, dbof_object key)
{ return __internal_map_base_remove((struct __internal_map_base*) map, key); }

static int __object_untyped_map_impl_has_key(struct __object_untyped_map_impl* map, dbof_object key)
{ return __internal_map_base_has_key((struct __internal_map_base*) map, key); }

static struct __object_untyped_map_impl* __new_object_untyped_map()
{ return __new_empty_object(DBOF_TYPE_UNTYPED_MAP, sizeof(struct __object_untyped_map_impl)); }

static void __delete_object_untyped_map(struct __object_untyped_map_impl* object)
{
    __internal_map_base_destruct((struct __internal_map_base*) object);
    free(object);
}

static int __hash_object_untyped_map(struct __object_untyped_map_impl* object)
{ return 0; } // TODO

dbof_type dbof_typeof(dbof_object object)
{
    return ((struct __object_impl*) object)->type;
}

dbof_object dbof_new(dbof_type type)
{
    dbof_object object = NULL;

    switch (type)
    {
    case DBOF_TYPE_NULL:
        object = __new_object_null();
        break;
    case DBOF_TYPE_SIGNED_BYTE:
        object = __new_object_signed_byte();
        break;
    case DBOF_TYPE_UNSIGNED_BYTE:
        object = __new_object_unsigned_byte();
        break;
    case DBOF_TYPE_SIGNED_INTEGER:
        object = __new_object_signed_integer();
        break;
    case DBOF_TYPE_UNSIGNED_INTEGER:
        object = __new_object_unsigned_integer();
        break;
    case DBOF_TYPE_SIGNED_LONG_INTEGER:
        object = __new_object_signed_long_integer();
        break;
    case DBOF_TYPE_UNSIGNED_LONG_INTEGER:
        object = __new_object_unsigned_long_integer();
        break;
    case DBOF_TYPE_BOOLEAN:
        object = __new_object_boolean();
        break;
    case DBOF_TYPE_SINGLE_FLOAT:
        object = __new_object_single_float();
        break;
    case DBOF_TYPE_DOUBLE_FLOAT:
        object = __new_object_double_float();
        break;
    case DBOF_TYPE_CHARACTER:
        object = __new_object_character();
        break;
    case DBOF_TYPE_UTF8_STRING:
        object = __new_object_utf8_string();
        break;
    case DBOF_TYPE_TYPED_ARRAY:
        object = __new_object_typed_array();
        break;
    case DBOF_TYPE_UNTYPED_ARRAY:
        object = __new_object_untyped_array();
        break;
    case DBOF_TYPE_TYPED_MAP:
        object = __new_object_typed_map();
        break;
    case DBOF_TYPE_UNTYPED_MAP:
        object = __new_object_untyped_map();
        break;
    }

    if (object == NULL)
    {
        object = __new_object_null();
    }

    return object;
}

dbof_object dbof_new_ex(dbof_type type, dbof_new_ex_params* params)
{
    // TODO: Implement hooks
}

void dbof_delete(dbof_object object)
{
    if (object == NULL)
    {
        return;
    }

    switch (dbof_typeof(object))
    {
    case DBOF_TYPE_NULL:
        __delete_object_null(object);
        break;
    case DBOF_TYPE_SIGNED_BYTE:
        __delete_object_signed_byte(object);
        break;
    case DBOF_TYPE_UNSIGNED_BYTE:
        __delete_object_unsigned_byte(object);
        break;
    case DBOF_TYPE_SIGNED_INTEGER:
        __delete_object_signed_integer(object);
        break;
    case DBOF_TYPE_UNSIGNED_INTEGER:
        __delete_object_unsigned_integer(object);
        break;
    case DBOF_TYPE_SIGNED_LONG_INTEGER:
        __delete_object_signed_long_integer(object);
        break;
    case DBOF_TYPE_UNSIGNED_LONG_INTEGER:
        __delete_object_unsigned_long_integer(object);
        break;
    case DBOF_TYPE_BOOLEAN:
        __delete_object_boolean(object);
        break;
    case DBOF_TYPE_SINGLE_FLOAT:
        __delete_object_single_float(object);
        break;
    case DBOF_TYPE_DOUBLE_FLOAT:
        __delete_object_double_float(object);
        break;
    case DBOF_TYPE_CHARACTER:
        __delete_object_character(object);
        break;
    case DBOF_TYPE_UTF8_STRING:
        __delete_object_utf8_string(object);
        break;
    case DBOF_TYPE_TYPED_ARRAY:
        __delete_object_typed_array(object);
        break;
    case DBOF_TYPE_UNTYPED_ARRAY:
        __delete_object_untyped_array(object);
        break;
    case DBOF_TYPE_TYPED_MAP:
        __delete_object_typed_map(object);
        break;
    case DBOF_TYPE_UNTYPED_MAP:
        __delete_object_untyped_map(object);
        break;
    }
}

int dbof_hash(dbof_object object)
{
    // Return zero for null inputs
    if (object == NULL)
    {
        return 0;
    }

    switch (dbof_typeof(object))
    {
    case DBOF_TYPE_NULL:
        return __hash_object_null(object);
    case DBOF_TYPE_SIGNED_BYTE:
        return __hash_object_signed_byte(object);
    case DBOF_TYPE_UNSIGNED_BYTE:
        return __hash_object_unsigned_byte(object);
    case DBOF_TYPE_SIGNED_INTEGER:
        return __hash_object_signed_integer(object);
    case DBOF_TYPE_UNSIGNED_INTEGER:
        return __hash_object_unsigned_integer(object);
    case DBOF_TYPE_SIGNED_LONG_INTEGER:
        return __hash_object_signed_long_integer(object);
    case DBOF_TYPE_UNSIGNED_LONG_INTEGER:
        return __hash_object_unsigned_long_integer(object);
    case DBOF_TYPE_BOOLEAN:
        return __hash_object_boolean(object);
    case DBOF_TYPE_SINGLE_FLOAT:
        return __hash_object_single_float(object);
    case DBOF_TYPE_DOUBLE_FLOAT:
        return __hash_object_double_float(object);
    case DBOF_TYPE_CHARACTER:
        return __hash_object_character(object);
    case DBOF_TYPE_UTF8_STRING:
        return __hash_object_utf8_string(object);
    case DBOF_TYPE_TYPED_ARRAY:
        return __hash_object_typed_array(object);
    case DBOF_TYPE_UNTYPED_ARRAY:
        return __hash_object_untyped_array(object);
    case DBOF_TYPE_TYPED_MAP:
        return __hash_object_typed_map(object);
    case DBOF_TYPE_UNTYPED_MAP:
        return __hash_object_untyped_map(object);
    }
}

int dbof_equals(dbof_object a, dbof_object b)
{
    // If at least one is null, they can only be equal if the other is also null
    // This is not defined in the specification
    if (a == NULL || b == NULL)
    {
        return a == b;
    }

    // Value types and container types can never be equal
    if (!dbof_same_category(a, b))
    {
        return 0;
    }

    dbof_type type_a = dbof_typeof(a);
    dbof_type type_b = dbof_typeof(b);

    // If a and b are different types of containers, they cannot be equal
    // We only need to test one type, as we know both types must be of the same category by now
    if (dbof_is_container_type(type_a) && type_a != type_b)
    {
        return 1;
    }

    // We now know that a and b are both the same type of container
    // TODO: Check equality on per-container basis

    // At this stage, we know that a and b are both value objects

    // If the hashes are different, the values must not be equal
    if (dbof_hash(a) != dbof_hash(b))
    {
        return 0;
    }

    // TODO: Actually implement equality checking

    return 1;
}

dbof_signed_byte dbof_get_value_signed_byte(dbof_object_signed_byte object)
{ return ((struct __object_signed_byte_impl*) object)->value; }

void dbof_set_value_signed_byte(dbof_object_signed_byte object, dbof_signed_byte value)
{ ((struct __object_signed_byte_impl*) object)->value = value; }

dbof_unsigned_byte dbof_get_value_unsigned_byte(dbof_object_unsigned_byte object)
{ return ((struct __object_unsigned_byte_impl*) object)->value; }

void dbof_set_value_unsigned_byte(dbof_object_unsigned_byte object, dbof_unsigned_byte value)
{ ((struct __object_unsigned_byte_impl*) object)->value = value; }

dbof_signed_integer dbof_get_value_signed_integer(dbof_object_signed_integer object)
{ return ((struct __object_signed_integer_impl*) object)->value; }

void dbof_set_value_signed_integer(dbof_object_signed_integer object, dbof_signed_integer value)
{ ((struct __object_signed_integer_impl*) object)->value = value; }

dbof_unsigned_integer dbof_get_value_unsigned_integer(dbof_object_unsigned_integer object)
{ return ((struct __object_unsigned_integer_impl*) object)->value; }

void dbof_set_value_unsigned_integer(dbof_object_unsigned_integer object, dbof_unsigned_integer value)
{ ((struct __object_unsigned_integer_impl*) object)->value = value; }

dbof_signed_long_integer dbof_get_value_signed_long_integer(dbof_object_signed_long_integer object)
{ return ((struct __object_signed_long_integer_impl*) object)->value; }

void dbof_set_value_signed_long_integer(dbof_object_signed_long_integer object, dbof_signed_long_integer value)
{ ((struct __object_signed_long_integer_impl*) object)->value = value; }

dbof_unsigned_long_integer dbof_get_value_unsigned_long_integer(dbof_object_unsigned_long_integer object)
{ return ((struct __object_unsigned_long_integer_impl*) object)->value; }

void dbof_set_value_unsigned_long_integer(dbof_object_unsigned_long_integer object, dbof_unsigned_long_integer value)
{ ((struct __object_unsigned_long_integer_impl*) object)->value = value; }

dbof_boolean dbof_get_value_boolean(dbof_object_boolean object)
{ return ((struct __object_boolean_impl*) object)->value; }

void dbof_set_value_boolean(dbof_object_boolean object, dbof_boolean value)
{ ((struct __object_boolean_impl*) object)->value = value; }

dbof_single_float dbof_get_value_single_float(dbof_object_single_float object)
{ return ((struct __object_single_float_impl*) object)->value; }

void dbof_set_value_single_float(dbof_object_single_float object, dbof_single_float value)
{ ((struct __object_single_float_impl*) object)->value = value; }

dbof_double_float dbof_get_value_double_float(dbof_object_double_float object)
{ return ((struct __object_double_float_impl*) object)->value; }

void dbof_set_value_double_float(dbof_object_double_float object, dbof_double_float value)
{ ((struct __object_double_float_impl*) object)->value = value; }

dbof_character dbof_get_value_character(dbof_object_character object)
{ return ((struct __object_character_impl*) object)->value; }

void dbof_set_value_character(dbof_object_character object, dbof_character value)
{ ((struct __object_character_impl*) object)->value = value; }

dbof_utf8_string dbof_get_value_utf8_string(dbof_object_utf8_string object)
{ return ((struct __object_utf8_string_impl*) object)->value; }

void dbof_set_value_utf8_string(dbof_object_utf8_string object, dbof_utf8_string value)
{
    struct __object_utf8_string_impl* string = (struct __object_utf8_string_impl*) object;

    dbof_string_size old_length = string->value == NULL ? 0 : strlen(string->value);
    dbof_string_size new_length = value == NULL ? 0 : strlen(value);

    // If new and old lengths are equal, just copy the new value in
    if (new_length == old_length)
    {
        // The null terminator will be preserved
        memcpy(string->value, value, new_length);
        return;
    }

    // Attempt to reallocate the existing string
    // NONE OF WHAT FOLLOWS IS ATOMIC. ONE THREAD AT A TIME, PLEASE.
    char* val = realloc(string->value, new_length + 1);
    if (val == NULL)
    {
        // ERROR: Reallocation failed. Out of memory?
        // Failure state: The original string has not been modified
        return;
    }

    // Copy in the new value
    memcpy(val, value, new_length);
    val[new_length] = '\0';

    string->value = val;
}

dbof_container_size dbof_typed_array_get_capacity(dbof_object_typed_array array)
{ return __object_typed_array_impl_get_capacity(array); }

dbof_container_size dbof_typed_array_get_size(dbof_object_typed_array array)
{ return __object_typed_array_impl_get_size(array); }

int dbof_typed_array_is_empty(dbof_object_typed_array array)
{ return __object_typed_array_impl_is_empty(array); }

dbof_type dbof_typed_array_get_type(dbof_object_typed_array array)
{ return __object_typed_array_impl_get_type(array); }

void dbof_typed_array_set_type(dbof_object_typed_array array, dbof_type type)
{ __object_typed_array_impl_set_type(array, type); }

void dbof_typed_array_shrink_to_fit(dbof_object_typed_array array)
{ __object_typed_array_impl_shrink_to_fit(array); }

dbof_object dbof_typed_array_get(dbof_object_typed_array array, dbof_container_size index)
{ return __object_typed_array_impl_get(array, index); }

void dbof_typed_array_set(dbof_object_typed_array array, dbof_container_size index, dbof_object object)
{ return __object_typed_array_impl_set(array, index, object); }

void dbof_typed_array_insert(dbof_object_typed_array array, dbof_container_size index, dbof_object object)
{ __object_typed_array_impl_insert(array, index, object); }

dbof_object dbof_typed_array_remove(dbof_object_typed_array array, dbof_container_size index)
{ return __object_typed_array_impl_remove(array, index); }

void dbof_typed_array_push_back(dbof_object_typed_array array, dbof_object object)
{ __object_typed_array_impl_push_back(array, object); }

dbof_object dbof_typed_array_pop_back(dbof_object_typed_array array)
{ return __object_typed_array_impl_pop_back(array); }

dbof_container_size dbof_untyped_array_get_capacity(dbof_object_untyped_array array)
{ return __object_untyped_array_impl_get_capacity(array); }

dbof_container_size dbof_untyped_array_get_size(dbof_object_untyped_array array)
{ return __object_untyped_array_impl_get_size(array); }

int dbof_untyped_array_is_empty(dbof_object_untyped_array map)
{ return __object_untyped_array_impl_is_empty(map); }

void dbof_untyped_array_shrink_to_fit(dbof_object_untyped_array array)
{ __object_untyped_array_impl_shrink_to_fit(array); }

dbof_object dbof_untyped_array_get(dbof_object_untyped_array array, dbof_container_size index)
{ return __object_untyped_array_impl_get(array, index); }

void dbof_untyped_array_set(dbof_object_untyped_array array, dbof_container_size index, dbof_object object)
{ return __object_untyped_array_impl_set(array, index, object); }

void dbof_untyped_array_insert(dbof_object_untyped_array array, dbof_container_size index, dbof_object object)
{ __object_untyped_array_impl_insert(array, index, object); }

dbof_object dbof_untyped_array_remove(dbof_object_untyped_array array, dbof_container_size index)
{ return __object_untyped_array_impl_remove(array, index); }

void dbof_untyped_array_push_back(dbof_object_untyped_array array, dbof_object object)
{ __object_untyped_array_impl_push_back(array, object); }

dbof_object dbof_untyped_array_pop_back(dbof_object_untyped_array array)
{ return __object_untyped_array_impl_pop_back(array); }

dbof_container_size dbof_typed_map_get_capacity(dbof_object_typed_map map)
{ return __object_typed_map_impl_get_capacity(map); }

dbof_container_size dbof_typed_map_get_size(dbof_object_typed_map map)
{ return __object_typed_map_impl_get_size(map); }

int dbof_typed_map_is_empty(dbof_object_typed_map map)
{ return __object_typed_map_impl_is_empty(map); }

dbof_type dbof_typed_map_get_key_type(dbof_object_typed_map map)
{ return __object_typed_map_impl_get_key_type(map); }

void dbof_typed_map_set_key_type(dbof_object_typed_map map, dbof_type key_type)
{ __object_typed_map_impl_set_key_type(map, key_type); }

dbof_type dbof_typed_map_get_value_type(dbof_object_typed_map map)
{ return __object_typed_map_impl_get_value_type(map); }

void dbof_typed_map_set_value_type(dbof_object_typed_map map, dbof_type value_type)
{ __object_typed_map_impl_set_key_value(map, value_type); }

dbof_object dbof_typed_map_get(dbof_object_typed_map map, dbof_object key)
{ return __object_typed_map_impl_get(map, key); }

void dbof_typed_map_put(dbof_object_typed_map map, dbof_object key, dbof_object value)
{ __object_typed_map_impl_put(map, key, value); }

dbof_object dbof_typed_map_remove(dbof_object_typed_map map, dbof_object key)
{ return __object_typed_map_impl_remove(map, key); }

int dbof_typed_map_has_key(dbof_object_typed_map map, dbof_object key)
{ return __object_typed_map_impl_has_key(map, key); }

dbof_container_size dbof_untyped_map_get_capacity(dbof_object_untyped_map map)
{ return __object_untyped_map_impl_get_capacity(map); }

dbof_container_size dbof_untyped_map_get_size(dbof_object_untyped_map map)
{ return __object_untyped_map_impl_get_size(map); }

int dbof_untyped_map_is_empty(dbof_object_untyped_map map)
{ return __object_untyped_map_impl_is_empty(map); }

dbof_object dbof_untyped_map_get(dbof_object_untyped_map map, dbof_object key)
{ return __object_untyped_map_impl_get(map, key); }

void dbof_untyped_map_put(dbof_object_untyped_map map, dbof_object key, dbof_object value)
{ __object_untyped_map_impl_put(map, key, value); }

dbof_object dbof_untyped_map_remove(dbof_object_untyped_map map, dbof_object key)
{ return __object_untyped_map_impl_remove(map, key); }

int dbof_untyped_map_has_key(dbof_object_untyped_map map, dbof_object key)
{ return __object_untyped_map_impl_has_key(map, key); }

//
// Object Serialization and Deserialization
//

/* DBOF Serialization Format 1 */

static dbof_object_null __dbof_1_read_object_null(dbof_reader* reader)
{
    // Null objects have no contents
    return __new_object_null();
}

static int __dbof_1_write_object_null(dbof_object_null object, dbof_writer* writer)
{
    // Null objects have no contents
    return 0;
}

static dbof_object_signed_byte __dbof_1_read_object_signed_byte(dbof_reader* reader)
{
    dbof_signed_byte value;

    // Read 1 byte
    if (reader->read(reader, (char*) &value, 1) < 1)
    {
        // ERROR: End of file
        return NULL;
    }

    // Set value
    dbof_object_signed_byte object = __new_object_signed_byte();
    dbof_set_value_signed_byte(object, value);
    return object;
}

static int __dbof_1_write_object_signed_byte(dbof_object_signed_byte object, dbof_writer* writer)
{
    // Get value
    dbof_signed_byte value = dbof_get_value_signed_byte(object);

    if (writer->write(writer, (char*) &value, 1) < 1)
    {
        // ERROR: End of file or out of space
        return -1;
    }

    return 0;
}

static dbof_object_unsigned_byte __dbof_1_read_object_unsigned_byte(dbof_reader* reader)
{
    dbof_unsigned_byte value = 0;

    // Read 1 byte
    if (reader->read(reader, (char*) &value, 1) < 1)
    {
        // ERROR: End of file
        return NULL;
    }

    // Set value
    dbof_object_unsigned_byte object = __new_object_unsigned_byte();
    dbof_set_value_unsigned_byte(object, value);
    return object;
}

static int __dbof_1_write_object_unsigned_byte(dbof_object_unsigned_byte object, dbof_writer* writer)
{
    // Get value
    dbof_unsigned_byte value = dbof_get_value_unsigned_byte(object);

    // Write 1 byte
    if (writer->write(writer, (char*) &value, 1) < 1)
    {
        // ERROR: End of file or out of space
        return -1;
    }

    return 0;
}

static dbof_object_signed_integer __dbof_1_read_object_signed_integer(dbof_reader* reader)
{
    dbof_signed_integer value = 0;

    // Read 4 bytes
    char value_buf[4];
    if (reader->read(reader, value_buf, 4) < 4)
    {
        // ERROR: End of file
        return NULL;
    }

    // Unpack little-endian 32-bit integer (LSB stored first)
    value |= ((uint32_t) value_buf[0]) << 0;
    value |= ((uint32_t) value_buf[1]) << 8;
    value |= ((uint32_t) value_buf[2]) << 16;
    value |= ((uint32_t) value_buf[3]) << 24;

    // Set value
    dbof_object_signed_integer object = __new_object_signed_integer();
    dbof_set_value_signed_integer(object, value);
    return object;
}

static int __dbof_1_write_object_signed_integer(dbof_object_signed_integer object, dbof_writer* writer)
{
    // Get value
    dbof_signed_integer value = dbof_get_value_signed_integer(object);

    // Pack little-endian 32-bit integer (LSB stored first)
    char value_buf[4];
    value_buf[0] = (uint8_t) ((value & 0x000000ffu) >> 0);
    value_buf[1] = (uint8_t) ((value & 0x0000ff00u) >> 8);
    value_buf[2] = (uint8_t) ((value & 0x00ff0000u) >> 16);
    value_buf[3] = (uint8_t) ((value & 0xff000000u) >> 24);

    // Write 4 bytes
    if (writer->write(writer, value_buf, 4) < 4)
    {
        // ERROR: End of file or out of space
        return -1;
    }

    return 0;
}

static dbof_object_unsigned_integer __dbof_1_read_object_unsigned_integer(dbof_reader* reader)
{
    dbof_unsigned_integer value = 0;

    // Read 4 bytes
    char value_buf[4];
    if (reader->read(reader, value_buf, 4) < 4)
    {
        // ERROR: End of file
        return NULL;
    }

    // Unpack little-endian 32-bit integer (LSB stored first)
    value |= ((uint32_t) value_buf[0]) << 0;
    value |= ((uint32_t) value_buf[1]) << 8;
    value |= ((uint32_t) value_buf[2]) << 16;
    value |= ((uint32_t) value_buf[3]) << 24;

    // Get value
    dbof_object_unsigned_integer object = __new_object_unsigned_integer();
    dbof_set_value_unsigned_integer(object, value);
    return object;
}

static int __dbof_1_write_object_unsigned_integer(dbof_object_unsigned_integer object, dbof_writer* writer)
{
    // Get value
    dbof_unsigned_integer value = dbof_get_value_unsigned_integer(object);

    // Pack little-endian 32-bit integer (LSB stored first)
    char value_buf[4];
    value_buf[0] = (uint8_t) ((value & 0x000000ffu) >> 0);
    value_buf[1] = (uint8_t) ((value & 0x0000ff00u) >> 8);
    value_buf[2] = (uint8_t) ((value & 0x00ff0000u) >> 16);
    value_buf[3] = (uint8_t) ((value & 0xff000000u) >> 24);

    // Write 4 bytes
    if (writer->write(writer, value_buf, 4) < 4)
    {
        // ERROR: End of file or out of space
        return -1;
    }

    return 0;
}

static dbof_object_signed_long_integer __dbof_1_read_object_signed_long_integer(dbof_reader* reader)
{
    dbof_signed_long_integer value = 0;

    // Read 8 bytes
    char value_buf[8];
    if (reader->read(reader, value_buf, 8) < 8)
    {
        // ERROR: End of file
        return NULL;
    }

    // Unpack little-endian 64-bit integer (LSB stored first)
    value |= ((uint64_t) value_buf[0]) << 0;
    value |= ((uint64_t) value_buf[1]) << 8;
    value |= ((uint64_t) value_buf[2]) << 16;
    value |= ((uint64_t) value_buf[3]) << 24;
    value |= ((uint64_t) value_buf[4]) << 32;
    value |= ((uint64_t) value_buf[5]) << 40;
    value |= ((uint64_t) value_buf[6]) << 48;
    value |= ((uint64_t) value_buf[7]) << 56;

    // Set value
    dbof_object_signed_long_integer object = __new_object_signed_long_integer();
    dbof_set_value_signed_long_integer(object, value);
    return object;
}

static int __dbof_1_write_object_signed_long_integer(dbof_object_signed_long_integer object, dbof_writer* writer)
{
    // Get value
    dbof_signed_long_integer value = dbof_get_value_signed_long_integer(object);

    // Pack little-endian 64-bit integer (LSB stored first)
    char value_buf[8];
    value_buf[0] = (uint8_t) ((value & 0x00000000000000fful) >> 0);
    value_buf[1] = (uint8_t) ((value & 0x000000000000ff00ul) >> 8);
    value_buf[2] = (uint8_t) ((value & 0x0000000000ff0000ul) >> 16);
    value_buf[3] = (uint8_t) ((value & 0x00000000ff000000ul) >> 24);
    value_buf[4] = (uint8_t) ((value & 0x000000ff00000000ul) >> 32);
    value_buf[5] = (uint8_t) ((value & 0x0000ff0000000000ul) >> 40);
    value_buf[6] = (uint8_t) ((value & 0x00ff000000000000ul) >> 48);
    value_buf[7] = (uint8_t) ((value & 0xff00000000000000ul) >> 56);

    // Write 8 bytes
    if (writer->write(writer, value_buf, 8) < 8)
    {
        // ERROR: End of file or out of space
        return -1;
    }

    return 0;
}

static dbof_object_unsigned_long_integer __dbof_1_read_object_unsigned_long_integer(dbof_reader* reader)
{
    dbof_unsigned_long_integer value = 0;

    // Read 8 bytes
    char value_buf[8];
    if (reader->read(reader, value_buf, 8) < 8)
    {
        // ERROR: End of file
        return NULL;
    }

    // Unpack little-endian 64-bit integer (LSB stored first)
    value |= ((uint64_t) value_buf[0]) << 0;
    value |= ((uint64_t) value_buf[1]) << 8;
    value |= ((uint64_t) value_buf[2]) << 16;
    value |= ((uint64_t) value_buf[3]) << 24;
    value |= ((uint64_t) value_buf[4]) << 32;
    value |= ((uint64_t) value_buf[5]) << 40;
    value |= ((uint64_t) value_buf[6]) << 48;
    value |= ((uint64_t) value_buf[7]) << 56;

    // Set value
    dbof_object_unsigned_long_integer object = __new_object_unsigned_long_integer();
    dbof_set_value_unsigned_long_integer(object, value);
    return object;
}

static int __dbof_1_write_object_unsigned_long_integer(dbof_object_unsigned_long_integer object, dbof_writer* writer)
{
    // Get value
    dbof_unsigned_long_integer value = dbof_get_value_unsigned_long_integer(object);

    // Pack little-endian 64-bit integer (LSB stored first)
    char value_buf[8];
    value_buf[0] = (uint8_t) ((value & 0x00000000000000fful) >> 0);
    value_buf[1] = (uint8_t) ((value & 0x000000000000ff00ul) >> 8);
    value_buf[2] = (uint8_t) ((value & 0x0000000000ff0000ul) >> 16);
    value_buf[3] = (uint8_t) ((value & 0x00000000ff000000ul) >> 24);
    value_buf[4] = (uint8_t) ((value & 0x000000ff00000000ul) >> 32);
    value_buf[5] = (uint8_t) ((value & 0x0000ff0000000000ul) >> 40);
    value_buf[6] = (uint8_t) ((value & 0x00ff000000000000ul) >> 48);
    value_buf[7] = (uint8_t) ((value & 0xff00000000000000ul) >> 56);

    // Write 8 bytes
    if (writer->write(writer, value_buf, 8) < 8)
    {
        // ERROR: End of file or out of space
        return -1;
    }

    return 0;
}

static dbof_object_boolean __dbof_1_read_object_boolean(dbof_reader* reader)
{
    dbof_boolean value = 0;

    // Read 1 byte
    if (reader->read(reader, (char*) &value, 1) < 1)
    {
        // ERROR: End of file
        return NULL;
    }

    // Set value
    dbof_object_boolean object = __new_object_boolean();
    dbof_set_value_boolean(object, value);
    return object;
}

static int __dbof_1_write_object_boolean(dbof_object_boolean object, dbof_writer* writer)
{
    // Get value
    dbof_boolean value = dbof_get_value_boolean(object);

    // Write 1 byte
    if (writer->write(writer, (char*) &value, 1) < 1)
    {
        // ERROR: End of file or out of space
        return -1;
    }

    return 0;
}

//
// IMPORTANT
//
// We are assuming the architecture stores single- and double-precision floating-point numbers in memory as the common
// IEEE 754 binary32 and binary64 representations. We don't require fully-conforming float *operations* from the
// compiler, but memory representation is a necessity. Using an architecture with another representation will result in
// ill-formed serialized objects.
//

static dbof_object_single_float __dbof_1_read_object_single_float(dbof_reader* reader)
{
    // Read 4 bytes
    char value_buf[4];
    if (reader->read(reader, value_buf, 4) < 4)
    {
        // ERROR: End of file
        return NULL;
    }

    // Unpack little-endian IEEE 754 binary32 float (LSB stored first)
    uint32_t value_tmp = 0;
    value_tmp |= ((uint32_t) value_buf[0]) << 0;
    value_tmp |= ((uint32_t) value_buf[1]) << 8;
    value_tmp |= ((uint32_t) value_buf[2]) << 16;
    value_tmp |= ((uint32_t) value_buf[3]) << 24;

    // Convert to single float value
    union
    {
        uint32_t in;
        dbof_single_float out;
    } cvt = { value_tmp };

    // Set value
    dbof_object_single_float object = __new_object_single_float();
    dbof_set_value_single_float(object, cvt.out);
    return object;
}

static int __dbof_1_write_object_single_float(dbof_object_single_float object, dbof_writer* writer)
{
    // Get value
    dbof_single_float value = dbof_get_value_single_float(object);

    // Convert to unsigned integer
    union
    {
        dbof_single_float in;
        uint32_t out;
    } cvt = { value };

    // Pack little-endian IEEE 754 binary32 float (LSB stored first)
    char value_buf[4];
    value_buf[0] = (uint8_t) ((cvt.out & 0x000000ffu) >> 0);
    value_buf[1] = (uint8_t) ((cvt.out & 0x0000ff00u) >> 8);
    value_buf[2] = (uint8_t) ((cvt.out & 0x00ff0000u) >> 16);
    value_buf[3] = (uint8_t) ((cvt.out & 0xff000000u) >> 24);

    // Write 4 bytes
    if (writer->write(writer, value_buf, 4) < 4)
    {
        // ERROR: End of file or out of space
        return -1;
    }

    return 0;
}

static dbof_object_double_float __dbof_1_read_object_double_float(dbof_reader* reader)
{
    // Read 8 bytes
    char value_buf[8];
    if (reader->read(reader, value_buf, 8) < 8)
    {
        // ERROR: End of file
        return NULL;
    }

    // Unpack little-endian IEEE 754 binary64 float (LSB stored first)
    uint64_t value_tmp = 0;
    value_tmp |= ((uint64_t) value_buf[0]) << 0;
    value_tmp |= ((uint64_t) value_buf[1]) << 8;
    value_tmp |= ((uint64_t) value_buf[2]) << 16;
    value_tmp |= ((uint64_t) value_buf[3]) << 24;
    value_tmp |= ((uint64_t) value_buf[4]) << 32;
    value_tmp |= ((uint64_t) value_buf[5]) << 40;
    value_tmp |= ((uint64_t) value_buf[6]) << 48;
    value_tmp |= ((uint64_t) value_buf[7]) << 56;

    // Convert to double float value
    union
    {
        uint64_t in;
        dbof_double_float out;
    } cvt = { value_tmp };

    // Set value
    dbof_object_double_float object = __new_object_double_float();
    dbof_set_value_double_float(object, cvt.out);
    return object;
}

static int __dbof_1_write_object_double_float(dbof_object_double_float object, dbof_writer* writer)
{
    // Get value
    dbof_double_float value = dbof_get_value_double_float(object);

    // Convert to unsigned integer
    union
    {
        dbof_double_float in;
        uint64_t out;
    } cvt = { value };

    // Pack little-endian IEEE 754 binary64 float (LSB stored first)
    char value_buf[8];
    value_buf[0] = (uint8_t) ((cvt.out & 0x00000000000000fful) >> 0);
    value_buf[1] = (uint8_t) ((cvt.out & 0x000000000000ff00ul) >> 8);
    value_buf[2] = (uint8_t) ((cvt.out & 0x0000000000ff0000ul) >> 16);
    value_buf[3] = (uint8_t) ((cvt.out & 0x00000000ff000000ul) >> 24);
    value_buf[4] = (uint8_t) ((cvt.out & 0x000000ff00000000ul) >> 32);
    value_buf[5] = (uint8_t) ((cvt.out & 0x0000ff0000000000ul) >> 40);
    value_buf[6] = (uint8_t) ((cvt.out & 0x00ff000000000000ul) >> 48);
    value_buf[7] = (uint8_t) ((cvt.out & 0xff00000000000000ul) >> 56);

    // Write 8 bytes
    if (writer->write(writer, value_buf, 8) < 8)
    {
        // ERROR: End of file or out of space
        return -1;
    }

    return 0;
}

static dbof_object_character __dbof_1_read_object_character(dbof_reader* reader)
{
    dbof_character value = 0;

    // Read 4 bytes
    char value_buf[4];
    if (reader->read(reader, value_buf, 4) < 4)
    {
        // ERROR: End of file
        return NULL;
    }

    // Unpack little-endian character (LSB stored first)
    value |= ((uint32_t) value_buf[0]) << 0;
    value |= ((uint32_t) value_buf[1]) << 8;
    value |= ((uint32_t) value_buf[2]) << 16;
    value |= ((uint32_t) value_buf[3]) << 24;

    // Get value
    dbof_object_character object = __new_object_character();
    dbof_set_value_character(object, value);
    return object;
}

static int __dbof_1_write_object_character(dbof_object_character object, dbof_writer* writer)
{
    // Get value
    dbof_character value = dbof_get_value_unsigned_integer(object);

    // Pack little-endian character (LSB stored first)
    char value_buf[4];
    value_buf[0] = (uint8_t) ((value & 0x000000ffu) >> 0);
    value_buf[1] = (uint8_t) ((value & 0x0000ff00u) >> 8);
    value_buf[2] = (uint8_t) ((value & 0x00ff0000u) >> 16);
    value_buf[3] = (uint8_t) ((value & 0xff000000u) >> 24);

    // Write 4 bytes
    if (writer->write(writer, value_buf, 4) < 4)
    {
        // ERROR: End of file or out of space
        return -1;
    }

    return 0;
}

/**
 * Internal algorithm to calculate the minimum number of 8-bit bytes necessary to represent up to a 64-bit integer
 * without loss of information.
 *
 * @param value The value in question
 * @return The required number of bytes
 */
static int __count_min_bytes_internal(uint64_t value)
{
    if ((value & 0x00000000000000fful) == value)
        return 1;
    if ((value & 0x000000000000fffful) == value)
        return 2;
    if ((value & 0x0000000000fffffful) == value)
        return 3;
    if ((value & 0x00000000fffffffful) == value)
        return 4;
    if ((value & 0x000000fffffffffful) == value)
        return 5;
    if ((value & 0x0000fffffffffffful) == value)
        return 6;
    if ((value & 0x00fffffffffffffful) == value)
        return 7;

    return 8;
}

/**
 * Internal procedure for reading flex lengths as defined in DBOF-1.
 *
 * @param       reader The reader
 * @param [out] out_length The length
 * @return Zero on success, otherwise nonzero
 */
static int __dbof_1_read_flex_length_internal(dbof_reader* reader, uint64_t* out_length)
{
    char length_size;
    char length_buf[8] = {};
    uint64_t length = 0;

    // Read size of flex length data
    if (reader->read(reader, &length_size, 1) < 1)
        goto fail_eof;

    // Limited by DBOF-1 spec to a max of 8
    if (length_size > 8)
        goto fail_out_of_spec;

    // Read flex length data
    if (reader->read(reader, length_buf, (size_t) length_size) < length_size)
        goto fail_eof;

    // Unpack flex length (little-endian, LSB stored first)
    for (int i = 0; i < length_size; ++i)
    {
        length |= ((uint64_t) length_buf[i]) << i * 8;
    }

    *out_length = length;
    return 0;

fail_eof:
fail_out_of_spec:
    return -1;
}

/**
 * Internal procedure for writing flex lengths as defined in DBOF-1.
 *
 * @param writer The writer
 * @param length The length
 * @return Zero on success, otherwise nonzero
 */
static int __dbof_1_write_flex_length_internal(dbof_writer* writer, uint64_t length)
{
    char length_buf[8];

    // Calculate size of flex length data
    char length_size = (char) __count_min_bytes_internal(length);

    // Write length size
    if (writer->write(writer, &length_size, 1) < 1)
        goto fail_eof;

    // Pack flex length (little-endian, LSB stored first)
    for (int i = 0; i < length_size; ++i)
    {
        length_buf[i] = (uint8_t) ((length & (0x00000000000000fful << i * 8)) >> i * 8);
    }

    // Write length data
    if (writer->write(writer, length_buf, (size_t) length_size) < length_size)
        goto fail_eof;

    return 0;

fail_eof:
    return -1;
}

static dbof_object_utf8_string __dbof_1_read_object_utf8_string(dbof_reader* reader)
{
    struct __object_utf8_string_impl* string = __new_object_utf8_string();

    dbof_string_size length;
    char* value = NULL; // free(NULL) is well-defined

    // Read string length as flex length
    if (__dbof_1_read_flex_length_internal(reader, &length))
        goto fail;

    // Allocate memory for string value (plus null terminator)
    value = malloc(length + 1);
    if (value == NULL)
        goto fail;

    // Read string value
    if (reader->read(reader, value, length) < length)
        goto fail_eof;

    // This is untrusted input, so make sure there's a null terminator
    value[length] = '\0';

    string->value = value;
    return string;

fail:
fail_eof:
    free(value);
    __delete_object_utf8_string(string);
    return NULL;
}

static int __dbof_1_write_object_string(dbof_object_string object, dbof_writer* writer)
{
    struct __object_utf8_string_impl* string = (struct __object_utf8_string_impl*) object;

    dbof_string value = string->value;
    dbof_string_size length = strlen(value);

    // Write string length as flex length
    if (__dbof_1_write_flex_length_internal(writer, length))
        goto fail;

    // Write string value
    if (writer->write(writer, value, length) < length)
        goto fail_eof;

    return 0;

fail:
fail_eof:
    return -1;
}

/**
 * Internal function to read an object in DBOF-1 format.
 *
 * @param reader The reader
 * @param read_type Whether to write the object type (nonzero) or not (zero)
 * @return The read object or NULL if an error occurred
 */
static dbof_object __dbof_1_read_object(dbof_reader* reader, int read_type);

/**
 * Internal function to write an object in DBOF-1 format.
 *
 * @param object The object to write
 * @param writer The writer
 * @param write_type Whether to write the object type (nonzero) or not (zero)
 * @return Zero upon success, otherwise nonzero
 */
static int __dbof_1_write_object(dbof_object object, dbof_writer* writer, int write_type);

static dbof_object_typed_array __dbof_1_read_object_typed_array(dbof_reader* reader)
{
    struct __object_typed_array_impl* array = __new_object_typed_array();

    uint64_t size;
    char element_type_id;

    // Read array length as flex length
    if (__dbof_1_read_flex_length_internal(reader, &size))
        goto fail;

    // Read element type ID
    if (reader->read(reader, &element_type_id, 1) < 1)
        goto fail_eof;

    // Pre-allocate the required storage space
    __object_typed_array_impl_resize(array, size);

    array->type = (dbof_type) element_type_id;

    // Read each object individually
    for (dbof_container_size i = 0; i < size; ++i)
    {
        dbof_object object = __dbof_1_read_object(reader, 0);
        if (object == NULL)
            goto fail_protocol;

        __object_typed_array_impl_push_back(array, object);
    }

    return array;

fail:
fail_eof:
fail_protocol:
    __delete_object_typed_array(array);
    return NULL;
}

static int __dbof_1_write_object_typed_array(dbof_object_typed_array array, dbof_writer* writer)
{
    struct __object_typed_array_impl* array_impl = (struct __object_typed_array_impl*) array;

    dbof_container_size size = __object_typed_array_impl_get_size(array_impl);
    char element_type_id = array_impl->type;

    // Write array length as flex length
    if (__dbof_1_write_flex_length_internal(writer, size))
        goto fail;

    // Write element type ID
    if (writer->write(writer, &element_type_id, 1) < 1)
        goto fail_eof;

    // Write each object individually
    for (dbof_container_size i = 0; i < size; ++i)
    {
        __dbof_1_write_object(__object_typed_array_impl_get(array_impl, i), writer, 0);
    }

    return 0;

fail:
fail_eof:
    return -1;
}

static dbof_object_untyped_array __dbof_1_read_object_untyped_array(dbof_reader* reader)
{
    struct __object_untyped_array_impl* array = __new_object_untyped_array();

    uint64_t size;

    // Read array size as flex length
    if (__dbof_1_read_flex_length_internal(reader, &size))
        goto fail;

    // Pre-allocate the required storage space
    __object_untyped_array_impl_resize(array, size);

    // Read each object individually
    for (dbof_container_size i = 0; i < size; ++i)
    {
        dbof_object object = __dbof_1_read_object(reader, 0);
        if (object == NULL)
            goto fail_protocol;

        __object_untyped_array_impl_push_back(array, object);
    }

    return array;

fail:
fail_protocol:
    __delete_object_untyped_array(array);
    return NULL;
}

static int __dbof_1_write_object_untyped_array(dbof_object_untyped_array array, dbof_writer* writer)
{
    struct __object_untyped_array_impl* array_impl = (struct __object_untyped_array_impl*) array;

    dbof_container_size size = __object_untyped_array_impl_get_size(array_impl);

    // Write array size as flex length
    if (__dbof_1_write_flex_length_internal(writer, size))
        goto fail;

    // Write each object individually
    for (dbof_container_size i = 0; i < size; ++i)
    {
        if (__dbof_1_write_object(__object_untyped_array_impl_get(array_impl, i), writer, 0))
            goto fail_eof;
    }

    return 0;

fail:
fail_eof:
    return -1;
}

static dbof_object_typed_map __dbof_1_read_object_typed_map(dbof_reader* reader)
{
    struct __object_typed_map_impl* map = __new_object_typed_map();

    uint64_t size;
    char key_type_id;
    char value_type_id;

    // Read map size as flex length
    if (__dbof_1_read_flex_length_internal(reader, &size))
        goto fail;

    // Read key type ID
    if (reader->read(reader, &key_type_id, 1) < 1)
        goto fail_eof;

    // Read value type ID
    if (reader->read(reader, &value_type_id, 1) < 1)
        goto fail_eof;

    map->size = (dbof_container_size) size;
    map->key_type = (dbof_type) key_type_id;
    map->value_type = (dbof_type) value_type_id;

    // TODO: Read children

    return map;

fail:
fail_eof:
    __delete_object_typed_map(map);
    return NULL;
}

static int __dbof_1_write_object_typed_map(dbof_object_typed_map object, dbof_writer* writer)
{
    struct __object_typed_map_impl* map = (struct __object_typed_map_impl*) object;

    dbof_container_size size = map->size;
    char key_type_id = map->key_type;
    char value_type_id = map->value_type;

    // Write map size as flex length
    if (__dbof_1_write_flex_length_internal(writer, size))
        goto fail;

    // Write key type ID
    if (writer->write(writer, &key_type_id, 1) < 1)
        goto fail_eof;

    // Write value type ID
    if (writer->write(writer, &value_type_id, 1) < 1)
        goto fail_eof;

    // TODO: Write key-value pairs of children

    return 0;

fail:
fail_eof:
    return -1;
}

static dbof_object_untyped_map __dbof_1_read_object_untyped_map(dbof_reader* reader)
{
    struct __object_untyped_map_impl* map = __new_object_untyped_map();

    uint64_t size;

    // Read map size as flex length
    if (__dbof_1_read_flex_length_internal(reader, &size))
        goto fail;

    map->size = (dbof_container_size) size;

    // TODO: Read children

    return map;

fail:
fail_eof:
    __delete_object_untyped_map(map);
    return NULL;
}

static int __dbof_1_write_object_untyped_map(dbof_object_untyped_map map, dbof_writer* writer)
{
    struct __object_untyped_map_impl* map_impl = (struct __object_untyped_map_impl*) map;

    dbof_container_size size = map_impl->size;

    // Write map size as flex length
    if (__dbof_1_write_flex_length_internal(writer, size))
        goto fail;

    // TODO: Write key-value pairs of children

    return 0;

fail:
fail_eof:
    return -1;
}

static dbof_object __dbof_1_read_object(dbof_reader* reader, int read_type)
{
    // Read object type ID
    char type_id;
    if (reader->read(reader, &type_id, 1) < 1)
        return NULL;

    // Delegate to appropriate read function
    switch (type_id)
    {
    case DBOF_TYPE_NULL:
        return __dbof_1_read_object_null(reader);
    case DBOF_TYPE_SIGNED_BYTE:
        return __dbof_1_read_object_signed_byte(reader);
    case DBOF_TYPE_UNSIGNED_BYTE:
        return __dbof_1_read_object_unsigned_byte(reader);
    case DBOF_TYPE_SIGNED_INTEGER:
        return __dbof_1_read_object_signed_integer(reader);
    case DBOF_TYPE_UNSIGNED_INTEGER:
        return __dbof_1_read_object_unsigned_integer(reader);
    case DBOF_TYPE_SIGNED_LONG_INTEGER:
        return __dbof_1_read_object_signed_long_integer(reader);
    case DBOF_TYPE_UNSIGNED_LONG_INTEGER:
        return __dbof_1_read_object_unsigned_long_integer(reader);
    case DBOF_TYPE_BOOLEAN:
        return __dbof_1_read_object_boolean(reader);
    case DBOF_TYPE_SINGLE_FLOAT:
        return __dbof_1_read_object_single_float(reader);
    case DBOF_TYPE_DOUBLE_FLOAT:
        return __dbof_1_read_object_double_float(reader);
    case DBOF_TYPE_CHARACTER:
        return __dbof_1_read_object_character(reader);
    case DBOF_TYPE_UTF8_STRING:
        return __dbof_1_read_object_utf8_string(reader);
    case DBOF_TYPE_TYPED_ARRAY:
        return __dbof_1_read_object_typed_array(reader);
    case DBOF_TYPE_UNTYPED_ARRAY:
        return __dbof_1_read_object_untyped_array(reader);
    case DBOF_TYPE_TYPED_MAP:
        return __dbof_1_read_object_typed_map(reader);
    case DBOF_TYPE_UNTYPED_MAP:
        return __dbof_1_read_object_untyped_map(reader);
    default:
        // ERROR: Unrecognized object type ID
        return NULL;
    }
}

static int __dbof_1_write_object(dbof_object object, dbof_writer* writer, int write_type)
{
    // Write object type ID
    // We rely on an equivalence between enum ordinal and object type ID
    // This is guaranteed as of right now, but not documented in the header
    char type_id = dbof_typeof(object);
    if (writer->write(writer, &type_id, 1) < 1)
        return -1;

    // Delegate to appropriate write function
    switch (type_id)
    {
    case DBOF_TYPE_NULL:
        return __dbof_1_write_object_null(object, writer);
    case DBOF_TYPE_SIGNED_BYTE:
        return __dbof_1_write_object_signed_byte(object, writer);
    case DBOF_TYPE_UNSIGNED_BYTE:
        return __dbof_1_write_object_unsigned_byte(object, writer);
    case DBOF_TYPE_SIGNED_INTEGER:
        return __dbof_1_write_object_signed_integer(object, writer);
    case DBOF_TYPE_UNSIGNED_INTEGER:
        return __dbof_1_write_object_unsigned_integer(object, writer);
    case DBOF_TYPE_SIGNED_LONG_INTEGER:
        return __dbof_1_write_object_signed_long_integer(object, writer);
    case DBOF_TYPE_UNSIGNED_LONG_INTEGER:
        return __dbof_1_write_object_unsigned_long_integer(object, writer);
    case DBOF_TYPE_BOOLEAN:
        return __dbof_1_write_object_boolean(object, writer);
    case DBOF_TYPE_SINGLE_FLOAT:
        return __dbof_1_write_object_single_float(object, writer);
    case DBOF_TYPE_DOUBLE_FLOAT:
        return __dbof_1_write_object_double_float(object, writer);
    case DBOF_TYPE_CHARACTER:
        return __dbof_1_write_object_character(object, writer);
    case DBOF_TYPE_UTF8_STRING:
        return __dbof_1_write_object_string(object, writer);
    case DBOF_TYPE_TYPED_ARRAY:
        return __dbof_1_write_object_typed_array(object, writer);
    case DBOF_TYPE_UNTYPED_ARRAY:
        return __dbof_1_write_object_untyped_array(object, writer);
    case DBOF_TYPE_TYPED_MAP:
        return __dbof_1_write_object_typed_map(object, writer);
    case DBOF_TYPE_UNTYPED_MAP:
        return __dbof_1_write_object_untyped_map(object, writer);
    default:
        // ERROR: Unrecognized object type ID
        return -1;
    }
}

/* Dispatched DBOF Serialization */

//
// Each serialized top-level object has a six-byte header, regardless of the serialization format or version.
//
// This header is composed of two fields:
// 1. A four-byte magic number (the UTF-8 characters 'D', 'B', 'O', and 'F')
// 2. A two-byte primary version ID (a sixteen-bit little-endian version number)
//

dbof_object dbof_read(dbof_reader* reader)
{
    unsigned short version;

    if (reader->no_header)
    {
        if (!reader->use_version)
        {
            // ERROR: Header skipped but no version specified
            return NULL;
        }

        version = reader->use_version;
    }
    else
    {
        // Extract the six-byte header
        char header[6];
        reader->read(reader, header, sizeof(header));

        // Compare the magic number to expected
        char magic[] = { header[0], header[1], header[2], header[3], '\0' };
        if (strcmp(magic, "DBOF") != 0)
        {
            // ERROR: Magic number does not match expected value
            return NULL;
        }

        // Get version integer in little-endian manner
        version = 0;
        version |= ((uint16_t) header[4]) << 0; // LSB stored first
        version |= ((uint16_t) header[5]) << 8; // MSB stored second
    }

    // Read top-level object depending on version
    switch (version)
    {
    case 1:
        // Read using DBOF-1
        return __dbof_1_read_object(reader, 1);
    default:
        // ERROR: Unsupported serialization format
        return NULL;
    }
}

int dbof_write(dbof_object object, dbof_writer* writer)
{
    // Get version to write, or default to latest
    short version = writer->use_version;
    if (version == 0)
    {
        version = DBOF_SER_DEFAULT;
    }

    if (!writer->no_header)
    {
        // Build header with magic number and version
        char version_lsb = (char) ((version & 0x00ff) >> 0);
        char version_msb = (char) ((version & 0xff00) >> 8);
        char header[] = { 'D', 'B', 'O', 'F', version_lsb, version_msb };

        // Write header
        writer->write(writer, header, sizeof(header));
    }

    // Write top-level object depending on version
    switch (version)
    {
    case 1:
        // Write using DBOF-1
        return __dbof_1_write_object(object, writer, 1);
    default:
        // ERROR: Unsupported serialization format
        return 1;
    }
}
