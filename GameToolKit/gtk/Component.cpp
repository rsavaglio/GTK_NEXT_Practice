#include "Component.h"


namespace gtk {

	Entity::Entity(const unsigned int& id) : _id(id), _Parent(nullptr) {}

	CompGroup::CompGroup(const unsigned int& id) : _id(id) {}

}