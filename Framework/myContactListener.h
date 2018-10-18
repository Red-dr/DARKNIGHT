#ifndef __MYCONTACTLISTENER_H__
#define __MYCONTACTLISTENER_H__



#include <Box2D/Box2D.h>
#include "FixtureType.h"
#include <set>

class myContactListener : public b2ContactListener
{
public:
	myContactListener();
	~myContactListener();
	void EndContact(b2Contact* contact);
	void BeginContact(b2Contact* contact);
	static std::set<b2Fixture*> fixturesUnderfoot;	
	static bool CanJumpNow();
	
private:
	
};

#endif // !__MAYCONTACTLISTENER_H__