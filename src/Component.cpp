#include "Component.hpp"

Component::~Component() {
	mOwner = nullptr;
}

void Component::Update() {
}

Component::Component(std::shared_ptr<class Actor> owner, i32 updateOrder) : mOwner(owner), mUpdateOrder(updateOrder) {
}
