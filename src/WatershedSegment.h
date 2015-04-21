class WatershedSegment{
private:
    cv::Mat markers;
public:
    void setMarkers(const cv::Mat &image){
        image.convertTo(markers,CV_32S);
    }

    cv::Mat process(const cv::Mat &image) {

        // Apply watershed
        cv::watershed(image,markers);
        markers.convertTo(markers,CV_8U);
        return markers;
    }
};
