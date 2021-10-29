#pragma once
#include <string>

namespace bvme
{
    class CColor
    {
        public:
            CColor(int _greyValue);
            CColor(int _redValue, int _greenValue, int _blueValue);
            CColor(double _hueValue, double _saturationValue, double _intensityValue, bool _bHsi);
            ~CColor();
            bool isMonochrom() const;
            bool isRgb() const;
            bool isHsi() const;
            
            void setGrey(int _greyValue);
            int getGrey() const;
            
            int getRed() const;
            int getGreen() const;
            int getBlue() const;
            void setRed(int _redValue);
            void setGreen(int _greenValue);
            void setBlue(int _blueValue);
           
            double getHue() const;
            double getSaturation() const;
            double getIntensity() const;
            void setHue(double _hueValue);
            void setSaturation(double _saturationValue);
            void setIntensity(double _intensityValue);
        private:
            int* m_prgbChannels = nullptr;
            double* m_phsiChannels = nullptr;
            bool m_bMonochrom = false;
            bool m_bHsi = false;
    };

}
