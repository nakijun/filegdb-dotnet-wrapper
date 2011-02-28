//
// GeodatabaseManagement.h
//

/// A set of functions for accessing, creating and deleting file geodatabases.
/// @file GeodatabaseManagement.h

#pragma once

namespace FileGDBAPI
{

class Geodatabase;

/// Creates a new 10.x file geodatabase in the specified location.
/// If the file geodatabase already exists a -2147220653 (TABLE_ALREADY_EXISTS) error will be returned.
/// If the path is seriously in error, say pointing to the wrong drive, a -2147467259 (E_FAIL) error is returned.
/// @param[in]    path The location where the geodatabase should be created.
/// @param[out]   geodatabase A reference to the newly-created geodatabase.
/// @return       A long integer indicating whether the method finished successfully.
EXT_FILEGDB_API long CreateGeodatabase(const std::wstring& path, Geodatabase& geodatabase);

/// Opens an existing 10.x file geodatabase.
/// If the path is incorrect a -2147024894 (PATH_NOT_FOUND) error will be returned.
/// @param[in]    path The path of the geodatabase.
/// @param[out]   geodatabase A reference to the opened geodatabase.
/// @return       A long integer indicating whether the method finished successfully.
EXT_FILEGDB_API long OpenGeodatabase(const std::wstring& path, Geodatabase& geodatabase);

/// Closes an open file geodatabase.
/// @param[in]    geodatabase A reference to the geodatabase.
/// @return       A long integer indicating whether the method finished successfully.
EXT_FILEGDB_API long CloseGeodatabase(Geodatabase& geodatabase);

/// Deletes a file geodatabase.
/// If the path is incorrect a -2147024894 (PATH_NOT_FOUND) error will be returned. 
/// If another process has a lock on the geodatabase, a -2147220947 (LOCK_CONFLICT) error will be returned.
/// If access is denied an E_FAIL is returned.
/// @param[in]    path The path of the geodatabase.
/// @return       A long integer indicating whether the method finished successfully.
EXT_FILEGDB_API long DeleteGeodatabase(const std::wstring& path);

};  // namespace FileGDBAPI
