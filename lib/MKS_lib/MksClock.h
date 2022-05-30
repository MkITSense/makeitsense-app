class MksClock {
    public:
        const int STOPED = 0;
        const int PAUSED = 1;
        const int STARTED = 2;
        
        struct Time {
            int minutes;
            int seconds;
            int hours;
        };
        
        MksClock() {

        }
        
        void start() {
            _state = STARTED;
            _startMilSec = millis();
        }
        
        void stop() { 
            _state = STOPED;
        }
        
        void pause() {
            _state = PAUSED;    
        }
        
        void resume() {
            _state = STARTED;
        }
        
        bool isStoped() {
            if (_state == STOPED) {
                return true;
            }
            
            return false;
        }
        
        bool isStarted() {
            return _state == STARTED;
        }
        
        float getMinutes() {
            if (isStoped() == false) {
                _currentMinutes = millis();
            }
            
            return (_currentMinutes - _startMilSec) / 60000;
        }
        
        float getSeconds() {
            if (isStoped() == false) {
                _currentMinutes = millis();
            }
            
            return (_currentMinutes - _startMilSec) / 1000;
        }
        
        Time getCurrentTime() {
            if (isStoped() == false) {
                _currentTime = millis();
            }
            
            Time time;
            
            long miliseconds = _currentTime - _startMilSec;
            time.seconds = (int)(miliseconds / 1000) % 60;
            time.minutes = (int)((miliseconds / (1000 * 60)) % 60);
            time.hours = (int)((miliseconds / (1000 * 60 * 60)) % 24);

            return time;
        }

        String getCurrentTimeAsString() {
            Time time = getCurrentTime();
            
            return _formatNumber(time.hours) + ":" + _formatNumber(time.minutes) + ":" + _formatNumber(time.seconds);
        }

    private:
        long _startMilSec;
        int _state;
        float _currentTime;
        float _currentMinutes;

        String _formatNumber(int number) {
            char result[2];
            sprintf(result, "%02d", number);
            
            return String(result);
        }
};
