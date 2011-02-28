//
// Raster.h
//

#pragma once

namespace FileGDBAPI
{

class ByteArray;
class Row;

/// Provides read and write access to raster data.
class EXT_FILEGDB_API Raster
{
public:

  /// @name Data access
  //@{
  /// TODO: Write description.
  /// @param[out]   format TODO
  /// @returns      A long integer indicating whether the method finished successfully.
  //long GetFormat(std::wstring& format);

  /// TODO: Write description.
  /// @param[in]    format TODO
  /// @returns      A long integer indicating whether the method finished successfully.
  //long SetFormat(const std::wstring& format);

  /// TODO: Write description.
  /// @param[out]   bytes TODO
  /// @returns      A long integer indicating whether the method finished successfully.
  //long GetBytes(ByteArray& bytes);

  /// TODO: Write description.
  /// @param[in]    bytes TODO
  /// @returns      A long integer indicating whether the method finished successfully.
  //long SetBytes(const ByteArray& bytes);

  /// TODO: Write description.
  /// @param[out]   attributes TODO
  /// @returns      A long integer indicating whether the method finished successfully.
  //long GetAttributes(Row attributes);

  /// TODO: Write description.
  /// @param[in]    attributes TODO
  /// @returns      A long integer indicating whether the method finished successfully.
  //long SetAttributes(Row attributes);
  //@}

  /// @name Constructors and Destructors
  //@{
  /// The class constructor.
  Raster();

  /// The class destructor.
  ~Raster();
  //@}

private:

  Raster(const Raster&){}
  Raster& operator=(const Raster&){ return *this; }


};

};  // namespace FileGDBAPI
