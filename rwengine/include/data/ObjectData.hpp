#pragma once
#ifndef __GLT_OBJECTDATA_HPP__
#define __GLT_OBJECTDATA_HPP__
#include <stdint.h>
#include <string>
#include <vector>
#include <memory>
#include <glm/glm.hpp>

#include <data/PathData.hpp>

typedef uint16_t ObjectID;

/**
 * Stores basic information about an Object and it's real type.
 */
struct ObjectInformation
{
	typedef size_t ObjectClass;
	static ObjectClass _class(const std::string& name)
	{
		return std::hash<std::string>()(name);
	}

	ObjectID ID;
	const ObjectClass class_type;

	ObjectInformation(const ObjectClass type)
		: class_type(type) { }
		
	virtual ~ObjectInformation() { }
};

typedef std::shared_ptr<ObjectInformation> ObjectInformationPtr;

/**
 * Data used by	Normal Objects
 */
struct ObjectData : public ObjectInformation
{
	static const ObjectClass class_id;

	ObjectData()
		: ObjectInformation(_class("OBJS")) { }

	std::string modelName;
	std::string textureName;
	uint8_t numClumps;
	float drawDistance[3];
	int32_t flags;
	bool LOD;
	
	short timeOn;
	short timeOff;
	
	enum {
		WET          = 1,       /// Render with a wet effect
		NIGHTONLY    = 1 << 1,  /// Render only during the night
		ALPHA1       = 1 << 2,  /// Alpha 
		ALPHA2       = 1 << 3,  /// Alpha
		DAYONLY      = 1 << 4,  /// Render only during the day
		INTERIOR     = 1 << 5,  /// Is part of an interior
		NOSHADOWMESH = 1 << 6,  /// Disable shadow mesh
		DONTCULL     = 1 << 7,  /// Disable culling
		NODRAWDIST   = 1 << 8,  /// Object won't be affected by draw distance
		BREAKABLE    = 1 << 9,  /// Object can be broken
		SMASHABLE    = 1 << 10, /// Object can be smashed and broken
		GRGEDOOR     = 1 << 11, /// Is a garage door (SA and IV only)
		MULTICLUMP   = 1 << 12, /// Multiclump
		WBRIGHTNESS  = 1 << 13, /// Weather PoleShd value effects brightness.
		EXPLODEONHIT = 1 << 14, /// Object explodes after being hit
	};

	// Information loaded from PATH sections
	std::vector<PathData> paths;
};

typedef std::shared_ptr<ObjectData> ObjectDataPtr;

/**
 * Data used by peds
 */
struct CharacterData : public ObjectInformation
{
	static const ObjectClass class_id;

	CharacterData()
		: ObjectInformation(_class("PEDS")) { }

	std::string modelName;
	std::string textureName;
	std::string type;
	std::string behaviour;
	std::string animGroup;
	uint8_t driveMask;
};

/**
 * @brief Stores vehicle data loaded from item definition files.
 */
struct VehicleData : public ObjectInformation
{
	static const ObjectClass class_id;

	VehicleData()
		: ObjectInformation(_class("CARS")) { }

	enum VehicleClass
	{
		IGNORE      = 0,
		NORMAL      = 1,
		POORFAMILY  = 1 << 1,
		RICHFAMILY  = 1 << 2,
		EXECUTIVE   = 1 << 3,
		WORKER      = 1 << 4,
		BIG         = 1 << 5,
		TAXI        = 1 << 6,
		MOPED       = 1 << 7,
		MOTORBIKE   = 1 << 8,
		LEISUREBOAT = 1 << 9,
		WORKERBOAT  = 1 << 10,
		BICYCLE     = 1 << 11,
		ONFOOT      = 1 << 12,
	};

	enum VehicleType {
		CAR,
		BOAT,
		TRAIN,
		PLANE,
		HELI,
	};

	std::string modelName;
	std::string textureName;
	VehicleType type;
	std::string handlingID;
	std::string gameName;
	VehicleClass classType;
	uint8_t frequency; // big enough int type?
	uint8_t lvl; // big enough int type?
	uint16_t comprules;
	union { // big enough int types?
		uint16_t wheelModelID; // used only when type == CAR
		int16_t modelLOD; // used only when type == PLANE
	};
	float wheelScale; // used only when type == CAR
};

typedef std::shared_ptr<VehicleData> VehicleDataHandle;

struct CutsceneObjectData : public ObjectInformation
{
	static const ObjectClass class_id;

	CutsceneObjectData()
		: ObjectInformation(_class("HIER")) { }

	std::string modelName;
	std::string textureName;
};

/** 
 * This is orthogonal to object class, it gives
 * Instances different physical properties.
 */
struct DynamicObjectData
{
	std::string modelName;
	float mass; // Kg
	float turnMass; // Kg m^3
	float airRes; // fraction
	float elacticity; // "
	float bouancy;
	float uprootForce; // Force
	float collDamageMulti;
	/*
	 * 1: change model
	 * 2: split model
	 * 3: smash
	 * 4: change and smash
	 */
	uint8_t collDamageFlags;
	/*
	 * 1: lampost
	 * 2: smallbox
	 * 3: bigbox
	 * 4: fencepart
	 */
	uint8_t collResponseFlags;
	bool cameraAvoid;
};


#endif
