
class Timer {
	
	public:
		Timer(void);
		Timer(int timeToWait);
		bool isTimeElapsed(void);
		void start(int timeToWait);
	protected:
		time_t startTime;
		int secondsToWait;
};

Timer::Timer(void) {
	
	startTime = 0;
	secondsToWait = 0;
}

Timer::Timer(int secondsToWait) {
	start(secondsToWait);
}

bool Timer::isTimeElapsed(void) {
	
	time_t currentTime = time(NULL);
	if(currentTime - startTime < secondsToWait) return false;
	return true;
}

void Timer::start(int secondsToWait) {
	
	startTime = time(NULL);
	this->secondsToWait = secondsToWait;
}
