#include "MultiThreading.h"


MultiThreading::MultiThreading(){

}

MultiThreading::~MultiThreading(){

}

void MultiThreading::LockUnlock(){
	m_lock.lock();
	counter = counter +1;
	//place logic here

	m_lock.unlock();
}

void MultiThreading:: MutualExclusion(){
	while (true){
		P(s);
			//add critical section logic

		V(s);
			//add non-critical logic
		}
	}
}

void MultiThreading::P(SDL_sem s){
	if(s>0)
	{
	s = s-1;
	}
}
void MultiThreading::V(SDL_sem s){
	s = s +1;
}