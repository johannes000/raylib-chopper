#include "Actor.hpp"
#include "Component.hpp"

Actor::~Actor() {
	mComponents.clear();
}

void Actor::Update() {
}

void Actor::UpdateActor() {
}

Component *Actor::AddComponent(std::unique_ptr<Component> component) {
	Component *rawPtr = component.get();

	auto it = std::lower_bound(mComponents.begin(), mComponents.end(), component,
							   [](const std::unique_ptr<Component> &a, const std::unique_ptr<Component> &b) {
								   return a->UpdateOrder() < b->UpdateOrder();
							   });
	mComponents.insert(it, std::move(component));
	return rawPtr;
}

void Actor::RemoveComponent(Component *component) {
	if (mComponents.size() == 0)
		return;
	auto it = std::find_if(mComponents.begin(), mComponents.end(),
						   [component](const std::unique_ptr<Component> &ptr) {
							   return ptr.get() == component;
						   });
	if (it != mComponents.end())
		mComponents.erase(it);
}

void Actor::UpdateComponents() {
	for (auto &component : mComponents) {
		component->Update();
	}
}

Actor::Actor(std::shared_ptr<class Game> game) : mState(State::Active),
												 mPosition(raylib::Vector2().Zero()),
												 mScale(1.f),
												 mRotation(0.f),
												 mGame(game) {
}
