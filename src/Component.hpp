#pragma once
#include "Utility\Includes.hpp"

class Component {
public:
	typedef std::shared_ptr<Component> Ptr;
	typedef std::unique_ptr<Component> UPtr;

	Component(std::shared_ptr<class Actor> owner, i32 updateOrder = 100);
	virtual ~Component();

	virtual void Update();
	i32 UpdateOrder() const { return mUpdateOrder; };

private:
	std::shared_ptr<class Actor> mOwner;
	i32 mUpdateOrder;
};