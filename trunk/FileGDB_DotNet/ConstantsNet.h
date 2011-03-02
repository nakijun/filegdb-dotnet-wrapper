using namespace System;

namespace FileGDB_DotNet 
{
	public ref class ConstantsNet 
	{
	public:
		// Item Types
		static const String^ ITEM_TYPE_FEATURE_CLASS = "Feature Class";
		static const String^ ITEM_TYPE_ITEM = "Item";
		static const String^ ITEM_TYPE_RANGE_DOMAIN = "Range Domain";
		static const String^ ITEM_TYPE_EXTENSION_DATASET = "Extension Dataset";
		static const String^ ITEM_TYPE_PARCEL_FABRIC = "Parcel Fabric";
		static const String^ ITEM_TYPE_WORKSPACE_EXTENSION = "Workspace Extension";
		static const String^ ITEM_TYPE_DOMAIN = "Domain";
		static const String^ ITEM_TYPE_RELATIONSHIP_CLASS = "Relationship Class";
		static const String^ ITEM_TYPE_RASTER_CATALOG = "Raster Catalog";
		static const String^ ITEM_TYPE_FOLDER = "Folder";
		static const String^ ITEM_TYPE_TIN = "Tin";
		static const String^ ITEM_TYPE_DATASET = "Dataset";
		static const String^ ITEM_TYPE_SURVEY_DATASET = "Survey Dataset";
		static const String^ ITEM_TYPE_ABSTRACT_TABLE = "AbstractTable";
		static const String^ ITEM_TYPE_MOSAIC_DATASET = "Mosaic Dataset";
		static const String^ ITEM_TYPE_FEATURE_DATASET = "Feature Dataset";
		static const String^ ITEM_TYPE_SCHEMATIC_DATASET = "Schematic Dataset";
		static const String^ ITEM_TYPE_TERRAIN = "Terrain";
		static const String^ ITEM_TYPE_REPLICA_DATASET = "Replica Dataset";
		static const String^ ITEM_TYPE_NETWORK_DATASET = "Network Dataset";
		static const String^ ITEM_TYPE_HISTORICAL_MARKER = "Historical Marker";
		static const String^ ITEM_TYPE_CATALOG_DATASET = "Catalog Dataset";
		static const String^ ITEM_TYPE_RESOURCE = "Resource";
		static const String^ ITEM_TYPE_TABLE = "Table";
		static const String^ ITEM_TYPE_RASTER_DATASET = "Raster Dataset";
		static const String^ ITEM_TYPE_GEOMETRIC_NETWORK = "Geometric Network";
		static const String^ ITEM_TYPE_TOPOLOGY = "Topology";
		static const String^ ITEM_TYPE_TOOLBOX = "Toolbox";
		static const String^ ITEM_TYPE_CODED_VALUE_DOMAIN = "Coded Value Domain";
		static const String^ ITEM_TYPE_REPLICA = "Replica";
		static const String^ ITEM_TYPE_REPRESENTATION_CLASS = "Representation Class";
		static const String^ ITEM_TYPE_WORKSPACE = "Workspace";

		// Relationship Types
		static const String^ RELATIONSHIP_TYPE_DATASETS_RELATED_THROUGH = "DatasetsRelatedThrough";
		static const String^ RELATIONSHIP_TYPE_ITEM_IN_FOLDER = "ItemInFolder";
		static const String^ RELATIONSHIP_TYPE_REPLICA_DATASET_IN_REPLICA = "ReplicaDatasetInReplica";
		static const String^ RELATIONSHIP_TYPE_FEATURE_CLASS_IN_TERRAIN = "FeatureClassInTerrain";
		static const String^ RELATIONSHIP_TYPE_FEATURE_CLASS_IN_TOPOLOGY = "FeatureClassInTopology";
		static const String^ RELATIONSHIP_TYPE_DATASET_IN_FEATURE_DATASET = "DatasetInFeatureDataset";
		static const String^ RELATIONSHIP_TYPE_DATASET_OF_REPLICA_DATASET = "DatasetOfReplicaDataset";
		static const String^ RELATIONSHIP_TYPE_FEATURE_CLASS_IN_PARCEL_FABRIC = "FeatureClassInParcelFabric";
		static const String^ RELATIONSHIP_TYPE_FEATURE_CLASS_IN_GEOMETRIC_NETWORK = "FeatureClassInGeometricNetwork";
		static const String^ RELATIONSHIP_TYPE_DATASET_IN_FOLDER = "DatasetInFolder";
		static const String^ RELATIONSHIP_TYPE_FOLDER_IN_FOLDER = "FolderInFolder";
		static const String^ RELATIONSHIP_TYPE_TABLE_IN_PARCEL_FABRIC = "TableInParcelFabric";
		static const String^ RELATIONSHIP_TYPE_FEATURE_CLASS_IN_NETWORK_DATASET = "FeatureClassInNetworkDataset";
		static const String^ RELATIONSHIP_TYPE_DOMAIN_IN_DATASET = "DomainInDataset";
		static const String^ RELATIONSHIP_TYPE_REPRESENTATION_OF_FEATURE_CLASS = "RepresentationOfFeatureClass";
		static const String^ RELATIONSHIP_TYPE_TABLE_IN_NETWORK_DATASET = "TableInNetworkDataset";

		// esriFieldTypes
		static const String^ ESRI_FIELD_TYPE_SMALL_INTEGER = "esriFieldTypeSmallInteger";
		static const String^ ESRI_FIELD_TYPE_INTEGER = "esriFieldTypeInteger";
		static const String^ ESRI_FIELD_TYPE_SINGLE = "esriFieldTypeSingle";
		static const String^ ESRI_FIELD_TYPE_DOUBLE = "esriFieldTypeDouble";
		static const String^ ESRI_FIELD_TYPE_STRING = "esriFieldTypeString";
		static const String^ ESRI_FIELD_TYPE_DATE = "esriFieldTypeDate";
		static const String^ ESRI_FIELD_TYPE_OID = "esriFieldTypeOID";
		static const String^ ESRI_FIELD_TYPE_GEOMETRY = "esriFieldTypeGeometry";
		static const String^ ESRI_FIELD_TYPE_BLOB = "esriFieldTypeBlob";
		static const String^ ESRI_FIELD_TYPE_RASTER = "esriFieldTypeRaster";
		static const String^ ESRI_FIELD_TYPE_GUID = "esriFieldTypeGUID";
		static const String^ ESRI_FIELD_TYPE_GLOBAL_ID = "esriFieldTypeGlobalID";
		static const String^ ESRI_FIELD_TYPE_XML = "esriFieldTypeXML";
	};
}