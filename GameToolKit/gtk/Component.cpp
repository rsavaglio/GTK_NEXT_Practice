#include "Component.h"


namespace gtk {

	Entity::Entity(const unsigned int& id, Entity* const parent) : _id(id), _Parent(parent), _Transform(), _Active(true) {}
	CompGroup::CompGroup(const unsigned int& id) : _id(id) {}

}