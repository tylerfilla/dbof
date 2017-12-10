/*
 * DBOF
 * Copyright 2017 glyre
 */

#ifndef DBOF_FILE_H
#define DBOF_FILE_H

#include <stdio.h>
#include "dbof.h"

#ifdef __cplusplus
extern "C"
{
#endif

size_t __dbof_file_reader_impl_read(struct dbof_reader* reader, char* ptr, size_t size)
{
    FILE* file = (FILE*) reader->data;
    return fread(ptr, 1, size, file);
}

/**
 * Read a DBOF object from the given file. Returns NULL on failure.
 *
 * @param file The file
 * @return The object or NULL
 */
dbof_object dbof_file_read(FILE* file)
{
    // Set up the reader
    dbof_reader reader;
    reader.read = __dbof_file_reader_impl_read;
    reader.use_version = 0;
    reader.no_header = 0;
    reader.data = file;

    // Perform the read
    return dbof_read(&reader);
}

size_t __dbof_file_writer_impl_write(struct dbof_writer* writer, const char* ptr, size_t size)
{
    FILE* file = (FILE*) writer->data;
    return fwrite(ptr, 1, size, file);
}

/**
 * Write a DBOF object to the given file.
 *
 * @param object The object
 * @param file The file
 * @return Zero upon success, otherwise nonzero
 */
int dbof_file_write(dbof_object object, FILE* file)
{
    // TODO: Allow selection of version

    // Set up the writer
    dbof_writer writer;
    writer.write = __dbof_file_writer_impl_write;
    writer.use_version = 0; // Use latest version by default
    writer.no_header = 0;
    writer.data = file;

    // Perform the write
    return dbof_write(object, &writer);
}

#ifdef __cplusplus
}
#endif

#endif // #ifndef DBOF_FILE_H
