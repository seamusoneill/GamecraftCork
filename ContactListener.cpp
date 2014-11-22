#include "ContactListener.h"
#include <iostream>

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
	//-8 = island
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

#pragma region PLAYER-ISLAND
 	if(i1 == 0 || i1 == -8){
		if(i2 == 0)
		{
			cout<<"You Won"<<endl;
		}
	}
	 if(i2 == 0 || i2 == -8){
		if(i1 == 0)
		{
			cout<<"You Won"<<endl;
		}
	}


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
<<<<<<< HEAD
=======

	/* Spare Contacts */
#pragma region PLAYER-CONVERYOR
	if(i1 == -8){
		if(i2 == 0){          
			body2->SetUserData((void*)-300);
		}
	}
#pragma endregion


#pragma region BOMB-LIFTPLATFORM
	if(i1 == -5 || i1 == -200){
		if(i2 == -1){          
			body2->SetUserData((void*)-100);
		}
	}
	if(i1 == -1){
		if(i2 == -5 || i2 == -200){      
			body1->SetUserData((void*)-100);
		}
	}
#pragma endregion

#pragma region BOMBANDBARRIER-FALLINGPLATFORM
	if(i1 == -7){
		if(i2 == -1 || i2 == -3){
				body1->SetUserData((void*)-300); //hold the platform
				body2->SetUserData((void*)-100); //Destroy the bomb
		}
	}
	if(i1 == -1 || i1 == -3){
		if(i2 == -7){
			body1->SetUserData((void*)-100); //Destroy the bomb
			body2->SetUserData((void*)-300); //hold the platform
		}
	}
#pragma endregion
>>>>>>> af72ee736753cece785d9ed971070abb70474dd9
}

//#pragma region PLAYER-FALLINGPLATFORM
// 	if(i1 == -7 || i1 == -300){
//		if(i2 == 0)
//		{
//			body1->SetUserData((void*)-200);//make the platform drop
//		}
//	}
//	if(i1 == 0){
//		if(i2 == -7 || i2 == -300)
//		{
//			body2->SetUserData((void*)-200);//make the platform drop
//		}
//	}
//#pragma endregion
//
//#pragma region BOMBANDBARRIER-FALLINGPLATFORM
//	if(i1 == -7){
//		if(i2 == -1 || i2 == -3){
//				body1->SetUserData((void*)-300); //hold the platform
//				body2->SetUserData((void*)-100); //Destroy the bomb
//		}
//	}
//	if(i1 == -1 || i1 == -3){
//		if(i2 == -7){
//			body1->SetUserData((void*)-100); //Destroy the bomb
//			body2->SetUserData((void*)-300); //hold the platform
//		}
//	}
//#pragma endregion
//#
//#pragma region BOMB-PLATFORM
//	if(i1 == -2){
//		if(i2 == -1){                     
//			body2->SetUserData((void*)-100);
//		}
//	}
//	if(i1 == -1){
//		if(i2 == -2){                     
//			body1->SetUserData((void*)-100);	
//		}
//	}
//#pragma endregion
//
//#pragma region BOMB-BARRIERPLATFORM
//	if(i1 == -3){
//		if(i2 == -1){          
//			body1->SetUserData((void*)-100);
//			body2->SetUserData((void*)-100);
//		}
//	}
//	if(i1 == -1){
//		if(i2 == -3){      
//			body1->SetUserData((void*)-100);
//			body1->SetUserData((void*)-100);
//		}
//	}
//#pragma endregion
//
//#pragma region BOMB-LIFTJAMMER
//	if(i1 == -4){
//		if(i2 == -1){          
//			body1->SetUserData((void*)-100);
//			body2->SetUserData((void*)-100);
//		}
//	}
//	if(i1 == -1){
//		if(i2 == -4){      
//			body1->SetUserData((void*)-100);
//			body2->SetUserData((void*)-100);
//		}
//	}
//#pragma endregion
//
//#pragma region PLAYER-LIFTPLATFORM
//	if(i1 == -5){
//		if(i2 == 0){          
//			body1->SetUserData((void*)-200);
//		}
//	}
//	if(i1 == 0){
//		if(i2 == -5){      
//			body1->SetUserData((void*)-200);
//		}
//	}
//#pragma endregion
//
//#pragma region PLAYER-CONVERYOR
//	if(i1 == -8){
//		if(i2 == 0){          
//			body2->SetUserData((void*)-300);
//		}
//	}
//	if(i1 == 0){
//		if(i2 == -8){      
//			body1->SetUserData((void*)-300);
//		}
//	}
//#pragma endregion
//
//#pragma region BOMB-LIFTPLATFORM
//	if(i1 == -5 || i1 == -200){
//		if(i2 == -1){          
//			body2->SetUserData((void*)-100);
//		}
//	}
//	if(i1 == -1){
//		if(i2 == -5 || i2 == -200){      
//			body1->SetUserData((void*)-100);
//		}
//	}
//#pragma endregion
//}

void ContactListener::EndContact(b2Contact* contact){

}