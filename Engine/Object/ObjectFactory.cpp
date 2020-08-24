#include "pch.h"
#include "ObjectFactory.h"
#include "Components/PhysicsComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/SpriteAnimationComponent.h"

void AZ::objectFactoryImpl::initialize(){
	f_register("GameObject", new creator<gameObject, object>);
	f_register("PhysicsComponent", new creator<physicsComponent, object>);
	f_register("SpriteComponent", new creator<spriteComponent, object>);
	f_register("SpriteAnimationComponent", new creator<spriteAnimationComponent, object>);
}
