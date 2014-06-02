// GDI+ helper class

#pragma once

class GdiPlusHelper : public Singleton<GdiPlusHelper>
{
public:
    void init();
    void uninit();

protected:
    GdiPlusHelper() = default;
    ~GdiPlusHelper() = default;

    friend class Singleton<GdiPlusHelper>;

private:
    ULONG_PTR token;
    Gdiplus::GdiplusStartupInput input;
};