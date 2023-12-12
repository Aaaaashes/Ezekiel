#include "ecs.h"

ECS ecs;

static u32 getSizeOfComponent(Component component) {
	u32 total = 12;
	for (int i = 0; i < (int)(component.GCD->cdtSize / sizeof(CDM)); i++) {
		total += component.GCD->dataTable[i].size;
	}
	return total;
}

static u32 getSizeOfComponents(u16 componentCount, Component* components) {
	u32 total = 0;
	for (int i = 0; i < (int)(componentCount); i++) {
		total += getSizeOfComponent(components[i]);
	}
	return total;
}

static u32 getSizeOfEntityComponents(Entity entity) {
	u32 total = 0;
	for (int i = 0; i < (int)(entity.sizeDesc.componentsLength); i++) {
		total += getSizeOfComponent(entity.components[i]);
	}
	return total;
}

static u32 getSizeOfEntityData(Entity entity) {
	u32 total = 12;
	for (int i = 0; i < (int)(entity.sizeDesc.EDTlength); i++) {
		total += entity.dataTable->size;
	}
}

static u32 getSizeOfEntity(Entity entity) {
	u32 total = sizeof(u32) +
		sizeof(ESD) +
		entity.sizeDesc.dataSize +
		(entity.sizeDesc.EDTlength * sizeof(EDM)) +
		getSizeOfEntityComponents(entity);
	return total;
}

Entity* createEntity(u16 componentCount, Component* components, u32 dataEntryCount, EDM dataEntries) {

	Entity* entity = malloc(sizeof(Entity));

	entity->components = components;
	entity->sizeDesc = (ESD){ 0,0, componentCount };
	entity->id = PLACEHOLDER_ID;


	/* TODO: initialise a default data table with :
		- index in generation
		- parent id
		- time of creation (NOW())
	*/ 

	return entity;
}

void addEntity(Entity* entityPtr) {
	u32 newCapacity = sizeof(Entity*) * ecs.entityCount;
	u32* newEntities = realloc(ecs.entities, newCapacity);

	assertErr(newEntities, "Failed to allocate memory for entities.\n", 0);

	ecs.entities = newEntities;

	entityPtr->id = ecs.idCounter++;
	ecs.entities[ecs.entityCount++] = entityPtr;
}

Entity* getEntityById(u32 id) {
	if (id < ecs.entityCount) {
		return ecs.entities[id];
	}
	return -1;
}