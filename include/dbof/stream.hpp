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

#ifndef DBOF_STREAM_HPP
#define DBOF_STREAM_HPP

#include <iostream>
#include "dbof.hpp"

namespace dbof
{

namespace stream
{

/**
 * Warning: Unstable API beyond this point. Use at your own risk.
 */
namespace __impl
{

std::size_t read(dbof_reader* reader, char* ptr, std::size_t size)
{
    // Unpack reference to input stream, then read the requested data
    std::istream& in = *static_cast<std::istream*>(reader->data);
    in.read(ptr, size);

    return static_cast<std::size_t>(in.gcount());
}

std::size_t write(dbof_writer* writer, const char* ptr, std::size_t size)
{
    // Unpack reference to output stream
    std::ostream& out = *static_cast<std::ostream*>(writer->data);

    // Remember the position in the stream so far, then write the requested data
    std::streamsize tellp_before = out.tellp();
    out.write(ptr, size);

    // Remember the I/O state after the write
    std::ostream::iostate state_before = out.rdstate();

    // If the write failed
    if (out.fail())
    {
        // Clear the I/O state to good so we can get some semblance of a write count from it
        out.clear();
    }

    // Calculate number of bytes written
    // Writes are buffered, anyway, so this is more or less "how many bytes DBOF no longer cares about"
    auto num_written = static_cast<std::size_t>(out.tellp() - tellp_before);

    // Replace the I/O state before it was cleared (this may set it back to a failure state)
    out.clear(state_before);

    return num_written;
}

} // namespace __impl

/**
 * Read a DBOF object from the given input stream.
 *
 * @param in The input stream
 * @return The object
 */
dbof::object* read(std::istream& in)
{
    // Set up the reader
    dbof_reader reader {};
    reader.read = __impl::read;
    reader.use_version = 0;
    reader.no_header = 0;
    reader.data = &in;

    // Perform the read
    return dbof::wrap(dbof_read(&reader));
}

/**
 * Write a DBOF object to the given output stream.
 *
 * @param out The output stream
 * @param object The object
 * @return True if the write was successful, otherwise false
 */
bool write(std::ostream& out, const dbof::object& object)
{
    // TODO: Allow selection of version

    // Set up the writer
    dbof_writer writer {};
    writer.write = __impl::write;
    writer.use_version = 0; // Use latest version by default
    writer.no_header = 0;
    writer.data = &out;

    // Perform the write
    return dbof_write(object.c_obj(), &writer) == 0;
}

} // namespace stream

} // namespace dbof

/**
 * Output stream DBOF object write operator.
 */
std::ostream& operator<<(std::ostream& out, const dbof::object& object)
{
    dbof::stream::write(out, object);
    return out;
}

#endif // #ifndef DBOF_STREAM_HPP
