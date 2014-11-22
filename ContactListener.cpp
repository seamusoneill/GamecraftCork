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
	//-1 = 
	//-2 = 
	//-3 = island
	//-4 = 
	//-5 = 
	//-6 = 
	//-7 = 
	//-8 = 
	//------------------------------
	//-100 = to be destroyed
	//-200 = dynamic event
	//-300 = conveyor belt

	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();
	b2Body* body1 = fixtureA->GetBody();
	b2Body* body2 = fixtureB->GetBody();

	int i1 = (int)body1->GetUserData();
	int i2 = (int)body2->GetUserData();

#pragma region PLAYER-ISLAND
 	if(i1 == 0 || i1 == -3){
		if(i2 == 0)
		{
			cout<<"You Won"<<endl;
		}
	}

	if(i1 == 0){
		if(i2 == -3|| i2 == 0)
		{
			cout<<"You Won"<<endl;
		}
	}
#pragma endregion

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