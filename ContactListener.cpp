#include "ContactListener.h"


ContactListener* ContactListener::instance;
b2World* ContactListener::mWorld;

ContactListener* ContactListener::getListener(){
	if(instance == NULL){
		instance = new ContactListener();
	}
	return instance;
}

ContactListener::ContactListener(void){
}


ContactListener::~ContactListener(void){
}
void ContactListener::setWorld(b2World* world){
	mWorld=world;
}
void ContactListener::BeginContact(b2Contact* contact){
	//0 = player
	//-1 = enemy
	//-2 = pick up
	//-3 = bullet
	//-4 = Goal
	//-5 = 
	//-6 = 
	//-7 = 
	//-8 = 
	//------------------------------
	//-100 = to be destroyed/damaged
	//-200 = dynamic event
	//-300 = victory


	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();
	b2Body* body1 = fixtureA->GetBody();
	b2Body* body2 = fixtureB->GetBody();

	int i1 = (int)body1->GetUserData();
	int i2 = (int)body2->GetUserData();

#pragma region PLAYER-PIRATE
 	if(i1 == -1){//body1 is the enemy
		if(i2 == 0)
		{
			body2->SetUserData((void*)-100);//player damaged 
		}
	}
	if(i1 == 0){//body1 is the player
		if(i2 == -1)
		{
			body1->SetUserData((void*)-100);//player damaged
		}
	}
#pragma endregion


#pragma region PLAYER-PICKUP
	if(i1 == -2){//if body1 is the pickup
		if(i2 == 0){                     
			body1->SetUserData((void*)-100);//Collect the pickup
		}
	}
	if(i1 == 0){
		if(i2 == -2){//if body2 is the pickup                     
			body2->SetUserData((void*)-100);//Collect the pickup	
		}
	}
#pragma endregion

#pragma region BULLET-ENEMY
	if(i1 == -3){ //If body1 is the bullet
		if(i2 == -1){          
			body1->SetUserData((void*)-100);
			body2->SetUserData((void*)-100);
		}
	}
	if(i1 == -1){//If body1 is the enemy
		if(i2 == -3){      
			body1->SetUserData((void*)-100);
			body2->SetUserData((void*)-100);
		}
	}
#pragma endregion

#pragma region BULLET-PLAYER
	if(i1 == -3){
		if(i2 == 0){          
			body1->SetUserData((void*)-100);//Player takes damage
			body2->SetUserData((void*)-100);//destroy the bullet
		}
	}
	if(i1 == 0){
		if(i2 == -3){      
			body1->SetUserData((void*)-100);//destroy the bullet
			body2->SetUserData((void*)-100);//Player takes damage
		}
	}
#pragma endregion

#pragma region PLAYER-GOAL
	if(i1 == -4){
		if(i2 == 0){          
			body1->SetUserData((void*)-300);//Player wins
		}
	}
	if(i1 == 0){
		if(i2 == -4){      
			body1->SetUserData((void*)-300);//Player wins
		}
	}
#pragma endregion
}

void ContactListener::EndContact(b2Contact* contact){

}