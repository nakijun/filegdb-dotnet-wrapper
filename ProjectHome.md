This is a .NET wrapper for ESRI's recently released FileGDB API.  Its written in C++/CLI, so it can be used in a C# and VB.NET  applications without the need for PInvoke.  The wrapper is built against the 1.0 beta2 release of the FileGDB API.  The source download contains the wrapper source code, as well as a number of tests/samples illustrating how the wrapper can be used to gain access to the File Geodatabase from a managed .NET environment.


## Release Notes: ##

Mar 24, 2011 - Wrapper updated to work with FileGDB API 1.0 beta3 release.  Source, binary, and data package downloads added.  Note: FileGDB API beta3 has a bug with the IsEditable check which slows down creating/editing/deleting features.  Issue will be fixed by ESRI in the final code release.

Mar 07, 2011 - All API functionality implemented, added test project, fixed numerous bugs.  Added download package. (0.2)

Feb 28, 2011 - Initial public release (0.1)

## Bugs/Issues: ##

- Advanced geometries are not supported (geometries including Z/M values, curved segments, point IDs, multipatch, etc)