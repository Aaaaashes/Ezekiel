#pragma once
#include <stdlib.h>
#include <inttypes.h>

#include "utils.h"
#include "error.h"

#define PLACEHOLDER_ID 0xc0a1e5ce

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
	u32 cdtLength;
	u32 id;
	CDM* dataTable;
} GlobalComponentDescriptor, GCD;

typedef struct Component {
	u32 id;
	GCD* GCD;
	void* data;
} Component;


typedef struct Entity {
	u32 id;
	ESD sizeDesc;
	void* data;
	Component* components;
	EDM* dataTable;
} Entity;

typedef struct ECS {
	u32 entityCount, freeIdCount, idCounter;
	Entity** entities;
	u32* freeIds;
} ECS;

extern ECS ecs;

static u32 getSizeOfGCDData(GCD* gcd);
static u32 getSizeOfComponents(u16 componentCount, Component* components);
static u32 getSizeOfEntityComponents(Entity entity);
static u32 getSizeOfEntityData(Entity entity);
static u32 getSizeOfEntity(Entity entity);

static u32 getSizeOfComponent(Component component);

Entity* createEntity(u16 componentCount, Component* components, u32 dataEntryCount, EDM* dataEntries);
Entity* getEntityById(u32 id);

u32* reallocFreeIds(u32 newSize);

u32 addEntity(Entity* entityPtr);

void removeEntity(Entity* entityPtr);

void freeEntity(Entity* entityPtr);

Component* createComponent(GCD* gcd);

u32 addComponent(Entity* entity, Component* component);

