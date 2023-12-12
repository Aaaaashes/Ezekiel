#pragma once
#include <stdlib.h>
#include <inttypes.h>

#include "utils.h"
#include "error.h"

#define PLACEHOLDER_ID 0xca5cadab1efacade

typedef struct EntitySizeDescriptor {
	u32 dataSize;
	u16 EDTlength, componentsLength;
} EntitySizeDescriptor, ESD;

typedef struct EntityDataMember {
	u16 type;
	u32 addressOffset, size;
} EntityDataMember, EDM;


typedef struct ComponentDataMember {
	u16 type;
	u32 addressOffset, size;
} ComponentDataMember, CDM;

typedef struct GlobalComponentDescriptor {
	u32 cdtSize;
	CDM* dataTable;
} GlobalComponentDescriptor, GCD;

typedef struct Component {
	u32 id;
	GCD* GCD;
	void* data;
} Component;


typedef struct Entity {
	u64 id;
	ESD sizeDesc;
	void* data;
	Component* components;
	EDM* dataTable;
} Entity;

typedef struct ECS {
	u32 entityCount, freeIdCount, idCounter;
	u32* entities;
	u32* freeIds;
} ECS;

extern ECS ecs;

static u32 getSizeOfComponent(Component component);
static u32 getSizeOfComponents(u16 componentCount, Component* components);
static u32 getSizeOfEntityComponents(Entity entity);
static u32 getSizeOfEntityData(Entity entity);
static u32 getSizeOfEntity(Entity entity);

Entity* createEntity(u16 componentCount, Component* components, u32 dataEntryCount, EDM dataEntries);
Entity* getEntityById(u32 id);

void addEntity(Entity* entityPtr);

