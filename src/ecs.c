#include "ecs.h"

ECS ecs;

static u32 getSizeOfGCDData(GCD* gcd) {
	u32 total = 0;
	for(u32 i = 0; i < gcd->cdtLength; i++) {
		total += gcd->dataTable[i].size;
	}
	return total;
}

static u32 getSizeOfComponent(Component component) {
	return getSizeOfGCDData(component.GCD) + 12;
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

Entity* createEntity(u16 componentCount, Component* components, u32 dataEntryCount, EDM* dataEntries) {

	Entity* entity = malloc(sizeof(Entity));

	assertErr(entity, "NON-FATAL::ENTITY::CREATE - Could not alloc space for entity.\n", 0, false);
	if (!entity) {
		return (Entity*)-1;
	}

	entity->components = components;
	entity->dataTable = malloc(10);
	entity->data = malloc(10);
	entity->sizeDesc = (ESD){ 10,1, componentCount };
	entity->id = PLACEHOLDER_ID;


	/* TODO: initialise a default data table with :
		- index in generation
		- parent id
		- time of creation (NOW())
	*/ 

	return entity;
}

u32 addEntity(Entity* entityPtr) {
	ecs.entityCount++;
	u32 newCapacity = sizeof(Entity*) * ecs.entityCount;
	Entity** newEntities = realloc(ecs.entities, newCapacity);


	assertErr(newEntities, "NON-FATAL::ENTITY::ADD - Could not realloc space for entity ids.\n", 0, false);
	if (!newEntities) {
		ecs.entityCount--;
		return PLACEHOLDER_ID;
	}

	ecs.entities = (Entity**)newEntities;


	if (ecs.freeIdCount > 0) {
		entityPtr->id = ecs.freeIds[--ecs.freeIdCount];

		ecs.freeIds = reallocFreeIds(ecs.freeIdCount);
	}
	else {
		entityPtr->id = ecs.idCounter++;
	}
	ecs.entities[entityPtr->id] = entityPtr;

	return entityPtr->id;
}

Entity* getEntityById(u32 id) {
	if (id < ecs.entityCount) {
		return ecs.entities[id];
	}
	return (Entity*)(-1);
}

u32* reallocFreeIds(u32 newSize) {
	u32 newCapacity = sizeof(u32*) * ecs.freeIdCount;
	u32* newFreeIds = malloc(0);
	if (newSize) {
		u32* newFreeIds = realloc(ecs.freeIds, newCapacity);
		assertErr(newFreeIds, "FATAL::ENTITY::DESTROY - Could not realloc space for free ids.\n", 0, true);
	}

	return newFreeIds;
}

void removeEntity(Entity* entityPtr) {
	ecs.entities[entityPtr->id] = 0;
	ecs.entityCount--;

	ecs.freeIdCount++;

	u32* newFreeIds = reallocFreeIds(ecs.freeIdCount);

	ecs.freeIds = newFreeIds;
	ecs.freeIds[ecs.freeIdCount - 1] = entityPtr->id;

	entityPtr->id = PLACEHOLDER_ID;
}

void freeEntity(Entity* entityPtr) {
	if (!entityPtr) {
		return;
	}
	if (entityPtr->data) {
		free(entityPtr->data);
		entityPtr->data = 0;
	}
	if (entityPtr->dataTable){
		free(entityPtr->dataTable);
		entityPtr->dataTable = 0;
	}
}  

Component* createComponent(GCD* gcd) {
	Component* component = malloc(sizeof(Component));

	assertErr(component, "NON-FATAL::COMPONENT::CREATE - Could not alloc space for component.\n", 0, false);
	if (component == NULL) {
		return (Component*) -1;
	}

	component->GCD = gcd;
	component->id = gcd->id;
	component->data = malloc(getSizeOfGCDData(gcd));	

	return component;
}

u32 addComponent(Entity* entity, Component* component) {
	u32 comsSize = ((u64)(entity->sizeDesc.componentsLength + 1) * 
													sizeof(Component));
	Component* newComponents = realloc(entity->components, comsSize);

	assertErr(newComponents, "NON-FATAL::COMPONENT::ADD - Could not realloc entity component space", 0, false);
	if (newComponents == NULL) {
		return -1;
	}
	entity->components = newComponents;

	entity->components[entity->sizeDesc.componentsLength++] = *component;

	return component->id;
}