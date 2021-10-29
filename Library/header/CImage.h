#pragma once
#include <string>
#include <complex>
#include <vector>

#include "CColor.h"

namespace cimg_library
{
    template <class T> class CImg;
    class CImgDisplay;
}

namespace bvme
{
    typedef std::complex<double> Complex;

    class CImage
    {
    public:
        CImage(int _height, int _width, bool _bGreyScale);
        CImage(std::string& _fileLocation);
        CImage(const char* const _fileLocation);
        ~CImage();
        
        void showImage(const char* const _title = 0);
        
        int getWidth() const;
        int getHeight() const;
        
        bool isMonochrom() const;
        bool isRgb() const;
        bool isHsi() const;
        
        bvme::CImage& toHsi();
        bvme::CImage& toRgb();

        bvme::CColor& getPointValue(int _x, int _y);
        void setPointValue(int _x, int _y, bvme::CColor& _point);
        
        bvme::CImage& getGreyscaleImage();
        bvme::CImage& sobelFilter(bool _filterX, bool _filterY);

        bvme::CImage& FourierTransformation(bool _inverse);
        Complex& getComplexPointValue(int _x, int _y);
        void setComplexPointValue(int _x, int _y, Complex& _point);

        void save(std::string& _fileLocation);
        void save(const char* const _fileLocation);

    private:
        CImage(int _width, int _height, bool _bComplexImage, bool _bGreyScale);
        void FastFourier1D(std::vector<Complex>& _input);
        void InverseFastFourier1D(std::vector<Complex>& _input);

    private:
        cimg_library::CImg<double>* m_image = nullptr;
        std::vector<std::vector<Complex>>* m_complexImage = nullptr;
        cimg_library::CImgDisplay* m_display = nullptr; 
        bool m_bMonochrom = false;
        bool m_bComplex = false;
        bool m_bHsi = false;
    };
}