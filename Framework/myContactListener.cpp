#include "myContactListener.h"
#include "inputhandler.h"
#include "logmanager.h"
#include <string>
#include "FixtureType.h"
#include "Box2D/Box2D.h"
#include <set>
#include "entity.h"


//static members 

std::set<b2Fixture*> myContactListener::fixturesUnderfoot;



myContactListener::myContactListener()	
{
}

myContactListener::~myContactListener()
{
}

void 
myContactListener::BeginContact(b2Contact* contact) {
	//check if fixture A was the foot sensor

	void* fixtureUserDataA = contact->GetFixtureA()->GetBody()->GetUserData();
	void* fixtureUserDataB = contact->GetFixtureB()->GetBody()->GetUserData();

	if (fixtureUserDataA && fixtureUserDataB)
	{
		Entity* m_entity_a = static_cast<Entity*>(fixtureUserDataA);
		Entity* m_entity_b = static_cast<Entity*>(fixtureUserDataB);

		m_entity_a->BeginContact(m_entity_b);
		m_entity_b->BeginContact(m_entity_a);
	}
	if ((int)fixtureUserDataA == FixtureType::PLAYER)
	{
		fixturesUnderfoot.insert(contact->GetFixtureB());//A is foot so B is ground
	}
	
	//check if fixture B was the foot sensor
	fixtureUserDataB = contact->GetFixtureB()->GetUserData();
	if ((int)fixtureUserDataB == FixtureType::PLAYER)
	{
		fixturesUnderfoot.insert(contact->GetFixtureA()); //B is foot so A is ground
	}		
}

void 
myContactListener::EndContact(b2Contact* contact) {
	//check if fixture A was the foot sensor
	void* fixtureUserData = contact->GetFixtureA()->GetUserData();
	if ((int)fixtureUserData == FixtureType::PLAYER)
	{
		fixturesUnderfoot.erase(contact->GetFixtureB());//A is foot so B is ground

	}
		
	//check if fixture B was the foot sensor
	fixtureUserData = contact->GetFixtureB()->GetUserData();
	if ((int)fixtureUserData == FixtureType::PLAYER)
	{
		fixturesUnderfoot.erase(contact->GetFixtureA());//B is foot so A is ground
		

	}
	
}

bool 
myContactListener::CanJumpNow()
{
	std::set<b2Fixture*>::iterator it = fixturesUnderfoot.begin();
	std::set<b2Fixture*>::iterator end = fixturesUnderfoot.end();
	while (it != end)
	{
		b2Fixture* fixture = *it;
		int userDataTag = (int)fixture->GetUserData();
		if (userDataTag == 0 || userDataTag == FixtureType::PLATFORM) //platform  or static ground
			return true;
		++it;
	}
	return false;
}