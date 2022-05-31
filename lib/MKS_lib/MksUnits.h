
class Temperature {
    public:
        void setCelsius(float celsius) {
            _celsius = celsius;
        }

        float getCelsius() {
            return _celsius;
        }

        String getCelsiusAsString() {
            return String(_celsius) + "ºC";
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
        }

        int getMaxVolumeM3() {
            return _getVolumeM3(_heightCm);
        }

        int getCurrentVolumeM3() {
            return _getVolumeM3(_currentLevelCm);
        } 

        int getMaxVolumeLts() {
            return _getVolumeLts(_heightCm);
        }

        int getCurrentVolumeLts() {
            return _getVolumeLts(_currentLevelCm);
        }

        int getFillPercentage() {
            return (getCurrentVolumeLts() / getMaxVolumeLts()) * 100;
        }

        String getCurrentVolumeLtsAsString() {
            return String(getCurrentVolumeLts()) + "Lts";
        }

        String getFillPercentageAsString() {
            return String(getFillPercentage()) + "%";
        }

    private:
        int _widthCm;
        int _lengthCm;
        int _heightCm;
        int _currentLevelCm;
        int _sensorZeroCm;
        int _sensorReadingCm;

        int _getVolumeM3(int height) {
            return (_widthCm /100) * (_lengthCm/100) * (_heightCm/100);
        }

        int _getVolumeLts(int height) {
            return _getVolumeM3(height) * 1000;
        }
};

