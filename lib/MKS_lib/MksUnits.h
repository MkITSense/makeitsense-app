
class Temperature {
    public:
        void setCelsius(float celsius) {
            _celsius = celsius;
        }

        float getCelsius() {
            return _celsius;
        }

        String getCelsiusAsString() {
            return String(_celsius) + "C";
        }

    private:
        float _celsius;

};

class Distance {
    public:
        void setCentimeters(int centimeters) {
            _centimeters = centimeters;
        }

        int getCentimeters() {
            return _centimeters;
        }

        String getCentimetersAsString() {
            return String(_centimeters) + "cm";
        }

    private:
        int _centimeters;
};

class Cube {
    public:
        Cube(int widthCm, int lengthCm, int heightCm, int sensorZeroCm) {
            _widthCm = widthCm;
            _lengthCm = lengthCm;
            _heightCm = heightCm;
            _sensorZeroCm = sensorZeroCm;
            _currentLevelCm = 0;
        }

        void setCurrentLevelCm(int sensorReadingCm) {
            _currentLevelCm = _heightCm - (sensorReadingCm - _sensorZeroCm);
            Serial.println("Current Level: " + String(_currentLevelCm));
        }

        int getMaxVolumeM3() {
                             Serial.println("Max: " + String(_getVolumeM3(_heightCm)) + " : " + String(_heightCm));
            return _getVolumeM3(_heightCm);
        }

        int getCurrentVolumeM3() {
                 Serial.println("Current: " + String(_getVolumeM3(_currentLevelCm)) +  " : " + String(_currentLevelCm));
       
            return _getVolumeM3(_currentLevelCm);
        } 

        float getMaxVolumeLts() {
            return _getVolumeLts(_heightCm);
        }

        float getCurrentVolumeLts() {
            return _getVolumeLts(_currentLevelCm);
        }

        float getFillPercentage() {
       
            return (getCurrentVolumeLts() / getMaxVolumeLts()) * 100;
        }

        String getCurrentVolumeLtsAsString() {
            return String(getCurrentVolumeLts()) + "Lts";
        }

        String getFillPercentageAsString() {
            return String((int)getFillPercentage()) + "%";
        }

    private:
        int _widthCm;
        int _lengthCm;
        int _heightCm;
        int _currentLevelCm;
        int _sensorZeroCm;
        int _sensorReadingCm;

        float _getVolumeM3(int height) {
      
            return (_widthCm /100.0) * (_lengthCm/100.0) * (height/100.0);
        }

        float _getVolumeLts(int height) {
            return _getVolumeM3(height) * 1000.0;
        }
};

