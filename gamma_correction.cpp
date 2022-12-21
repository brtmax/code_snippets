void GammaCorrection(Mat& src, Mat& dst, float gamma) {
    unsigned char lut[256];
    for (int i = 0; i < 256; i++) {
        lut[i] = saturate_cast<uchar>(pow((float)(i / 255.0), gamma) * 255.0f)
    }

    dst = src.clone();

    const int channels = dst.channels();
    switch(channels)
    {
        case 1:
        {
            MatIterator_<uchar> it, end;
            for (it = dst.begin<uchar>(), end = dst.end<uchar>(); it != end; it++)
                *it = lut[(*it)];
            break;
        }
        case 2: 
        {
            MatIterator_<Vec3b> it, end;
            for (it = dst.begin<Vec3b>(), end = dst.end<Vec3b>(); it != end; it++) {
                (*it)[0] = lut[((*it)[0])];
                (*it)[1] = lut[((*it)[1])];
                (*it)[2] = lut[((*it)[2])];
            }
        }
    }
}