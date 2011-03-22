///**
// * Code by Sasa Ivetic (Map It Out Inc.) 2011
// */
//
//
//
//
//using namespace System;
//
//namespace FileGDB_DotNet 
//{
//	public ref class ConstantsNet 
//	{
//	public:
//		enum class FieldType
//		{
//		  fieldTypeSmallInteger = 0,
//		  fieldTypeInteger      = 1,
//		  fieldTypeSingle       = 2,
//		  fieldTypeDouble       = 3,
//		  fieldTypeString       = 4,
//		  fieldTypeDate         = 5,
//		  fieldTypeOID          = 6,
//		  fieldTypeGeometry     = 7,
//		  fieldTypeBlob         = 8,
//		  fieldTypeRaster       = 9,
//		  fieldTypeGUID         = 10,
//		  fieldTypeGlobalID     = 11,
//		  fieldTypeXML          = 12,
//		};
//
//		enum class ShapeType
//		{
//		  shapeNull               = 0,
//		  shapePoint              = 1,
//		  shapePointM             = 21,
//		  shapePointZM            = 11,
//		  shapePointZ             = 9,
//		  shapeMultipoint         = 8,
//		  shapeMultipointM        = 28,
//		  shapeMultipointZM       = 18,
//		  shapeMultipointZ        = 20,
//		  shapePolyline           = 3,
//		  shapePolylineM          = 23,
//		  shapePolylineZM         = 13,
//		  shapePolylineZ          = 10,
//		  shapePolygon            = 5,
//		  shapePolygonM           = 25,
//		  shapePolygonZM          = 15,
//		  shapePolygonZ           = 19,
//		  shapeMultiPatchM        = 31,
//		  shapeMultiPatch         = 32,
//		  shapeGeneralPolyline    = 50,
//		  shapeGeneralPolygon     = 51,
//		  shapeGeneralPoint       = 52,
//		  shapeGeneralMultipoint  = 53,
//		  shapeGeneralMultiPatch  = 54,
//		};
//
//		enum class ShapeModifiers
//		{
//		  shapeHasZs                  = 0x80000000,
//		  shapeHasMs                  = 1073741824,
//		  shapeHasCurves              = 536870912,
//		  shapeHasIDs                 = 268435456,
//		  shapeHasNormals             = 134217728,
//		  shapeHasTextures            = 67108864,
//		  shapeHasPartIDs             = 33554432,
//		  shapeHasMaterials           = 16777216,
//		  shapeIsCompressed           = 8388608,
//		  shapeModifierMask           = -16777216,
//		  shapeMultiPatchModifierMask = 15728640,
//		  shapeBasicTypeMask          = 255,
//		  shapeBasicModifierMask      = -1073741824,
//		  shapeNonBasicModifierMask   = 1056964608,
//		  shapeExtendedModifierMask   = -587202560
//		};
//
//		enum class GeometryType
//		{
//		  geometryNull        = 0,
//		  geometryPoint       = 1,
//		  geometryMultipoint  = 2,
//		  geometryPolyline    = 3,
//		  geometryPolygon     = 4,
//		  geometryMultiPatch  = 9,
//		};
//
//
//		// Item Types
//		static const String^ ITEM_TYPE_FEATURE_CLASS = "Feature Class";
//		static const String^ ITEM_TYPE_ITEM = "Item";
//		static const String^ ITEM_TYPE_RANGE_DOMAIN = "Range Domain";
//		static const String^ ITEM_TYPE_EXTENSION_DATASET = "Extension Dataset";
//		static const String^ ITEM_TYPE_PARCEL_FABRIC = "Parcel Fabric";
//		static const String^ ITEM_TYPE_WORKSPACE_EXTENSION = "Workspace Extension";
//		static const String^ ITEM_TYPE_DOMAIN = "Domain";
//		static const String^ ITEM_TYPE_RELATIONSHIP_CLASS = "Relationship Class";
//		static const String^ ITEM_TYPE_RASTER_CATALOG = "Raster Catalog";
//		static const String^ ITEM_TYPE_FOLDER = "Folder";
//		static const String^ ITEM_TYPE_TIN = "Tin";
//		static const String^ ITEM_TYPE_DATASET = "Dataset";
//		static const String^ ITEM_TYPE_SURVEY_DATASET = "Survey Dataset";
//		static const String^ ITEM_TYPE_ABSTRACT_TABLE = "AbstractTable";
//		static const String^ ITEM_TYPE_MOSAIC_DATASET = "Mosaic Dataset";
//		static const String^ ITEM_TYPE_FEATURE_DATASET = "Feature Dataset";
//		static const String^ ITEM_TYPE_SCHEMATIC_DATASET = "Schematic Dataset";
//		static const String^ ITEM_TYPE_TERRAIN = "Terrain";
//		static const String^ ITEM_TYPE_REPLICA_DATASET = "Replica Dataset";
//		static const String^ ITEM_TYPE_NETWORK_DATASET = "Network Dataset";
//		static const String^ ITEM_TYPE_HISTORICAL_MARKER = "Historical Marker";
//		static const String^ ITEM_TYPE_CATALOG_DATASET = "Catalog Dataset";
//		static const String^ ITEM_TYPE_RESOURCE = "Resource";
//		static const String^ ITEM_TYPE_TABLE = "Table";
//		static const String^ ITEM_TYPE_RASTER_DATASET = "Raster Dataset";
//		static const String^ ITEM_TYPE_GEOMETRIC_NETWORK = "Geometric Network";
//		static const String^ ITEM_TYPE_TOPOLOGY = "Topology";
//		static const String^ ITEM_TYPE_TOOLBOX = "Toolbox";
//		static const String^ ITEM_TYPE_CODED_VALUE_DOMAIN = "Coded Value Domain";
//		static const String^ ITEM_TYPE_REPLICA = "Replica";
//		static const String^ ITEM_TYPE_REPRESENTATION_CLASS = "Representation Class";
//		static const String^ ITEM_TYPE_WORKSPACE = "Workspace";
//
//		// Relationship Types
//		static const String^ RELATIONSHIP_TYPE_DATASETS_RELATED_THROUGH = "DatasetsRelatedThrough";
//		static const String^ RELATIONSHIP_TYPE_ITEM_IN_FOLDER = "ItemInFolder";
//		static const String^ RELATIONSHIP_TYPE_REPLICA_DATASET_IN_REPLICA = "ReplicaDatasetInReplica";
//		static const String^ RELATIONSHIP_TYPE_FEATURE_CLASS_IN_TERRAIN = "FeatureClassInTerrain";
//		static const String^ RELATIONSHIP_TYPE_FEATURE_CLASS_IN_TOPOLOGY = "FeatureClassInTopology";
//		static const String^ RELATIONSHIP_TYPE_DATASET_IN_FEATURE_DATASET = "DatasetInFeatureDataset";
//		static const String^ RELATIONSHIP_TYPE_DATASET_OF_REPLICA_DATASET = "DatasetOfReplicaDataset";
//		static const String^ RELATIONSHIP_TYPE_FEATURE_CLASS_IN_PARCEL_FABRIC = "FeatureClassInParcelFabric";
//		static const String^ RELATIONSHIP_TYPE_FEATURE_CLASS_IN_GEOMETRIC_NETWORK = "FeatureClassInGeometricNetwork";
//		static const String^ RELATIONSHIP_TYPE_DATASET_IN_FOLDER = "DatasetInFolder";
//		static const String^ RELATIONSHIP_TYPE_FOLDER_IN_FOLDER = "FolderInFolder";
//		static const String^ RELATIONSHIP_TYPE_TABLE_IN_PARCEL_FABRIC = "TableInParcelFabric";
//		static const String^ RELATIONSHIP_TYPE_FEATURE_CLASS_IN_NETWORK_DATASET = "FeatureClassInNetworkDataset";
//		static const String^ RELATIONSHIP_TYPE_DOMAIN_IN_DATASET = "DomainInDataset";
//		static const String^ RELATIONSHIP_TYPE_REPRESENTATION_OF_FEATURE_CLASS = "RepresentationOfFeatureClass";
//		static const String^ RELATIONSHIP_TYPE_TABLE_IN_NETWORK_DATASET = "TableInNetworkDataset";
//
//		// esriFieldTypes
//		static const String^ ESRI_FIELD_TYPE_SMALL_INTEGER = "esriFieldTypeSmallInteger";
//		static const String^ ESRI_FIELD_TYPE_INTEGER = "esriFieldTypeInteger";
//		static const String^ ESRI_FIELD_TYPE_SINGLE = "esriFieldTypeSingle";
//		static const String^ ESRI_FIELD_TYPE_DOUBLE = "esriFieldTypeDouble";
//		static const String^ ESRI_FIELD_TYPE_STRING = "esriFieldTypeString";
//		static const String^ ESRI_FIELD_TYPE_DATE = "esriFieldTypeDate";
//		static const String^ ESRI_FIELD_TYPE_OID = "esriFieldTypeOID";
//		static const String^ ESRI_FIELD_TYPE_GEOMETRY = "esriFieldTypeGeometry";
//		static const String^ ESRI_FIELD_TYPE_BLOB = "esriFieldTypeBlob";
//		static const String^ ESRI_FIELD_TYPE_RASTER = "esriFieldTypeRaster";
//		static const String^ ESRI_FIELD_TYPE_GUID = "esriFieldTypeGUID";
//		static const String^ ESRI_FIELD_TYPE_GLOBAL_ID = "esriFieldTypeGlobalID";
//		static const String^ ESRI_FIELD_TYPE_XML = "esriFieldTypeXML";
//
//	};
//}