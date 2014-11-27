#ifndef _MULTITHREADING_H_
#define _MULTITHREADING_H_

#include "SDL_dev/SDL2-2.0.3/include/SDL.h"
#include "SDL_dev/SDL2_image-2.0.0/include/SDL_image.h"
#include "SDL_dev/SDL2-2.0.3/include/SDL_thread.h"
#include <SDL_mutex.h>
#include <string>

	/**I do not know how to use any of the SDL threading, and Lazyfoo has out right said that we should not be doing this if we are not familiar with Threading, 
	I have not been able to complete a single lab on concurrency, and feel completely unprepared for this project, I don't know how to implement threating,
	I have no examples of how to do it correctly, and have been asked to place it into a project that honestly doesn't have room or need for it.
	I've attempted to look online for uses or ways of implementing threading and have been left confused and overwhelmed. 
	As I type this I'm on the verge of a panic attack, due to the combination of pressure due to this project's 20% weighting, the projects limited deadline and frustration
	and my own lack of understanding of this subject, I have asked for extra help and been told that students can't be prioritised, which honestly angers me greatly,
	since students that are falling behind SHOULD be prioritised, since they are the ones that need help.
	I’ve already come to terms with the fact I have failed this project, my main worry now is that I have no way of making the lost marks back, 
	even if I’m given a similar project to do, the outcome will be the same, due to the fact that bluntly I have no idea how to do the most basic of exercise in this subject.
	I want to learn, I want to pass this subject, but at the moment, with my current rate of progress, that’s impossible, I need help badly,
	but if I have no way of getting that aid, and if that’s the case what’s the point in staying in this course? 
	What is the point in coming to a class and being told to teach myself off the internet? This is not what I paid €2500 to do this year.

	*/
class MultiThreading

{
public:
	MultiThreading();
	~MultiThreading();
	void LockUnlock();
	void MutualExclusion();

private:
	//for lock/unlock
	SDL_mutex m_lock;

	static int counter = 0;

	//for mutual exclution
	SDL_sem s;
	SDL_semaphore m_mutex= 1;
	bool bool_lock = false;

	void P(SDL_sem s);
	void V(SDL_sem s);
};


#endif